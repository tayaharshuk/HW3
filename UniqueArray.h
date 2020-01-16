#ifndef MTMPARKINGLOT_UNIQUEARRAY_H
#define MTMPARKINGLOT_UNIQUEARRAY_H

#include <cstdio>
#include <functional>
#include "UniqueArrayExceptions.h"


template <class Element, class Compare = std::equal_to<Element>>
class UniqueArray {
    unsigned int size;
    Element** arr;
    int next;
    const Compare compare;

public:

    explicit UniqueArray(unsigned int size);
    UniqueArray(const UniqueArray& other);

    ~UniqueArray();
    UniqueArray& operator=(const UniqueArray&) = delete;
    unsigned int insert(const Element& element);

    bool getIndex(const Element& element, unsigned int& index) const;

    const Element* operator[] (const Element& element) const;

    bool remove(const Element& element);

    unsigned int getCount() const;
    unsigned int getSize() const;

    class Filter {
    public:
        virtual bool operator() (const Element&) const = 0;
    };

    UniqueArray filter(const Filter& f) const{
        UniqueArray newArr(*this);

        for (int i = 0; i < size ; i++) {
            if (arr[i] != NULL && !f(*arr[i])){
                  newArr.remove(*(newArr.arr[i]));
            }
        }
        return newArr;
    }

    class UniqueArrayIsFullException : public std::exception{
        const char *what() const noexcept override {
            return "Array is full";
        }
    };

    class Iterator{
        Element* element;

    public:
        explicit Iterator(Element* elementPtr) : element(elementPtr){}
        ~Iterator() = default;

        bool operator==(const Iterator &rhs) const {
            return element == rhs.element;
        }

        bool operator!=(const Iterator &rhs) const {
            return !(rhs == *this);
        }

        Iterator& operator=(const Iterator &rhs) {
            this->element = rhs.element;
            return *this;
        }

        Iterator& operator++(){
            element++;
            return *this;
        }

        Element& operator*(){
            return *element;
        }
    };

    Iterator& begin(){
        return Iterator(arr);
    }

    Iterator& end(){
        return Iterator(arr+size);
    }
};

#include "UniqueArrayImp.h"



#endif //MTMPARKINGLOT_UNIQUEARRAY_H
