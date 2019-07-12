/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCActionInitialization.hh file     //
//                                         //
/////////////////////////////////////////////

#ifndef HEPD2MCActionInitialization_h
#define HEPD2MCActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class HEPD2MCDetectorConstruction;

class HEPD2MCActionInitialization : public G4VUserActionInitialization
{
  public:
    HEPD2MCActionInitialization(HEPD2MCDetectorConstruction*);
    virtual ~HEPD2MCActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
    HEPD2MCDetectorConstruction* fDetConstruction;
};

#endif

    
