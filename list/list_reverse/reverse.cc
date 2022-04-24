#include <iostream>

struct ListNode
{
  ListNode() : val(0), next(nullptr) {}
  ListNode(int val) : val(val), next(nullptr) {}

  int val;
  ListNode* next;
};

ListNode* ListReverse(ListNode* head) {
  ListNode* prev = nullptr;
  ListNode* cur = head;

  if (head == nullptr || head->next == nullptr) {
    return head;
  }

  while(cur != nullptr) {
    ListNode* tmp = cur->next;
    cur->next = prev;
    prev = cur;
    cur = tmp;
  }
  return prev;
}

int main() {
  ListNode ln1(1);
  ListNode ln2(2);
  ListNode ln3(3);

  ln1.next = &ln2;
  ln2.next = &ln3;

  ListNode* p = &ln1;
  while (p != nullptr) {
    std::cout << p->val << std::endl;
    p = p->next;
  }

  p = ListReverse(&ln1);

  while (p != nullptr) {
    std::cout << p->val << std::endl;
    p = p->next;
  }

  return 0;
}