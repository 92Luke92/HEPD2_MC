/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCEventAction.hh file              //
//                                         //
/////////////////////////////////////////////

#ifndef HEPD2MCEventAction_h
#define HEPD2MCEventAction_h 1

#include "HEPD2MCDetConst.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"

#include <vector>
#include <array>


class HEPD2MCEventAction : public G4UserEventAction
{
public:
  HEPD2MCEventAction();
  virtual ~HEPD2MCEventAction();
  
  virtual void  BeginOfEventAction(const G4Event* event);
  virtual void  EndOfEventAction(const G4Event* event);
  
  void AddAbso(G4double de, G4double dl, G4int copynumber);
  
  void AddVetoB(G4double de, G4double dl);
  void AddVetoL1(G4double de, G4double dl);
  void AddVetoL2(G4double de, G4double dl);
  void AddVetoL3(G4double de, G4double dl);
  void AddVetoL4(G4double de, G4double dl);
  
  void AddTBars1(G4double de, G4double dl, G4int copynumber);
  void AddTBars2(G4double de, G4double dl, G4int copynumber);
  void AddCBars1(G4double de, G4double dl, G4int copynumber);
  void AddCBars2(G4double de, G4double dl, G4int copynumber);
  
  void AddAlp(G4double de, G4double dl, G4int copynumber, G4double X, G4double Y, G4double Z);
  
  void AddAlpMSC(G4int copynumber, G4double theta, G4double phi);
  void AddEBeforeT1(G4double E);
  void AddEBeforeT2(G4double E);
  void AddEBeforeP1(G4double E);
  
  std::vector<G4double>& GetVgen() {return fVgen;}
  std::vector<G4double>& GetVp() {return fVp;}
  std::vector<G4double>& GetVT1Edep() {return fVT1Edep;}
  std::vector<G4double>& GetVT2Edep() {return fVT2Edep;}
  std::vector<G4double>& GetVPEdep() {return fVPEdep;}
  std::vector<G4double>& GetVL1Edep() {return fVL1Edep;}
  std::vector<G4double>& GetVL2Edep() {return fVL2Edep;}
  std::vector<G4double>& GetVVEdep() {return fVVEdep;}
  
  std::vector<G4double>& GetVT1Leng() {return fVT1Leng;}
  std::vector<G4double>& GetVT2Leng() {return fVT2Leng;}
  std::vector<G4double>& GetVPLeng() {return fVPLeng;}
  std::vector<G4double>& GetVL1Leng() {return fVL1Leng;}
  std::vector<G4double>& GetVL2Leng() {return fVL2Leng;}
  std::vector<G4double>& GetVVLeng() {return fVVLeng;}
  
  std::vector<G4double>& GetAlp1Pos() {return fVAlp1Pos;}
  std::vector<G4double>& GetAlp2Pos() {return fVAlp2Pos;}
  std::vector<G4double>& GetAlp3Pos() {return fVAlp3Pos;}
  
  std::vector<G4double>& GetAlp1Dir() {return fVAlp1Dir;}
  std::vector<G4double>& GetAlp2Dir() {return fVAlp2Dir;}
  std::vector<G4double>& GetAlp3Dir() {return fVAlp3Dir;}
  
  void AddPhot(G4int pmtID);
  std::vector<G4int>& GetPhot() {return fVphot;}
  
private:
  
  std::vector<G4double> fVgen;
  std::vector<G4double> fVp;
  std::vector<G4double> fVT1Edep;
  std::vector<G4double> fVT2Edep;
  std::vector<G4double> fVPEdep;
  std::vector<G4double> fVL1Edep;
  std::vector<G4double> fVL2Edep;
  std::vector<G4double> fVVEdep;
  
  std::vector<G4int> fVphot;
  
  std::vector<G4double> fVT1Leng;
  std::vector<G4double> fVT2Leng;
  std::vector<G4double> fVPLeng;
  std::vector<G4double> fVL1Leng;
  std::vector<G4double> fVL2Leng;
  std::vector<G4double> fVVLeng;
  
  G4double  fTA[3];
  G4double  fTT1[NBARS];
  G4double  fTT2[NBARS];
  G4double  fTP[NCOUPLEDPLANES+1];
  G4double  fTC1[NCRYSTALS];
  G4double  fTC2[NCRYSTALS];
  
  G4double fTVL1;
  G4double fTVL2;
  G4double fTVL3;
  G4double fTVL4;
  G4double fTVB;

  G4int fPhot[NPMTS];
  
