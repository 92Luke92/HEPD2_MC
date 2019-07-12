/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCSteppingAction.hh file           //
//                                         //
/////////////////////////////////////////////

#ifndef HEPD2MCSteppingAction_h
#define HEPD2MCSteppingAction_h 1

#include "G4UserSteppingAction.hh"

class HEPD2MCDetectorConstruction;
class HEPD2MCEventAction;

class HEPD2MCSteppingAction : public G4UserSteppingAction
{
public:
  HEPD2MCSteppingAction(const HEPD2MCDetectorConstruction* detectorConstruction,
                    HEPD2MCEventAction* eventAction);
  virtual ~HEPD2MCSteppingAction();

  virtual void UserSteppingAction(const G4Step* step);

private:
  const HEPD2MCDetectorConstruction* fDetConstruction;
  HEPD2MCEventAction*  fEventAction;
    
};

#endif
