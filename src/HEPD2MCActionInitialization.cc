/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCActionInitialization.cc file     //
//                                         //
/////////////////////////////////////////////

#include "HEPD2MCActionInitialization.hh"
#include "HEPD2MCPrimaryGeneratorAction.hh"
#include "HEPD2MCRunAction.hh"
#include "HEPD2MCEventAction.hh"
#include "HEPD2MCSteppingAction.hh"
#include "HEPD2MCDetectorConstruction.hh"

HEPD2MCActionInitialization::HEPD2MCActionInitialization
                            (HEPD2MCDetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{
}

HEPD2MCActionInitialization::~HEPD2MCActionInitialization()
{
}

void HEPD2MCActionInitialization::BuildForMaster() const
{
  HEPD2MCEventAction* eventAction = new HEPD2MCEventAction;
  SetUserAction(new HEPD2MCRunAction(eventAction));
}

void HEPD2MCActionInitialization::Build() const  
{
  SetUserAction(new HEPD2MCPrimaryGeneratorAction);
  auto eventAction = new HEPD2MCEventAction;
  SetUserAction(new HEPD2MCRunAction(eventAction));
  SetUserAction(eventAction);
  SetUserAction(new HEPD2MCSteppingAction(fDetConstruction,eventAction));
  
}

