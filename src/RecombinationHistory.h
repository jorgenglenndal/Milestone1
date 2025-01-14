#ifndef _RECOMBINATION_HISTORY_HEADER
#define _RECOMBINATION_HISTORY_HEADER
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "BackgroundCosmology.h"

using Vector = std::vector<double>;

class RecombinationHistory{
  private:

    // The cosmology we use
    BackgroundCosmology *cosmo = nullptr;
    
    // Helium fraction
    double Yp = 0;

    // cosmological parameters
    //double rho_c0;
    //double OmegaB0;
 
    // The start and end points for recombination arrays (can be modified) 
    const double x_start  = Constants.x_start;  //remember this
    const double x_end    = Constants.x_end;
    const double x_today  = Constants.x_today;
    const double x_very_very_early  = Constants.x_very_very_early;
    const double x_decoupling  = Constants.x_decoupling;
    
    // Numbers of points of Xe,ne array (modify as you see fit)
    const int npts_rec_arrays = 1e3;
  
    // Xe for when to switch between Saha and Peebles
    const double Xe_saha_limit = 0.99;

    //===============================================================
    // [1] Computation of Xe (Saha and Peebles equation)
    //===============================================================
 
    // Compute Xe from the Saha equation
    std::pair<double,double> electron_fraction_from_saha_equation(double x) const;
    
    // Right hand side of the dXedx Peebles equation
    int rhs_peebles_ode(double x, const double *y, double *dydx);
    
    // Solve for Xe 
    void solve_number_density_electrons();
    void solve_number_density_electrons_with_separate_solutions();
    
    //===============================================================
    // [2] Compute tau and visibility functions
    //===============================================================

    // The two things we need to solve: Xe/ne and tau
    void solve_for_optical_depth_tau();
    double g_tilde(double x) const;
    
    // sound horizon
    void sound_horizon();

    // Splines contained in this class
    Spline Xe_of_x_spline{"Xe"};
    Spline log_ne_of_x_spline{"ne"};
    Spline tau_of_x_spline{"tau"}; 
    Spline g_tilde_of_x_spline{"g"};  
    Spline sound_horizon_spline{"SH"};

    Spline Xe_of_x_saha_spline{"Xe_saha"};
    Spline log_ne_of_x_saha_spline{"ne_saha"};
    Spline Xe_of_x_peebles_spline{"Xe_peebles"};
    Spline log_ne_of_x_peebles_spline{"ne_peebles"};

  public:

    // Construtors
    RecombinationHistory() = delete;
    RecombinationHistory(
        BackgroundCosmology *cosmo, 
        double Yp);//,double rho_c0,double OmegaB0);

    // Do all the solving
    void solve();

    
    // Print some useful info about the class
    void info();

    // Output some data to file
    void output(const std::string filename) const;

    // Get functions that we must implement

    double tau_of_x(double x) const;
    double dtaudx_of_x(double x) const;
    double ddtauddx_of_x(double x) const;
    double g_tilde_of_x(double x) const;
    double dgdx_tilde_of_x(double x) const;
    double ddgddx_tilde_of_x(double x) const;
    double Xe_of_x(double x) const;
    double ne_of_x(double x) const;
    double get_Yp() const;
    double get_sound_horizon(double x) const;

    double Xe_of_x_saha(double x) const;
    double Xe_of_x_peebles(double x) const;
};

#endif
