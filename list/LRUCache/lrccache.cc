
#include <iostream>
#include <unordered_map>

struct DLinkedNode {
  int key;
  int value;
  DLinkedNode* prev;
  DLinkedNode* next;
  DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
  DLinkedNode(int key_, int value_) : key(key_), value(value_), prev(nullptr), next(nullptr) {}
};

class LRUCache {
  public:
    LRUCache(int _capacity) : capacity(_capacity), size(0) {
      head = new DLinkedNode();
      tail = new DLinkedNode();
      head->next = tail;
      tail->prev = head; 
    }

    int get(int key) {
      if (!cache.count(key)) {
        return -1;
      }
      DLinkedNode* node = cache[key];
      MoveToHead(node);
      return node->value;
    }
    void put(int key, int value) {
      if (!cache.count(key)) {
        DLinkedNode* node = new DLinkedNode(key, value);
        cache[key] = node;
        AddToHead(node);
        size++;
        if (size > capacity) {
          DLinkedNode* node = RemoveTail();
          cache.erase(node->key);
          delete node;
          --size;
        } else {
          DLinkedNode* node = cache[key];
          node->value = value;
          MoveToHead(node);
        }
      }
    }
    void AddToHead(DLinkedNode* node) {
      node->prev = head;
      node->next = head->next;
      head->next->prev = node;
      head->next = node;
    }
    void RemoveNode(DLinkedNode* node) {
      node->prev->next = node->next;
      node->next->prev = node->prev;
    }
    void MoveToHead(DLinkedNode* node) {
      RemoveNode(node);
      AddToHead(node);
    }
    DLinkedNode* RemoveTail() {
      DLinkedNode* node = tail->prev;
      RemoveNode(node);
      return node;
    }

  private:
    std::unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int size;
    int capacity;
};
