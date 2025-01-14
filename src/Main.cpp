#include "Utils.h"
#include "BackgroundCosmology.h"
#include "RecombinationHistory.h"
#include "Perturbations.h"
#include "PowerSpectrum.h"
#include "SupernovaFitting.h"

int main(int argc, char **argv){
  Utils::StartTiming("Everything");

  //=========================================================================
  // Parameters
  //=========================================================================

  //Background parameters
  //double h           = 0.7;//0.67;
  //double OmegaB      = 0.05;
  //double OmegaCDM    = 0.45;//0.267;
  //double OmegaK      = 0.0;
  //double Neff        = 0;//3.046;
  //double TCMB        = 2.7255;

  //double h           = 0.67;
  //double OmegaB      = 0.05;
  //double OmegaCDM    = 0.267;
  //double OmegaK      = 0.0;
  //double Neff        = 3.046;
  //double TCMB        = 2.7255;

  double h           = 0.67;
  double OmegaB      = 0.05;
  double OmegaCDM    = 0.267;
  double OmegaK      = 0.0;
  double Neff        = 0.;//3.046;
  double TCMB        = 2.7255;


  // Recombination parameters
  double Yp          = 0.0;

  // Power-spectrum parameters
  double A_s         = 2.1e-9;
  double n_s         = 0.965;
  double kpivot_mpc  = 0.05;

  //=========================================================================
  // Module I
  //=========================================================================

  // Set up and solve the background
  BackgroundCosmology cosmo(h, OmegaB, OmegaCDM, OmegaK, Neff, TCMB);
  cosmo.solve();
  //cosmo.info();  
  // Output background evolution quantities
  //cosmo.output("cosmology.txt");

  //mcmc_fit_to_supernova_data("data/supernovadata.txt", "results.txt");

  // Remove when module is completed
  //return 0;

  //=========================================================================
  // Module II
  //=========================================================================
  
  // Solve the recombination history
  RecombinationHistory rec(&cosmo, Yp);
  //std::cout << "before rec" << std::endl;
  rec.solve();
  //rec.info();

  // Output recombination quantities
  //rec.output("recombination_separate_solutions.txt");
  //rec.output("recombination.txt");
  
  // Remove when module is completed
  //return 0;

  //=========================================================================
  // Module III
  //=========================================================================
 
  // Solve the perturbations
  //neutrinos are turned off
  Perturbations pert(&cosmo, &rec);

  pert.solve();
  //pert.info();
  
  // Output perturbation quantities
  //double kvalue0 = 0.001 / Constants.Mpc;
  //double kvalue1 = 0.01 / Constants.Mpc;
  //double kvalue2 = 0.1 / Constants.Mpc;
  //pert.output(kvalue0, "perturbations_k_0_001.txt");
  //pert.output(kvalue1, "perturbations_k_0_01.txt");
  //pert.output(kvalue2, "perturbations_k_0_1.txt");

  
  // Remove when module is completed
  //return 0;
  
  //=========================================================================
  // Module IV
  //=========================================================================
  
  
  //takes 16 min to run
  PowerSpectrum power(&cosmo, &rec, &pert, A_s, n_s, kpivot_mpc);
  power.solve();
  //power.output("cells_result_test_311610.txt");
  //power.output_matter("matter_power_spectrum_result_no_neutronos.txt");
  // Remove when module is completed
  //power.output_Source("source_new.txt");
  //power.output_45("45_new.txt");
  //power.output_test45("test45_new.txt");
  //power.output_matter("matter_test_311610.txt");
  //power.output_stuff("stuff_2.txt");
  //power.output_stuff("stuff_3.txt");
  //power.output_stuff("stuff_4.txt");

  

  Utils::EndTiming("Everything");
  return 0;
}
