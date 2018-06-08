

#include <vector>
#include <iostream>
#include "Matrix.hpp"
using std::cout;
using std::endl;

#ifndef _CALCULATE_HEATFLUX_H_
#define _CALCULATE_HEATFLUX_H_

namespace anpi{

using std::vector;
using std::function;
using std::abs;


template <typename T>
void calculateHeatFlux(const Matrix<T>& M ,size_t grid_size, 
                       vector<T>& x,vector<T>& y,
                       vector<T>& u,vector<T>& v){
    for (size_t i = 1; i + grid_size < M.rows();i+=grid_size){
        for(size_t j = 1; j + grid_size < M.cols();j+=grid_size){
            x.push_back(T(j));
            y.push_back(T(i));
            u.push_back(M[i][j] - M[i][j+grid_size]);
            v.push_back(M[i+grid_size][j] - M[i][j]);
        }
    }
}

}


#endif //_CALCULATE_HEATFLUX_H_