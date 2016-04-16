#ifndef MYQUEUE
#define MYQUEUE


template<class QUEUETYPE> class myQueueNode;

template <class QUEUETYPE>
class myQueue{
public:
    myQueue();          // constructor
    ~myQueue();         // destructor

    void push(const QUEUETYPE &); // add an element to the end myQueue
    QUEUETYPE front();            // return the first element from myQueue
    void pop();                   // delete the first element from myQueue
    bool empty() const;

private:
    myQueueNode<QUEUETYPE> *firstPtr;        // pointer on the first node
    myQueueNode<QUEUETYPE> *lastPtr;         // pointer on the last node

    myQueueNode<QUEUETYPE> *getNewNode(const QUEUETYPE &); // creat new node
};


template<class QUEUETYPE>
myQueue<QUEUETYPE>::myQueue(){
    firstPtr = 0;
    lastPtr = 0;
}

template<class QUEUETYPE>
myQueue<QUEUETYPE>::~myQueue(){
    if(!empty()){
        myQueueNode<QUEUETYPE> *currentPtr = firstPtr;
        myQueueNode<QUEUETYPE> *temp;

        while(currentPtr != 0){
            temp = currentPtr;
            currentPtr = currentPtr->nextPtr;
            delete temp;
        }
    }
}

template<class QUEUETYPE>
void myQueue<QUEUETYPE>::push(const QUEUETYPE &value){
    myQueueNode<QUEUETYPE> *newPtr = getNewNode(value);

    if(empty()){
        firstPtr = lastPtr = newPtr;
    }else{
        lastPtr->nextPtr = newPtr;
        lastPtr = newPtr;
    }
}

template<class QUEUETYPE>
QUEUETYPE myQueue<QUEUETYPE>::front(){
    return firstPtr->getData();
}

template<class QUEUETYPE>
void myQueue<QUEUETYPE>::pop(){
    if(empty()){
        return;
    }else{
        myQueueNode<QUEUETYPE> *temp = firstPtr;
        if(firstPtr == lastPtr){
            firstPtr = lastPtr = 0;
        }else{
            firstPtr = firstPtr->nextPtr;
        }
        delete temp;
    }
}


template<class QUEUETYPE>
bool myQueue<QUEUETYPE>::empty() const {
    return firstPtr == 0;
}


template<class QUEUETYPE>
myQueueNode<QUEUETYPE>* myQueue<QUEUETYPE>::getNewNode(const QUEUETYPE &value){
    myQueueNode<QUEUETYPE> * ptr = new myQueueNode<QUEUETYPE>(value);
    return ptr;
}


//------------------------------ class myQueueNode ------------------------------------


template<class QUEUETYPE>
class myQueueNode{
public:
    myQueueNode(const QUEUETYPE &);  // constructor
    QUEUETYPE getData() const;       // return data
    myQueueNode *nextPtr;            // pointer on the next node

private:
    QUEUETYPE data;
};

template <class QUEUETYPE>
myQueueNode<QUEUETYPE>::myQueueNode(const QUEUETYPE &value)
{
    data = value;
    nextPtr = 0;
}

template<class QUEUETYPE>
QUEUETYPE myQueueNode<QUEUETYPE>::getData() const
{
    return data;
}


#endif // MYQUEUE

