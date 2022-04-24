#include<vector>
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {} 
};

ListNode* MergeTwoLists(ListNode* l1, ListNode* l2) {
  if (l1 == nullptr && l2 == nullptr) {
    return nullptr;
  }
  if (l1 == nullptr) {
    return l2;
  }
  if (l2 == nullptr) {
    return l1;
  }

  ListNode* head = new ListNode();
  ListNode* p = head;
  while (l1 != nullptr && l2 != nullptr) {
    if (l1->val < l2->val) {
      p->next = l1;
      l1 = l1->next;
    } else {
      p->next = l2;
      l2 = l2->next;
    }
    p = p->next;
  }
  p->next = l1 == nullptr ? l2 : l1;
  return p->next;
}

ListNode* MergeKLists(std::vector<ListNode*>& lists) {
  ListNode* ans = nullptr;
  for (const auto& item : lists) {
    ans = MergeTwoLists(ans, item);
  }
  return ans;
}