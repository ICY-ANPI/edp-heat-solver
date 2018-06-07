/**
 * Copyright (C) 2017 
 * Área Académica de Ingeniería en Computadoras, TEC, Costa Rica
 *
 * This file is part of the CE3102 Numerical Analysis lecture at TEC
 *
 * @Author: Pablo Alvarado
 * @Date  : 10.02.2018
 */

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <exception>
#include <cstdlib>
#include <complex>
#include <functional>
#include <cmath>

#include "GaussSeidel.hpp"
#include "CalculateTemperature.hpp"
//#include "PrintMat.hpp"

namespace anpi {
  namespace test {
    
    /// Test the given closed root finder
    template<typename T>
    void calculateHeat(const function<void(Matrix<T>&,size_t,size_t,T&)>& edp) {

        Matrix<T> A;
        A.allocate(12,12);

        A.fill(T(0));
        for(size_t x = 1; x < A.cols()-1; x++){
            A[0][x] = T(50);
        }

        gaussSeidel(A,edp,T(0.05));

        printMat(A);


        A.fill(T(0));
        for(size_t x = 1; x < A.cols()-1; x++){
            A[0][x] = T(50);
            A[x][0] = T(50);
        }

        gaussSeidel(A,edp,T(0.05));

        printMat(A);


    }



  } // test
}  // anpi




BOOST_AUTO_TEST_SUITE( HeatCalculation )

BOOST_AUTO_TEST_CASE( MatrixHeat ) 
{
    anpi::test::calculateHeat<float>(anpi::calculateTemperature<float>);
    anpi::test::calculateHeat<double>(anpi::calculateTemperature<double>);
}



BOOST_AUTO_TEST_SUITE_END()
