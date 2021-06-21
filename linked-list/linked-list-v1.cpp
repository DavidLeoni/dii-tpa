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


/** LinkedList - returns a NEW empty LinkedList

    HINT: remember to use  new operator!
*/
LinkedList* init(){
    // write here

};

/** Return true if the list is empty, false otherwise            
*/
bool is_empty(LinkedList* ll){
    // write here

}

/** Adds item at the beginning of the list   
*/                
void add(LinkedList* ll, const char * label){    
    debug(string("adding ") + label );

    // write here

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
            
    // write here

    Node* current = ll->head;

    while (current != NULL){
        // fai qualcosa con current
        //current->label

        current = current->next;
    }

}

/**  Returns the size of the list 
 */
int size(LinkedList* ll){
    
    // write here

} 

/**
 *  Returns true if label is present in list, false otherwise       
    HINT: per comparare usare strcmp del C RICORDANDOSI  che 
          se trova due stringhe uguali ritorna ZERO
*/
bool search(LinkedList* ll, const char * label){
                
    // write here

}

/*
    Removes the last item of the list, and returns its label

    - If the list is empty, write

        throw std::invalid_argument( "empty list!" );

      to stop function (and program) excecution (needs #include <stdexcept>)
*/        
const char* pop(LinkedList* ll){
        
    debug("popping last item...");

    // write here
}


/** Appends label to the end of the list.
*/                
void append(LinkedList* ll, const char* label){    
}


/**
    Remove first occurrence of item from the list

    - If label is not found, throw std::invalid_argument                    
*/
void remove(LinkedList* ll, const char * label){
}


/* Insert an item at a given position. 

    - if index is out of bounds, throw std::invalid_argument   
*/
void insert(LinkedList* ll, int i, const char * e){
}
    


/*
    Deletes all nodes in the chain    
    Careful about deletion order!
*/
void destroy(LinkedList* ll){    
    
    // write here
    

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
   

/* OUTPUT ATTESO

DEBUG: adding a
DEBUG: adding b
DEBUG: adding c
LinkedList: c,b,a
size:3
DEBUG: adding d
LinkedList: d,c,b,a
size:4
search(ll,"a"): true
search(ll,"z"): false
DEBUG: popping last item...
a
LinkedList: d,c,b
DEBUG: popping last item...
b
LinkedList: d,c
DEBUG: popping last item...
c
LinkedList: d
DEBUG: popping last item...
d
LinkedList:
destroyed

*/