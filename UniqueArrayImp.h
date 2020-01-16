#ifndef HW3_UNIQUEARRAYIMP_H
#define HW3_UNIQUEARRAYIMP_H


template<class Element, class Compare>
bool UniqueArray<Element, Compare>::remove(const Element &element) {
    unsigned int index;
    if(!getIndex(element,index))
        return false;

    delete arr[index];
    arr[index] = NULL;

    if (index<next)
        next = index;
    return true;
}


template<class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::insert(const Element &element) {
    unsigned int index = next;
    for ( int i = 0 ; i < size ; i++){
        if (arr[i] != NULL && compare(*(arr[i]),element)){ //is not empty
            return i;
        }
    }
    // if does not exist- insert in the first available place
    if(next >= size)
        throw UniqueArrayIsFullException();

    try {
        arr[next] = new Element(element);
    }
    catch(std::exception& e){
        throw OutOfMemory(__LINE__);
    }

    while ( next<size && arr[++next] != NULL);
    return index;
}

template<class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size) : size(size), compare(){
    try{
        arr = new Element*[size];
        next = 0;
    }catch (std::exception& e){
        throw OutOfMemory(__LINE__);
    }

    for (int i = 0; i < size ; ++i) {
        arr[i] = NULL;
    }
}

template<class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray &other) : UniqueArray(other.size) {
    try{
        for (int  i = 0;  i < size ; i++) {
            if(other.arr[i] != NULL){
                arr[i] = new Element(*(other.arr[i]));
            }
        }
    }catch (std::exception& e) {
        throw OutOfMemory(__LINE__);
    }
}

template<class Element, class Compare>
UniqueArray<Element, Compare>::~UniqueArray() {
    for (int i = 0; i < size; ++i) {
        if(arr[i] != NULL)
            delete arr[i];
    }
    delete[] arr;
}

template<class Element, class Compare>
bool UniqueArray<Element, Compare>::getIndex(const Element &element,
                                             unsigned int &index) const {
    for(int i = 0 ; i < size ; i++){
        if(arr[i]!= NULL && compare(*(arr[i]),element)){
            index = i;
            return true;
        }
    }
    return false;
}

template<class Element, class Compare>
const Element *UniqueArray<Element, Compare>::operator[](const Element &element) const {
    unsigned int index;
    getIndex(element, index);
    return arr[index];
}

template<class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getCount() const {
    int counter = 0;
    for (int i = 0; i < size ; ++i) {
        if(arr[i] != NULL)
            counter++;
    }
    return counter;
}

template<class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getSize() const {
    return size;
}


#endif