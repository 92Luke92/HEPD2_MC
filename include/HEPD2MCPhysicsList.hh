/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCPhysicsList.hh file              //
//                                         //
/////////////////////////////////////////////

#ifndef HEPD2MCPhysicsList_h
#define HEPD2MCPhysicsList_h 1

#include "globals.hh"
#include "G4VUserPhysicsList.hh"
#include "G4VPhysicsConstructor.hh"

class HEPD2MCPhysicsList : public G4VUserPhysicsList
{
public:
  HEPD2MCPhysicsList();
  virtual ~HEPD2MCPhysicsList();
  
public:
  virtual void ConstructParticle();
  virtual void ConstructProcess();
  
  virtual void SetCuts();
  
  void ConstructDecay();
  void ConstructEM();
  void ConstructOp();
  
private:
  G4int fVerboseLebel;
  G4int fMaxNumPhotonStep;
  std::vector<G4VPhysicsConstructor*> hadronPhys;
};

#endif /* HEPD2MCPhysicsList_h */
