#include <iostream>
#include <stdexcept>

#include <circular_queue.h>
#include <ItalianQueueV1.h>
#include <ItalianQueueV2.h>

#include <queue>

using namespace std;


void run_circular_queue() {

    cout << endl;
    cout << "**** RUNNING CIRCULAR QUEUE  ****" << endl;
    cout << endl;

    cout << "Starting" << endl;
    my::CircularQueue q(7);

    cout << "is queue empty? " << (q.isEmpty() ? "true" : "false") << endl;
    q.enqueue('a');
    cout << "top of the queue: " << q.top() << endl;
    cout << "is queue empty? " << (q.isEmpty() ? "true" : "false") << endl;
    q.enqueue('b');
    cout << "top of the queue: " << q.top() << endl;
    q.enqueue('c');
    q.enqueue('d');
    q.enqueue('e');
    char x = q.dequeue();  // a
    cout << "got " << x << endl;  // a
    q.dequeue();   // b
    q.enqueue('f'); 
    q.enqueue('g');
    q.enqueue('h');
    q.enqueue('i');
    try {        
        q.enqueue('z');
    } catch (std::runtime_error& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };
    q.dequeue();  // c
    q.dequeue();  // d
    q.dequeue();  // e
    q.dequeue();  // f
    q.dequeue();  // g
    q.dequeue();  // h
    cout << "is queue empty? " << (q.isEmpty() ? "true" : "false") << endl;
    q.dequeue();  // i

    cout << "is queue empty? " << (q.isEmpty() ? "true" : "false") << endl;
    try {
        q.dequeue();
    } catch (std::runtime_error& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };

    cout << "end of the program!" << endl;

    
}

void run_italian_queue(ItalianQueueV1<string>* pq){ 

    cout << *pq << endl; 
    
    //ItalianQueue:
    //
    //    _head: None
    //    _tail: None
    //   tails_: {
    //           }

    pq->enqueue("a","x");   // "a" is the element,"x" is the group
    cout << *pq << endl; 

    // ItalianQueue: a
    //               x
    //               _head: Node(a,x)
    //               _tail: Node(a,x)
    //              tails_: {
    //                         x : Node(a,x)
    //                      }

    pq->enqueue("c","y");    // "c" belongs to new group "y", goes to the end of the queue
    cout << *pq << endl; 

    // ItalianQueue: a->c
    //               x  y
    //               _head: Node(a,x)
    //               _tail: Node(c,y)
    //              tails_: {
    //                        y : Node(c,y),
    //                        x : Node(a,x)
    //                      }
    
    pq->enqueue("d","y");    // "d" belongs to existing group "y", goes to the end of the group
    cout << *pq << endl; 
    // ItalianQueue: a->c->d
    //               x  y  y
    //        _head: Node(a,x)
    //        _tail: Node(d,y)
    //       tails_: {
    //                 y : Node(d,y),
    //                 x : Node(a,x)
    //               }    

    pq->enqueue("b","x");    // "b" belongs to existing group "x", goes to the end of the group
    cout << *pq << endl; 
    // ItalianQueue: a->b->c->d
    //               x  x  y  y
    //        _head: Node(a,x)
    //        _tail: Node(d,y)
    //      tails_: {
    //                 y : Node(d,y),
    //                 x : Node(b,x)
    //              }

    pq->enqueue("f","z");    // "f" belongs to new group, goes to the end of the queue
    cout << *pq << endl; 
    // ItalianQueue: a->b->c->d->f
    //               x  x  y  y  z
    //        _head: Node(a,x)
    //        _tail: Node(f,z)
    //       tails_: {
    //                 z : Node(f,z),
    //                 y : Node(d,y),
    //                 x : Node(b,x)
    //               }

    pq->enqueue("e","y");   // "e" belongs to an existing group "y", goes to the end of the group
    cout << *pq << endl; 
    //  ItalianQueue: a->b->c->d->e->f
    //                x  x  y  y  y  z
    //         _head: Node(a,x)
    //         _tail: Node(f,z)
    //        tails_: {
    //                  z : Node(f,z),
    //                  y : Node(e,y),
    //                  x : Node(b,x)
    //                }

    cout << "pq->tail(): " << pq->tail() << endl;   // f
    cout << "pq->tail_group(): " << pq->tail_group() << endl; // z
    cout << "pq->top(): " << pq->top() << endl;     // a
    cout << "pq->top_group(): " << pq->top_group() << endl;  // x
    cout << "pq->size(): " << pq->size() << endl;  // 6

    pq->enqueue("g","z");   // "g" belongs to an existing group "z", goes to the end of the group
    cout << *pq << endl; 
    //  ItalianQueue: a->b->c->d->e->f->g
    //                x  x  y  y  y  z  z
    //         _head: Node(a,x)
    //         _tail: Node(g,z)
    //        tails_: {
    //                  z : Node(g,z),
    //                  y : Node(e,y),
    //                  x : Node(b,x)
    //                }


    pq->enqueue("h","z");  // "h" belongs to an existing group "z", goes to the end of the group
    cout << *pq << endl; 
    //  ItalianQueue: a->b->c->d->e->f->g->h
    //                x  x  y  y  y  z  z  z
    //         _head: Node(a,x)
    //         _tail: Node(h,z)
    //        tails_: {
    //                   z : Node(h,z),
    //                   y : Node(e,y),
    //                   x : Node(b,x)
    //                }    

    pq->enqueue("h","z");   //  'h' belongs to an existing group 'z', goes at the end of the group
    cout << *pq << endl; 
    //    ItalianQueue: a->b->c->d->e->f->g->h->h
    //                  x  x  y  y  y  z  z  z  z
    //                  head_: Node(a,x)
    //                  tail_: Node(h,z)
    //                 tails_: {
    //                           z : Node(h,z),
    //                           y : Node(e,y),
    //                           x : Node(b,x)
    //                         }


    // Dequeue is always from the head, without taking in consideration the group:
    pq->dequeue();
    // "a"
    cout << *pq << endl; 
    // ItalianQueue: b->c->d->e->f->g->h->h
    //               x  y  y  y  z  z  z  z
    //        head_: Node(b,x)
    //        tail_: Node(h,z)
    //        tails_: {
    //                  z : Node(h,z),
    //                  y : Node(e,y),
    //                  x : Node(b,x)
    //                }

    pq->dequeue();
    // "b"
    cout << *pq << endl; 
    // ItalianQueue: c->d->e->f->g->h->h
    //               y  y  y  z  z  z  z
    //        head_: Node(c,y)
    //        tail_: Node(h,z)    
    //        tails_: {
    //                  z : Node(h,z),
    //                  y : Node(e,y)
    //                }

    pq->dequeue();
    // "c"
    cout << *pq << endl; 
    // ItalianQueue: d->e->f->g->h->h
    //               y  y  z  z  z  z
    //        head_: Node(d,y)
    //        tail_: Node(h,z)
    //     tails_: {
    //               z : Node(h,z),
    //               y : Node(e,y)
    //             }

    }


