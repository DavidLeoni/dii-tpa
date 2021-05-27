#ifndef MY_ITALIAN_QUEUE_V1_H
#define MY_ITALIAN_QUEUE_V1_H

#include <iostream>
#include <sstream>

using std::stringstream;
using std::string;
using std::ostream;
using std::cout;
using std::endl;

/** A Node of an ItalianQueue. 
    Holds both data and group provided by the user. 
*/

template<typename T> 
class Node {
    
    private:
        T data_;
        string group_;
        Node<T>* next_;

    public:

        Node(const T& initdata, const string& initgroup){
            this->data_ = initdata;
            this->group_ = initgroup;
            this->next_ = NULL;
        }

        const T& data() {
            return this->data_;
        }

        const string& group() const {
            return this->group_;
        }

        Node<T>* next() const {
            return this->next_;
        }

        void data(const T& newdata){
            this->data_ = newdata;
        }

        void next(Node<T>* newnext){
            this->next_ = newnext;
        }

      template<typename U> // TODO
      friend ostream& operator<<(ostream& os, const Node<U>& queue);  
};


template<typename T>
ostream& operator<<(ostream& os, const Node<T>& node){
    
    os << "Node(";
    os << node.data_ << "," << node.group_ << ")";

    return os;
}

/** An Italian queue, v1.  
    
- Implemented as a LinkedList
- Worst case enqueue is O(n)
- has extra methods, for accessing groups and tail:
    - top_group()
    - tail()
    - tail_group()
                
Each element is assigned a group; during enqueing, queue is 
scanned from head to tail to find if there is another element
with a matching group. 
    - If there is, element to be enqueued is inserted after the 
        last element in the same group sequence (that is, to the 
        right of the group)
    - otherwise the element is inserted at the end of the queue
*/

template<typename T>
class ItalianQueueV1 {

    private:
        Node<T>* head_;
        Node<T>* tail_;
        int size_;

    public:
    /** Initializes the queue.
            
        - MUST run in O(1)
    */
    ItalianQueueV1(){
        //jupman-raise
        this->head_ = NULL;
        this->tail_ = NULL;
        this->size_ = 0;
        ///jupman-raise
    }

    /** Return the size of the queue.
    
        - MUST run in O(1)
    */    
    int size() const {
        //jupman-raise
        return this->size_;
        ///jupman-raise
    }

    /** Return true if the queue is empty, false otherwise.
    
        - MUST run in O(1)
    */
    bool is_empty() const {
        //jupman-raise
        return this->head_ == NULL;
        ///jupman-raise
    }

    /** Return the element at the head of the queue, without removing it. 
    
        - If the queue is empty, throws a std::out_of_range exception
        - MUST run in O(1)
    */
    const T& top() const {
        //jupman-raise
        if (this->head_ != NULL) {
            return this->head_->data();
        } else {
            throw std::out_of_range("Queue is empty !");
        }
        ///jupman-raise
    }

    /** Return the group of the element at the head of the queue, 
            without removing it. 
        
            - If the queue is empty, throws a std::out_of_range exception
            - MUST run in O(1)
    */
    const string& top_group() const {
        //jupman-raise
        if (this->head_ != NULL){
            return this->head_->group();
        } else{
            throw std::out_of_range("Queue is empty !");
        }
        ///jupman-raise
    }

    /** Return the element at the tail of the queue (without removing it)
    
        - If the queue is empty, throws a std::out_of_range exception
        - MUST run in O(1)
    */
    const T& tail() const {
        //jupman-raise
        if (this->tail_ != NULL){
            return this->tail_->data();
        } else {
            throw std::out_of_range("Queue is empty !");
        }            
        ///jupman-raise
    }

    /** Return the group of the element at the tail of the queue (without removing it). 
        
            - If the queue is empty, throws a std::out_of_range exception
            - MUST run in O(1)
    */
    const string& tail_group() const {
        //jupman-raise
        if (this->tail_ != NULL){
            return this->tail_->group();
        } else {
            throw std::out_of_range("Queue is empty !");
        }
        ///jupman-raise
    }        

    /** Enqueues provided element v having group g, with the following 
        criteria:
    
        Queue is scanned from head to find if there is another element 
        with a matching group:
            - if there is, v is inserted after the last element in the 
                same group sequence (so to the right of the group)
            - otherwise v is inserted at the end of the queue

        - MUST run in O(n)
    */
    void enqueue(const T& v, const string g){
        //jupman-raise
        cout << endl << "DEBUG: enqueing " << v << "," << g << endl;
        Node<T>* new_node = new Node<T>(v,g);
        this->size_ += 1;
        
        if (this->head_ == NULL){     // empty queue
            this->head_ = new_node;
            this->tail_ = new_node;
        } else {                     // non-empty queue
            Node<T>* current = this->head_;
            Node<T>* prev = this->head_;                
            bool found_group = false;
            
            while (current != NULL){
                if (found_group){
                    if (current->group() != g) { // time to insert                      
                        new_node->next(current);
                        prev->next(new_node);
                        return;
                    };
                } else {  // didn't previously find group                                        
                    if (current->group() == g) {
                        found_group = true;
                    };
                };

                prev = current;
                current = current->next();
            };
            // if it already found group end, it means it already returned
            this->tail_->next(new_node);
            this->tail_ = new_node;
        };
        ///jupman-raise
    }
    
    /** Removes head element and returns it.
            
            - If the queue is empty, raises a std::out_of_range exception
            - MUST run in O(1)
    */
    const T& dequeue(){
        //jupman-raise
        cout << endl <<  "DEBUG: dequeuing.." << endl;
        if (this->head_ != NULL){
            this->size_ -= 1;
            const T& ret = this->head_->data();
            this->head_ = this->head_->next();
            if (this->head_ == NULL){
                this->tail_ = NULL;
            }            
            return ret;
        } else {
            throw std::out_of_range("Queue is empty !");
        }
        //jupman-raise
    }

    template<typename U> // TODO
    friend ostream& operator<<(ostream& os, const ItalianQueueV1<U>& queue);
};

/** For potentially complex data structures like this one, having 
    a __str__ method is essential to quickly inspect the data by printing it. 
*/

template<typename T>
ostream& operator<<(ostream& os, const ItalianQueueV1<T>& queue){
    
    os << "ItalianQueueV1: ";

    Node<T>* current = queue.head_;    
    
    int i = 0;
    while (current != NULL) {        
        if (i>0){
            os << "->";
        }
        os << current->data();        
        current = current->next();
        i++;
    };

    os << "\n                ";

    i = 0;
    current = queue.head_;    
    while (current != NULL) {        
        if (i>0){
            os << "  ";
        }
        os << current->group();
        current = current->next();
        i++;
    };
    
    os << "\n         head_: "; 
    if (queue.head_){
        os << *queue.head_;
    } else {
        os << "NULL";
    };
    
    os  << "\n         tail_: ";
    if (queue.tail_){
        os << *queue.tail_;
    } else {
        os << "NULL";
    };
}


#endif   // MY_ITALIAN_QUEUE_V1_H