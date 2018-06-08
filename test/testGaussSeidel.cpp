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
#include <chrono>

#include "GaussSeidel.hpp"
#include "CalculateTemperature.hpp"
//#include "PrintMat.hpp"
#include "PlotHeatMap.hpp"
#include "CalculateHeatFlux.hpp"

namespace anpi
{
namespace test
{

/// Test the given closed root finder
template <typename T>
void calculateHeat(const function<void(Matrix<T> &, size_t, size_t, T &)> &edp)
{

    Matrix<T> A;
    A.allocate(128, 128);

    A.fill(T(0));
    size_t x;
    for (x = 0; x < A.cols(); x++)
    {
        A[0][x] = T(100); //T(abs(128 - x));
        A[x][0] = T(100);
        //A[x][A.cols()-1] = T(25);
        //A[A.rows()-1][x] = T(x);
    }
    const T eps = std::numeric_limits<T>::epsilon() * T(90);

    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::microseconds us;
    typedef std::chrono::duration<T> fsec;
    
    
    auto t0 = Time::now();
    gaussSeidel(A, edp, eps);
    auto t1 = Time::now();
    fsec fs = t1 - t0;
    us d = std::chrono::duration_cast<us>(fs);
    std::cout << fs.count() << "s\n";
    std::cout << d.count() << "us\n";

    vector<T> x0,y;
    vector<T> u,v;    

    PlotHeadMap<T> plot;
    plot.initialize(0);
    plot.plot(A);
    calculateHeatFlux(A ,4, x0,y,u,v);
    plot.quiver(x0,y,u,v);

    plot.show();

    A.fill(T(0));
    for (x = 0; x < A.cols(); x++)
    {
        A[0][x] = T(100); //T(abs(128 - x));
        A[A.cols()-1][x] = T(100);
        //A[x][0] = T(-int(x));
        //A[x][A.cols()-1] = T(25);
        //A[A.rows()-1][x] = T(x);
    }

    t0 = Time::now();
    gaussSeidelOpenMP(A, edp, eps);
    t1 = Time::now();
    fs = t1 - t0;
    d = std::chrono::duration_cast<us>(fs);
    std::cout << fs.count() << "s\n";
    std::cout << d.count() << "us\n";

    vector<T> x1,y1;
    vector<T> u1,v1;    

    plot.plot(A);
    calculateHeatFlux(A ,4, x1,y1,u1,v1);
    plot.quiver(x1,y1,u1,v1);
    plot.show();
}

} // test
} // anpi

BOOST_AUTO_TEST_SUITE(HeatCalculation)

BOOST_AUTO_TEST_CASE(MatrixHeat)
{
    anpi::test::calculateHeat<float>(anpi::calculateTemperature<float>);
    anpi::test::calculateHeat<double>(anpi::calculateTemperature<double>);
}

BOOST_AUTO_TEST_SUITE_END()
