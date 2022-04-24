#include <iostream>

template <typename T>
class my_shared_ptr {
 public:
  my_shared_ptr(T* value) {
    ptr = value;
    count = new int(1);
  }
  my_shared_ptr(const my_shared_ptr& m) {
    ptr = m.ptr;
    count = m.count;
    (*count)++;
  }
  my_shared_ptr& operator=(const my_shared_ptr& m) {
    if (this != m) {
      ptr = m.ptr;
      count = m.count;
      (*count)++;
    }
    return *this;
  }
  T& operator->() {
    return this->prt;
  }
  ~my_shared_ptr() {
    *(count)--;
    if (*(this->count) == 0) {
      delete ptr;
      delete count;
    }
  }
  public:
   T* ptr;
   int* count;
};

int main() {
	my_shared_ptr<int> res(new int(2));
	std::cout << *(res.count) << std::endl;
#if 0
	my_shared_ptr<int> res2(res);
	std::cout << *(res2.count) << std::endl;
	my_shared_ptr<int> res3 = res;
	std::cout << *(res.count) << std::endl;
	std::cout << *(res2.count) << std::endl;
	std::cout << *(res3.count) << std::endl;
	res.~my_shared_ptr();
	std::cout << *(res3.count) << std::endl;
	res2.~my_shared_ptr();
	std::cout << *(res3.count) << std::endl;
  res3.~my_shared_ptr();
#endif
}
