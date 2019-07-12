/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCRunAction.hh file                //
//                                         //
/////////////////////////////////////////////
#ifndef HEPD2MCRunAction_h
#define HEPD2MCRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>

class HEPD2MCEventAction;

class G4Run;

class HEPD2MCRunAction : public G4UserRunAction
{
public:
  HEPD2MCRunAction(HEPD2MCEventAction* eventAction);
  virtual ~HEPD2MCRunAction();
  
  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);
  
private:
  HEPD2MCEventAction* fEventAction;
  
};

#endif

