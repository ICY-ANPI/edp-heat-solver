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
    std::string pltcmd = "ax = plt.imshow(data, cmap='jet', interpolation='bicubic')";

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
    PyRun_SimpleString("plt.colorbar()");
  }

  template <typename T>
  void PlotHeadMap<T>::quiver(vector<T>& x,vector<T>& y, vector<T>& u,vector<T>& v){
      std::string xstr = "x = [";
      std::string ystr = "y = [";
      std::string ustr = "u = [";
      std::string vstr = "v = [";
      std::string pltcmd = "plt.quiver(x,y,u,v)";

      for(size_t i = 0; i < x.size()-1; i++) {
          xstr.append(std::to_string(x[i]) + ",");
          ystr.append(std::to_string(y[i]) + ",");
          ustr.append(std::to_string(u[i]) + ",");
          vstr.append(std::to_string(v[i]) + ",");
      }
      xstr.append(std::to_string(x[x.size()-1]) + "]");
      ystr.append(std::to_string(y[x.size()-1]) + "]");
      ustr.append(std::to_string(u[x.size()-1]) + "]");
      vstr.append(std::to_string(v[x.size()-1]) + "]");
    PyRun_SimpleString(xstr.c_str());
    PyRun_SimpleString(ystr.c_str());
    PyRun_SimpleString(ustr.c_str());
    PyRun_SimpleString(vstr.c_str());
    PyRun_SimpleString(pltcmd.c_str());
  }

  
  template <typename T>
  void PlotHeadMap<T>::show(){
    PyRun_SimpleString("plt.show()");
  }
  
} // namespace anpi
