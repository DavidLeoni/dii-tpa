#ifndef DENSE_MATRIX_H
#define DENSE_MATRIX_H

#include <Matrix.h>

#include <stdexcept>
#include <string>
#include <sstream>

#include <iostream>
#include <unordered_map>
#include <tuple>
#include <cmath>



/** A Matrix interface which holds elements of type T in a vector of vectors
*/
template <typename T>
class DenseMatrix : public Matrix<T>{
    
    private:
        vector<vector<T>> cells_;
        std::pair<int,int> shape_;

    public:
        /**
            A Matrix represented internally as a vector of vectors
                        
        */            
        DenseMatrix(const vector<vector<T>>& values) : Matrix<T>(values){
            //jupman-raise
            
            int prev = -1;
            for (const vector<T>& v : values){
                if (prev == -1){
                    prev = v.size();
                } else {
                    if (prev != v.size()){
                        throw std::invalid_argument("Found rows of different length!");
                    }
                }                
            }
            
            int n = values.size();
            if (n == 0){
                throw std::invalid_argument("Must have at least one row !");
            }                
            int m = values[0].size();
            if (m == 0){
                throw std::invalid_argument("Must have at least one column !");
            }            
            
            this->cells_ = values;

            this->shape_ = std::pair<int,int>(n, m);
            ///jupman-raise
        }

        DenseMatrix(const int n, 
                    const int m, 
                    const Triplet<T> triplets[], 
                    const int triplets_size) : Matrix<T>(n, m, triplets, triplets_size) {
            //jupman-raise
            

            if (triplets_size <= 0){
                throw std::invalid_argument("Expected a non-empty list of triplets!");
            }
            if (n < 1){
                throw std::invalid_argument(string("Expected a strictly positive n! Found") +  to_string(n));
            }
            if (m < 1){
                throw std::invalid_argument(string("Expected a strictly positive m! Found ") + to_string(m));
            }                
                    
            this->cells_.resize(n);
            for (int i=0;i<n;i++){
                this->cells_[i].resize(m);
            }

            for (int k=0; k < triplets_size; k++){
                const Triplet<T>& t = triplets[k];
                if ( t.row >= n){
                    throw std::invalid_argument("Found triplets with row index exceeding the declared one!");
                }
                if (t.col >= m){
                    throw std::invalid_argument("Found triplets with column index exceeding the declared one!");
                }                    
                this->cells_[t.row][t.col] = t.value;
            }
            this->shape_ = std::pair<int, int>(n,m);
            ///jupman-raise
        }

        virtual string as_string() const {
            stringstream ss = stringstream();
            ss << "DenseMatrix {";
            
            for (int i = 0; i < this->shape().first; i++){
                if (i > 0){
                    ss << ",";            
                }
                ss << endl << "   {";
                for (int j = 0; j < this->shape().second; j++){
                    if (j > 0){
                        ss << ", ";
                    }
                    ss << this->cells_[i][j];
                }
                ss << "}";
            }
            ss << endl << "}";

            return ss.str();
        }
        
        virtual std::pair<int,int> shape() const {
            return this->shape_;
        }

        virtual T operator()(const int row, const int col) const {
            if (row < 0 || row >= this->shape().first){
                throw std::out_of_range(string("Invalid row ") + to_string(row));
            }
            if (col < 0 || col >= this->shape().second){
                throw std::out_of_range(string("Invalid col ") + to_string(col));
            }
                                    
            return this->cells_[row][col];
        }

        virtual T& operator()(const int row, const int col) {
            if (row < 0 || row >= this->shape().first){
                throw std::out_of_range(string("Invalid row ") + to_string(row));
            }
            if (col < 0 || col >= this->shape().second){
                throw std::out_of_range(string("Invalid col ") + to_string(col));
            }
                                    
            return this->cells_[row][col];
        }
        
        virtual vector<Triplet<T>> nonzero() const {
            //jupman-raise
            vector<Triplet<T>> ret;
            
            for (int i = 0; i < this->shape().first; i++){
                for (int j = 0; j < this->shape().second; j++){
                    T v = this->cells_[i][j];
                    if (v != T()){
                        ret.push_back(Triplet<T>{i,j,v});
                    }
                }
            }
            return ret;
            ///jupman-raise
        }


        virtual DenseMatrix<T> operator+(const Matrix<T>& other) const {
            //jupman-raise  
            if (this->shape() != other.shape()){
                throw std::invalid_argument(string("Mismatch in dimensions! this: ") + pair2str(this->shape()) 
                                                                                     + " other: " + pair2str(other.shape()) );
            }          
            DenseMatrix<T> ret = DenseMatrix(this->cells_);
            for (int i = 0; i < this->shape().first; i++){
                for (int j = 0; j < this->shape().second; j++){
                    ret.cells_[i][j] += other(i,j);
                }
            }
            return ret;            

            ///jupman-raise
        }

        virtual DenseMatrix<T>& operator+=(const Matrix<T>& other) {
            //jupman-raise            
            
            if (this->shape() != other.shape()){
                throw std::invalid_argument(string("Mismatch in dimensions! this: ") + pair2str(this->shape()) 
                                                                                     + " other: " + pair2str(other.shape()) );
            }
            for (int i = 0; i < this->shape().first; i++){
                for (int j = 0; j < this->shape().second; j++){
                    this->cells_[i][j] += other(i,j);
                }
            }
            return *this;

            ///jupman-raise
        }

        
};


#endif // DENSE_MATRIX_H