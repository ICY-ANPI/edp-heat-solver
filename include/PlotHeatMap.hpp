/**
 *
 * Plotting HeatMap in python, wrapping Matplotlib (Python)
 * @author: Cristian Rivera Lopez.
 * @email: crisrivlop@gmail.com
 * @date:   07.06.2018
 */

#ifndef ANPI_PLOTHEATMAP_HPP
#define ANPI_PLOTHEATMAP_HPP

#include <python2.7/Python.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Matrix.hpp"

namespace anpi {
  
  /**
   * Two-dimensional plots
   *
   * Given a set of x coordinates and a corresponding set of y values,
   * plot a line between each point (x,y).
   *
   * You give a pair of vectors with the x and y values with the
   * plot() method to plot a curve.  You may overlay as many curves as
   * you need simply by calling plot() as many times as you need to.
   *
   * Finally, you call show() to display the window with all plotted curves.
   */
  template<typename T>
  class  PlotHeadMap {    
  public:
    /// Constructors
    //@{
    PlotHeadMap();
    ~PlotHeadMap();
    //@}
   
    /**
     * Initialize a plot window.
     *
     * Each id is associated with a different plot window.
     */
    void initialize(int id);

    /**
     * Plot a curve by drawing line segments from
     * the sequence of points (datax[i],datay[i]).  The
     * curve will have the given legend 
     */
    void plot(const anpi::Matrix<T>& data);
    
    /**
     * Show all curves plotted so far.
     */
    void show();


  }; //class Plot2d

} // namespace anpi
  
#include "PlotHeatMap.tpp"

#endif // PLOTHEADMAP_H
