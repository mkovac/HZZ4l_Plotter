// Include classes
#include "M4lZX.h"
#include "ZXVariables.h"

using namespace std;

// Constructor
//============
M4lZX::M4lZX()
{
   _n_entries = 1000000; // Tried more entries, but it takes way too long to run
   _bin_down  = 70.;
   _bin_up    = 3000.; // Define full mass range
   
   
   f_4e_comb    = new TF1("f_4e_comb", "TMath::Landau(x, [0], [1])", _bin_down, _bin_up);
   f_4mu_comb   = new TF1("f_4mu_comb","TMath::Landau(x, [0], [1])", _bin_down, _bin_up);
   f_2e2mu_comb = new TF1("f_2e2mu_comb","[0]*TMath::Landau(x, [1], [2]) + [3]*TMath::Landau(x, [4], [5])", _bin_down, _bin_up);

   f_4e_comb->SetParameters(ZXVariables::ZX4e().par0, ZXVariables::ZX4e().par1);
   f_4mu_comb->SetParameters(ZXVariables::ZX4mu().par0, ZXVariables::ZX4mu().par1);
   f_2e2mu_comb->SetParameters(ZXVariables::ZX2e2mu().par0, ZXVariables::ZX2e2mu().par1, ZXVariables::ZX2e2mu().par2, ZXVariables::ZX2e2mu().par3, ZXVariables::ZX2e2mu().par4, ZXVariables::ZX2e2mu().par5);

}
//=====================


//================
M4lZX::~M4lZX()
{
}
//================

//===================================================================================
void M4lZX::GetM4lZX(int n_bins, int x_min, int x_max, int category, TH1F* h_4e, TH1F* h_4mu, TH1F* h_2e2mu, TH1F* h_4l )
{ 
   SetNormalization(category);
    
   _norm_4mu = _norm_ZX_full_SR_4mu * f_4mu_comb->Integral(x_min, x_max) / f_4mu_comb->Integral(_bin_down, _bin_up);
   _norm_4e = _norm_ZX_full_SR_4e * f_4e_comb->Integral(x_min, x_max) / f_4e_comb->Integral(_bin_down, _bin_up);
   _norm_2e2mu = _norm_ZX_full_SR_2e2mu * f_2e2mu_comb->Integral(x_min, x_max) / f_2e2mu_comb->Integral(_bin_down, _bin_up);
   
   h_4mu  ->FillRandom("f_4mu_comb"  , _n_entries);
   h_4e   ->FillRandom("f_4e_comb"   , _n_entries);
   h_2e2mu->FillRandom("f_2e2mu_comb", _n_entries);
   
   h_4mu  ->Scale(_norm_4mu   / h_4mu->Integral());
   h_4e   ->Scale(_norm_4e    / h_4e->Integral());
   h_2e2mu->Scale(_norm_2e2mu / h_2e2mu->Integral());
  
   h_4l->Add(h_4mu);
   h_4l->Add(h_4e);
   h_4l->Add(h_2e2mu);
}
//===================================================================================



//================================================================================
double M4lZX::GetM4lZX_Yields(int x_min, int x_max, int final_state, int category)
{ 
   SetNormalization(category);

   _norm_4mu = _norm_ZX_full_SR_4mu * f_4mu_comb->Integral(x_min, x_max) / f_4mu_comb->Integral(_bin_down, _bin_up);
   _norm_4e = _norm_ZX_full_SR_4e * f_4e_comb->Integral(x_min, x_max) / f_4e_comb->Integral(_bin_down, _bin_up);
   _norm_2e2mu = _norm_ZX_full_SR_2e2mu * f_2e2mu_comb->Integral(x_min, x_max) / f_2e2mu_comb->Integral(_bin_down, _bin_up);
   
   if ( final_state == Settings::fs4mu ) return _norm_4mu;
   else if (final_state == Settings::fs4e)  return _norm_4e;
   else if (final_state == Settings::fs2e2mu) return _norm_2e2mu;
   else if (final_state == Settings::num_of_final_states - 1) return _norm_4e + _norm_4mu + _norm_2e2mu;
   else
   {
      cout << "[ERROR] Computing Z+X histogram: wrong final state: " << final_state << endl;
      abort();
   }       
}
//================================================================================



