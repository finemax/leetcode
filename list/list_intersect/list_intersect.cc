#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int val) : val(val), next(nullptr) {}
};

bool ListIntersect(ListNode* l1, ListNode* l2) {
    ListNode*p1 = l1;
    while (p1) {
        ListNode*p2 = l2;
        while (p2) {
            if (p1 == p2) return true;
            p2=p2->next;
        } 
        p1=p1->next;
    }
    return false;
}

bool ListIntersect2(ListNode* l1, ListNode* l2) {
    auto p1 = l1;
    auto p2 = l2;

    while (p1->next) {
        p1 = p1->next;
    }
    while (p2->next) {
        p2 = p2->next;
    }

    return p1 == p2 ? true : false;
}

bool ListIntersect3(ListNode* l1, ListNode* l2) {
    auto list_long = l1;
    auto list_short = l2;
    int num_long = 0;
    int num_short = 0;

    while (list_long) {
        num_long++;
        list_long = list_long->next;
    }
    while (list_short) {
        num_short++;
        list_short = list_short->next;
    }
    int step = std::abs(num_long - num_short);
    if (num_long < num_short) {
        list_long = l2;
        list_short = l1;
    }
    auto tmp = list_long;
    while (step) {
        tmp = tmp->next;
        step--;
    }
    while (tmp && list_short) {
        if (tmp == list_short) return true;
        tmp = tmp->next;
        list_short = list_short->next;
    }
    return false;
}
