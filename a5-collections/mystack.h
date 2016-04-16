#ifndef MYSTACK
#define MYSTACK

template<class STACKTYPE>
class myStack{
private:
    class Node{
    public:
        STACKTYPE data;
        Node* prePtr;
        Node(const STACKTYPE &);  //constructor
    };

    Node* lastPtr;
    int stackSize;
    Node* getNewNode(const STACKTYPE &);

public:
    myStack();   // constructor
    ~myStack();  // destructor

    void push(const STACKTYPE &);   // add an element to the myStack
    void pop();                     // delete the top element from myStack
    STACKTYPE top();                // return top element
    int size();
    bool empty();
};

//---------------------------- class MyStack -------------------

template<class STACKTYPE>
myStack<STACKTYPE>::myStack(){
    lastPtr = 0;
    stackSize = 0;
}

template<class STACKTYPE>
myStack<STACKTYPE>::~myStack(){
    if(!empty()){
        Node* current = lastPtr;
        Node* temp;

        while (current != 0) {
            temp = current;
            current = current->prePtr;
            delete temp;
        }
    }
}

template<class STACKTYPE>
void myStack<STACKTYPE>::push(const STACKTYPE &value){
    Node* newPtr = getNewNode(value);

    if(empty()){
        lastPtr = newPtr;
    }else{
        newPtr->prePtr = lastPtr;
        lastPtr = newPtr;
    }
    stackSize++;
}

template<class STACKTYPE>
void myStack<STACKTYPE>::pop(){
    if(empty()){
        return;
    }else{
        Node* newPtr = lastPtr;
        lastPtr = lastPtr->prePtr;
        delete newPtr;
    }
    stackSize--;
}

template<class STACKTYPE>
STACKTYPE myStack<STACKTYPE>::top(){
    return lastPtr->data;
}


template<class STACKTYPE>
int myStack<STACKTYPE>::size(){
    return stackSize;
}

template<class STACKTYPE>
bool myStack<STACKTYPE>::empty(){
    return stackSize == 0;
}

template<class STACKTYPE>
typename myStack<STACKTYPE>::Node* myStack<STACKTYPE>::getNewNode(const STACKTYPE &value){
    return new Node(value);
}

//---------------------------- class Node ----------------------

template<class STACKTYPE>
myStack<STACKTYPE>::Node::Node(const STACKTYPE &value){
    data = value;
    prePtr = 0;
}

#endif // MYSTACK

