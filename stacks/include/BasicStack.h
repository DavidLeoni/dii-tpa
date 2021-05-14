#ifndef BASIC_STACK_H
#define BASIC_STACK_H

#include <iostream>

#include <Stack.h>

class BasicStack : public Stack {
    
    protected:
        string elements;

    public:

        virtual int size() const;

        virtual string as_string() const;

        virtual bool is_empty() const;

        virtual void push(const char c);

        virtual char peek() const;

        virtual char pop();

        virtual string peekn(const int n) const;

        virtual string popn(const int n);

        /**
         * Creates an empty BasicStack                   
        */        
        BasicStack();


};



#endif  // BASIC_STACK_H
