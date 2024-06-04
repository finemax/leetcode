#include <iostream>

int calculate(std::string s) {

    std::stack<int> values;
    int num = 0;
    char sign = '+';
    for (int i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (isdigit(c)) {
            num = 10*num + (s[i] - '0');
        }
        if ((!isdight(c) && c != ' ') || i == s.size() - 1) {
            switch(sign) {
                case '+' :
                    values.push(num); break;
                case '-':
                    values.push(-num); break;
                case '*':
                    int pre = values.top();
                    values.pop();
                    values.push(pre*num);
                case '/':
                    int pre = values.top();
                    values.pop();
                    values.push(pre/num);
            }
            sign = c;
            num = 0;
        }
    }
    int res = 0;
    //for (const auto& item : values) {
    //    res += item;
    //}
    while (!values.empty()) {
        res += values.top();
        values.pop();
    }
    return res;
}
