#ifndef MY_ITALIAN_QUEUE_V2_H
#define MY_ITALIAN_QUEUE_V2_H

#include <iostream>
#include <sstream>
#include <unordered_map>

using std::stringstream;
using std::string;
using std::ostream;
using std::cout;
using std::endl;

/** A Node of an ItalianQueue. 
    Holds both data and group provided by the user. 
*/


/** An Italian queue, v2.  
    
    - Implemented as a LinkedList
    - In this case, worst case enqueue MUST be O(1)
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
class ItalianQueueV2 : public ItalianQueueV1<T> {

    protected:
        std::unordered_map<string, Node<T>*> tails_;   //  <---- NEW  !
        
        
        virtual void print(std::ostream& os) const{
            ItalianQueueV1<T>::print(os);
            os << "\n         tails_: {";             
            
            int i = 0;
            for (std::pair<string, Node<T>*> els : this->tails_){
                if (i > 0){
                    os << ",";
                }
                os << endl;
                os << "                   " << els.first << " : " << *els.second;
                i++;
            }
            os << endl << "                 }";
            
        }

    public:
        /** Initializes the queue.
                
            - MUST run in O(1)
        */
        ItalianQueueV2() : ItalianQueueV1<T>{} {
            //jupman-raise
            std::unordered_map<string, Node<T>*> tails_ = {};
            ///jupman-raise
        }
    

        /** Enqueues provided element v having group g, with the following 
            criteria:
        
            Queue is scanned from head to find if there is another element 
            with a matching group:
            - if there is, v is inserted after the last element in the 
                same group sequence (so to the right of the group)
            - otherwise v is inserted at the end of the queue

            - MUST run in O(1)
        */
        virtual void enqueue(const T& v, const string g){
            //jupman-raise
            cout << endl << "DEBUG: enqueing " << v << "," << g << endl;
            Node<T>* new_node = new Node<T>(v,g);
            this->size_ += 1;

            if (this->head_ == NULL){     // empty queue
                this->head_ = new_node;
                this->tail_ = new_node;
                this->tails_[g] = new_node;
            } else {                      // non-empty queue
                
                Node<T>* gt;
                if (this->tails_.count(g) == 1){
                    gt = this->tails_[g];
                } else {
                    gt = this->tail_;
                }
                new_node->next(gt->next());
                gt->next(new_node);
                if (new_node->next() == NULL){
                    this->tail_ = new_node;
                }
                this->tails_[g] = new_node;
            }
            ///jupman-raise

        }
        
        /** Removes head element and returns it.
                
            - If the queue is empty, throws a std::out_of_range exception
            - MUST perform in O(1)
            - REMEMBER to clean unused tails_ keys
        */
        virtual const T& dequeue(){
            //jupman-raise
            cout << endl <<  "DEBUG: dequeuing.." << endl;
            if (this->head_ == NULL){
                throw std::out_of_range("Queue is empty !");
            }
            string g = this->head_->group();
            Node<T>* second = this->head_->next();
            const T& ret = this->head_->data();

            if (second == NULL){
                this->tail_ = NULL;
                this->tails_ = {};
            } else {  // no more group g
                if (g != second->group()){
                    this->tails_.erase(g);
                }
            }
            this->head_ = second;
            this->size_ -= 1;       
            return ret;

            //jupman-raise
        }        
        
};




#endif   // MY_ITALIAN_QUEUE_V2_H