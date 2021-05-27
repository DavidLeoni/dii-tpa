#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <string>
#include <sstream>

#include <iostream>
#include <tuple>
#include <vector>

using std::vector;

template <typename T>
struct Triplet {
    int row;
    int col;
    T value;
};

/**
 * RETURN the pair as a string like 12,345
*/
string pair2str(const std::pair<int,int>& shape) {
    //jupman-raise
    return to_string(shape.first) + "," + to_string(shape.second);
    ///jupman-raise
}


/**
 * Given a string like 12,345 RETURN the pair (12, 345)
*/
std::pair<int,int> str2pair(string s){
    int i = s.find(',');
    return {stoi(s.substr(0,i)), stoi(s.substr(i+1))};
}


/**
 * RETURN the nonzero cells as triplets in a string like {{1,4,2},{3,5,7},{2,1,5},{3,5,1}}
*/
template<typename T>
string triplets2str(const vector<Triplet<T>>& ts) {
    //jupman-raise
    stringstream ss;
    ss << '{';    

    for (int i=0; i < ts.size(); i++){
        if (i>0){
            ss << ',';
        }
        ss << '{' << ts[i].row << ',' << ts[i].col << "," << ts[i].value << '}';
    }
    ss << '}';
    return ss.str();
    ///jupman-raise
}


/** A Matrix interface which holds elements of type T
*/
template <typename T>
class Matrix {
    
    public:
        /**
         * Initializes the Matrix with a vector of vector of cells   

            - Provided data must allow the creation of a matrix with 
              at least one row and a column, otherwise throw std::invalid_argument
            - if vector rows have different length, throws std::invalid_argument
        */
        Matrix(const vector<vector<T>>& values){            
        }

        /**
            Initializes the Matrix with four arguments: 
            - number of rows
            - number of columns
            - an array of cell triplets (row_index,col_index,value)
            - size of the trplets
            
            If number of rows or columns is less than indeces found 
            in triplets, throw std::invalid_argument

            Provided data must allow the creation of a matrix with 
            at least one row and a column, otherwise throw std::invalid_argument
        */
        Matrix( const int n, 
                const int m, 
                const Triplet<T> triplets[], 
                const int triplets_size){            
        }

        /** RETURN a nice human-readable formatted string, when POSSIBLE like this:
                
                Matrix  { {5,2,6,3},
                          {8,4,7,4},
                          {2,1,9,8} }

                - substitute Matrix with the descendant class name
                - NOTE: sometimes this representation is impractical (i.e. sparse matrices 
                        with large n/m), in that case use another format of your choice
        */
        virtual string as_string() const {
            throw std::runtime_error("Should be implemented in a descendant of Matrix!");
        }
        
    
        /**
            RETURN the number of rows and columns as a std::pair
        */
        virtual std::pair<int,int> shape() const {
            throw std::runtime_error("Should be implemented in a descendant of Matrix!");
        }

        /**
            Overrides default round parenthesis access behaviour when *reading*
            
            my_mat(2,5)  to access element at row 2 and column 5

            - on wrong indeces, throw std::out_of_bounds exception
        */        
        virtual T operator()(const int row, const int col) const {
            throw std::runtime_error("Should be implemented in a descendant of Matrix!");
        }

        /**
            Overrides default round parenthesis access behaviour when *writing*
            
            my_mat(2,5) = 3  to access element at row 2 and column 5

            - on wrong indeces, throw std::out_of_bounds exception            

        */        
        virtual T& operator()(const int row, const int col) {
            throw std::runtime_error("Should be implemented in a descendant of Matrix!");
        }

        /**
            RETURN a vector of triplets {row index, column index, value} of non-zero cells,
            in *no particular order*.            

            - NOTE: DO *NOT* write 0, use T() instead
        */
        virtual vector<Triplet<T>> nonzero() const {
            throw std::runtime_error("Should be implemented in a descendant of Matrix!");
        }                                        
        
};



#endif // MATRIX_H