//==========================================================================
void M4lZX::RenormalizeZX( int cat, vector< vector <float> > _expected_yield_SR, TH1F* histo4e_ZX, TH1F* histo4mu_ZX, TH1F* histo2e2mu_ZX)
{
   SetNormalization(cat);
   
   histo4e_ZX->Scale(_norm_ZX_full_SR_4e / _expected_yield_SR[Settings::fs4e][cat]);
   histo4mu_ZX->Scale(_norm_ZX_full_SR_4mu / _expected_yield_SR[Settings::fs4mu][cat]);
   histo2e2mu_ZX->Scale(_norm_ZX_full_SR_2e2mu / _expected_yield_SR[Settings::fs2e2mu][cat]);

}
//==========================================================================

//==========================================================================
void M4lZX::SetNormalization( int category)
{
    switch (category) {
        case 0:
        _norm_ZX_full_SR_4e    = ZXVariables::ZX4e().norm_untagged;
        _norm_ZX_full_SR_4mu   = ZXVariables::ZX4mu().norm_untagged;
        _norm_ZX_full_SR_2e2mu = ZXVariables::ZX2e2mu().norm_untagged;
        break;
        
        case 1:
        _norm_ZX_full_SR_4e    = ZXVariables::ZX4e().norm_VBF_1j_tagged;
        _norm_ZX_full_SR_4mu   = ZXVariables::ZX4mu().norm_VBF_1j_tagged;
        _norm_ZX_full_SR_2e2mu = ZXVariables::ZX2e2mu().norm_VBF_1j_tagged;
        break;
        
        case 2:
        _norm_ZX_full_SR_4e    = ZXVariables::ZX4e().norm_VBF_2j_tagged;
        _norm_ZX_full_SR_4mu   = ZXVariables::ZX4mu().norm_VBF_2j_tagged;
        _norm_ZX_full_SR_2e2mu = ZXVariables::ZX2e2mu().norm_VBF_2j_tagged;
        break;
        
        case 3:
        _norm_ZX_full_SR_4e    = ZXVariables::ZX4e().norm_VH_lepton_tagged;
        _norm_ZX_full_SR_4mu   = ZXVariables::ZX4mu().norm_VH_lepton_tagged;
        _norm_ZX_full_SR_2e2mu = ZXVariables::ZX2e2mu().norm_VH_lepton_tagged;
        break;
        
        case 4:
        _norm_ZX_full_SR_4e    = ZXVariables::ZX4e().norm_VH_hadron_tagged;
        _norm_ZX_full_SR_4mu   = ZXVariables::ZX4mu().norm_VH_hadron_tagged;
        _norm_ZX_full_SR_2e2mu = ZXVariables::ZX2e2mu().norm_VH_hadron_tagged;
        break;
        
        case 5:
        _norm_ZX_full_SR_4e    = ZXVariables::ZX4e().norm_ttH_tagged;
        _norm_ZX_full_SR_4mu   = ZXVariables::ZX4mu().norm_ttH_tagged;
        _norm_ZX_full_SR_2e2mu = ZXVariables::ZX2e2mu().norm_ttH_tagged;
        break;
          
        case 6:
        _norm_ZX_full_SR_4e    = ZXVariables::ZX4e().norm_VH_MET_tagged;
        _norm_ZX_full_SR_4mu   = ZXVariables::ZX4mu().norm_VH_MET_tagged;
        _norm_ZX_full_SR_2e2mu = ZXVariables::ZX2e2mu().norm_VH_MET_tagged;
        break;
        
        case 7:
        _norm_ZX_full_SR_4e    = ZXVariables::ZX4e().norm_combined;
        _norm_ZX_full_SR_4mu   = ZXVariables::ZX4mu().norm_combined;
        _norm_ZX_full_SR_2e2mu = ZXVariables::ZX2e2mu().norm_combined;
        break;
        
        default:
        cout << "[ERROR] Computing Z+X histogram normalization wrong category: " << category << endl;
        abort();
        break;
    }

}
//==========================================================================