/** 
 * - a std::deque allows 
 *   - fast O(1) insertion / removal at both ends,
 *   - fast O(1) internal read/write with operator[]
 *   - Internal insertion / removal are O(n)
*/  
void run_std_deque_example(){
    cout << endl;
    cout << "--- std::deque" << endl;
    deque<char> q;    
    q.push_back('a');
    q.push_back('b');
    q.push_back('c');
    q.push_back('d');
    q.push_back('e');

    cout << "q[0]: " << q[0] << endl;  // a
    cout << "q[1]: " << q[1] << endl;  // b
    cout << "q[2]: " << q[2] << endl;  // c 
    cout << "q[3]: " << q[3] << endl;  // d
    cout << "q[4]: " << q[4] << endl;  // e

    cout << "q.back(): " << q.back() << endl;    // e
    cout << "q.front(): " << q.front() << endl;  // a 
    
    cout << "calling q.pop_front()" << endl;
    q.pop_front();   // NOTE: returns void
    cout << "q.back(): " << q.back() << endl;    // e
    cout << "q.front(): " << q.front() << endl;  // b
    
    cout << "calling q.pop_back()" << endl;
    q.pop_back();   // NOTE: returns void
    cout << "q.back(): " << q.back() << endl;    // d
    cout << "q.front(): " << q.front() << endl;  // b

    cout << "writing q[0] = 'x'" << endl;
    q[0] = 'x';   
    cout << "writing q[1] = 'y'" << endl;
    q[1] = 'y';   // can write inside
    cout << "writing q[2] = 'z'" << endl;
    q[2] = 'z';   
    cout << "q.back(): " << q.back() << endl;    // z
    cout << "q.front(): " << q.front() << endl;  // x

    cout << "Initializing deque<char> q2 = {'a','b','c','d'}" << endl;
    deque<char> q2 = {'a','b','c'};

    cout << "Iterating with for each construct" << endl;
    for (char el : q2){
        cout << el << endl;          
    }
    // a
    // b
    // c
}


int main() {
    run_circular_queue();
    
    cout << "---- ItalianQueueV1" << endl;
    ItalianQueueV1<string> q1 = ItalianQueueV1<string>();    
    run_italian_queue(&q1);

    
    cout << "---- ItalianQueueV2" << endl;
    ItalianQueueV2<string> q2 = ItalianQueueV2<string>();
    run_italian_queue(&q2);
        
    run_std_deque_example();
}

