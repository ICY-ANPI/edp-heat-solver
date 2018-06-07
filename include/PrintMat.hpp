

#include <vector>
#include <iostream>
#include <cmath>
#include "Matrix.hpp"

namespace anpi{
template<typename T>
void printMat(Matrix<T> c){
	std::cout << "MATRIX START HERE!" << std::endl;
	std::cout << "==================="<< std::endl;

	for (size_t i = 0; i < c.rows(); i++){
		for(size_t j = 0; j < c.cols();j++){
			std::cout << c[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "==================="<< std::endl;
}

}