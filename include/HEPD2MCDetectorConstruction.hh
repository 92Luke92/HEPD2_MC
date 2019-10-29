////////////////////////////////////////////
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
  
  void ActivateOptics(G4bool optics);
  
  
private:
  
  // methods
  void DefineMaterials();
  G4VPhysicalVolume* DefineVolumes();
  
  // data member
  G4MaterialPropertiesTable* absOptMat_MPT;
  G4MaterialPropertiesTable* cryOptMat_MPT;
  G4MaterialPropertiesTable* pmtMat_MPT;
  
  G4VPhysicalVolume* worldPV;
  
  G4VPhysicalVolume* fBlanketPV;
  
  G4VPhysicalVolume* fWindowContainerPV;
  G4VPhysicalVolume* fWindowOutPV;
  G4VPhysicalVolume* fWindowInPV;
  G4VPhysicalVolume* fWallHoneyCombPV;
  G4VPhysicalVolume* fWallExternalOutPV;
  G4VPhysicalVolume* fWallExternalInPV;
  
  G4VPhysicalVolume* fAlpContPV;
  G4VPhysicalVolume* fAlpTowerPV;
  G4VPhysicalVolume* fAlpDoublePV;
  G4VPhysicalVolume* fAlp1PV;
  G4VPhysicalVolume* fAlp2PV;
  G4VPhysicalVolume* fAlpActive1PV;
  G4VPhysicalVolume* fAlpActive2PV;
  G4VPhysicalVolume* fAlpPlane1PV;
  G4VPhysicalVolume* fAlpPlane2PV;
  G4VPhysicalVolume* fAlpPlane3PV;
  
  G4VPhysicalVolume* fCuSupport1_PV;
  G4VPhysicalVolume* fCuSupport2_PV;
  G4VPhysicalVolume* fCuSupport3_PV;
  G4VPhysicalVolume* fFPC1_PV;
  G4VPhysicalVolume* fFPC2_PV;
  G4VPhysicalVolume* fFPC3_PV;
  G4VPhysicalVolume* fColdPlate1_PV;
  G4VPhysicalVolume* fColdPlate2_PV;
  G4VPhysicalVolume* fColdPlate3_PV;
  G4VPhysicalVolume* fAlpRibs1_PV;
  G4VPhysicalVolume* fAlpRibs2_PV;
  G4VPhysicalVolume* fAlpRibs3_PV;
  G4VPhysicalVolume* fAlpRibs4_PV;
  G4VPhysicalVolume* fAlpRibs5_PV;
  G4VPhysicalVolume* fAlpRibs6_PV;
  
  G4VPhysicalVolume* fAlpInterfacePlatePV;
  
  G4VPhysicalVolume* ftrigger1_1PV;
  G4VPhysicalVolume* ftrigger1_2PV;
  G4VPhysicalVolume* ftrigger1_3PV;
  G4VPhysicalVolume* ftrigger1_4PV;
  G4VPhysicalVolume* ftrigger1_5PV;
  G4VPhysicalVolume* fTBars1PV;
  G4VPhysicalVolume* fPoronBeforeT1PV;
  G4VPhysicalVolume* fPoronAfterT1PV;
  G4VPhysicalVolume* fWrappingBeforeT1PV;
  G4VPhysicalVolume* fWrappingAfterT1PV;
  G4VPhysicalVolume* fCompPlaneBeforeT1PV;
  G4VPhysicalVolume* fCompPlaneAfterT1PV;
  G4VPhysicalVolume* fFrameT1PV;
  G4VPhysicalVolume* fT1RibsPV_1;
  G4VPhysicalVolume* fT1RibsPV_2;
  G4VPhysicalVolume* fT1RibsPV_3;
  G4VPhysicalVolume* fT1RibsPV_4;
  
  G4VPhysicalVolume* ftrigger2_1PV;
  G4VPhysicalVolume* ftrigger2_2PV;
  G4VPhysicalVolume* ftrigger2_3PV;
  G4VPhysicalVolume* ftrigger2_4PV;
  G4VPhysicalVolume* ftrigger2_5PV;
  G4VPhysicalVolume* fTBars2PV;
  G4VPhysicalVolume* fPoronBeforeT2PV;
  G4VPhysicalVolume* fPoronAfterT2PV;
  G4VPhysicalVolume* fWrappingBeforeT2PV;
  G4VPhysicalVolume* fWrappingAfterT2PV;
  G4VPhysicalVolume* fCompPlaneBeforeT2PV;
  G4VPhysicalVolume* fCompPlaneAfterT2PV;
  G4VPhysicalVolume* fT2RibsPV_1;
  G4VPhysicalVolume* fT2RibsPV_2;
  G4VPhysicalVolume* fT2RibsPV_3;
  G4VPhysicalVolume* fT2RibsPV_4;
  
  G4VPhysicalVolume* fPCompPlane1_Block1PV;
  G4VPhysicalVolume* fPCompPlane2_Block1PV;
  G4VPhysicalVolume* fPCompPlane1_Block2PV;
  G4VPhysicalVolume* fPCompPlane2_Block2PV;
  G4VPhysicalVolume* fPCompPlane1_Block3PV;
  G4VPhysicalVolume* fPCompPlane2_Block3PV;
  G4VPhysicalVolume* fPPorondxPV;
  G4VPhysicalVolume* fPPoronsxPV;
  G4VPhysicalVolume* fPWrappingdx1PV;
  G4VPhysicalVolume* fPWrappingdx2PV;
  G4VPhysicalVolume* fPWrappingsx1PV;
  G4VPhysicalVolume* fPWrappingsx2PV;
  G4VPhysicalVolume* fPlanedxPV;
  G4VPhysicalVolume* fPlanesxPV;
  G4VPhysicalVolume* fPPoronEndBlock1PV;
  G4VPhysicalVolume* fPPoronEndBlock2PV;
  G4VPhysicalVolume* fPPoronEndBlock3PV;
  
  G4VPhysicalVolume* fLysoCoverPV;
  
  G4VPhysicalVolume* fBarCont1_plane1PV;
  G4VPhysicalVolume* fBarCont2_plane1PV;
  G4VPhysicalVolume* fBarCont3_plane1PV;
  G4VPhysicalVolume* fCrystal1PV;
  G4VPhysicalVolume* fCWrappingLat1_plane1PV;
  G4VPhysicalVolume* fCWrappingLat2_plane1PV;
  G4VPhysicalVolume* fCWrapping1_plane1PV;
  G4VPhysicalVolume* fCWrapping2_plane1PV;
  G4VPhysicalVolume* fCScotchTapeLat1_plane1PV;
  G4VPhysicalVolume* fCScotchTapeLat2_plane1PV;
  G4VPhysicalVolume* fCScotchTape1_plane1PV;
  G4VPhysicalVolume* fCScotchTape2_plane1PV;
  G4VPhysicalVolume* fCScotchTape3_plane1PV;
  G4VPhysicalVolume* fCScotchTape4_plane1PV;
  
  G4VPhysicalVolume* fBarCont1_plane2PV;
  G4VPhysicalVolume* fBarCont2_plane2PV;
  G4VPhysicalVolume* fBarCont3_plane2PV;
  G4VPhysicalVolume* fCrystal2PV;
  G4VPhysicalVolume* fCWrappingLat1_plane2PV;
  G4VPhysicalVolume* fCWrappingLat2_plane2PV;
  G4VPhysicalVolume* fCWrapping1_plane2PV;
  G4VPhysicalVolume* fCWrapping2_plane2PV;
  G4VPhysicalVolume* fCScotchTapeLat1_plane2PV;
  G4VPhysicalVolume* fCScotchTapeLat2_plane2PV;
  G4VPhysicalVolume* fCScotchTape1_plane2PV;
  G4VPhysicalVolume* fCScotchTape2_plane2PV;
  G4VPhysicalVolume* fCScotchTape3_plane2PV;
  G4VPhysicalVolume* fCScotchTape4_plane2PV;
  
  G4VPhysicalVolume* fVetoBotContPV;
  G4VPhysicalVolume* fRearVetoBotPV;
  G4VPhysicalVolume* fVetoBotCoverPV;
  G4VPhysicalVolume* fVetoBotPoronPV;
  G4VPhysicalVolume* fVetoBotWrappingPV;
  G4VPhysicalVolume* fVetobPV;
  
  G4VPhysicalVolume* fVetoLatContainer1PV;
  G4VPhysicalVolume* fVetoLatContainer2PV;
  G4VPhysicalVolume* fVetoLatContainer3PV;
  G4VPhysicalVolume* fVetoLatContainer4PV;
  G4VPhysicalVolume* fVetoLatCoverPV;
  G4VPhysicalVolume* fVetoLatPoronIntPV;
  G4VPhysicalVolume* fVetoLatPoronExtPV;
  G4VPhysicalVolume* fVetoLatWrappingIntPV;
  G4VPhysicalVolume* fVetoLatWrappingExtPV;
  G4VPhysicalVolume* fVetoLatPV;
  
  
  G4bool  fCheckOverlaps;

  G4bool fOptics;
  
  HEPD2MCDetectorMessenger* fDetectorMessenger;
  
};

#endif

