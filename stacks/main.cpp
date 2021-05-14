#include <iostream>
#include <stdexcept>

#include "Stack.h"
#include "BasicStack.h"
#include "CappedStack.h"


using namespace std;


int main () {
    
    cout << endl;
    cout << "-----  BASIC STACK" << endl;    

    BasicStack bs = BasicStack();

    Stack* ps1 = &bs;
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
    bs = BasicStack();
    ps1->push('a');
    ps1->push('b');
    ps1->push('c');
    ps1->push('d');
    ps1->push('e');
    cout << ps1->as_string() << endl;  // abcde
    cout << ps1->peekn(3) << endl;     // cde
    cout << ps1->peekn(5) << endl;     // abcde
    try {
        cout << ps1->peekn(6) << endl;    // error
    } catch (std::invalid_argument& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };

    cout << ps1->as_string() << endl;  // abcde
    cout << ps1->popn(3) << endl;      // cde
    cout << ps1->as_string() << endl;  // ab


    cout << endl;
    cout << "-----  CAPPED STACK" << endl;    

    CappedStack cs = CappedStack(2);

    Stack* ps2 = &cs;
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
    cs = CappedStack(10);
    ps2->push('a');
    ps2->push('b');
    ps2->push('c');
    ps2->push('d');
    ps2->push('e');
    cout << ps2->as_string() << endl;  // abcde
    cout << ps2->peekn(3) << endl;     // cde
    cout << ps2->peekn(5) << endl;     // abcde
    try {
        cout << ps2->peekn(6) << endl;    // error
    } catch (std::invalid_argument& ex) {
        cout << "something bad happened!" << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    };

    cout << ps2->as_string() << endl;  // abcde
    cout << ps2->popn(3) << endl;      // cde
    cout << ps2->as_string() << endl;  // ab

    cout << endl;
    cout << "-----  RESETTING CAPPED STACK" << endl;    
    cs = CappedStack(10);
    ps2->push('a');
    ps2->push('b');
    ps2->push('c');
    ps2->push('d');
    ps2->push('e');

    // need casting here
    ((CappedStack*) ps2)->set_cap(5); // limit, shouldn't change
    cout << ps2->as_string() << endl;  // abcde
    ((CappedStack*) ps2)->set_cap(3);  // cutting characters in excess
    cout << ps2->as_string() << endl;  // abc


    return 0;
};
