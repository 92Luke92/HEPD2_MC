/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCDetectorMessenger.hh file        //
//                                         //
/////////////////////////////////////////////

#ifndef HEPD2MCDetectorMessenger_h
#define HEPD2MCDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class HEPD2MCDetectorConstruction;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;
class G4UIcmdWithABool;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HEPD2MCDetectorMessenger: public G4UImessenger
{
public:
  HEPD2MCDetectorMessenger(HEPD2MCDetectorConstruction* );
  ~HEPD2MCDetectorMessenger();
  
  virtual void SetNewValue(G4UIcommand*, G4String);
  
private:
  HEPD2MCDetectorConstruction* Detector;

  G4UIdirectory* fHEPD2Dir;
  G4UIcmdWithABool* fOpticsCmd;
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

