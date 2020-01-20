#ifndef HW3_UNIQUEARRAYEXCEPTIONS_H
#define HW3_UNIQUEARRAYEXCEPTIONS_H

#include <exception>

class UniqueArrayExceptions : public std::exception{
    unsigned int line;

public:
    explicit UniqueArrayExceptions(int line = 0) : line(line){}

    unsigned int getLine() const {
        return line;
    }
};

class OutOfMemory : public UniqueArrayExceptions{
    unsigned int line;
public:
    explicit OutOfMemory(int line = 0) : UniqueArrayExceptions(line) {}

    const char* what() const noexcept override {
        return "Out Of Memory";
    }
};


#endif //HW3_UNIQUEARRAYEXCEPTIONS_H
