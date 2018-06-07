
#include "SymmetricMatrixGenerator.hpp"
#include "EigenVectorCalculation.hpp"
#include <boost/test/unit_test.hpp>
namespace anpi {
  namespace test {
      template <typename T>
      void EigenvectorCalculationTest(){

        for(size_t N = 0; N < 50; ++N){
            anpi::Matrix<T> M = randomSymmetricSqr<T>(N);
            anpi::Matrix<T> E;
            std::vector<T> val;
            anpi::eig(M,val,E);

            const T eps = std::numeric_limits<T>::epsilon();
            for(size_t i = 0; i < N; ++i){
              for(size_t j = 0; j < N; ++j){
                BOOST_CHECK(std::abs(M[i][j] - M[j][i]) < eps);
              }
            }
        }
      }

    }
}

BOOST_AUTO_TEST_SUITE( EIGENTEST )

BOOST_AUTO_TEST_CASE(EIGENTESTCALL) 
{
  anpi::test::EigenvectorCalculationTest<float>();
  anpi::test::EigenvectorCalculationTest<double>();
}


BOOST_AUTO_TEST_SUITE_END()
