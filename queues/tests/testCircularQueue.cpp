#include "circular_queue.h"
#include "catch2/catch2.hpp"


using namespace my;

TEST_CASE ("capacity shouldn't be negative", "[CircularQueue][constructor]"){        
    REQUIRE_THROWS_AS( CircularQueue(-2), std::invalid_argument);                    
}    


TEST_CASE ("capacity shouldn't be zero", "[CircularQueue][constructor]"){        
    REQUIRE_THROWS_AS( CircularQueue(-0), std::invalid_argument);                    
}        
            
TEST_CASE ("capacity of one", "[CircularQueue][constructor]"){

    CircularQueue q (1);
    REQUIRE(q.get_capacity() == 1);
    REQUIRE(q.isEmpty());
}

TEST_CASE ("capacity of two", "[CircularQueue][constructor]"){
    REQUIRE(CircularQueue(2).get_capacity() == 2);
}


TEST_CASE ("exceed capacity", "[CircularQueue][enqueue]"){
    
        CircularQueue q(1);
        q.enqueue('a');
        REQUIRE(!q.isEmpty());
                
        REQUIRE_THROWS_AS( q.enqueue('b'), std::runtime_error);
}

TEST_CASE ("no enqueue empty", "[CircularQueue][enqueue]"){
    
        CircularQueue q(5);
                
        REQUIRE(q.get_size() == 0);
        REQUIRE_THROWS_AS(q.top(), std::runtime_error);        
            
}

TEST_CASE ("enqueue simple", "[CircularQueue][enqueue]"){
        CircularQueue q(5);
                
        q.enqueue('a');               
        REQUIRE(q.top() == 'a');
        REQUIRE(q.get_size() == 1);
        q.enqueue('b');
        REQUIRE(q.top() == 'a');
        REQUIRE(q.get_size() == 2);
}

TEST_CASE ("enqueue circular", "[CircularQueue][enqueue]"){
        CircularQueue q(2);    // 2 elements capacity  [head->None,None]

        q.enqueue('a');             // [head->a, None]                    
        REQUIRE(q.top() == 'a');
        REQUIRE(q.get_size() == 1);
        
        q.enqueue('b');                     // [head->a, b]
        REQUIRE(q.top() == 'a');
        REQUIRE(q.get_size() == 2);
        
        REQUIRE_THROWS_AS(q.enqueue('c'), std::runtime_error);
            
}  
        

TEST_CASE ("dequeue empty", "[CircularQueue][dequeue]"){
    
        CircularQueue q(5);
        
        REQUIRE_THROWS_AS(q.dequeue(), std::runtime_error);
};

TEST_CASE ("dequeue simple", "[CircularQueue][dequeue]"){

        CircularQueue q(5);        
        q.enqueue('a');                        // [head->a, None]
        q.enqueue('b');                       // [head->a, b]  
    
        REQUIRE(q.dequeue() == 'a');    // [a, head->b]
        REQUIRE(q.top() == 'b');
        REQUIRE(q.get_size() == 1);
        REQUIRE(q.dequeue() == 'b');    // [head->a, b]     
        REQUIRE(q.get_size() == 0);
}

TEST_CASE ("dequeue circular", "[CircularQueue][dequeue]"){    
        CircularQueue q(2);    // 2 elements capacity  [head->None,None]
        q.enqueue('z');  // [head->z,None]
        q.dequeue();     // so head is moved of 1 left [z,head->None]
        REQUIRE(q.get_size() == 0);

        q.enqueue('a');                     // [z,head->a]                    
        REQUIRE(q.top() == 'a');   
        REQUIRE(q.get_size() == 1);
        q.enqueue('b');              // [b,head->a]
        REQUIRE(q.top() == 'a');
        REQUIRE(q.get_size() == 2);
        
        REQUIRE(q.dequeue() == 'a'); // [head->b,a] 
        REQUIRE(q.top() == 'b');
        REQUIRE(q.get_size() == 1);
        REQUIRE(q.dequeue() == 'b'); // [b,head->a]
        REQUIRE(q.get_size() == 0);
}
