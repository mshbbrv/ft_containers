#if 1 //CREATE A REAL STL EXAMPLE
#include <stack>
namespace ft = std;
#else
#include "stack.hpp"
#endif
#include <iostream>

int main(){

    std::cout << "--------ALL TESTS---------";

    {
        ft::stack<int> stack;
        stack.push(21);
        stack.push(22);
        stack.push(24);
        stack.push(25);

        stack.pop();
        stack.pop();

        std::cout << "\nSize : " << stack.size() << std::endl;

        while (!stack.empty()) {
            std::cout << ' ' << stack.top();
            stack.pop();
        }
    }
    std::cout << std::endl;
}
