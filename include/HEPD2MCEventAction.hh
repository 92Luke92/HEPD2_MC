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
  
  void AddPlane(G4double X,  G4double Y, G4double de, G4double dl, G4int copynumber);
  
  void AddBotVeto(G4double de, G4double dl);
  void AddLatVeto(G4double de, G4double dl, G4int copyNumber);
  
  void AddT1Bars(G4double X,  G4double Y, G4double de, G4double dl, G4int copynumber);
  void AddT2Bars(G4double X,  G4double Y, G4double de, G4double dl, G4int copynumber);
  void AddC1Bars(G4double de, G4double dl, G4int copynumber);
  void AddC2Bars(G4double de, G4double dl, G4int copynumber);
  
  void AddAlp(G4double de, G4double dl, G4int copynumber, G4double X, G4double Y, G4double Z);
  
  void AddAlpMSC(G4int copynumber, G4double theta, G4double phi);
  void AddAlpMSCPre(G4int copynumber, G4double theta, G4double phi);
  void AddEBeforeT1(G4double E);
  void AddEBeforeT2(G4double E);
  void AddEBeforeP1(G4double E);
  void AddT1Pre(G4double theta, G4double phi);
  void AddT1Post(G4double theta, G4double phi);
  
  void AddGammaKin(G4double E);
  
  void AddWin(G4double X, G4double Y, G4double Z, G4double theta, G4double phi);

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

  std::vector<G4double> &GetWinPos() { return fVWinPos; }
  std::vector<G4double> &GetWinDir() { return fVWinDir; }
  std::vector<G4double> &GetT1Dir() { return fVT1Dir; }
  std::vector<G4double> &GetT1Pos() {  return fVT1Pos;}
  std::vector<G4double> &GetT2Pos() {  return fVT2Pos;}
  std::vector<G4double> &GetPPosX() {  return fVPPosX;}
  std::vector<G4double> &GetPPosY() {  return fVPPosY;}




  void AddPhot(G4int pmtID);
  void AddPhotEnergy(G4int pmtID, G4double E);
  std::vector<G4int>& GetPhot() {return fVphot;}
  std::vector<G4double>& GetPhotEnergy() {return fVphotenergy;}
  
private:
  
  std::vector<G4double> fVgen;
  std::vector<G4double> fVp;
  std::vector<G4double> fVT1Edep;
  std::vector<G4double> fVT2Edep;
  std::vector<G4double> fVPEdep;
  std::vector<G4double> fVL1Edep;
  std::vector<G4double> fVL2Edep;
  std::vector<G4double> fVVEdep;
  std::vector<G4double> fVT1Dir;

  std::vector<G4int> fVphot;
  std::vector<G4double> fVphotenergy;
  
  std::vector<G4double> fVT1Leng;
  std::vector<G4double> fVT2Leng;
  std::vector<G4double> fVT1Pos;
  std::vector<G4double> fVT2Pos;
  std::vector<G4double> fVPLeng;
  std::vector<G4double> fVPPosX;
  std::vector<G4double> fVPPosY;
  std::vector<G4double> fVL1Leng;
  std::vector<G4double> fVL2Leng;
  std::vector<G4double> fVVLeng;
  std::vector<G4double> fVWinPos;
  std::vector<G4double> fVWinDir;
  G4double fWinDir[2], fWinPos[3];

  G4double fTA[3];
  G4double  fTT1[NBARST1];
  G4double  fPT1[NBARST1];
  G4double  fTT2[NBARST2];
  G4double  fPT2[NBARST2];
  G4double  fTP[NCALOPLANES];
  G4double  fXP[NCALOPLANES];
  G4double  fYP[NCALOPLANES];
  G4double  fTC1[NCRYSTALS];
  G4double  fTC2[NCRYSTALS];
  G4double  fT1Dir[4];

  G4double fTVL[4];
  G4double fTVB;
  
  G4int fPhot[NPMTS];
  G4double fPhotEnergy[NPMTS];
  
  G4double  fEA[3];
  G4double  fET1[NBARST1];
  G4double  fET2[NBARST2];
  G4double  fEP[NCALOPLANES];
  G4double  fEC1[NCRYSTALS];
  G4double  fEC2[NCRYSTALS];
  
  G4double fEVL[4];
  G4double fEVB;

  std::vector<G4double> fVAlp1Pos;
  std::vector<G4double> fVAlp2Pos;
  std::vector<G4double> fVAlp3Pos;
  G4double fAlp1Pos[3], fAlp2Pos[3], fAlp3Pos[3];
  
  std::vector<G4double> fVAlp1Dir;
  std::vector<G4double> fVAlp2Dir;
  std::vector<G4double> fVAlp3Dir;
  G4double fAlp1Dir[4], fAlp2Dir[4], fAlp3Dir[4];
  
  G4double fGammaKin;
  
  G4double fEBeforeT1;
  G4double fEBeforeT2;
  G4double fEBeforeP1;
};

