#include <iostream>

#include "MultiSet.h"

using namespace std;

#include <Matrix.h>
#include <DenseMatrix.h>
#include <SparseMatrix.h>


using std::cout;
using std::endl;


void pair_example(){
    std::pair<char, int> mypair('a',48);
    cout << mypair.first << endl;  // a
    cout << mypair.second << endl;  // 48
}

void unordered_map_example(){
    cout << endl;
    cout << "----- UNORDERED MAP" << endl;

    // empty init
    std::unordered_map<char, int> umap;
    

    cout << "----  Setting key to a value" << endl;

    // Setting associations doesn't depend on map size so it's very fast. 
    // In technical terms we say it has O(1) computational complexity

    umap['a'] = 7;   
    umap['b'] = 4;
    umap['c'] = 5;

    // initializer list
    std::unordered_map<char, int> umap2 = {
        {'a', 7},
        {'b', 4},
        {'c', 5}
    };

    // size
    cout << "number of keys: " <<  umap.size() << endl;  // 3

    cout << "---- Getting values from keys" << endl;

    // Getting a value given a key is fast as well, retrieval is constant time O(1) 
    // and doesn't depend on map size
    // WARNING: [] operator is *NOT* a const method!
    cout << "reading umap['a']: " << umap['a'] << endl;  // 7

    cout << "size(): " << umap.size() << '\n';  // 3

    cout << "---- Getting non-present keys with [] doesn't give exception"  << endl;
    // When you use square brackets and item is not found, inserts item associated to default constructor for value, 
    // in this case 0 for int.  
    cout << "Reading non present key umap['z']: " << umap['z'] << endl;  // 0
    cout << "size(): " << umap.size() << endl;  // 4

    cout << "---- Getting non-present keys with .at() gives exceptions"  << endl;
    // If you don't what automatic insertion you can use .at() method, which raises an exception on missing key:
    // NOTE: at is a const method
    try {
        cout << umap.at('X') << '\n';  // not found, throws exception
    } catch (std::out_of_range& ex) {
       cout << "something bad happened!" << ex.what() << endl;
       cout << "I caught the exception, will continue" << endl;
    };
    cout << "size(): " << umap.size() << endl;  // 4
    cout << "reading umap['c']: " << umap['c'] << endl;  // 5
    cout << "umap['c']++"<< endl;   
    umap['c']++;
    cout << umap['c'] << endl;  // 6

    cout << "----  Iterating" << endl;

    // There are many ways to iterate stl collections, in unordered_map case a handy one 
    // is iterating through key/value pairs with a  range based for loop like this:

    // **WARNING 1**: order of iteration is **NOT** guaranteed! Never make assumptions about it!    

    for (std::pair<char, int> element : umap) {
        cout << element.first << " : " << element.second << endl;
    }
    
    
    cout << "----  Iterating and modifying without a reference" << endl;
    // **WARNING 2**: without a reference, element holds a *copy* of key/values taken from the map

    for (std::pair<char, int> element : umap) {
        element.second = 666;  // doesn't actually change umap
    }
    for (std::pair<char, int> element : umap) {
        cout << element.first << " : " << element.second << endl;
    }
    // c : 6
    // b : 4
    // z : 0
    // a : 7

    cout << "----  Iterating and modifying with a reference" << endl;
    //  WARNING: with a reference we can rewrite values *but not keys*, so we MUST put const in keys
    //  otherwise compiler complains
    for (std::pair<const char, int>& element : umap) {   // notice const and &
        // element.first = 'z'; // can't
        element.second = 123;  // now ok
    }
    for (std::pair<char, int> element : umap) {
        cout << element.first << " : " << element.second << endl;
    }
    // c : 123
    // b : 123
    // z : 123
    // a : 123


    cout << "---- Finding an element" << endl;

    // There are many ways to check whether or not an element is present,  we can use count which in this case takes constant time O(1) 
    char ch = 'a';
    cout << "umap.count(" << ch << "): " << umap.count(ch) << endl;
    if (umap.count(ch) == 1) {
        std::cout << "Found key '" << ch << "' with value " << umap[ch] << endl;
    } else {
        std::cout << "Key '" << ch << "' not found\n";
    }

    ch = 'z';
    cout << "umap.count(" << ch << "): " << umap.count(ch) << endl;
    if (umap.count(ch) == 1) {
        std::cout << "Found key " << ch << " with associated value " << umap[ch] << endl;
    } else {
        std::cout << "Key '" << ch << "' not found\n";
    }

    cout << "---- Erasing an association" << endl;

    cout << "umap.erase('a')" << endl;
    umap.erase('a');
    cout << "size: " << umap.size() << endl;    

    
    int ret = umap.erase('W');   // if key is not present returns a zero
    cout << "'W' not present, umap.erase('W') returns " << ret << endl;
    if (ret == 0){
        cout << "Couldn't erase 'W'"  << endl;
    }


    cout << " ---- MUTABLE KEYS test" << endl;
 
    string s = "ciao";
    //std::unordered_map<string&, int> umr;
    //umr[s] = 4;           // doesn't like string &

    std::unordered_map<string, int> um;
        
    um[s] = 4;
    cout << um[s] << endl;
    s += "mondo";        
    cout << um[s] << endl;
    //w += "borg";
    cout << um[s] << endl;
    cout << um["ciao"] << endl;
    
    //std::unordered_map<std::pair<int,int>, int> umpa; // pair not hashable
    //std::unordered_map<std::tuple<int,int>, int> umpa; // tuple not hashable

}

