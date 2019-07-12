/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCDetectorMessenger.cc file        //
//                                         //
/////////////////////////////////////////////

#include "HEPD2MCDetectorMessenger.hh"

#include <sstream>

#include "HEPD2MCDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"

HEPD2MCDetectorMessenger::HEPD2MCDetectorMessenger(HEPD2MCDetectorConstruction * Det)
:Detector(Det)
{
  fHEPD2Dir = new G4UIdirectory("/HEPD02/");
  fHEPD2Dir->SetGuidance("UI commands specific for HEPD-02");
  
  fOpticsCmd = new G4UIcmdWithABool("/HEPD02/ActivateOptics",this);
  fOpticsCmd->SetGuidance("Enable or disable optics configuration");
  fOpticsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
}

HEPD2MCDetectorMessenger::~HEPD2MCDetectorMessenger()
{
  delete fOpticsCmd;
}

void HEPD2MCDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if(command == fOpticsCmd){
    Detector->ActivateOptics(fOpticsCmd->GetNewBoolValue(newValue));
  }
  
}
