/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCDetectorConstruction.hh file     //
//                                         //
/////////////////////////////////////////////

#ifndef HEPD2MCDetectorConstruction_h
#define HEPD2MCDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4MaterialPropertiesTable;
class HEPD2MCDetectorMessenger;

class HEPD2MCDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  HEPD2MCDetectorConstruction();
  virtual ~HEPD2MCDetectorConstruction();
  
public:
  virtual G4VPhysicalVolume* Construct();
  
  // get methods
  const G4VPhysicalVolume* GetAbso1PV() const;
  const G4VPhysicalVolume* GetAbso2PV() const;
  const G4VPhysicalVolume* GetLastAbsoPV() const;
  const G4VPhysicalVolume* GetCBars1PV() const;
  const G4VPhysicalVolume* GetCBars2PV() const;
  const G4VPhysicalVolume* GetVetoBPV() const;
  const G4VPhysicalVolume* GetVetoL1PV() const;
  const G4VPhysicalVolume* GetVetoL2PV() const;
  const G4VPhysicalVolume* GetVetoL3PV() const;
  const G4VPhysicalVolume* GetVetoL4PV() const; 
  const G4VPhysicalVolume* GetTBars1PV() const;
  const G4VPhysicalVolume* GetTBars2PV() const;
  const G4VPhysicalVolume* GetAlpPV() const;
  
  void ActivateOptics(G4bool optics);
  
  
private:
  
  // methods
  void DefineMaterials();
  G4VPhysicalVolume* DefineVolumes();
  
  // data member
  G4MaterialPropertiesTable* absOptMat_MPT;
  G4MaterialPropertiesTable* cryOptMat_MPT;
  G4MaterialPropertiesTable* pmtMat_MPT;
  
  G4VPhysicalVolume*   fDoubleLayerPV;
  G4VPhysicalVolume*   fLayer1PV;
  G4VPhysicalVolume*   fLayer2PV;
  G4VPhysicalVolume*   fAbsorber1PV;
  G4VPhysicalVolume*   fAbsorber2PV;
  G4VPhysicalVolume*   fGap1PV;
  G4VPhysicalVolume*   fGap2PV;
  G4VPhysicalVolume*   fLastLayerPV;
  G4VPhysicalVolume*   fLastAbsorberPV;
  G4VPhysicalVolume*   fLastGapPV;
  
  G4VPhysicalVolume*   fCrystal1PV;
  G4VPhysicalVolume*   fCBars1PV;
  G4VPhysicalVolume*   fCrystal2PV;
  G4VPhysicalVolume*   fCBars2PV;
  
  G4VPhysicalVolume*   fVetobPV;
  G4VPhysicalVolume*   fLveto1PV;
  G4VPhysicalVolume*   fLveto2PV;
  G4VPhysicalVolume*   fLveto3PV;
  G4VPhysicalVolume*   fLveto4PV;
  
  G4VPhysicalVolume*   ftrigger1PV;
  G4VPhysicalVolume*   fTBars1PV;
  G4VPhysicalVolume*   ftrigger2PV;
  G4VPhysicalVolume*   fTBars2PV;
  
  G4VPhysicalVolume*   fCFplaneBeforeT1PV;
  G4VPhysicalVolume*   fCFplaneAfterT1PV;
  G4VPhysicalVolume*   fCFplaneBeforeT2PV;
  G4VPhysicalVolume*   fCFplaneAfterT2PV;
  
  G4VPhysicalVolume*   fGrk1PV;
  G4VPhysicalVolume*   fGrk2PV;
  
  G4VPhysicalVolume*   fAlumPlanePV;
  
  G4VPhysicalVolume*   fAlpContPV;
  G4VPhysicalVolume*   fAlpTowerPV;
  G4VPhysicalVolume*   fAlpPlane1PV;
  G4VPhysicalVolume*   fAlpPlane2PV;
  G4VPhysicalVolume*   fAlpPlane3PV;
  G4VPhysicalVolume*   fAlpHPlanePV;
  G4VPhysicalVolume*   fAlpPV;
  
  G4VPhysicalVolume* fCuSupport1_PV;
  G4VPhysicalVolume* fCuSupport2_PV;
  G4VPhysicalVolume* fCuSupport3_PV;
  
  G4VPhysicalVolume* fFPC1_PV;
  G4VPhysicalVolume* fFPC2_PV;
  G4VPhysicalVolume* fFPC3_PV;
  
  G4VPhysicalVolume* fColdPlate1_PV;
  G4VPhysicalVolume* fColdPlate2_PV;
  G4VPhysicalVolume* fColdPlate3_PV;
  
  G4VPhysicalVolume* fRibs1_PV;
  G4VPhysicalVolume* fRibs2_PV;
  G4VPhysicalVolume* fRibs3_PV;
  G4VPhysicalVolume* fRibs4_PV;
  G4VPhysicalVolume* fRibs5_PV;
  G4VPhysicalVolume* fRibs6_PV;
  
  G4VPhysicalVolume* fBlanketPV;
  
  G4VPhysicalVolume* fWindowOutPV;
  G4VPhysicalVolume* fWindowInPV;
  G4VPhysicalVolume* fWallHoneyCombPV;
  G4VPhysicalVolume* fWallExternalOutPV;
  G4VPhysicalVolume* fWallExternalInPV;
  
  G4bool  fCheckOverlaps;

  G4bool fOptics;
  
  HEPD2MCDetectorMessenger* fDetectorMessenger;
  
};

// inline functions
inline const G4VPhysicalVolume* HEPD2MCDetectorConstruction::GetVetoBPV() const  {return fVetobPV;}
inline const G4VPhysicalVolume* HEPD2MCDetectorConstruction::GetVetoL1PV() const  {return fLveto1PV;}
inline const G4VPhysicalVolume* HEPD2MCDetectorConstruction::GetVetoL2PV() const  {return fLveto2PV;}
inline const G4VPhysicalVolume* HEPD2MCDetectorConstruction::GetVetoL3PV() const  {return fLveto3PV;}
inline const G4VPhysicalVolume* HEPD2MCDetectorConstruction::GetVetoL4PV() const  {return fLveto4PV;}
inline const G4VPhysicalVolume* HEPD2MCDetectorConstruction::GetAbso1PV() const {return fAbsorber1PV;}
inline const G4VPhysicalVolume* HEPD2MCDetectorConstruction::GetAbso2PV() const {return fAbsorber2PV;}
inline const G4VPhysicalVolume* HEPD2MCDetectorConstruction::GetLastAbsoPV() const {return fLastAbsorberPV;}
inline const G4VPhysicalVolume* HEPD2MCDetectorConstruction::GetCBars1PV() const  {return fCBars1PV;}
inline const G4VPhysicalVolume* HEPD2MCDetectorConstruction::GetCBars2PV() const  {return fCBars2PV;}
inline const G4VPhysicalVolume* HEPD2MCDetectorConstruction::GetTBars1PV() const  {return fTBars1PV;}
inline const G4VPhysicalVolume* HEPD2MCDetectorConstruction::GetTBars2PV() const  {return fTBars2PV;}
inline const G4VPhysicalVolume* HEPD2MCDetectorConstruction::GetAlpPV() const {return fAlpPV;}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

