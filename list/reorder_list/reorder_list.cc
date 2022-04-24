#include<vector>

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

void ReorderList1(ListNode* head) {
  std::vector<ListNode*> result;
  ListNode* p = head;
  while(p != nullptr) {
    result.push_back(p);
    p = p->next;
  }

  int i = 0;
  int j = result.size() -1;
  while (i < j) {
    result[i]->next = result[j];
    i++;
    if (i == j) {
      break;
    }
    result[j]->next = result[i];
    j--;
  }
  result[j]->next = nullptr;
}

void ReorderList(ListNode* head) {
  if (head == nullptr) {
    return;
  }
  ListNode* mid = MiddleList(head);
  ListNode* l1 = head;
  ListNode*l2 = mid->next;
  mid->next = nullptr;
  l2 = ReverseList(l2);
  MergeList(l1, l2); 
}

ListNode* ReverseList(ListNode* head) {
  ListNode* prev = nullptr;
  ListNode* cur = head;
  while(cur != nullptr) {
    ListNode*tmp = cur->next;
    cur->next = prev;
    prev = cur;
    cur = tmp;
  }
}

ListNode* MiddleList(ListNode* head) {
  ListNode* slow = head;
  ListNode* fast = head;
  while(fast->next != nullptr && fast->next->next != nullptr) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}
void MergeList(ListNode* l1, ListNode* l2) {
  ListNode* l1_tmp;
  ListNode* l2_tmp;

  while(l1 != nullptr && l2 != nullptr) {
    l1_tmp = l1->next;
    l2_tmp = l2->next;

    l1->next = l2;
    l1 = l1_tmp;

    l2->next = l1;
    l2 = l2_tmp;
  }
}
