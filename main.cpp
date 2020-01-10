#include <iostream>
#include "UniqueArray.h"
class Foo{
public:
    Foo() = default;
    int operator()(const int n) const {
        return n;
    }
};

int main() {
    Foo foo;
    try{
        UniqueArray<int> arr(10);
    }catch (UniqueArrayExceptions& e){
        std::cout << e.what() << e.getLine() << std::endl;
        return -1;
    }
    foo(6);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

