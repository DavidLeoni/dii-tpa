#include <iostream>
#include <stdexcept>

#include "Stack.h"
#include "BasicStack.h"
#include "CappedStack.h"


using namespace std;


template<typename T>
string vec2str(vector<T> v){
    std::stringstream ss;
    for (int i = 0; i < v.size(); i++){
        ss << v[i];
    }
    return ss.str();
}

void run_vector_example(){

    cout << endl;
    cout << "------ VECTOR EXAMPLE" << endl;
        // for printing
    cout << "Example to convert any basic type to string" << endl;
    std::stringstream ss;
    ss << 'a';
    ss << 4;
    ss << "ciao";
    string s = ss.str();  // ar4ciao
    cout << s << endl;
    
    // our vector, we need to specify wihch type contains
    // here we chose char but could be any
    vector<char> vec;
    
    vec.push_back('a');
    vec.push_back('b');
    vec.push_back('c');
    vec.push_back('d');
    vec.push_back('e');
    vec.push_back('f');
    vec.push_back('g');
    vec.push_back('h');
    
    cout << "vec: " << vec2str(vec) << endl;
    
    cout << "vec.size(): " << vec.size() << endl;  // 8
    
    cout << "access element 0: "  << vec[0] << endl;  // a
    
    cout << "get a new subvector from index 3 *included* to 5 *excluded*: " << endl;
    vector<char> subvec1 = {vec.begin() + 3, vec.begin() + 5};
    
    cout << "subvec1: " << vec2str(subvec1) << endl;  // de
    
    cout << "get a new subvector from index 3 *included* to end:" << endl;
    vector<char> subvec2 = {vec.begin() + 3, vec.end()};
    
    cout << "subvec2: " << vec2str(subvec2) << endl;  // defgh
    
    cout << "cut vec to 3 elements:" << endl;
    vec.resize(3);
    
    cout << "vec: " << vec2str(vec) << endl;  // abc
    
    cout << "vec: vec.back(): " << vec.back() << endl;
    
    cout << "for each construct" << endl;
    // at each iteration, assigns variable c to a *copy* of element of vector
    vector<char> v = {'a','c','b','e'};
    for (char c : v){
        cout << c << endl;        
    }
    cout << endl;
    // a
    // c
    // b
    // e

    cout << "for each construct, no reference" << endl;
    for (char c : v){
        c = 'z';  // c is a copy, does *not* change characters inside v!        
    }
    for (char c : v){
        cout << c << endl;        
    }
    // a
    // c
    // b
    // e

    cout << "for each construct with reference" << endl;
    for (char& cr : v){  // note the &     
        cr = 'z';  // Reference can change characters inside v
    }
    for (char c : v){
        cout << c << endl;     
    }

    // z
    // z
    // z
    // z
    
    cout << "for each on regular arrays" << endl;
    // works also on regular arrays (ONLY IF compiler knows the dimension)
    char prova[3] = {'a','b','c'};
    for (char& c : prova){
        cout << c << endl;        
    }

    cout << endl;
    // a
    // b
    // c   
}

