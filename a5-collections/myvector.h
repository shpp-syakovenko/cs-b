#ifndef MYVECTOR
#define MYVECTOR

#include <iostream>

using namespace std;

template <class VECTORTYPE>
class myVector{

public:
    myVector();                // constructor
    myVector(int);             // install capacity
    myVector(const myVector&); // copy constructor
    ~myVector();               // destructor

    void push_back(const VECTORTYPE &); // add an element to the end myVector
    void pop_back();                    // delete an element from end myVector
    int size();                         // count element into myVector

    VECTORTYPE& operator[](int);
    myVector& operator=(const myVector &);

private:
    int vSize;           // size of the array
    int capacity;        // capacity myVector
    VECTORTYPE *array;
    void array_new();    // increasing the capacity of the array.

};

template<class VECTORTYPE>
myVector<VECTORTYPE>::myVector(){
    capacity = 20;
    array = new VECTORTYPE[capacity];
    vSize = 0;
}

template<class VECTORTYPE>
myVector<VECTORTYPE>::myVector(int i){
    capacity = i;
    array = new VECTORTYPE[capacity];
    vSize = 0;
}

template<class VECTORTYPE>
myVector<VECTORTYPE>::myVector(const myVector &v){
    capacity = v.capacity;
    vSize = v.vSize;

    array = new VECTORTYPE[capacity];
    for(int i = 0; i < vSize; i++){
        array[i] = v.array[i];
    }
}

template<class VECTORTYPE>
myVector<VECTORTYPE>::~myVector(){
    delete [] array;
}

template<class VECTORTYPE>
void myVector<VECTORTYPE>::push_back(const VECTORTYPE &value){
    if((vSize + 1) > capacity){
        array_new();
    }

    array[vSize] = value;
    vSize++;
}

template<class VECTORTYPE>
void myVector<VECTORTYPE>::pop_back(){
    if(vSize > 0){
        vSize--;
    }
}

template<class VECTORTYPE>
VECTORTYPE& myVector<VECTORTYPE>::operator[](int index){
    return array[index];
}

template<class VECTORTYPE>
void myVector<VECTORTYPE>::array_new(){
    capacity = vSize * 2;
    VECTORTYPE * temp = new VECTORTYPE[capacity];

    for(int i = 0; i < vSize; i++){
        temp[i] = array[i];
    }

    delete [] array;
    array = temp;
}

template<class VECTORTYPE>
int myVector<VECTORTYPE>::size(){
    return vSize;
}

template<class VECTORTYPE>
myVector<VECTORTYPE>& myVector<VECTORTYPE>::operator =(const myVector& v){
    if(this != &v){
        capacity = v.capacity;
        vSize = v.vSize;
        delete[] array;

        array = new VECTORTYPE[capacity];
        for(int i = 0; i < vSize; i++){
            array[i] = v.array[i];
        }
    }

    return *this;
}
#endif // MYVECTOR

