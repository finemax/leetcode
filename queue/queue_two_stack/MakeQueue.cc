#include <stack>

class MakeQueue {
private:
  int front = -1;
  std::stack<int> s1;
  std::stack<int> s2;
public:
  MakeQueue() = default;
  ~MakeQueue() = default;

  void push(int x);
  int pop();
  int peek();
  bool empty();
};

void MakeQueue::push(int x) {
  if (s1.empty()) {
    front = x;
  }
  s1.push(x);
}

int MakeQueue::pop() {
  if (s2.empty()) {
    s2.push(s1.top());
    s1.pop();
  }
  int val = s2.top();
  s2.pop();
  return val;
}

int MakeQueue::peek() {
  if (!s2.empty()) {
    return s2.top();
  }
  return front;
}

bool MakeQueue::empty() {
  return s1.empty() && s2.empty();
}