void multiset_example(){

    cout << endl;
    cout << " ----- MULTISET" << endl;
    MultiSet<char> m = MultiSet<char>();
    m.add('a');
    m.add('a');
    m.add('b');    
    cout << "a: " << m.get('a') << endl;  // a: 2 
    cout << "b: " << m.get('b') << endl;  // b: 1
    cout << "c: " << m.get('c') << endl;  // c: 0
    cout << "size: " << m.size() << endl; // 3
    cout << m.as_string() << endl;     

    m.removen('a', 2);
    cout << m.as_string() << endl;          
     // b: 1     // note no a:0 should be present

    m.removen('a',0);
    cout << m.as_string() << endl;         
    // b: 1      
    m.removen('b', 1);
    cout << m.as_string() << endl;     // empty

    m.removen('c',0);  // no problem
    cout << m.as_string() << endl;     // empty

    m.add('c');
    m.add('c');
    m.add('c');
    cout << m.as_string() << endl;     
    // c: 3
    try {
        m.removen('c',5);  // too many
    } catch (std::out_of_range& ex) {
       cout << "something bad happened!" << ex.what() << endl;
       cout << "I caught the exception, will continue" << endl;
    };
    cout << m.as_string() << endl;     
    // c: 2    

}


void conversions_example(){
    cout << endl;
    cout << "---- Conversions" << endl;
    cout << "pair2str(12,345): " << pair2str({12,345}) << endl;
    cout << "str2pair(\"12,345\"): " << pair2str(str2pair("12,345")) << endl;
    cout << "triplets2str<int>({{1,3,2}, {6,3,5}, {9,2,5}, {1,5,3}})"
         << triplets2str<int>({{1,3,2}, {6,3,5}, {9,2,5}, {1,5,3}}) << endl;
}

void dense_matrix_example(){

    cout << endl;
    cout << "---- DenseMatrix" << endl;
    vector<vector<int>> vmat = {  {0,6,8,0},
                                  {0,0,0,5},
                                  {9,0,7,0} };    

    cout << "dma = From vectors constructor:" << endl;
    DenseMatrix<int> dma = DenseMatrix<int>(vmat);
    Matrix<int>* pdma = &dma;
    cout << pdma->as_string() << endl;

    try {
        cout << "Trying to instantiate \n  DenseMatrix<int>({{1,2},\n                    {3,4,5}}) ..." << endl;
        DenseMatrix<int> zdm = DenseMatrix<int>({{1,2},
                                                 {3,4,5}});
    } catch(std::invalid_argument& ex){
        cout << "something bad happened! " << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    }
    
    cout << "dma.shape(): " << pair2str(dma.shape()) << endl;   // shape is a std::pair
    cout << "dma(1,3): " << dma(1,3) << endl;        
    cout << "dma(1,3) += 9" << endl;
    dma(1,3) += 9;
    cout << pdma->as_string() << endl; 

    cout << "dma.nonzero(): "<< triplets2str(dma.nonzero()) << endl;
    
    cout << endl;
    cout << "dmb = From triplets constructor:" << endl;
    Triplet<int> triplets[] = {{1,3,5},{2,1,8},{2,3,0},{2,0,-9},{0,0,7}};
    DenseMatrix<int> dmb = DenseMatrix<int>(3,4, triplets, 5);
    Matrix<int>* pdmb = &dmb;
    cout << pdmb->as_string() << endl;
        

    cout << endl;
    cout << "dmc = dma + dmb:" << endl;
    DenseMatrix<int> dmc = dma + dmb; 

    Matrix<int>* pdmc = &dmc;
    cout << pdmc->as_string() << endl;

    cout << "Trying + with different dimensions..." << endl;
    try {
        dma + DenseMatrix<int>({{3,5,6},
                                {1,0,3}});
    } catch (std::invalid_argument& ex) {
        cout << "something bad happened! " << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    }

    cout << "dmc += dma" << endl;
    dmc += dma;
    cout << pdmc->as_string() << endl;

    cout << "Trying += with different dimensions..." << endl;
    try {
        dma += DenseMatrix<int>({{3,5},
                                 {1,0},
                                 {0,9}});
    } catch (std::invalid_argument& ex) {
        cout << "something bad happened! " << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    }

}

