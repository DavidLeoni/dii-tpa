#ifndef MULTISET_H
#define MULTISET_H



#include <stdexcept>
#include <string>
#include <sstream>

#include <iostream>
#include <unordered_map>


using std::unordered_map;
using std::to_string;
using std::string;
using std::cout;
using std::endl;


/* A multiset (or bag) generalizes a set by allowing multiple instances of the multiset's elements. 

    The multiplicity of an element is the number of instances of the element in a specific multiset.

    For example:

        The multiset "a, b"  contains only elements 'a' and 'b', each having multiplicity 1
        In multiset "a, a, b",  'a' has multiplicity 2 and 'b' has multiplicity 1
        In multiset "a, a, a, b, b, b", 'a' and 'b' both have multiplicity 3

    Notice order of insertion does *not* matter, so "a, a, b" and "a, b, a" are the same multiset,
    where 'a' has multiplicity 2 and 'b' has multiplicity 1.


*/
template<typename T>
class MultiSet{

    private:
        std::unordered_map<char,int> umap;

    public: 
    
        /** Initializes the MultiSet as empty.
        */
        MultiSet(){
            //jupman-raise
            this->umap = {};
            ///jupman-raise
        }

        /** Adds one instance of element el to the multiset 

            MUST run in O(1)        
        */
        void add(const T el){
            
            //jupman-raise
            cout << "DEBUG: adding " << el << endl;
            if (this->umap.count(el) == 1){
                this->umap[el] += 1;
            } else {
                this->umap[el] = 1;
            }            
            ///jupman-raise
        }

        /**
         *  RETURN the multiplicity of element el in the multiset
                
            - If no instance of el is present, return 0.

            MUST run in O(1)        
            
        */    
        int get(const T el) const {
            
            //jupman-raise
            if (this->umap.count(el) == 1){
                return this->umap.at(el);
            } else {
                return 0;
            }
            ///jupman-raise
        }

        /** Removes n instances of element el from the multiset (that is, reduces el multiplicity by n) 
                
                If n is negative, throws std::invalid_argument            
                If n represents a multiplicity bigger than el current multiplicity, throws std::out_of_range
                
                NOTE: multiset multiplicities are never negative
                MUST run in O(1)
        */
        void removen(const T el, const int n){
            
            //jupman-raise
            cout << "DEBUG: removing " << el << "," << to_string(n) << endl;
            if (n < 0){
                throw std::invalid_argument("Provided n is negative: " + to_string(n));
            }

            if (n == 0){
                return;
            }

            int current;
            if (this->umap.count(el) == 1){
                current = this->umap[el];
            } else {
                current = 0;
            }

            if (current < n){
                throw std::out_of_range(string("Tried to remove ")  + to_string(n) + "  elements, but only " +  to_string(current) + " were found");
            } else if (current == n && this->umap.count(el) == 1){
                this->umap.erase(el);  // small optimization to remove elements with 0 cardinality
            } else {
                this->umap[el] = current - n;
            }            
            ///jupman-raise
        }        

        string as_string() const {
            std::stringstream ss;

            bool first = true;                                                    
            ss << "{" << endl;
            for (std::pair<char, int> element : this->umap) {
               
               if (!first){
                   ss << "," << endl;
               }
               ss << "    {" << element.first << " , " << element.second << "}";               
               first = false;
            }
            ss << endl << "}";
            return ss.str();
        }

        /**
         * RETURN the number of elements within the multiset (sum of all multiplicites)
         * 
         * MUST run in O(k) where k is the number of keys
        */
        int size() const {
            int ret = 0;
            for (std::pair<char, int> element : this->umap) {
                ret += element.second;
            }
            return ret;
        }
};

#endif // MULTISET_H
