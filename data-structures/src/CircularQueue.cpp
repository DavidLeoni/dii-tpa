
#include "circular_queue.h"
#include <cmath>
#include "iostream"


my::CircularQueue::CircularQueue(int capacity){
    //jupman-raise                                
    if (capacity <= 0){
        throw std::invalid_argument(std::string("Expected positive capacity, found instead: ") + std::to_string( capacity));
    }

    this->arr = new char[capacity];  // Creates array of capacity objects, fills it with zeroes TODO
    this->head = 0;
    this->size = 0;
    this->capacity = capacity;

    ///jupman-raise
}

my::CircularQueue::~CircularQueue(){
    std::cout << "Destructor is being called ..." << std::endl;
    delete this->arr;
    std::cout << "End of destructor ..." << std::endl;
}
                        
                
 
int my::CircularQueue::get_size(){
    //jupman-raise
    return this->size;
    ///jupman-raise
}


 int my::CircularQueue::get_capacity(){
    //jupman-raise
    return this->capacity;
    ///jupman-raise
}

bool my::CircularQueue::isEmpty(){
    
    //jupman-raise
    return this->size == 0;
    ///jupman-raise
}

char my::CircularQueue::top(){
    //jupman-raise
    if (this->size > 0){
        return this->arr[this->head];
    } else {
        throw std::runtime_error("Queue is empty !");    
    }
    ///jupman-raise
}


void my::CircularQueue::enqueue(char v){                                
    std::cout << "DEBUG: enqueing " << v << std::endl;

    //jupman-raise                
    if (this->size < this->capacity){
        this->arr[(this->head + this->size) % this->capacity ] = v;
        this->size += 1;
    } else {
        throw std::runtime_error("Queue is full !");
    }            
    ///jupman-raise
}

char my::CircularQueue::dequeue(){
    std::cout << "DEBUG: dequeuing ";
    //jupman-raise
    if (this->size > 0){
        char temp = this->arr[this->head];
        this->head = (this->head + 1) % this->capacity;
        this->size -= 1;
        std::cout << temp << std::endl;
        return temp;
    } else {
        std::cout << std::endl;
        throw std::runtime_error("Queue is empty !");
    }
    ///jupman-raise
}
    

