
#include <vector>
#include <iostream>
#include <functional>
#include <cmath>
#include "Matrix.hpp"
#include <string>
#include "PrintMat.hpp"
#include <omp.h>

#ifndef _GAUSS_SEIDEL_H_
#define _GAUSS_SEIDEL_H_

namespace anpi{

using std::vector;
using std::function;
using std::abs;
using std::string;
using std::cout;
using std::endl;

string ERROR_MESSAGE = "Error: Matrix must have appropiate size on gauss-seidel function. Must have 3 or more columns, that applies for rows also.";


template <typename T>
void gaussSeidel(Matrix<T> &A, 
                 const function<void(Matrix<T>&,size_t,size_t,T&)>& edp,
                 T threshold){
    
    if(A.rows() < 3 && A.cols() < 3)
        throw Exception(ERROR_MESSAGE.c_str());

    //cout << "gauss seidel is starting..." << endl;
    T local_threshold = T(threshold + T(1));
    T calculated_threshold = T(0);
    int count = 0;
    while (local_threshold > threshold){
        count++;
        edp(A,1,1,local_threshold);
        local_threshold = abs(local_threshold);
        #pragma omp parallel
	{
        size_t id,Nthrds,istart,iend;
	id = omp_get_thread_num();
	Nthrds = omp_get_num_threads();
	istart = id*(A.rows()-1)/Nthrds;
	iend = (id+1)*(A.rows()-1)/Nthrds;
	if(id == Nthrds-1)iend = A.rows()-1;
	//cout << "id: " << id << " from: " <<  istart << " to: " << iend << " nthrd: " << Nthrds<< endl;
        for(size_t i = istart; i < iend; i++){
            for(size_t j = 1; j < A.cols()-1; j++){
                edp(A,i,j,calculated_threshold);
                calculated_threshold = abs(calculated_threshold);
                /*
                if (calculated_threshold > local_threshold){
                    cout << i << " " << j << endl;
                }
                */
                local_threshold = (calculated_threshold > local_threshold)?calculated_threshold : local_threshold;
            }
        }
	}
        //cout << "local threshold = " <<  local_threshold << endl;
    }
    cout << "final threshold = " <<  local_threshold << " final count = " << count << endl;


}

}

#endif //_GAUSS_SEIDEL_H_