void run_basic_stack(){
    cout << endl;
    cout << "-----  BASIC STACK" << endl;    

    BasicStack<char> bs;

    Stack<char>* ps1 = &bs;
    cout << ps1->as_string() << endl;  // BasicStack: elements=
    ps1->push('a');
    cout << ps1->as_string() << endl;  // BasicStack: elements=a
    cout << ps1->peek() << endl;       // 'a'
    ps1->push('b');
    cout << ps1->peek() << endl;       // 'b'
    cout << ps1->as_string() << endl;  // BasicStack: elements=ab
    cout << ps1->peek() << endl;       // 'b'
    ps1->push('c');                    
    cout << ps1->peek() << endl;       // 'c'
    cout << ps1->as_string() << endl;  // BasicStack: elements=abc
    cout << ps1->pop() << endl;        // 'c'
    cout << ps1->pop() << endl;        // 'b'
    cout << ps1->as_string() << endl;  // BasicStack: elements=a
    cout << ps1->pop() << endl;        // 'a'
    
    try {
        ps1->pop(); //  can't pop empty stack
    } catch (std::runtime_error& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };

    try {
        ps1->peek(); // can't peek empty stack
    } catch (std::runtime_error& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };

    cout << endl;
    cout << "-----  RESETTING BASIC STACK" << endl;    
    bs = BasicStack<char>();
    ps1->push('a');
    ps1->push('b');
    ps1->push('c');
    ps1->push('d');
    ps1->push('e');
    cout << ps1->as_string() << endl;           // abcde
    cout << vec2str(ps1->peekn(3)) << endl;     // cde
    cout << vec2str(ps1->peekn(5)) << endl;     // abcde
    try {
        cout << vec2str(ps1->peekn(6)) << endl;    // error
    } catch (std::invalid_argument& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };

    cout << ps1->as_string() << endl;        // abcde
    cout << vec2str(ps1->popn(3)) << endl;   // cde
    cout << ps1->as_string() << endl;        // ab

}

void run_capped_stack(){
    
    cout << endl;
    cout << "-----  CAPPED STACK" << endl;    

    CappedStack<char> cs = CappedStack<char>(2);

    Stack<char>* ps2 = &cs;
    cout << ps2->as_string() << endl;  // CappedStack: cap=2 elements=
    ps2->push('a');
    cout << ps2->as_string() << endl;  // CappedStack: cap=2 elements=a
    cout << ps2->peek() << endl;       // 'a'
    ps2->push('b');
    cout << ps2->peek() << endl;       // 'b'
    cout << ps2->as_string() << endl;  // CappedStack: cap=2 elements=ab
    cout << ps2->peek() << endl;       // 'b'
    ps2->push('c');                    //  exceeds cap, gets silently discarded
    cout << ps2->as_string() << endl;  // no c here:    CappedStack: cap=2 elements=ab
    cout << ps2->pop() << endl;        // 'b'
    cout << ps2->as_string() << endl;  // CappedStack: cap=2 elements=a
    cout << ps2->pop() << endl;        // 'a'
    
    try {
        ps2->pop(); //  can't pop empty stack
    } catch (std::runtime_error& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };

    try {
        ps2->peek(); // can't peek empty stack
    } catch (std::runtime_error& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };

    cout << endl;
    cout << "-----  RESETTING CAPPED STACK" << endl;    
    cs = CappedStack<char>(10);
    ps2->push('a');
    ps2->push('b');
    ps2->push('c');
    ps2->push('d');
    ps2->push('e');
    cout << ps2->as_string() << endl;          // abcde
    cout << vec2str(ps2->peekn(3)) << endl;    // cde
    cout << vec2str(ps2->peekn(5)) << endl;    // abcde
    try {
        cout << vec2str(ps2->peekn(6)) << endl;    // error
    } catch (std::invalid_argument& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };

    cout << ps2->as_string() << endl;  // abcde
    cout << vec2str(ps2->popn(3)) << endl;      // cde
    cout << ps2->as_string() << endl;  // ab

    cout << endl;
    cout << "-----  RESETTING CAPPED STACK" << endl;    
    cs = CappedStack<char>(10);
    ps2->push('a');
    ps2->push('b');
    ps2->push('c');
    ps2->push('d');
    ps2->push('e');

    // need casting here
    ((CappedStack<char>*) ps2)->set_cap(5); // limit, shouldn't change
    cout << ps2->as_string() << endl;  // abcde
    ((CappedStack<char>*) ps2)->set_cap(3);  // cutting characters in excess
    cout << ps2->as_string() << endl;  // abc

}



int main () {

    run_vector_example();
    
    run_basic_stack();

    run_capped_stack();


    return 0;
};
