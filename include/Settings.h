#ifndef Settings_h
#define Settings_h

using namespace std;

class Settings
{

public:
	
	Settings();
	~Settings();
   
//   static int GetNumberOfProcesses() { return num_of_processes; }
//   static int GetNumberOfFinalStates() { return MAX_NUM_OF_FINAL_STATES + 1 ; }
//   static int GetNumberOfResonantStatuses() { return MAX_NUM_OF_RESONANT_STATUSES + 1; }
   
   enum _blindings { fullyblind = 0, blindabove_110 = 1, blindbelow_150 = 2, blind_110_150 = 3, unblinded = 4 };
   enum _process { Data = 0, H125 = 1, H125VBF = 2, H125NOVBF = 3, qqZZ = 4, ggZZ = 5, DY = 6, ttbar = 7, MAX_NUM_OF_PROCESSES };
   enum _final_state { fs4mu = 0, fs4e = 1, fs2e2mu = 2, fs2mu2e = 3, fs4l = 4, MAX_NUM_OF_FINAL_STATES };
   enum _resonant_status { resonant = 0, nonresonant = 1, all_resonant = 2, MAX_NUM_OF_RESONANT_STATUSES };
   enum _category { untagged = 0, VBF_1j_tagged = 1, VBF_2j_tagged = 2, VH_lepton_tagged = 3, VH_hadron_tagged = 4, ttH_tagged = 5,
                    inclusive = 6, MAX_NUM_OF_CATEGORIES };
   enum _plot_name { M4lMain = 0, M4lMainZoomed = 1, MAX_NUM_OF_PLOT_NAMES};


   static const int num_of_processes    = MAX_NUM_OF_PROCESSES;
   static const int num_of_final_states = MAX_NUM_OF_FINAL_STATES;
   static const int num_of_res_statuses = MAX_NUM_OF_RESONANT_STATUSES;
   static const int num_of_categories   = MAX_NUM_OF_CATEGORIES;
   static const int num_of_plot_names   = MAX_NUM_OF_PLOT_NAMES;
   
   private:
   
};

#endif