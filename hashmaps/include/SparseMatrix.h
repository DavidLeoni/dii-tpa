#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <Matrix.h>

#include <stdexcept>
#include <string>
#include <sstream>

#include <iostream>
#include <unordered_map>
#include <tuple>
#include <cmath>


/**   
 * A SparseMatrix is a matrix which contains very few non-zero elements.

  In this implementation, storage is modelled as a dictionary of keys (DOK in short),
  where each key is a pair of cell coordinates which maps to a non-zero cell value.

  NOTE: *NEVER* store zero-valued cells.
*/
template <typename T>
class SparseMatrix : public Matrix<T>{
    
    private:
        // using a string sucks, but if we wanted to use a std::pair as key we would need to redefine hash for it
        std::unordered_map<string, T> cells_;

        std::pair<int,int> shape_;


    public:        
                        
                    
        SparseMatrix(const vector<vector<T>>& values) : Matrix<T>(values){
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

            this->shape_ = {n, m};

            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++){
                    if (values[i][j] != T()){
                        this->cells_[pair2str({i,j})] = values[i][j];
                    }
                }
            }
            
            ///jupman-raise
        }

        SparseMatrix(   const int n, 
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
                                
            for (int k=0; k < triplets_size; k++){
                const Triplet<T>& t = triplets[k];
                if ( t.row >= n){
                    throw std::invalid_argument("Found triplets with row index exceeding the declared one!");
                }
                if (t.col >= m){
                    throw std::invalid_argument("Found triplets with column index exceeding the declared one!");
                }       
                if (t.value != T()){                    
                    this->cells_[pair2str({t.row,t.col})] = t.value;
                }
            }
            this->shape_ = std::pair<int, int>(n,m);
            ///jupman-raise
        }

        virtual string as_string() const {
            stringstream ss = stringstream();
            ss << "SparseMatrix " << this->shape().first << "," << this->shape().second << " {" << endl;
            
            for (pair<string, T> els : this->cells_){
                ss << "  " << els.first << " : " << els.second << endl;
            }
            ss << "}";

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

            string s = pair2str({row, col});

            if (this->cells_.count(s) == 1){
                return this->cells_.at(s);
            } else {
                return T(); 
            }
        }

        virtual T& operator()(const int row, const int col) {
            if (row < 0 || row >= this->shape().first){
                throw std::out_of_range(string("Invalid row ") + to_string(row));
            }
            if (col < 0 || col >= this->shape().second){
                throw std::out_of_range(string("Invalid col ") + to_string(col));
            }

            string s = pair2str({row, col});
            
            // NOTE: it will automatically instantiate T(), so user could write zeroes :-/
            // unfortunately, to perform a check we should instantiate a proxy, not fun https://stackoverflow.com/q/30806786
            return this->cells_[s]; 
        }
        
        virtual vector<Triplet<T>> nonzero() const {
            //jupman-raise
            vector<Triplet<T>> ret;
            
            for (pair<string, T> els : this->cells_){            
                std::pair<int,int> coords = str2pair(els.first);
                ret.push_back({coords.first, coords.second, els.second});                
            }
            return ret;
            ///jupman-raise
        }


        virtual SparseMatrix<T> operator+(const Matrix<T>& other) const {
            //jupman-raise            
            if (this->shape() != other.shape()){
                throw std::invalid_argument(string("Mismatch in dimensions! this: ") + pair2str(this->shape()) 
                                                                                     + " other: " + pair2str(other.shape()) );
            }
            SparseMatrix<T> ret = SparseMatrix(*this);

            for (Triplet<T>& t : other.nonzero()){

                string coords = pair2str({t.row, t.col});

                if (ret.cells_.count(coords) == 1){
                    if (ret.cells_[coords] + t.value == T()){
                        ret.cells_.erase(coords);  // don't want zero
                    } else {
                        ret.cells_[coords] += t.value;
                    }
                } else {
                    ret.cells_[coords] = t.value;
                }
            }                            
            return ret;
            ///jupman-raise
        }

        virtual SparseMatrix<T>& operator+=(const Matrix<T>& other) {
            //jupman-raise            
            if (this->shape() != other.shape()){
                throw std::invalid_argument(string("Mismatch in dimensions! this: ") + pair2str(this->shape()) 
                                                                                     + " other: " + pair2str(other.shape()) );
            }
            for (Triplet<T>& t : other.nonzero()){
                string coords = pair2str({t.row, t.col});
                if (this->cells_.count(coords) == 1){
                    if (this->cells_[coords] + t.value == T()){
                        this->cells_.erase(coords);  // don't want zero
                    } else {
                        this->cells_[coords] += t.value;
                    }
                    
                } else {
                    this->cells_[coords] = t.value;
                }
            }
            
            return *this;

            ///jupman-raise
        }

        
};


#endif // SPARSE_MATRIX_H