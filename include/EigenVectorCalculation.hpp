#include <vector>
#include "Matrix.hpp"
#include "LapackeAdapter.hpp"

namespace anpi {


    template<typename T>
    /**
     * Funcion eig. Retorna en la matriz E los eigen valores de la matriz cuadrada A
     * para los eigen valores dados por val.
     * @param A. Matriz de entrada.
     * @param val. Son los eigen valores
     * @param E. Son los eigenvectores. Tambien son la salida del algoritmo.
     */
    void eig(const anpi::Matrix<T> & A, std::vector<T>& val, anpi::Matrix<T> & E){

    	Matrix<T> D,TAU;
    	T* Atest = 0;

    	anpi::toThirdBandMatrix<T>(0,'L',A.cols(),Atest,0,D.data(),E.data(),TAU.data());


    }

}
