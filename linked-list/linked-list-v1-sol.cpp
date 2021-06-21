#include <iostream>
#include <string.h>
#include <stdexcept>

using namespace std;


void debug(string msg){
    cout << "DEBUG: " << msg << endl;
}

/*
    A Node of an LinkedList. 

    Nodes are never returned by functions
 */

struct Node {
        
    const char* label = NULL;
    Node* next = NULL;
};

/** Holds only one pointer to the first node
*/
struct LinkedList {

    Node* head = NULL;
};


// LinkedList - eturns a NEW empty LinkedList

LinkedList* init(){
    return new LinkedList;
};

/** Return true if the list is empty, false otherwise            
*/
bool is_empty(LinkedList* ll){
    return ll->head == NULL;
}

/** Adds item at the beginning of the list   
*/                
void add(LinkedList* ll, const char * label){    
    debug(string("adding ") + label );

    Node *new_head = new Node;
    new_head->label = label;
    new_head->next = ll->head;
    ll->head = new_head;
}


/** For potentially complex data structures like this one, having a to_string function 
 *  is essential to  quickly inspect the label by printing it. 
 * 
 *  Note string to return has c++ type  string 
 * 
 *  - To initialize a c++ string, you can just set it to some like
 * 
 *      string s = "some characters"
 * 
 *  - To augment the string, you can write:
 * 
 *      s += "some characters"
*/
string to_string(LinkedList* ll) {
            
    const char prep[] = "LinkedList: ";

    string s = prep;    

    Node* current = ll->head;

    while (current != NULL){        
        s += current->label;         
        s += ',';        
        current = current->next;
    }    
    s.resize(s.length()-1);
    return s;
}

/**  Returns the size of the list 
 */
int size(LinkedList* ll){
    
    Node* current = ll->head;
    int count = 0;
    
    while (current != NULL){
        current = current->next;
        count += 1;
    }

    return count;
} 

/**
 *  Returns true if label is present in list, false otherwise              
*/
bool search(LinkedList* ll, const char * label){
                
    Node* current = ll->head;
    
    while (current != NULL){
        if (strcmp(current->label, label)==0){
            return true;
        } else {
            current = current->next;
        }            
    }

    return false;
}

/*
    Removes the last item of the list, and returns its label

    - If the list is empty, throw std::invalid_argument.      
*/        
const char* pop(LinkedList* ll){
        
    debug("popping last item...");
    if (ll->head == NULL){
         throw std::invalid_argument( "empty list!" );
    } else {
        
        Node* current = ll->head;
        const char* last_item;
        Node* prev;

        if (current->next == NULL){   // one element list
            last_item = ll->head->label;
            delete ll->head;
            ll->head = NULL;
        } else {    // we have more than one element
            prev = NULL;
            while (current->next != NULL) {  // current will reach last element
                prev = current;
                current = current->next; 
            }                      
            last_item = current->label;
            delete prev->next;
            prev->next = NULL;
        }   
        return last_item;
    }
}

/*
    Deletes all nodes in the chain    
    Careful about deletion order!
*/
void destroy(LinkedList* ll){    
    
    Node* current = ll->head;

    while (current != NULL){
        Node* to_delete = current;
        current = current->next;
        delete to_delete;
    }    
}

int main(int, char**) {

    LinkedList* ll = init();

    add(ll, "a");
    add(ll, "b");
    add(ll, "c");

        
    cout << to_string(ll) << endl;

    cout << "size:" << size(ll) << endl;

    add(ll, "d");

    cout << to_string(ll) << endl;

    cout << "size:" << size(ll) << endl;


    cout << "search(ll,\"a\"): " << (search(ll, "a") ? "true" : "false") << endl;

    cout << "search(ll,\"z\"): " << (search(ll, "z")  ? "true" : "false") << endl;

    cout << pop(ll) << endl;    
    
    cout << to_string(ll) << endl;

    cout << pop(ll) << endl;    

    cout << to_string(ll) << endl;

    cout << pop(ll) << endl;    
    
    cout << to_string(ll) << endl;

    cout << pop(ll) << endl;    
    
    cout << to_string(ll) << endl;

    // to test exception
    // cout << pop(ll) << endl;            

    destroy(ll);

    cout << "destroyed"  << endl;    

} 