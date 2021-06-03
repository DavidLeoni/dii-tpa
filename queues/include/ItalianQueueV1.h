#ifndef MY_ITALIAN_QUEUE_V1_H
#define MY_ITALIAN_QUEUE_V1_H

#include <iostream>
#include <sstream>

#include <vector>

using std::stringstream;
using std::string;
using std::ostream;
using std::vector;
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

        ~Node(){
            cout << "DEBUG: " << *this << " destructor" << endl;
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

    // Overrides default ostream << behaviour
    // NOTE: - C++ weirdness: we redefine the template type with a different name U because 
    //         this is a function *EXTERNAL* to the class
    //       - friend means that even if external to the class, the function body will be able to access private members
      template<typename U> 
      friend ostream& operator<<(ostream& os, const Node<U>& node);  

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

    protected:
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

    /** Remember to delete nodes */
    ~ItalianQueueV1(){
        //jupman-raise
        cout << "DEBUG: Queue destructor" << endl;
        Node<T>* current = this->head_;
        while (current != NULL) {
            Node<T>* pnext = current->next();
            delete current;
            current = pnext;

        }
        ///jupman-raise
    }

    /** Return the size of the queue.
    
        - MUST run in O(1)
    */    
    virtual int size() const {
        //jupman-raise
        return this->size_;
        ///jupman-raise
    }

    /** Return true if the queue is empty, false otherwise.
    
        - MUST run in O(1)
    */
    virtual bool is_empty() const {
        //jupman-raise
        return this->head_ == NULL;
        ///jupman-raise
    }

    /** Return the element at the head of the queue, without removing it. 
    
        - If the queue is empty, throws a std::out_of_range exception
        - MUST run in O(1)
    */
    virtual const T& top() const {
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
    virtual const string& top_group() const {
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
    virtual const T& tail() const {
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
    virtual const string& tail_group() const {
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
    virtual void enqueue(const T& v, const string g){
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
    virtual const T& dequeue(){
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
     
    // Overrides default ostream << behaviour
    // NOTE: - C++ weirdness: we redefine the template type with a different name U because 
    //         this is a function *EXTERNAL* to the class
    //       - friend means that even if external to the class, the function body will be able to access private members
    template<typename U> 
    friend ostream& operator<<(ostream& os, const ItalianQueueV1<U>& queue);

    protected:
        
        virtual void print(std::ostream& os) const{
            os << "ItalianQueue: ";

            Node<T>* current = this->head_;    
            
            int i = 0;
            while (current != NULL) {        
                if (i>0){
                    os << "->";
                }
                os << current->data();        
                current = current->next();
                i++;
            };

            os << "\n              ";

            i = 0;
            current = this->head_;    
            while (current != NULL) {        
                if (i>0){
                    os << "  ";
                }
                os << current->group();
                current = current->next();
                i++;
            };
            
            os << "\n         head_: "; 
            if (this->head_){
                os << *this->head_;
            } else {
                os << "NULL";
            };
            
            os  << "\n         tail_: ";
            if (this->tail_){
                os << *this->tail_;
            } else {
                os << "NULL";
            };            

        }    

        /**
         * RETURN a vector holding the data found in nodes
         * 
         * We intend it as an inspection function which we don't 
         * necessarily need ship to the client, so we declare it as an external 
         * function which is a friend of this class, meaning it can access 
         * private fields. We will implement it in tests.
        */
        template<typename U> 
        friend vector<U> q2vn(const ItalianQueueV1<U>* pq);

        /**
         * RETURN a vector holding the groups found in nodes
         * 
         * We intend it as an inspection function which we don't 
         * necessarily need ship to the client, so we declare it as an external 
         * function which is a friend of this class, meaning it can access 
         * private fields. We will implement it in tests.
        */
        template<typename U> 
        friend vector<U> q2vg(const ItalianQueueV1<U>* pq);
};


// Overrides default ostream << behaviour
template<typename T>
ostream& operator<<(ostream& os, const ItalianQueueV1<T>& queue){
    
    queue.print(os);
    return os;
}


#endif   // MY_ITALIAN_QUEUE_V1_H