  G4double  fEA[3];
  G4double  fET1[NBARS];
  G4double  fET2[NBARS];
  G4double  fEP[NCOUPLEDPLANES+1];
  G4double  fEC1[NCRYSTALS];
  G4double  fEC2[NCRYSTALS];
  
  G4double fEVL1;
  G4double fEVL2;
  G4double fEVL3;
  G4double fEVL4;
  G4double fEVB;

  std::vector<G4double> fVAlp1Pos;
  std::vector<G4double> fVAlp2Pos;
  std::vector<G4double> fVAlp3Pos;
  G4double fAlp1Pos[3], fAlp2Pos[3], fAlp3Pos[3];
  
  std::vector<G4double> fVAlp1Dir;
  std::vector<G4double> fVAlp2Dir;
  std::vector<G4double> fVAlp3Dir;
  G4double fAlp1Dir[2], fAlp2Dir[2], fAlp3Dir[2];

  G4double fEBeforeT1;
  G4double fEBeforeT2;
  G4double fEBeforeP1;
};

// inline functions
inline void HEPD2MCEventAction::AddAbso(G4double de, G4double dl, G4int copynumber) {fEP[copynumber] += de; fTP[copynumber] += dl;}
inline void HEPD2MCEventAction::AddVetoB(G4double de, G4double dl) {fEVB += de; fTVB += dl;}
inline void HEPD2MCEventAction::AddVetoL1(G4double de, G4double dl) {fEVL1 += de; fTVL1 += dl;}
inline void HEPD2MCEventAction::AddVetoL2(G4double de, G4double dl) {fEVL2 += de; fTVL2 += dl;}
inline void HEPD2MCEventAction::AddVetoL3(G4double de, G4double dl) {fEVL3 += de; fTVL3 += dl;}
inline void HEPD2MCEventAction::AddVetoL4(G4double de, G4double dl) {fEVL4 += de; fTVL4 += dl;}
inline void HEPD2MCEventAction::AddTBars1(G4double de, G4double dl, G4int copynumber) {fET1[copynumber] += de; fTT1[copynumber] += dl;}
inline void HEPD2MCEventAction::AddTBars2(G4double de, G4double dl, G4int copynumber) {fET2[copynumber] += de; fTT2[copynumber] += dl;}
inline void HEPD2MCEventAction::AddCBars1(G4double de, G4double dl, G4int copynumber) {fEC1[copynumber] += de; fTC1[copynumber] += dl;}
inline void HEPD2MCEventAction::AddCBars2(G4double de, G4double dl, G4int copynumber) {fEC2[copynumber] += de; fTC2[copynumber] += dl;}

inline void HEPD2MCEventAction::AddAlp(G4double de, G4double dl, G4int copynumber, G4double X, G4double Y, G4double Z) {
  
  G4int nplane = copynumber/100;
  //G4int ncol = (copynumber-(copynumber/100)*100)/10;
  //G4int nrow = copynumber-(copynumber/100)*100-((copynumber-(copynumber/100)*100)/10)*10;
  
  fEA[nplane-1] += de;
  fTA[nplane-1] += dl;
  
  if(nplane==1){
    fAlp1Pos[0] = X;
    fAlp1Pos[1] = Y;
    fAlp1Pos[2] = Z;
  }
  
  if(nplane==2){
    fAlp2Pos[0] = X;
    fAlp2Pos[1] = Y;
    fAlp2Pos[2] = Z;
  }
  
  if(nplane==3){
    fAlp3Pos[0] = X;
    fAlp3Pos[1] = Y;
    fAlp3Pos[2] = Z;
  }
  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void HEPD2MCEventAction::AddAlpMSC(G4int copynumber, G4double theta, G4double phi) {
  
  G4int nplane = copynumber/100;
  
  if(nplane==1){
    fAlp1Dir[0] = theta;
    fAlp1Dir[1] = phi;
  }
  
  if(nplane==2){
    fAlp2Dir[0] = theta;
    fAlp2Dir[1] = phi;
  }
  
  if(nplane==3){
    fAlp3Dir[0] = theta;
    fAlp3Dir[1] = phi;
  }
  
}


inline void HEPD2MCEventAction::AddEBeforeT1(G4double E){
  fEBeforeT1 = E;
}

inline void HEPD2MCEventAction::AddEBeforeT2(G4double E){
  fEBeforeT2 = E;
}

inline void HEPD2MCEventAction::AddEBeforeP1(G4double E){
  fEBeforeP1 = E;
}

inline void HEPD2MCEventAction::AddPhot(G4int pmtID){fPhot[pmtID] += 1;}

#endif
