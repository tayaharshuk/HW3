#ifndef MTMPARKINGLOT_UNIQUEARRAY_H
#define MTMPARKINGLOT_UNIQUEARRAY_H

#include <cstdio>
#include <functional>

template <class Element, class Compare = std::equal_to<Element>>
class UniqueArray {
    unsigned int size;
    Element* arr;
    bool* isAvailable;

public:

    UniqueArray(unsigned int size);
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
    UniqueArray filter(const Filter& f) const;

    class UniqueArrayIsFullException{};
    
};

template<class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size) : size(size){
    arr = new Element[size];
    isAvailable = new bool[size];
    for (int i = 0; i < size ; ++i) {
        isAvailable[i] = false;
    }
}

#include "UniqueArrayImp.h"



#endif //MTMPARKINGLOT_UNIQUEARRAY_H
