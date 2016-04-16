#ifndef MYLIST
#define MYLIST

#include <iostream>
using namespace std;

template<class LISTTYPE>
class myList{
private:

    class Node{
    public:
        Node(const LISTTYPE &);       // constructor
        Node* nextPtr;
        Node* prePtr;
        LISTTYPE data;
    };

    Node* firstPtr;                    // pointer on the first node
    Node* lastPtr;                     // pointer on the last node
    int listSize;                      // count node into myList
    Node* getNewNode(const LISTTYPE &);// create new node

public:
    myList();   // constructor
    ~myList();  // destructor

    void push_back(const LISTTYPE &);  // add an element to the end myList
    void push_front(const LISTTYPE &); // add an element to the start myList
    void pop_back();                   // delete an element from the end myList.
    void pop_front();                  // delete an element from the start myList
    LISTTYPE front();                  // return first element
    LISTTYPE back();                   // return last element
    int size();                        // return size of the myList
    void sort();
    bool empty();


    class iterator{
    private:
        Node* node;
    public:
        iterator(Node *node = NULL);            // constructor
        iterator(const iterator& itr);          // copy constructor
        iterator operator++();                  // ++itr
        iterator operator++(int);               // itr++
        bool operator != (const iterator& itr);
        bool operator == (const iterator& itr);
        LISTTYPE& operator *();
    };

    iterator begin() const;
    iterator end() const;

};

//-------------------- class myList ------------------------

template<class LISTTYPE>
myList<LISTTYPE>::myList(){
    firstPtr = NULL;
    lastPtr = NULL;
    listSize = 0;
}

template<class LISTTYPE>
myList<LISTTYPE>::~myList(){
    if(!empty()){
        Node* current = firstPtr;
        Node* temp;

        while(current != NULL){
            temp = current;
            current = current->nextPtr;
            delete temp;
        }
    }
}

template<class LISTTYPE>
void myList<LISTTYPE>::push_back(const LISTTYPE &value){
    Node *newPtr = getNewNode(value);

    if(empty()){
       firstPtr = lastPtr = newPtr;
    }else{
        newPtr->prePtr = lastPtr;
        lastPtr->nextPtr = newPtr;
        lastPtr = newPtr;
    }
    listSize++;
}

template<class LISTTYPE>
void myList<LISTTYPE>::push_front(const LISTTYPE &value){
    Node* newPtr = getNewNode(value);

    if(empty()){
        firstPtr = lastPtr = newPtr;
    }else{
        newPtr->nextPtr = firstPtr;
        firstPtr->prePtr = newPtr;
        firstPtr = newPtr;
    }
    listSize++;
}

template<class LISTTYPE>
void myList<LISTTYPE>::pop_back(){
    if(empty()){
        return;
    }else{
        if(firstPtr == lastPtr){
            delete lastPtr;
            firstPtr = lastPtr = NULL;
        }else{
            lastPtr = lastPtr->prePtr;
            delete lastPtr->nextPtr;
            lastPtr->nextPtr = NULL;
        }
        listSize--;
    }
}

template<class LISTTYPE>
void myList<LISTTYPE>::pop_front(){
    if(empty()){
        return;
    }else{
        if(firstPtr == lastPtr){
            delete firstPtr;
            firstPtr = lastPtr = NULL;
        }else{
            firstPtr = firstPtr->nextPtr;
            delete firstPtr->prePtr;
            firstPtr->prePtr = NULL;
        }
        listSize--;
    }
}

template<class LISTTYPE>
LISTTYPE myList<LISTTYPE>::front(){
    return firstPtr->data;
}

template<class LISTTYPE>
LISTTYPE myList<LISTTYPE>::back(){
    return lastPtr->getData();
}

template<class LISTTYPE>
int myList<LISTTYPE>::size(){
    return listSize;
}

template<class LISTTYPE>
void myList<LISTTYPE>::sort(){
    Node *currentPtr = firstPtr;
    Node *temp;

    while (currentPtr != NULL) {
        temp = currentPtr->nextPtr;
        while (temp != NULL) {
            if(currentPtr->data > temp->data){
                LISTTYPE t = temp->data;
                temp->data = currentPtr->data;
                currentPtr->data = t;
            }
           temp = temp->nextPtr;
        }
        currentPtr = currentPtr->nextPtr;
    }
}

template<class LISTTYPE>
bool myList<LISTTYPE>::empty(){
    return listSize == 0;
}

template<class LISTTYPE>
typename myList<LISTTYPE>::Node* myList<LISTTYPE>::getNewNode(const LISTTYPE &value){
    Node *ptr = new Node(value);
    return ptr;
}

template<class LISTTYPE>
typename myList<LISTTYPE>::iterator myList<LISTTYPE>::begin()const{
    return iterator(this->firstPtr);
}

template<class LISTTYPE>
typename myList<LISTTYPE>::iterator myList<LISTTYPE>::end() const{
    if(lastPtr == NULL)
        return NULL;
    return iterator(lastPtr->nextPtr);
}


//------------------------------------ class iterator ------------------------------

template<class LISTTYPE>
myList<LISTTYPE>::iterator::iterator(Node *node){
    this->node = node;
}

template<class LISTTYPE>
myList<LISTTYPE>::iterator::iterator(const iterator &itr){
    this->node = itr.node;
}

template<class LISTTYPE>
typename myList<LISTTYPE>::iterator myList<LISTTYPE>::iterator::operator ++(){
    if(node == NULL){
        return NULL;
    }
    node = node->nextPtr;
    return *this;
}

template<class LISTTYPE>
typename myList<LISTTYPE>::iterator myList<LISTTYPE>::iterator::operator ++(int){
    if(node == NULL){
        return NULL;
    }
    iterator copy(*this);
    operator ++();
    return copy;
}

template<class LISTTYPE>
bool myList<LISTTYPE>::iterator::operator ==(const iterator &itr){
    return node == itr.node;
}

template<class LISTTYPE>
bool myList<LISTTYPE>::iterator::operator !=(const iterator &itr){
    return !(*this == itr);
}

template<class LISTTYPE>
LISTTYPE& myList<LISTTYPE>::iterator::operator *(){
    return node->data;
}




// ----------------------------------- class Node -----------------------------------

template<class LISTTYPE>
myList<LISTTYPE>::Node::Node(const LISTTYPE &value){
    data = value;
    nextPtr = NULL;
    prePtr = NULL;
}


#endif // MYLIST

