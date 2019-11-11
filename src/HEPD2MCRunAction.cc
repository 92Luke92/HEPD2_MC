/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCRunAction.cc file                //
//                                         //
/////////////////////////////////////////////

#include "HEPD2MCRunAction.hh"
#include "HEPD2MCEventAction.hh"
#include "HEPD2MCAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

HEPD2MCRunAction::HEPD2MCRunAction(HEPD2MCEventAction* eventAction)
  : G4UserRunAction(),
    fEventAction(eventAction)
{ 
  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;
  
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);
  
  analysisManager->CreateNtuple("HEPD2", "HEPD2");
  
  analysisManager->CreateNtupleIColumn("particleid");
  analysisManager->CreateNtupleDColumn("energy");
  analysisManager->CreateNtupleDColumn("gen", fEventAction->GetVgen());
  analysisManager->CreateNtupleDColumn("theta");
  analysisManager->CreateNtupleDColumn("phi");
  analysisManager->CreateNtupleDColumn("p", fEventAction->GetVp());
  
  analysisManager->CreateNtupleDColumn("Alp1Edep");
  analysisManager->CreateNtupleDColumn("Alp2Edep");
  analysisManager->CreateNtupleDColumn("Alp3Edep");
  analysisManager->CreateNtupleDColumn("Alp1Pos", fEventAction->GetAlp1Pos());
  analysisManager->CreateNtupleDColumn("Alp2Pos", fEventAction->GetAlp2Pos());
  analysisManager->CreateNtupleDColumn("Alp3Pos", fEventAction->GetAlp3Pos());
  
  analysisManager->CreateNtupleDColumn("Alp1Dir", fEventAction->GetAlp1Dir());
  analysisManager->CreateNtupleDColumn("Alp2Dir", fEventAction->GetAlp2Dir());
  analysisManager->CreateNtupleDColumn("Alp3Dir", fEventAction->GetAlp3Dir());
  
  analysisManager->CreateNtupleDColumn("T1Edep", fEventAction->GetVT1Edep());
  analysisManager->CreateNtupleDColumn("T2Edep", fEventAction->GetVT2Edep());
  analysisManager->CreateNtupleDColumn("TRIGEdep");
  analysisManager->CreateNtupleDColumn("PEdep", fEventAction->GetVPEdep());
  analysisManager->CreateNtupleDColumn("TOWEREdep");
  analysisManager->CreateNtupleDColumn("L1Edep", fEventAction->GetVL1Edep());
  analysisManager->CreateNtupleDColumn("L2Edep", fEventAction->GetVL2Edep());
  analysisManager->CreateNtupleDColumn("LYSOEdep");
  analysisManager->CreateNtupleDColumn("CALOEdep");
  analysisManager->CreateNtupleDColumn("VEdep", fEventAction->GetVVEdep());
  
  analysisManager->CreateNtupleIColumn("phot", fEventAction->GetPhot());
  analysisManager->CreateNtupleDColumn("phot_energy", fEventAction->GetPhotEnergy());
  
  analysisManager->CreateNtupleDColumn("Alp1Leng");
  analysisManager->CreateNtupleDColumn("Alp2Leng");
  analysisManager->CreateNtupleDColumn("Alp3Leng");
  analysisManager->CreateNtupleDColumn("T1Leng", fEventAction->GetVT1Leng());
  analysisManager->CreateNtupleDColumn("T2Leng", fEventAction->GetVT2Leng());
  analysisManager->CreateNtupleDColumn("PLeng", fEventAction->GetVPLeng());
  analysisManager->CreateNtupleDColumn("L1Leng", fEventAction->GetVL1Leng());
  analysisManager->CreateNtupleDColumn("L2Leng", fEventAction->GetVL2Leng());
  analysisManager->CreateNtupleDColumn("VLeng", fEventAction->GetVVLeng());
  
  analysisManager->CreateNtupleDColumn("EGammaKin");
  
  analysisManager->CreateNtupleDColumn("EBeforeT1");
  analysisManager->CreateNtupleDColumn("EBeforeT2");
  analysisManager->CreateNtupleDColumn("EBeforeP1");
  
  analysisManager->FinishNtuple();
}

HEPD2MCRunAction::~HEPD2MCRunAction()
{
  delete G4AnalysisManager::Instance();
}

void HEPD2MCRunAction::BeginOfRunAction(const G4Run* /*run*/)
{
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  G4String fileName = "HEPD2";
  analysisManager->OpenFile(fileName);
}

void HEPD2MCRunAction::EndOfRunAction(const G4Run* /*run*/)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}
