#include <iostream>
#include <stdexcept>

#include <circular_queue.h>
#include <ItalianQueueV1.h>

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

    pq->enqueue("a","x");   // "a" is the element,"x" is the group
    cout << *pq << endl; 

    // ItalianQueue: a
    //               x
    //               _head: Node(a,x)
    //               _tail: Node(a,x)
    pq->enqueue("c","y");    // "c" belongs to new group "y", goes to the end of the queue
    cout << *pq << endl; 

    // ItalianQueue: a->c
    //               x  y
    //               _head: Node(a,x)
    //               _tail: Node(c,y)
    pq->enqueue("d","y");    // "d" belongs to existing group "y", goes to the end of the group
    cout << *pq << endl; 
    // ItalianQueue: a->c->d
    //               x  y  y
    //        _head: Node(a,x)
    //        _tail: Node(d,y)
    

    pq->enqueue("b","x");    // "b" belongs to existing group "x", goes to the end of the group
    cout << *pq << endl; 
    // ItalianQueue: a->b->c->d
    //               x  x  y  y
    //        _head: Node(a,x)
    //        _tail: Node(d,y)
    pq->enqueue("f","z");    // "f" belongs to new group, goes to the end of the queue
    cout << *pq << endl; 
    // ItalianQueue: a->b->c->d->f
    //               x  x  y  y  z
    //        _head: Node(a,x)
    //        _tail: Node(f,z)
    pq->enqueue("e","y");   // "e" belongs to an existing group "y", goes to the end of the group
    cout << *pq << endl; 
    //  ItalianQueue: a->b->c->d->e->f
    //                x  x  y  y  y  z
    //         _head: Node(a,x)
    //         _tail: Node(f,z)

    cout << "pq->tail(): " << pq->tail() << endl;
    cout << "pq->tail_group(): " << pq->tail_group() << endl;
    cout << "pq->top(): " << pq->top() << endl;
    cout << "pq->top_group(): " << pq->top_group() << endl;
    cout << "pq->size(): " << pq->size() << endl;

    pq->enqueue("g","z");   // "g" belongs to an existing group "z", goes to the end of the group
    cout << *pq << endl; 
    //  ItalianQueue: a->b->c->d->e->f->g
    //                x  x  y  y  y  z  z
    //         _head: Node(a,x)
    //         _tail: Node(g,z)
    pq->enqueue("h","z");  // "h" belongs to an existing group "z", goes to the end of the group
    cout << *pq << endl; 
    //  ItalianQueue: a->b->c->d->e->f->g->h
    //                x  x  y  y  y  z  z  z
    //         _head: Node(a,x)
    //         _tail: Node(h,z)
    
    // Dequeue is always from the head, without taking in consideration the group:
    pq->dequeue();
    // "a"
    cout << *pq << endl; 
    // ItalianQueue: b->c->d->e->f->g->h
    //               x  y  y  y  z  z  z
    //        _head: Node(b,x)
    //        _tail: Node(h,z)
    pq->dequeue();
    // "b"
    cout << *pq << endl; 
    // ItalianQueue: c->d->e->f->g->h
    //               y  y  y  z  z  z
    //        _head: Node(c,y)
    //        _tail: Node(h,z)
    pq->dequeue();
    // "c"
    cout << *pq << endl; 
    }

int main() {
    //run_circular_queue();

    ItalianQueueV1<string> q1 = ItalianQueueV1<string>();    
    run_italian_queue(&q1);
}
