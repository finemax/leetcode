#include "process.h"
#include<iostream>

int main() {
    auto thread_pool = std::make_shared<ThreadPool>(1);
    {
        std::shared_ptr<Process> process = Process::Create(thread_pool);
        auto test_data =
            std::make_unique<std::vector<int>>(std::vector<int>({1,2,3,4,5,6,7,8,9}));
        process->SetContext(std::move(test_data));
        std::cout << " output: " << process->GetValue() << std::endl;
    }
    using namespace std::chrono_literals;
    // std::this_thread::sleep_for(3s);
    return 0;
}
