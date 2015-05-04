#include <assert.h>
#include <cxxabi.h>
#include <dirent.h>
#include <execinfo.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "gstacktrace.h"

// ----------------------------------------------------------------------------
// GStracTrace
// ----------------------------------------------------------------------------
GStackTrace::GStackTrace() {
  prev_handler_ = 0;
  setOutput(stdout);
  setSkipFrames(3);
  setMaxFrames(10);
  setSignal(SIGUSR1);
}

GStackTrace::~GStackTrace() {
  unsetSignal();
}

void GStackTrace::setOutput(FILE* output) {
  output_ = output;
}

void GStackTrace::setSkipFrames(int skipFrames) {
  skipFrames_ = skipFrames;
}

void GStackTrace::setMaxFrames(int maxFrames) {
  maxFrames_ = maxFrames;
}

void GStackTrace::setSignal(int signum) {
  unsetSignal();
  prev_handler_ = signal(signum, sighandler);
  if (prev_handler_ == SIG_ERR) {
    fprintf(stderr, "Calling signal(%d) return SIG_ERR err=%s\n", signum, strerror(errno));
    prev_handler_ = 0;
  }
  signum_ = signum;
}

void GStackTrace::unsetSignal() {
  if (prev_handler_ != 0) {
    __sighandler_t res = signal(signum_, prev_handler_);
    assert(res == sighandler);
    prev_handler_ = 0;
  }
}

void GStackTrace::dump(){
  DIR *dir;

  if ((dir = opendir ("/proc/self/task")) == NULL) {
    fprintf(stderr, "opendir return NULL err=%s\n", strerror(errno));
    return;
  }

  pid_t tgid = getpid();
  struct dirent *ent;
  while ((ent = readdir(dir)) != NULL) {
    std::string s = ent->d_name;
    if (s == "." || s == "..") continue;
    pid_t tid = std::stoi(s);
    long int res = syscall(SYS_tgkill, tgid, tid, signum_); // tgkill(tgid, tid, signum_);
    if (res != 0) {
      fprintf(stderr, "Error in call kill err=%s\n", strerror(errno));
    }
  }
  closedir(dir);
}

void GStackTrace::printStacktrace() {
  mutex_.lock();

  fprintf(output_, "******** stack trace ******** (%ld)\n", syscall(SYS_gettid));

  // storage array for stack trace address data
  void* addrlist[maxFrames_ + 1];

  // retrieve current stack addresses
  int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));

  if (addrlen == 0) {
    fprintf(output_, "  <empty, possibly corrupt>\n");
    mutex_.unlock();
    return;
  }

  // resolve addresses into strings containing "filename(function+address)",
  // this array must be free()-ed
  char** symbollist = backtrace_symbols(addrlist, addrlen);

  // allocate string which will be filled with the demangled function name
  size_t funcnamesize = 256;
  char* funcname = (char*)malloc(funcnamesize);

  // iterate over the returned symbol lines. skip the first, it is the
  // address of this function.
  for (int i = skipFrames_; i < addrlen; i++) {
    char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

    // find parentheses and +address offset surrounding the mangled name:
    // ./module(function+0x15c) [0x8048a6d]
    for (char *p = symbollist[i]; *p; ++p) {
      if (*p == '(')
        begin_name = p;
      else if (*p == '+')
        begin_offset = p;
      else if (*p == ')' && begin_offset) {
        end_offset = p;
        break;
      }
    }

    if (begin_name && begin_offset && end_offset && begin_name < begin_offset) {
      *begin_name++ = '\0';
      *begin_offset++ = '\0';
      *end_offset = '\0';

      // mangled name is now in [begin_name, begin_offset) and caller
      // offset in [begin_offset, end_offset). now apply
      // __cxa_demangle():

      int status;
      char* ret = abi::__cxa_demangle(begin_name,
      funcname, &funcnamesize, &status);
      if (status == 0) {
        funcname = ret; // use possibly realloc()-ed string
        fprintf(output_, "  %s : %s+%s\n",
        symbollist[i], funcname, begin_offset);
      }
      else {
        // demangling failed. Output function name as a C function with
        // no arguments.
        fprintf(output_, "  %s : %s()+%s\n",
        symbollist[i], begin_name, begin_offset);
      }
    }
    else {
      // couldn't parse the line? print the whole line.
      fprintf(output_, "  %s\n", symbollist[i]);
    }
  }

  free(funcname);
  free(symbollist);

  mutex_.unlock();
}

void GStackTrace::sighandler(int signum) {
  if (signum == GStackTrace::instance().signum_)
    GStackTrace::instance().printStacktrace();
}

GStackTrace& GStackTrace::instance() {
  static GStackTrace _instance;
  return _instance;
}
