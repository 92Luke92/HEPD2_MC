/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCPrimaryGeneratorMessenger.hh file//
//                                         //
/////////////////////////////////////////////

#ifndef HEPD2MCPrimaryGeneratorMessenger_h
#define HEPD2MCPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class HEPD2MCPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcommand;

class HEPD2MCPrimaryGeneratorMessenger: public G4UImessenger
{
public:
  HEPD2MCPrimaryGeneratorMessenger(HEPD2MCPrimaryGeneratorAction*);
  ~HEPD2MCPrimaryGeneratorMessenger();
  
  virtual void SetNewValue(G4UIcommand*, G4String);
  
private:
  HEPD2MCPrimaryGeneratorAction*    fAction;
  
  G4UIdirectory* fGunDir;
  G4UIcmdWithAString* fPartCmd;
  G4UIcmdWithADoubleAndUnit* fEnerCmd;
  G4UIcommand* fPointCmd;
  G4UIcommand* fPlanewaveCmd;
  G4UIcommand* fRandomCmd;
  G4UIcommand* fPowEnergyCmd;
  G4UIcommand* fRadioCmd;
  
};

#endif

