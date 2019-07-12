/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCEventAction.cc file              //
//                                         //
/////////////////////////////////////////////

#include "HEPD2MCDetectorConstruction.hh"
#include "HEPD2MCEventAction.hh"
#include "HEPD2MCRunAction.hh"
#include "HEPD2MCAnalysis.hh"
#include "HEPD2MCDetConst.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

HEPD2MCEventAction::HEPD2MCEventAction()
 : G4UserEventAction(),
   fTA{0},
   fTT1{0},
   fTT2{0},
   fTP{0},
   fTC1{0},
   fTC2{0},
   fTVL1(0),
   fTVL2(0),
   fTVL3(0),
   fTVL4(0),
   fTVB(0),
   
   fPhot{0},
   
   fEA{0},
   fET1{0},
   fET2{0},
   fEP{0},
   fEC1{0},
   fEC2{0},
   fEVL1(0),
   fEVL2(0),
   fEVL3(0),
   fEVL4(0),
   fEVB(0),
   
   fAlp1Pos{0},
   fAlp2Pos{0},
   fAlp3Pos{0},
   
   fAlp1Dir{0},
   fAlp2Dir{0},
   fAlp3Dir{0},
   
   fEBeforeT1(0),
   fEBeforeT2(0),
   fEBeforeP1(0)
{
}

HEPD2MCEventAction::~HEPD2MCEventAction()
{
}

void HEPD2MCEventAction::BeginOfEventAction(const G4Event* /*event*/)
{
  // initialisation per event
  fVgen = {0.};
  fVp = {0.};
  fVT1Edep = {0.};
  fVT2Edep = {0.};
  fVPEdep = {0.};
  fVL1Edep = {0.};
  fVL2Edep = {0.};
  
  for (int i=0; i<3; i++) fAlp1Pos[i] = 0.;
  for (int i=0; i<3; i++) fAlp2Pos[i] = 0.;
  for (int i=0; i<3; i++) fAlp3Pos[i] = 0.;
  
  for (int i=0; i<2; i++) fAlp1Dir[i] = 0.;
  for (int i=0; i<2; i++) fAlp2Dir[i] = 0.;
  for (int i=0; i<2; i++) fAlp3Dir[i] = 0.;
  
  fEBeforeT1 = 0.;
  fEBeforeT2 = 0.;
  fEBeforeP1 = 0.;
  
  for (int i=0; i<3; i++) fEA[i] = 0.;
  for (int i = 0 ; i < NBARS ; i++) fET1[i]  = 0.;
  for (int i = 0 ; i < NBARS ; i++) fET2[i]  = 0.;
  for (int i = 0 ; i < NCOUPLEDPLANES+1 ; i++) fEP[i]=0.;
  for (int i = 0 ; i < NCRYSTALS ; i++) fEC1[i]=0.;
  for (int i = 0 ; i < NCRYSTALS ; i++) fEC2[i]=0.;
  fEVB  =0.;
  fEVL1 = 0.;
  fEVL2 = 0.;
  fEVL3 = 0.;
  fEVL4 = 0.;
  
  for (int i=0; i<NPMTS; i++) fPhot[i] = 0;
  
  for (int i=0; i<3; i++) fTA[i] = 0.;
  for (int i = 0 ; i < NBARS ; i++) fTT1[i]  = 0.;
  for (int i = 0 ; i < NBARS ; i++) fTT2[i]  = 0.;
  for (int i = 0 ; i < NCOUPLEDPLANES+1 ; i++) fTP[i]=0.;
  for (int i = 0 ; i < NCRYSTALS ; i++) fTC1[i]=0.;
  for (int i = 0 ; i < NCRYSTALS ; i++) fTC2[i]=0.;
  fTVB  =0.;
  fTVL1 = 0.;
  fTVL2 = 0.;
  fTVL3 = 0.;
  fTVL4 = 0.;
  
}

