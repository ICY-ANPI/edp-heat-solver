
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

namespace anpi
{

using std::vector;
using std::function;
using std::abs;
using std::string;
using std::cout;
using std::endl;

string ERROR_MESSAGE = "Error: Matrix must have appropiate size on gauss-seidel function. Must have 3 or more columns, that applies for rows also.";

template <typename T>
void gaussSeidelAux(Matrix<T> &A, size_t istart, size_t iend,
                    const function<void(Matrix<T> &, size_t, size_t, T &)> &edp,
                    T &threshold_out){
    T calculated_threshold = threshold_out;
    for (size_t i = istart; i < iend; i++){
        for (size_t j = 1; j < A.cols() - 1; j++){
            edp(A, i, j, calculated_threshold);
            calculated_threshold = abs(calculated_threshold);
            threshold_out = (calculated_threshold > threshold_out) ? calculated_threshold : threshold_out;
        }
    }
}

template <typename T>
void gaussSeidelOpenMP(Matrix<T> &A,
                 const function<void(Matrix<T> &, size_t, size_t, T &)> &edp,
                 T threshold)
{

    if (A.rows() < 3 && A.cols() < 3)
        throw Exception(ERROR_MESSAGE.c_str());
    T local_threshold = T(threshold + T(1));
    int count = 0;
    while (local_threshold > threshold)
    {
        count++;
        edp(A, 1, 1, local_threshold);
        local_threshold = abs(local_threshold);
        size_t id, Nthrds, istart, iend;
        omp_lock_t lck;
        omp_init_lock(&lck);
#pragma omp parallel
        {
            id = omp_get_thread_num();
            Nthrds = omp_get_num_threads();
            istart = id * (A.rows() - 1) / Nthrds + 1;
            iend = (id + 1) * (A.rows() - 1) / Nthrds + 1;
            if (id == Nthrds-1)
                iend = A.rows() - 1;
            T pragma_threshold = local_threshold;
            gaussSeidelAux(A, istart, iend, edp, pragma_threshold);
            omp_set_lock(&lck);
            local_threshold = (pragma_threshold > local_threshold) ? pragma_threshold : local_threshold;
            //cout << "id: " << id << " from: " <<  istart << " to: " << iend << " nthrd: " << Nthrds<< endl;
            //cout << "thread id: " << id << " local threshold: " << local_threshold << " target: " << threshold<< endl;
            omp_unset_lock(&lck);
        }
        omp_destroy_lock(&lck);
        edp(A, 1, 1, local_threshold);
        local_threshold = abs(local_threshold);
        //Esta seccion es de refinamiento
        //Por algun motivo quedan lineas horizontales en el mapa de calor
        //Al usar openmp
        //Por esta razon se realiza un refinamiento sobre la matriz
        //Esto suaviza dichas lineas, El algoritmo converge a una razon similar 
        //que lo hace el openmp
        gaussSeidelAux(A, (size_t)1, (size_t)1, edp, local_threshold);
        //cout << "local threshold = " <<  local_threshold << endl;
    }
    //cout << "final threshold = " <<  local_threshold << " final count = " << count << endl;
}

template <typename T>
void gaussSeidel(Matrix<T> &A,
                 const function<void(Matrix<T> &, size_t, size_t, T &)> &edp,
                 T threshold)
{

    if (A.rows() < 3 && A.cols() < 3)
        throw Exception(ERROR_MESSAGE.c_str());
    T local_threshold = T(threshold + T(1));
    int count = 0;
    while (local_threshold > threshold)
    {
        count++;
        edp(A, 1, 1, local_threshold);
        local_threshold = abs(local_threshold);
        gaussSeidelAux(A, (size_t)1, A.rows(), edp, local_threshold);
        //cout << "local threshold = " <<  local_threshold << endl;
    }
    //cout << "final threshold = " <<  local_threshold << " final count = " << count << endl;
}


}

#endif //_GAUSS_SEIDEL_H_
