#include "realvector.h"
#include <stdexcept>

// Constructor #1
template<class valueType>
RealVector<valueType>::RealVector():
    logical_size(0), array_size(kInitialSize)
    {
        elems = new valueType[kInitialSize];
    } 

// Constructor #2
template<class valueType>
RealVector<valueType>::RealVector(size_t n, const valueType& val):
    logical_size(n), array_size(n)
    {
        elems = new valueType[n];
        for(size_t i=0; i<n; i++){
            elems[i] = val;
        }
    }

// Deconstructor
template<class valueType>
RealVector<valueType>::~RealVector(){
    delete [] elems;
}

//interface
template<class valueType>
size_t RealVector<valueType>::size() const{
    return logical_size;
}

template<class valueType>
bool RealVector<valueType>::empty() const{
    return size() == 0;
}

template<class valueType>
typename RealVector<valueType>::iterator RealVector<valueType>::begin(){
    return elems;
}

template<class valueType>
typename RealVector<valueType>::const_iterator RealVector<valueType>::begin() const{
    return elems;
}


template<class valueType>
typename RealVector<valueType>::iterator RealVector<valueType>::end(){
    return begin() + size();
}

template<class valueType>
typename RealVector<valueType>::const_iterator RealVector<valueType>::end() const{
     return begin() + size();
}

template<class valueType>
valueType& RealVector<valueType>::operator[] (size_t index){
    return *(begin() + index);
}

template<class valueType>
valueType& RealVector<valueType>::at(size_t index) {
    if (index >= logical_size) {
        throw std::out_of_range("Out of range.");
    }

    return operator[](index); 
}

template<class valueType>
void RealVector<valueType>::grow(){
    iterator new_elems = new valueType[2*kInitialSize];
    for (size_t i = 0; i < size(); i++) {
        new_elems[i] = elems[i];
    }

    delete [] elems;
    array_size *= 2;
    elems = new_elems;
}

template<class valueType>
void RealVector<valueType>::insert(size_t pos, const valueType& elem){
    if (size() == array_size) {
        grow();
    }
    for (size_t i = size(); i >= pos; i--) {
        elems[i+1] = elems[i];
    }

    elems[pos] = elem;
    ++logical_size;
}

template<class valueType>
void RealVector<valueType>::push_back(const valueType& elem){
    insert(size(), elem);
}