#include "gasynctcpsession.h"

// ----------------------------------------------------------------------------
// GAsyncTcpSession
// ----------------------------------------------------------------------------
GAsyncTcpSession::~GAsyncTcpSession() {
  close();
}

bool GAsyncTcpSession::open() {
  return GTcpSession::open();
}

bool GAsyncTcpSession::close() {
  bool res = GTcpSession::close();
  if (eventSock_ != nullptr) {
    eventSock_->del();
    delete eventSock_;
    eventSock_ = nullptr;
  }
  return res;
}

void GAsyncTcpSession::assignEventBase(
  GEventBase* eventBase,
  event_callback_fn callback,
  void* arg,
  GEvent::Options options) {
  if (eventSock_ != nullptr) {
    eventSock_->del();
    delete eventSock_;
  }
  if (arg == nullptr) arg = this;
  eventSock_ = new GEventSock(eventBase, sock_, callback, arg, options);
  eventSock_->add();
}
