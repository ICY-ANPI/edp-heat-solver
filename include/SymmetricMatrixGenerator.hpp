#include <vector>
#include "Matrix.hpp"
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

#include <sys/time.h>
namespace anpi {

//Took from: https://stackoverflow.com/questions/6470074/boostrandom-and-boostuniform-real-works-with-doubles-not-with-floats
template <typename N>
N getRandom(N min, N max)
{

  typedef typename boost::mpl::if_<
    boost::is_floating_point<N>, // if we have a floating point type
    boost::uniform_real<>,       // use this, or
    boost::uniform_int<>         // else use this one
  >::type distro_type;

  timeval t;
  gettimeofday(&t,NULL);
  boost::mt19937 seed( (int)t.tv_sec );
  distro_type dist(min,max);
  boost::variate_generator<boost::mt19937&, distro_type > random(seed,dist);
  return random(); 
}


template<typename T> Matrix<T> randomSymmetricSqr(const size_t N){

    Matrix<T> M;
    M.allocate(N,N);
    for(size_t i = 0; i < N; ++i){
      for(size_t j = 0; j < N; ++j){
        M[j][i] = getRandom<T>(T(0),T(N));
        M[i][j] = M[j][i];
      }
    }
    return M;
}

}