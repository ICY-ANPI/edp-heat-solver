/**
 * Copyright (C) 2017 
 * Área Académica de Ingeniería en Computadoras, TEC, Costa Rica
 *
 * This file is part of the CE3102 Numerical Analysis lecture at TEC
 *
 * Plotting methods, wrapping Matplotlib (Python)
 * @author: David Badilla S.
 * @email: davbs94@gmail.com
 * @date:   15.07.2017
 */

namespace anpi {

  template <typename T>
  PlotHeadMap<T>::PlotHeadMap(){}

  template <typename T>
  PlotHeadMap<T>::~PlotHeadMap(){}
  
  template <typename T>
  void PlotHeadMap<T>::initialize(int id){
    Py_Initialize();
    PyRun_SimpleString("import matplotlib.pylab as plt");
  }

  template <typename T>
  void PlotHeadMap<T>::plot(const anpi::Matrix<T>& data) {
    std::string str = "data = [";
    std::string pltcmd = "ax = plt.imshow(data, cmap='jet', interpolation='nearest')";

    for(size_t i = 0; i < data.rows(); i++) {
      str.append("[");
      for(size_t j = 0; j < data.cols()-1; j++) {
          str.append(std::to_string(data[i][j]) + ",");
      }
      str.append(std::to_string(data[i][data.cols()-1]) + "]");
      if (i < data.rows()-1) str.append(+ ",");
      else str.append("]");
    }

    PyRun_SimpleString(str.c_str());
    PyRun_SimpleString(pltcmd.c_str());
    PyRun_SimpleString("plt.axis('off')");
  }

  
  template <typename T>
  void PlotHeadMap<T>::show(){
    PyRun_SimpleString("plt.show()");
  }
  
} // namespace anpi
