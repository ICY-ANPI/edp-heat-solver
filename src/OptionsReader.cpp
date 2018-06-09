#include "boost/program_options.hpp" 
 
 
#include "OptionsReader.hpp"
#include "ReadProFile.hpp"
#include <string.h>
#include <iostream>

using namespace std; 
namespace 
{ 
  const size_t ERROR_IN_COMMAND_LINE = 1; 
  const size_t SUCCESS = 0; 
  const size_t ERROR_UNHANDLED_EXCEPTION = 2; 
 
} // namespace 
 
int option_reader(int argc, char** argv) 
{ 
  try 
  { 
    /** Define and parse the program options 
     */ 
    namespace po = boost::program_options; 
    po::options_description desc("Options"); 
    int t,b,l,d,h,v,g = 0;
    string p,i = "";
    bool q,f = false;
    desc.add_options() 
      ("help", "Muestra la ayuda al usuario") 
      (",t", po::value<int>(&t), "Temperatura del borde superior") 
      (",b", po::value<int>(&b), "Temperatura del borde inferior") 
      (",l", po::value<int>(&l), "Temperatura del borde izquierdo") 
      (",d", po::value<int>(&d), "Temperatura del borde derecho") 
      (",i", po::value<std::string>(&i), "Aisla los bordes indicados (t=arriba, b=abajo,l=izquierda,r=derecha) puede indicar varias opciones, por ejemplo -i bt") 
      (",p", po::value<std::string>(&p), "Perfil termico, indica el archivo del cual se quiere extraer la informacion") 
      (",h", po::value<int>(&h), "Numero de pixeles horizontales de la solucion") 
      (",v", po::value<int>(&v), "Numero de pixeles verticales de la solucion") 
      (",q", "Desactiva la visualizacion de los graficos obtenidos") 
      (",f", "Activa el calculo del flujo de calor") 
      (",g", po::value<int>(&g), "tamano de rejilla para la visualizacion del flujo de calor"); 
 
    po::variables_map vm; 
    try { 
      po::store(po::parse_command_line(argc, argv, desc),  
                vm); // can throw 
 
      /** --help option 
       */ 
      if ( vm.count("help") && vm.size() > 1 ) { 
        std::cout << ">>> EDP ============" << std::endl 
                  << desc << std::endl; 
        return SUCCESS; 
      }
      if (vm.count("-p")){
          p = vm["-p"].as<std::string>();
          std::cout << p << std::endl;
          anpi::parseFile(p);
          anpi::filikili();
      }
      else{

      }
      if (vm.count("-t")){
          std::cout << p << vm["-t"].as<int>() << std::endl;

      }
      else{
          //if(esta en archivo)
          //else
          std::cout << "Debe indicar la cantidad de pixeles horizontales" << std::endl;
          return SUCCESS;
      }
      if (vm.count("-b")){

      }
      else{
          
      }
      if (vm.count("-l")){

      }
      else{
          
      }
      if (vm.count("-d")){

      }
      else{
          
      }
      if (vm.count("-i")){

      }
      if (vm.count("-h")){

      }
      else{
          std::cout << "Debe indicar la cantidad de pixeles horizontales" << std::endl;
          return SUCCESS;
      }
      if (vm.count("-v")){

      }
      else{
          std::cout << "Debe indicar la cantidad de pixeles verticales" << std::endl;
          return SUCCESS;
      }

      if (vm.count("-q")){
          q = true;

      }
      else if (vm.count("-f")){
            f = true;
      }


 
      po::notify(vm); // throws on error, so do after help in case 
                      // there are any problems 
    } 
    catch(po::error& e) 
    { 
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
      std::cerr << desc << std::endl; 
      return ERROR_IN_COMMAND_LINE; 
    } 
 
    // application code here // 
 
  } 
  catch(std::exception& e) 
  { 
    std::cerr << "Unhandled Exception reached the top of main: " 
              << e.what() << ", application will now exit" << std::endl; 
    return ERROR_UNHANDLED_EXCEPTION; 
 
  } 
 
  return SUCCESS; 
 
} // main 