void sparse_matrix_example(){
    cout << endl;
    cout << "---- SparseMatrix" << endl;    

    vector<vector<int>> vmat = {  {0,6,8,0},
                                  {0,0,0,5},
                                  {9,0,7,0} };    
    cout << "sma = From vectors constructor:" << endl;
    SparseMatrix<int> sma = SparseMatrix<int>(vmat);
    Matrix<int>* psma = &sma;
    cout << psma->as_string() << endl;

    try {
        cout << "Trying to instantiate \n  SparseMatrix<int>({{0,2},\n                     {3,0,5}}) ..." << endl;
        SparseMatrix<int> zsm = SparseMatrix<int>({{0,2},
                                                   {3,0,5}});
    } catch(std::invalid_argument& ex){
        cout << "something bad happened! " << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    }
    
    cout << "sma.shape(): " << pair2str(sma.shape()) << endl;   // shape is a std::pair
    cout << "sma(1,3): " << sma(1,3) << endl;        
    cout << "sma(1,3) += 9" << endl;
    sma(1,3) += 9;
    cout << psma->as_string() << endl; 

    cout << "sma.nonzero(): "<< triplets2str(sma.nonzero()) << endl;
    
    cout << endl;
    cout << "smb = From triplets constructor:" << endl;
    Triplet<int> triplets[] = {{1,3,5},{2,1,8},{2,3,0},{2,0,-9},{0,0,7}};
    SparseMatrix<int> smb = SparseMatrix<int>(3,4, triplets, 5);
    Matrix<int>* psmb = &smb;
    cout << psmb->as_string() << endl;
        

    cout << endl;
    cout << "smc = sma + smb:" << endl;
    SparseMatrix<int> smc = sma + smb; 

    Matrix<int>* psmc = &smc;
    cout << psmc->as_string() << endl;

    cout << "Trying + with different dimensions..." << endl;
    try {
        sma + SparseMatrix<int>({{3,5,6},
                                {1,0,3}});
    } catch (std::invalid_argument& ex) {
        cout << "something bad happened! " << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    }

    cout << "smc += sma" << endl;
    smc += sma;
    cout << psmc->as_string() << endl;

    cout << "Trying += with different dimensions..." << endl;
    try {
        sma += SparseMatrix<int>({{3,5},
                                  {1,0},
                                  {0,9}});
    } catch (std::invalid_argument& ex) {
        cout << "something bad happened! " << ex.what() << endl;
        cout << "I caught the exception, will continue" << endl;
    }

}


void dense_and_sparse_matrix_example(){

    cout << endl;
    cout << "---- Dense and Sparse combined" << endl;

    DenseMatrix<int> dma = DenseMatrix<int>({   
        {4,0,7},
        {0,6,5}
    });
    cout << "dma =" << dma.as_string() << endl;

    SparseMatrix<int> sma = SparseMatrix<int>({   
        {6,8, 0},
        {0,9,-5}
    });
    cout << "sma =" << sma.as_string() << endl;

    cout << "dmb = dma + sma" << endl;
    DenseMatrix<int> dmb = dma + sma;  // since we only defined as methods, we need to keep desired type on the left
    cout << dmb.as_string() << endl;

    cout << endl;
    cout << "smb = sma + dma" << endl;
    SparseMatrix<int> smb = sma + dma;
    cout << smb.as_string() << endl;
}

int main() {

    //std::unordered_map<string, int> umap;

    //std::unordered_map<vector<int>, int> umap2;   // no

    //std::unordered_map<char*, int> umap3;   // no

    unordered_map_example();
    
    
    multiset_example();
    
    conversions_example();
    dense_matrix_example();
    sparse_matrix_example();
    dense_and_sparse_matrix_example();
    

    return 0;
}
