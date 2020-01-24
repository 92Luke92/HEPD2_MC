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
   fTT1{0},
   fTA{0},
   fTT2{0},
   fTP{0},
   fTC1{0},
   fTC2{0},
   fTVL{0},
   fTVB(0),
   
   fPhot{0},
   fPhotEnergy{0},
   
   fET1{0},
   fEA{0},
   fET2{0},
   fEP{0},
   fEC1{0},
   fEC2{0},
   fEVL{0},
   fEVB(0),
   
   fAlp1Pos{0},
   fAlp2Pos{0},
   fAlp3Pos{0},
   
   fAlp1Dir{0},
   fAlp2Dir{0},
   fAlp3Dir{0},
   
   fGammaKin(0),
   fProtonKin(0),
   
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
  
  fGammaKin = 0.;
  fProtonKin = 0.;
  
  fEBeforeT1 = 0.;
  fEBeforeT2 = 0.;
  fEBeforeP1 = 0.;
  
  for (int i=0; i<3; i++) fEA[i] = 0.;
  for (int i = 0 ; i < NBARST1 ; i++) fET1[i]  = 0.;
  for (int i = 0 ; i < NBARST2 ; i++) fET2[i]  = 0.;
  for (int i = 0 ; i < NCALOPLANES ; i++) fEP[i]=0.;
  for (int i = 0 ; i < NCRYSTALS ; i++) fEC1[i]=0.;
  for (int i = 0 ; i < NCRYSTALS ; i++) fEC2[i]=0.;
  fEVB = 0.;
  for (int i = 0 ; i < 4 ; i++) fEVL[i] = 0.;
  
  for (int i=0; i<NPMTS; i++) fPhot[i] = 0;
  for (int i=0; i<NPMTS; i++) fPhotEnergy[i] = 0;
  
  for (int i=0; i<3; i++) fTA[i] = 0.;
  for (int i = 0 ; i < NBARST1 ; i++) fTT1[i]  = 0.;
  for (int i = 0 ; i < NBARST2 ; i++) fTT2[i]  = 0.;
  for (int i = 0 ; i < NCALOPLANES ; i++) fTP[i]=0.;
  for (int i = 0 ; i < NCRYSTALS ; i++) fTC1[i]=0.;
  for (int i = 0 ; i < NCRYSTALS ; i++) fTC2[i]=0.;
  fTVB = 0.;
  for (int i = 0 ; i < 4 ; i++) fTVL[i] = 0.;
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

  if(NBARST1!=5) G4cout << "WARNING: NBARST1 is " << NBARST1 << ". Modify code in EventAction" << G4endl;
  fVT1Edep = {fET1[0], fET1[1], fET1[2], fET1[3], fET1[4]};
  
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
  
  if(NBARST2!=4) G4cout << "WARNING: NBARST2 is " << NBARST2 << ". Modify code in EventAction" << G4endl;
  fVT2Edep = {fET2[0], fET2[1], fET2[2], fET2[3]};
  G4double TRIGEdep = fET1[0]+fET1[1]+fET1[2]+fET1[3]+fET1[4]+fET2[0]+fET2[1]+fET2[2]+fET2[3];
  analysisManager->FillNtupleDColumn(7, TRIGEdep);
  
  if(NCALOPLANES!=12) G4cout << "WARNING: N planes is " << NCALOPLANES << ". Modify code in EventAction" << G4endl;
  fVPEdep = {fEP[0], fEP[1], fEP[2], fEP[3], fEP[4], fEP[5], fEP[6], fEP[7], fEP[8], fEP[9], fEP[10], fEP[11]};
  G4double TOWEREdep = fEP[0]+fEP[1]+fEP[2]+fEP[3]+fEP[4]+fEP[5]+fEP[6]+fEP[7]+fEP[8]+fEP[9]+fEP[10]+fEP[11];
  analysisManager->FillNtupleDColumn(8, TOWEREdep);
  
  if(NCRYSTALS!=3) G4cout << "WARNING: NCRYSTALS is " << NCRYSTALS << ". Modify code in EventAction" << G4endl;
  fVL1Edep = {fEC1[0], fEC1[1], fEC1[2]};
  fVL2Edep = {fEC2[0], fEC2[1], fEC2[2]};
  G4double LYSOEdep = fEC1[0]+fEC1[1]+fEC1[2]+fEC2[0]+fEC2[1]+fEC2[2];
  analysisManager->FillNtupleDColumn(9, LYSOEdep);
  G4double CALOEdep = TRIGEdep + TOWEREdep + LYSOEdep;
  analysisManager->FillNtupleDColumn(10, CALOEdep);
  
  fVVEdep = {fEVL[0], fEVL[1], fEVL[2], fEVL[3], fEVB};
  
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
  
  fVphotenergy = {fPhotEnergy[0], fPhotEnergy[1], fPhotEnergy[2], fPhotEnergy[3], fPhotEnergy[4],
		  fPhotEnergy[5], fPhotEnergy[6], fPhotEnergy[7], fPhotEnergy[8], fPhotEnergy[9],
		  fPhotEnergy[10], fPhotEnergy[11], fPhotEnergy[12], fPhotEnergy[13], fPhotEnergy[14],
		  fPhotEnergy[15], fPhotEnergy[16], fPhotEnergy[17], fPhotEnergy[18], fPhotEnergy[19],
		  fPhotEnergy[20], fPhotEnergy[21], fPhotEnergy[22], fPhotEnergy[23], fPhotEnergy[24],
		  fPhotEnergy[25], fPhotEnergy[26], fPhotEnergy[27], fPhotEnergy[28], fPhotEnergy[29],
		  fPhotEnergy[30], fPhotEnergy[31], fPhotEnergy[32], fPhotEnergy[33], fPhotEnergy[34],
		  fPhotEnergy[35], fPhotEnergy[36], fPhotEnergy[37], fPhotEnergy[38], fPhotEnergy[39],
		  fPhotEnergy[40], fPhotEnergy[41], fPhotEnergy[42], fPhotEnergy[43], fPhotEnergy[44],
		  fPhotEnergy[45], fPhotEnergy[46], fPhotEnergy[47], fPhotEnergy[48], fPhotEnergy[49],
		  fPhotEnergy[50], fPhotEnergy[51], fPhotEnergy[52], fPhotEnergy[53], fPhotEnergy[54],
		  fPhotEnergy[55], fPhotEnergy[56], fPhotEnergy[57], fPhotEnergy[58], fPhotEnergy[59],
		  fPhotEnergy[60], fPhotEnergy[61], fPhotEnergy[62], fPhotEnergy[63]};
  
  if(NBARST1!=5) G4cout << "WARNING: NBARST1 is " << NBARST1 << ". Modify code in EventAction" << G4endl;
  fVT1Leng = {fTT1[0], fTT1[1], fTT1[2], fTT1[3], fTT1[4]};
  
  G4double Alp1Leng = 0.;
  Alp1Leng += fTA[0];
  analysisManager->FillNtupleDColumn(11, Alp1Leng);
  
  G4double Alp2Leng = 0.;
  Alp2Leng += fTA[1];
  analysisManager->FillNtupleDColumn(12, Alp2Leng);
  
  G4double Alp3Leng = 0.;
  Alp3Leng += fTA[2];
  analysisManager->FillNtupleDColumn(13, Alp3Leng);
  
  if(NBARST2!=4) G4cout << "WARNING: NBARST2 is " << NBARST2 << ". Modify code in EventAction" << G4endl;
  fVT2Leng = {fTT2[0], fTT2[1], fTT2[2], fTT2[3]};
  
  if(NCALOPLANES!=12) G4cout << "WARNING: N planes is " << NCALOPLANES << ". Modify code in EventAction" << G4endl;
  fVPLeng = {fTP[0], fTP[1], fTP[2], fTP[3], fTP[4], fTP[5], fTP[6], fTP[7], fTP[8], fTP[9], fTP[10], fTP[11]};
  
  if(NCRYSTALS!=3) G4cout << "WARNING: NCRYSTALS is " << NCRYSTALS << ". Modify code in EventAction" << G4endl;
  fVL1Leng = {fTC1[0], fTC1[1], fTC1[2]};
  fVL2Leng = {fTC2[0], fTC2[1], fTC2[2]};
  
  fVVLeng = {fTVL[0], fTVL[1], fTVL[2], fTVL[3], fTVB};
  
  analysisManager->FillNtupleDColumn(14, fGammaKin);
  analysisManager->FillNtupleDColumn(15, fProtonKin);
  
  analysisManager->FillNtupleDColumn(16, fEBeforeT1);
  analysisManager->FillNtupleDColumn(17, fEBeforeT2);
  analysisManager->FillNtupleDColumn(18, fEBeforeP1);
  
  analysisManager->AddNtupleRow();

}
