#include <iostream>
#include <GTimeDiffChrono>

struct Node {
  Node(int value = 0) { this->value = value; }
  struct Node* next;
  int value;
};

Node* makeNode() {
  Node* res = new Node;
  Node* node = res;
  for (int i = 0; i < 10; i++) {
    Node* next = new Node;
    node->next = next;
    node = next;
  }
  return res;
}

#define foo0(node) { node->value = 0; }

#define foo1(node) { node->next->value = 0; }

#define foo2(node) { node->next->next->value = 0; }

#define foo3(node) { node->next->next->next->value = 0; }

#define foo4(node) { node->next->next->next->next->value = 0; }

#define foo5(node) { node->next->next->next->next->next->value = 0; }

#define foo6(node) { node->next->next->next->next->next->next->value = 0; }

#define foo7(node) { node->next->next->next->next->next->next->next->value = 0; }

#define foo8(node) { node->next->next->next->next->next->next->next->next->value = 0; }

static const int LOOP_CNT = 10000000;

int main() {
  Node* node = makeNode();
  GTimeDiffChrono td;

  Node node_;
  {
    td.check(9);
    for (int i = LOOP_CNT; i > 0; --i)
      node_.value = 0;
  }

  td.check(10);
  for (int i = LOOP_CNT; i > 0; --i)
    foo0(node);

  td.check(11);
  for (int i = LOOP_CNT; i > 0; --i)
    foo1(node);

  td.check(12);
  for (int i = LOOP_CNT; i > 0; --i)
    foo2(node);

  td.check(13);
  for (int i = LOOP_CNT; i > 0; --i)
    foo3(node);

  td.check(14);
  for (int i = LOOP_CNT; i > 0; --i)
    foo4(node);

  td.check(15);
  for (int i = LOOP_CNT; i > 0; --i)
    foo5(node);

  td.check(16);
  for (int i = LOOP_CNT; i > 0; --i)
    foo6(node);

  td.check(17);
  for (int i = LOOP_CNT; i > 0; --i)
    foo7(node);

  td.check(18);
  for (int i = LOOP_CNT; i > 0; --i)
    foo8(node);

  td.check(19);
  for (int i = LOOP_CNT; i > 0; --i)
    foo0(node);

  td.check(-1);
  td.report();
}