void HEPD2MCEventAction::EndOfEventAction(const G4Event* event)
{
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  G4PrimaryVertex* primaryVertex = event->GetPrimaryVertex();
  G4PrimaryParticle* primaryParticle = primaryVertex->GetPrimary();
  
  G4int particleid = primaryParticle->GetPDGcode();
  G4double energy = primaryParticle->GetKineticEnergy();
  G4double theta = primaryParticle->GetMomentumDirection().getTheta();
  G4double phi = primaryParticle->GetMomentumDirection().getPhi();
  theta *= 180./3.14;
  phi *= 180./3.14;
  
  G4double gen[3];
  gen[0] = primaryVertex->GetX0();
  gen[1] = primaryVertex->GetY0();
  gen[2] = primaryVertex->GetZ0();
  
  G4double p[3];
  p[0] = primaryParticle->GetPx();
  p[1] = primaryParticle->GetPy();
  p[2] = primaryParticle->GetPz();
  
  // fill ntuple
  analysisManager->FillNtupleIColumn(0, particleid);
  analysisManager->FillNtupleDColumn(1, energy);
  fVgen = {gen[0], gen[1], gen[2]};
  analysisManager->FillNtupleDColumn(2, theta);
  analysisManager->FillNtupleDColumn(3, phi);
  fVp = {p[0], p[1], p[2]};
  
  G4double Alp1Edep = 0.;
  Alp1Edep += fEA[0];
  analysisManager->FillNtupleDColumn(4, Alp1Edep);
  
  G4double Alp2Edep = 0.;
  Alp2Edep += fEA[1];
  analysisManager->FillNtupleDColumn(5, Alp2Edep);
  
  G4double Alp3Edep = 0.;
  Alp3Edep += fEA[2];
  analysisManager->FillNtupleDColumn(6, Alp3Edep);
  
  fVAlp1Pos = {fAlp1Pos[0], fAlp1Pos[1], fAlp1Pos[2]};
  fVAlp2Pos = {fAlp2Pos[0], fAlp2Pos[1], fAlp2Pos[2]};
  fVAlp3Pos = {fAlp3Pos[0], fAlp3Pos[1], fAlp3Pos[2]};
  
  fVAlp1Dir = {fAlp1Dir[0], fAlp1Dir[1]};
  fVAlp2Dir = {fAlp2Dir[0], fAlp2Dir[1]};
  fVAlp3Dir = {fAlp3Dir[0], fAlp3Dir[1]};
  
  if(NBARS!=5) G4cout << "WARNING: NBARS is " << NBARS << ". Modify code in EventAction" << G4endl;
  fVT1Edep = {fET1[0], fET1[1], fET1[2], fET1[3], fET1[4]};
  fVT2Edep = {fET2[0], fET2[1], fET2[2], fET2[3], fET2[4]};
  G4double TRIGEdep = fET1[0]+fET1[1]+fET1[2]+fET1[3]+fET1[4]+fET2[0]+fET2[1]+fET2[2]+fET2[3]+fET2[4];
  analysisManager->FillNtupleDColumn(7, TRIGEdep);
  
  if(NCOUPLEDPLANES+1!=11) G4cout << "WARNING: N planes is " << NCOUPLEDPLANES+1 << ". Modify code in EventAction" << G4endl;
  fVPEdep = {fEP[0], fEP[1], fEP[2], fEP[3], fEP[4], fEP[5], fEP[6], fEP[7], fEP[8], fEP[9], fEP[10]};
  G4double TOWEREdep = fEP[0]+fEP[1]+fEP[2]+fEP[3]+fEP[4]+fEP[5]+fEP[6]+fEP[7]+fEP[8]+fEP[9]+fEP[10];
  analysisManager->FillNtupleDColumn(8, TOWEREdep);
  
  if(NCRYSTALS!=3) G4cout << "WARNING: NCRYSTALS is " << NCRYSTALS << ". Modify code in EventAction" << G4endl;
  fVL1Edep = {fEC1[0], fEC1[1], fEC1[2]};
  fVL2Edep = {fEC2[0], fEC2[1], fEC2[2]};
  G4double LYSOEdep = fEC1[0]+fEC1[1]+fEC1[2]+fEC2[0]+fEC2[1]+fEC2[2];
  analysisManager->FillNtupleDColumn(9, LYSOEdep);
  G4double CALOEdep = TRIGEdep + TOWEREdep + LYSOEdep;
  analysisManager->FillNtupleDColumn(10, CALOEdep);
  
  fVVEdep = {fEVL1, fEVL2, fEVL3, fEVL4, fEVB};
  
  if(NPMTS!=64) G4cout << "WARNING: NPMTS is " << NPMTS << ". Modify code in EventAction" << G4endl;
  fVphot = {fPhot[0], fPhot[1], fPhot[2], fPhot[3], fPhot[4],
	    fPhot[5], fPhot[6], fPhot[7], fPhot[8], fPhot[9],
	    fPhot[10], fPhot[11], fPhot[12], fPhot[13], fPhot[14],
	    fPhot[15], fPhot[16], fPhot[17], fPhot[18], fPhot[19],
	    fPhot[20], fPhot[21], fPhot[22], fPhot[23], fPhot[24],
	    fPhot[25], fPhot[26], fPhot[27], fPhot[28], fPhot[29],
	    fPhot[30], fPhot[31], fPhot[32], fPhot[33], fPhot[34],
	    fPhot[35], fPhot[36], fPhot[37], fPhot[38], fPhot[39],
	    fPhot[40], fPhot[41], fPhot[42], fPhot[43], fPhot[44],
	    fPhot[45], fPhot[46], fPhot[47], fPhot[48], fPhot[49],
	    fPhot[50], fPhot[51], fPhot[52], fPhot[53], fPhot[54],
	    fPhot[55], fPhot[56], fPhot[57], fPhot[58], fPhot[59],
	    fPhot[60], fPhot[61], fPhot[62], fPhot[63]};
  
  G4double Alp1Leng = 0.;
  Alp1Leng += fTA[0];
  analysisManager->FillNtupleDColumn(11, Alp1Leng);
  
  G4double Alp2Leng = 0.;
  Alp2Leng += fTA[1];
  analysisManager->FillNtupleDColumn(12, Alp2Leng);
  
  G4double Alp3Leng = 0.;
  Alp3Leng += fTA[2];
  analysisManager->FillNtupleDColumn(13, Alp3Leng);
  
  if(NBARS!=5) G4cout << "WARNING: NBARS is " << NBARS << ". Modify code in EventAction" << G4endl;
  fVT1Leng = {fTT1[0], fTT1[1], fTT1[2], fTT1[3], fTT1[4]};
  fVT2Leng = {fTT2[0], fTT2[1], fTT2[2], fTT2[3], fTT2[4]};
  
  if(NCOUPLEDPLANES+1!=11) G4cout << "WARNING: N planes is " << NCOUPLEDPLANES+1 << ". Modify code in EventAction" << G4endl;
  fVPLeng = {fTP[0], fTP[1], fTP[2], fTP[3], fTP[4], fTP[5], fTP[6], fTP[7], fTP[8], fTP[9], fTP[10]};
  
  if(NCRYSTALS!=3) G4cout << "WARNING: NCRYSTALS is " << NCRYSTALS << ". Modify code in EventAction" << G4endl;
  fVL1Leng = {fTC1[0], fTC1[1], fTC1[2]};
  fVL2Leng = {fTC2[0], fTC2[1], fTC2[2]};
  
  fVVLeng = {fTVL1, fTVL2, fTVL3, fTVL4, fTVB};
  
  analysisManager->FillNtupleDColumn(14, fEBeforeT1);
  analysisManager->FillNtupleDColumn(15, fEBeforeT2);
  analysisManager->FillNtupleDColumn(16, fEBeforeP1);
  
  analysisManager->AddNtupleRow();
  
}