// inline functions
inline void HEPD2MCEventAction::AddT1Pre(G4double theta, G4double phi){
  fT1Dir[0]=theta;
  fT1Dir[1]=phi;
}

inline void HEPD2MCEventAction::AddT1Post(G4double theta, G4double phi){
  fT1Dir[2]=theta;
  fT1Dir[3]=phi;
}

inline void HEPD2MCEventAction::AddAlp(G4double de, G4double dl, G4int copynumber, G4double X, G4double Y, G4double Z)
{
  G4int nplane = copynumber;
  
  fEA[nplane] += de;
  fTA[nplane] += dl;
  
  if(nplane==0){
    fAlp1Pos[0] = X;
    fAlp1Pos[1] = Y;
    fAlp1Pos[2] = Z;
  }
  
  if(nplane==1){
    fAlp2Pos[0] = X;
    fAlp2Pos[1] = Y;
    fAlp2Pos[2] = Z;
  }
  
  if(nplane==2){
    fAlp3Pos[0] = X;
    fAlp3Pos[1] = Y;
    fAlp3Pos[2] = Z;
  }
  
}

inline void HEPD2MCEventAction::AddWin(G4double X, G4double Y, G4double Z, G4double theta, G4double phi)
{
  fWinPos[0] = X;
  fWinPos[1] = Y;
  fWinPos[2] = Z;
  fWinDir[0] = theta;
  fWinDir[1] = phi;
}



inline void HEPD2MCEventAction::AddAlpMSC(G4int copynumber, G4double theta, G4double phi)
{
  G4int nplane = copynumber;
  
  if(nplane==0){
    fAlp1Dir[0] = theta;
    fAlp1Dir[1] = phi;
  }
  
  if(nplane==1){
    fAlp2Dir[0] = theta;
    fAlp2Dir[1] = phi;
  }
  
  if(nplane==2){
    fAlp3Dir[0] = theta;
    fAlp3Dir[1] = phi;
  }
  
}

inline void HEPD2MCEventAction::AddAlpMSCPre(G4int copynumber, G4double theta, G4double phi)
{
  G4int nplane = copynumber;

  if (nplane == 0)
  {
    fAlp1Dir[2] = theta;
    fAlp1Dir[3] = phi;
  }

  if (nplane == 1)
  {
    fAlp2Dir[2] = theta;
    fAlp2Dir[3] = phi;
  }

  if (nplane == 2)
  {
    fAlp3Dir[2] = theta;
    fAlp3Dir[3] = phi;
  }
}


inline void HEPD2MCEventAction::AddT1Bars(G4double X,  G4double Y, G4double de, G4double dl, G4int copynumber)
{
  fET1[copynumber] += de;
  fTT1[copynumber] += dl;
  fPT1[0]  = X;
  fPT1[1]  = Y;}

inline void HEPD2MCEventAction::AddT2Bars(G4double X,  G4double Y, G4double de, G4double dl, G4int copynumber)
{
  fET2[copynumber] += de;
  fTT2[copynumber] += dl;
  fPT2[0]  = X;
  fPT2[1]  = Y;
}

inline void HEPD2MCEventAction::AddPlane(G4double X,  G4double Y, G4double de, G4double dl, G4int copynumber)
{
  fEP[copynumber] += de;
  fTP[copynumber] += dl;
  fXP[copynumber]  = X;
  fYP[copynumber]  = Y;
}

inline void HEPD2MCEventAction::AddC1Bars(G4double de, G4double dl, G4int copynumber)
{
  fEC1[copynumber] += de;
  fTC1[copynumber] += dl;
}

inline void HEPD2MCEventAction::AddC2Bars(G4double de, G4double dl, G4int copynumber)
{
  fEC2[copynumber] += de;
  fTC2[copynumber] += dl;
}

inline void HEPD2MCEventAction::AddBotVeto(G4double de, G4double dl)
{
  fEVB += de;
  fTVB += dl;
}

inline void HEPD2MCEventAction::AddLatVeto(G4double de, G4double dl, G4int copynumber)
{
  fEVL[copynumber] += de;
  fTVL[copynumber] += dl;
}


inline void HEPD2MCEventAction::AddEBeforeT1(G4double E)
{
  fEBeforeT1 = E;
}

inline void HEPD2MCEventAction::AddEBeforeT2(G4double E)
{
  fEBeforeT2 = E;
}

inline void HEPD2MCEventAction::AddEBeforeP1(G4double E)
{
  fEBeforeP1 = E;
}

inline void HEPD2MCEventAction::AddGammaKin(G4double E)
{
  fGammaKin += E;
}

inline void HEPD2MCEventAction::AddPhot(G4int pmtID)
{
  fPhot[pmtID] += 1;
}

inline void HEPD2MCEventAction::AddPhotEnergy(G4int pmtID, G4double E)
{
  fPhotEnergy[pmtID] = E;
}

#endif
