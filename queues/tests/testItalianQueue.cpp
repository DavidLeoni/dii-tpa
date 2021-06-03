
#include "ItalianQueueV1.h"
#include "ItalianQueueV2.h"
#include "catch2/catch2.hpp"

using std::vector;


/** NOTE: this is only a function to inspect the internal stuff of the data structure,
 *  we would not be obliged to ship this code to a client.
 *  Since it accesses internal stuff, we had to declare it as friend in ItalianQueueV1 header
 */
template<typename T>
vector<T> q2vn(const ItalianQueueV1<T>* pq){
    vector<T> ret;
    Node<T>* current = pq->head_;
    while (current != NULL){
        ret.push_back(current->data());
        current = current->next();
    }
    return ret;
}

/** NOTE: this is only a function to inspect the internal stuff of the data structure,
 *  we would not be obliged to ship this code to a client.
 *  Since it accesses internal stuff, we had to declare it as friend in ItalianQueueV1 header
 */
template<typename T>
vector<T> q2vg(const ItalianQueueV1<T>* pq){
    vector<T> ret;
    Node<T>* current = pq->head_;
    while (current != NULL){
        ret.push_back(current->group());
        current = current->next();
    }
    return ret;
}


TEST_CASE ("enqueue V1", "[ItalianQueue][constructor]"){        

    ItalianQueueV1<string>* pq = new ItalianQueueV1<string>();

    pq->enqueue("a","x"); 
    pq->enqueue("c","y"); 
    pq->enqueue("d","y"); 
    pq->enqueue("b","x"); 
    pq->enqueue("f","z");
    pq->enqueue("e","y");

    REQUIRE(q2vn(pq) == vector<string>({"a","b","c","d","e","f"}));
    REQUIRE(q2vg(pq) == vector<string>({"x","x","y","y","y","z"}));    
    
}    


TEST_CASE ("enqueue V2", "[ItalianQueue][constructor]"){        

    ItalianQueueV2<string>* pq = new ItalianQueueV2<string>();

    pq->enqueue("a","x"); 
    pq->enqueue("c","y"); 
    pq->enqueue("d","y"); 
    pq->enqueue("b","x"); 
    pq->enqueue("f","z");
    pq->enqueue("e","y");

    REQUIRE(q2vn(pq) == vector<string>({"a","b","c","d","e","f"}));
    REQUIRE(q2vg(pq) == vector<string>({"x","x","y","y","y","z"}));    
    
}    