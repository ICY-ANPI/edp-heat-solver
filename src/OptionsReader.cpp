#include "boost/program_options.hpp"

#include "OptionsReader.hpp"
#include "ReadProFile.hpp"
#include <string.h>
#include <iostream>
#include <chrono>
#include "GaussSeidel.hpp"
#include "CalculateTemperature.hpp"
#include "PlotHeatMap.hpp"
#include "CalculateHeatFlux.hpp"

using namespace std;
namespace
{
const size_t ERROR_IN_COMMAND_LINE = 1;
const size_t SUCCESS = 0;
const size_t ERROR_UNHANDLED_EXCEPTION = 2;

} // namespace

void fillRight(anpi::Matrix<double> &A, double value)
{

  for (size_t x = 0; x < A.rows(); x++)
  {
    A[x][A.cols() - 1] = value;
  }
}
void fillLeft(anpi::Matrix<double> &A, double value)
{
  for (size_t x = 0; x < A.rows(); x++)
  {
    A[x][0] = value;
  }
}
void fillTop(anpi::Matrix<double> &A, double value)
{
  for (size_t x = 0; x < A.cols(); x++)
  {
    A[0][x] = value;
  }
}

void fillBottom(anpi::Matrix<double> &A, double value)
{
  for (size_t x = 0; x < A.cols(); x++)
  {
    A[A.rows()-1][x] = value;
  }
}

int option_reader(int argc, char **argv)
{
  try
  {
    /** Define and parse the program options 
     */
    //http://www.radmangames.com/programming/how-to-use-boost-program_options
    namespace po = boost::program_options;
    po::options_description desc("Options");
    int t = 0, b= 0, l= 0, d= 0, g = 0;
    g = 4;
    int h= 3, v = 3;
    string p, i = "";
    desc.add_options()
    ("help", "Muestra la ayuda al usuario")
    (",t", po::value<int>(&t), "Temperatura del borde superior")
    (",b", po::value<int>(&b), "Temperatura del borde inferior")
    (",l", po::value<int>(&l), "Temperatura del borde izquierdo")
    (",d", po::value<int>(&d), "Temperatura del borde derecho")
    (",i", po::value<string>(&i), "Aisla los bordes indicados (t=arriba, b=abajo,l=izquierda,r=derecha) puede indicar varias opciones, por ejemplo -i bt")
    (",p", po::value<string>(&p), "Perfil termico, indica el archivo del cual se quiere extraer la informacion")
    (",h", po::value<int>(&h), "Numero de pixeles horizontales de la solucion")
    (",v", po::value<int>(&v), "Numero de pixeles verticales de la solucion")
    (",q", "Desactiva la visualizacion de los graficos obtenidos")
    (",f", "Activa el calculo del flujo de calor")
    ("omp,o", "Activa el uso de openmp para el algoritmo")
    (",g", po::value<int>(&g), "tamano de rejilla para la visualizacion del flujo de calor");

    po::variables_map vm;
    try
    {
      po::store(po::parse_command_line(argc, argv, desc),
                vm); // can throw


      /** --help option 
       */
      if (vm.count("help"))
      {
        std::cout << ">>> EDP ============" << std::endl
                  << desc << std::endl;
        return SUCCESS;
      }
      if (vm.count("-p"))
      {
        p = vm["-p"].as<std::string>();
        std::cout << p << std::endl;
        anpi::parseFile(p);
        anpi::filikili();
      }
      else
      {
      }
      if (vm.count("-t"))
      {
        t = vm["-t"].as<int>();
      }
      if (vm.count("-b"))
      {
        b = vm["-b"].as<int>();
      }
      if (vm.count("-l"))
      {
        l = vm["-l"].as<int>();
      }
      if (vm.count("-d"))
      {
        d = vm["-d"].as<int>();
      }
      if (vm.count("-i"))
      {
        i = vm["-i"].as<std::string>();
      }
      if (vm.count("-v") && vm.count("-h"))
      {
        h = vm["-h"].as<int>();
        v = vm["-v"].as<int>();
        anpi::Matrix<double> A;
        A.allocate(v + 2, h + 2);
        A.fill(0.0);
        fillBottom(A, b);
        fillLeft(A, l);
        fillRight(A, d);
        fillTop(A, t);
        
        const double eps = std::numeric_limits<double>::epsilon() * double(1000);

        typedef std::chrono::high_resolution_clock Time;
        typedef std::chrono::microseconds us;
        typedef std::chrono::duration<double> fsec;

        auto t0 = Time::now();
        if (vm.count("-o") || vm.count("omp"))
          anpi::gaussSeidelOpenMP<double>(A,anpi::calculateTemperature<double>,eps);
        else 
          anpi::gaussSeidel<double>(A, anpi::calculateTemperature<double>, eps);
        auto t1 = Time::now();

        fsec fs = t1 - t0;
        us d = std::chrono::duration_cast<us>(fs);
        std::cout << "Duracion: " << fs.count() << "s\n";

        if (!vm.count("-q"))
        {
          anpi::PlotHeadMap<double> plot;
          plot.initialize(0);
          plot.plot(A);

          if (vm.count("-f"))
          {
            if (vm.count("-g")) g = vm["-g"].as<int>();
            else cout << "Parametro g no encontrado, se usara -g=4 por defecto"<< endl;
            vector<double> x0, y0;
            vector<double> u0, v0;
            anpi::calculateHeatFlux<double>(A, g, x0, y0, u0, v0);
            plot.quiver(x0, y0, u0, v0);
          }
          plot.show();
        }
      }
      else
      {
        cout << "Debe indicar el tamano de la placa mediante los parametros -h y -v" << endl;
      }
      po::notify(vm); // throws on error, so do after help in case
                      // there are any problems
    }
    catch (po::error &e)
    {
      std::cerr << "ERROR: " << e.what() << std::endl
                << std::endl;
      std::cerr << desc << std::endl;
      return ERROR_IN_COMMAND_LINE;
    }

    // application code here //
  }
  catch (std::exception &e)
  {
    std::cerr << "Unhandled Exception reached the top of main: "
              << e.what() << ", application will now exit" << std::endl;
    return ERROR_UNHANDLED_EXCEPTION;
  }

  return SUCCESS;

} // main