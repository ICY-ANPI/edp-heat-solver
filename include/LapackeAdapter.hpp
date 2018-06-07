/*
 * LapackeAdapter.hpp
 *
 *  Created on: May 20, 2018
 *      Author: cristian
 */

#include <vector>
#include <lapacke.h>
#include <complex>


#ifndef INCLUDE_LAPACKEADAPTER_HPP_
#define INCLUDE_LAPACKEADAPTER_HPP_



namespace anpi {



    template<typename T>
    int toThirdBandMatrix(int matrix_layout, char UPLO,int N, T* A, int LDA, T* D, T* E, T* TAU);

    template<> inline
    int __attribute__((__always_inline__))
	toThirdBandMatrix<float>
    	(int layout, char UPLO,int N, float* A, int LDA, float* D, float* E, float* TAU){

    	LAPACKE_ssytrd(layout,UPLO,N,A,LDA,D,E,TAU);
    	return 0;

    }
    template<> inline
    int __attribute__((__always_inline__))
	toThirdBandMatrix<double>
    	(int layout, char UPLO,int N, double* A, int LDA, double* D, double* E, double* TAU){

    	LAPACKE_dsytrd(layout,UPLO,N,A,LDA,D,E,TAU);
    	return 0;
    }
    /*
    template<> inline
    int __attribute__((__always_inline__))
	toThirdBandMatrix<std::complex<float>>
    	(int layout, char UPLO,int N, std::complex<float>* A, int LDA, std::complex<float>* D, std::complex<float>* E, std::complex<float>* TAU){
    	return LAPACKE_chetrd(layout,UPLO,N,A,LDA,D,E,TAU);
    }
    template<> inline
    int __attribute__((__always_inline__))
	toThirdBandMatrix<std::complex<double>>
        (int layout, char UPLO,int N, std::complex<double>* A, int LDA, std::complex<double>* D, std::complex<double>* E, std::complex<double>* TAU){
    	return LAPACKE_zhetrd(layout,UPLO,N,A,LDA,D,E,TAU);
    }
    */

}


#endif /* INCLUDE_LAPACKEADAPTER_HPP_ */
