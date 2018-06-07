

#include <vector>
#include <iostream>
#include "Matrix.hpp"
using std::cout;
using std::endl;

#ifndef _CALCULATE_TEMPERATURE_H_
#define _CALCULATE_TEMPERATURE_H_

namespace anpi{

using std::vector;
using std::function;
using std::abs;


template <typename T>
void calculateTemperature(Matrix<T>& M ,size_t i,size_t j,T &threshold){
    T tmp = M[i][j];
    M[i][j] = (M[i+1][j] + M[i-1][j] + M[i][j+1] + M[i][j-1])/T(4);
    T w  = T(1.6);
    M[i][j] = w*M[i][j] + (T(1)-w) * tmp;

    threshold = tmp - M[i][j];
}

}


#endif //_CALCULATE_TEMPERATURE_H_