////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCDetectorConstruction.cc file     //
//                                         //
/////////////////////////////////////////////

#include "HEPD2MCDetectorConstruction.hh"
#include "HEPD2MCDetectorMessenger.hh"
#include "HEPD2MCDetConst.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

HEPD2MCDetectorConstruction::HEPD2MCDetectorConstruction()
  : G4VUserDetectorConstruction(),
    fBlanketPV(0),
    fWindowContainerPV(0),
    fWindowOutPV(0),
    fWindowInPV(0),
    fWallHoneyCombPV(0),
    fWallExternalOutPV(0),
    fWallExternalInPV(0),
    
    fAlpContPV(0),
    fAlpTowerPV(0),
    fAlpDoublePV(0),
    fAlp1PV(0),
    fAlp2PV(0),
    fAlpActive1PV(0),
    fAlpActive2PV(0),
    fAlpPlane1PV(0),
    fAlpPlane2PV(0),
    fAlpPlane3PV(0),
    
    fCuSupport1_PV(0),
    fCuSupport2_PV(0),
    fCuSupport3_PV(0),
    fFPC1_PV(0),
    fFPC2_PV(0),
    fFPC3_PV(0),
    fColdPlate1_PV(0),
    fColdPlate2_PV(0),
    fColdPlate3_PV(0),
    fAlpRibs1_PV(0),
    fAlpRibs2_PV(0),
    fAlpRibs3_PV(0),
    fAlpRibs4_PV(0),
    fAlpRibs5_PV(0),
    fAlpRibs6_PV(0),
    
    fAlpInterfacePlatePV(0),
    
    ftrigger1_1PV(0),
    ftrigger1_2PV(0),
    ftrigger1_3PV(0),
    ftrigger1_4PV(0),
    ftrigger1_5PV(0),
    fTBars1PV(0),
    fPoronBeforeT1PV(0),
    fPoronAfterT1PV(0),
    fWrappingBeforeT1PV(0),
    fWrappingAfterT1PV(0),
    fCompPlaneBeforeT1PV(0),
    fCompPlaneAfterT1PV(0),
    fFrameT1PV(0),
    fT1RibsPV_1(0),
    fT1RibsPV_2(0),
    fT1RibsPV_3(0),
    fT1RibsPV_4(0),
    
    ftrigger2_1PV(0),
    ftrigger2_2PV(0),
    ftrigger2_3PV(0),
    ftrigger2_4PV(0),
    ftrigger2_5PV(0),
    fTBars2PV(0),
    fPoronBeforeT2PV(0),
    fPoronAfterT2PV(0),
    fWrappingBeforeT2PV(0),
    fWrappingAfterT2PV(0),
    fCompPlaneBeforeT2PV(0),
    fCompPlaneAfterT2PV(0),
    fT2RibsPV_1(0),
    fT2RibsPV_2(0),
    fT2RibsPV_3(0),
    fT2RibsPV_4(0),
    
    fPCompPlane1_Block1PV(0),
    fPCompPlane2_Block1PV(0),
    fPCompPlane1_Block2PV(0),
    fPCompPlane2_Block2PV(0),
    fPCompPlane1_Block3PV(0),
    fPCompPlane2_Block3PV(0),
    fPPorondxPV(0),
    fPPoronsxPV(0),
    fPWrappingdx1PV(0),
    fPWrappingdx2PV(0),
    fPWrappingsx1PV(0),
    fPWrappingsx2PV(0),
    fPlanedxPV(0),
    fPlanesxPV(0),
    fPPoronEndBlock1PV(0),
    fPPoronEndBlock2PV(0),
    fPPoronEndBlock3PV(0),
    
    fLysoCoverPV(0),
    
    fBarCont1_plane1PV(0),
    fBarCont2_plane1PV(0),
    fBarCont3_plane1PV(0),
    fCrystal1PV(0),
    fCWrappingLat1_plane1PV(0),
    fCWrappingLat2_plane1PV(0),
    fCWrapping1_plane1PV(0),
    fCWrapping2_plane1PV(0),
    fCScotchTapeLat1_plane1PV(0),
    fCScotchTapeLat2_plane1PV(0),
    fCScotchTape1_plane1PV(0),
    fCScotchTape2_plane1PV(0),
    fCScotchTape3_plane1PV(0),
    fCScotchTape4_plane1PV(0),
    
    fBarCont1_plane2PV(0),
    fBarCont2_plane2PV(0),
    fBarCont3_plane2PV(0),
    fCrystal2PV(0),
    fCWrappingLat1_plane2PV(0),
    fCWrappingLat2_plane2PV(0),
    fCWrapping1_plane2PV(0),
    fCWrapping2_plane2PV(0),
    fCScotchTapeLat1_plane2PV(0),
    fCScotchTapeLat2_plane2PV(0),
    fCScotchTape1_plane2PV(0),
    fCScotchTape2_plane2PV(0),
    fCScotchTape3_plane2PV(0),
    fCScotchTape4_plane2PV(0),
    
    fVetoBotContPV(0),
    fRearVetoBotPV(0),
    fVetoBotCoverPV(0),
    fVetoBotPoronPV(0),
    fVetoBotWrappingPV(0),
    fVetobPV(0),
    
    fVetoLatContainer1PV(0),
    fVetoLatContainer2PV(0),
    fVetoLatContainer3PV(0),
    fVetoLatContainer4PV(0),
    fVetoLatCoverPV(0),
    fVetoLatPoronIntPV(0),
    fVetoLatPoronExtPV(0),
    fVetoLatWrappingIntPV(0),
    fVetoLatWrappingExtPV(0),
    fVetoLatPV(0),
    
    fCheckOverlaps(true)
{
  fDetectorMessenger = new HEPD2MCDetectorMessenger(this);
  
  fOptics = false;
  
}

HEPD2MCDetectorConstruction::~HEPD2MCDetectorConstruction()
{
  if(fDetectorMessenger) delete fDetectorMessenger;
}

G4VPhysicalVolume* HEPD2MCDetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
  
}

void HEPD2MCDetectorConstruction::DefineMaterials()
{
  // Lead material defined using NIST Manager
  G4NistManager* nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  nistManager->FindOrBuildMaterial("G4_POLYCARBONATE");
  nistManager->FindOrBuildMaterial("G4_Galactic");
  nistManager->FindOrBuildMaterial("G4_Al");
  nistManager->FindOrBuildMaterial("G4_Si");
  nistManager->FindOrBuildMaterial("G4_KAPTON");
  nistManager->FindOrBuildMaterial("G4_Cu");
  nistManager->FindOrBuildMaterial("G4_MYLAR");
  
}

G4VPhysicalVolume* HEPD2MCDetectorConstruction::DefineVolumes()
{
  // Geometry parameters
  
  //axes
  G4double axes = AXESBLANKET_DIST;
  
  //thermal blanket
  G4double Blanket_X = BLANKET_SIZEX;
  G4double Blanket_Y = BLANKET_SIZEY;
  G4double Blanket_Z = BLANKET_SIZEZ;
  G4double blanket_dist = BLANKETWINDOW_DIST;
  
  //window
  G4double window_X = WINDOW_SIZEX;
  G4double window_Y = WINDOW_SIZEY;
  G4double windowOut_Z = WINDOWOUT_THICKNESS;
  G4double windowIn_Z = WINDOWIN_THICKNESS;
  G4double window_dist = WINDOWALPIDE_DIST;
  
  //wall
  G4double Wall_X = WALLHONEYCOMB_SIZEX;
  G4double Wall_Y = WALLHONEYCOMB_SIZEY;
  G4double WallHoneyComb_Z = WALLHONEYCOMB_THICKNESS;
  G4double WallExternal_Z = WALLEXTERNAL_THICKNESS;
  
  G4double WallHole_X = -17.*mm;
  G4double WallHole_Y = 92.*mm;
  G4double WallHole_Z = 6.*mm; //must be greater than WALLHONEYCOMB_THICKNESS
  
  //alpide
  G4int nofAlpideX = NALPIDEX;
  G4int nofAlpideY = NALPIDEY;
  G4double alpideSizeX = ALPIDE_SIZEX;
  G4double alpideSizeY = ALPIDE_SIZEY;
  G4double alpideSizeZ = ALPIDE_SIZEZ;
  G4double alpideActiveSizeX = ALPIDEACTIVE_SIZEX;
  G4double alpideActiveSizeY = ALPIDEACTIVE_SIZEY;
  G4double alpideActiveSizeZ = ALPIDEACTIVE_SIZEZ;
  G4double alpideGap_Y = ALPIDE_GAPY;
  G4double alpideGap = ALPIDE_GAP;
  G4double alpchip_gap = ALPCHIP_GAP;
  
  //Copper support alpide
  G4double CuSupportSizeX = CUSUPP_SIZEX;
  G4double CuSupportSizeY = CUSUPP_SIZEY;
  G4double CuSupportSizeZ = CUSUPP_SIZEZ;
  
  //FPC
  G4double FPCSizeX = FPC_SIZEX;
  G4double FPCSizeY = FPC_SIZEY;
  G4double FPCSizeZ = FPC_SIZEZ;
  G4double FPCShift_X = FPCSHIFT_X;
  
  //Glue Araldite 2011 FPC-chip and chip-cold plate
  G4double GlueSizeX = GLUE_SIZEX;
  G4double GlueSizeY = GLUE_SIZEY;
  G4double GlueFPC_SizeZ = GLUE_FPC_SIZEZ;
  G4double GlueColdPlate_SizeZ = GLUE_COLDPLATE_SIZEZ;
  
  //Cold plate
  G4double ColdPlateSizeX = COLDPLATE_SIZEX;
  G4double ColdPlateSizeY = COLDPLATE_SIZEY;
  G4double ColdPlateSizeZ = COLDPLATE_SIZEZ;
  G4double ColdPlateShift_X = COLDPLATESHIFT_X;
  
  //Alpide Ribs
  G4double AlpRibsX = ALPRIBS_SIZEX;
  G4double AlpRibsY = ALPRIBS_SIZEY;
  G4double AlpRibsZ = ALPRIBS_SIZEZ;
  
  //Alpide interface plate
  G4double AlpInterfacePlate_X = ALPINTERFACE_SIZEX;
  G4double AlpInterfacePlate_Y = ALPINTERFACE_SIZEY;
  G4double AlpInterfacePlate_Z = ALPINTERFACE_THICKNESS;
  
  //Trigger T1
  G4int nofBars = NBARS;
  G4double trigger1SizeX = TRIGGER1_SIZEX;
  G4double trigger1SizeY = TRIGGER1_SIZEY;
  G4double barsGap = BARS_GAP;
  G4double trigger1Thickness = TRIGGER1_THICKNESS;
  G4double triggerGap = TRIGGER_GAP;
  
  G4double T1PoronThickness = T1PORON_THICKNESS;
  G4double T1WrappingThickness = T1WRAPPING_THICKNESS;
  
  //Light guide for T1
  G4double LG_X = LGEXIT_X;
  G4double LG_Y = LGEXIT_Y;
  G4double LG_height = LG_HEIGHT;
  
  //Support ribs between T1 bars
  G4double T1Ribs_X = T1RIBS_SIZEX;
  G4double T1Ribs_Y = T1RIBS_SIZEY;
  G4double T1Ribs_Z = T1RIBS_SIZEZ;
  
  //Comp plane before and after T1
  G4double T1CompPlane_X = TRIGGER1_SIZEX + 2*LG_HEIGHT;
  G4double T1CompPlane_Y = TRIGGER1_SIZEY;
  G4double T1CompPlane_Z = T1COMP_THICKNESS;
  
  //Frame T1
  G4double FrameT1_X = FRAMET1_SIZEX;
  G4double FrameT1_Y = FRAMET1_SIZEY;
  G4double FrameT1_Z = FRAMET1_THICKNESS;
  G4double PmtFrameT1_dist = PMTFRAMET1_DIST;
  
  //Trigger T2
  G4double trigger2SizeX = TRIGGER2_SIZEX;
  G4double trigger2SizeY = TRIGGER2_SIZEY;
  G4double trigger2Thickness = TRIGGER2_THICKNESS;
  G4double dist = TRIGPLANE_DIST;
  
  G4double T2PoronThickness = T2PORON_THICKNESS;
  G4double T2WrappingThickness = T2WRAPPING_THICKNESS;
  
  //Support ribs between T2 bars
  G4double T2Ribs_X = T2RIBS_SIZEX;
  G4double T2Ribs_Y = T2RIBS_SIZEY;
  G4double T2Ribs_Z = T2RIBS_SIZEZ;
  
  //Comp plane before and after T2
  G4double T2CompPlane_X = TRIGGER2_SIZEX;
  G4double T2CompPlane_Y = TRIGGER2_SIZEY;
  G4double T2CompPlane_Z = T2COMP_THICKNESS;
  
  //calorimeter
  G4int nofPlanes_Block1 = NCALOPLANES_BLOCK1;
  G4int nofPlanes_Block2 = NCALOPLANES_BLOCK2;
  G4int nofPlanes_Block3 = NCALOPLANES_BLOCK3;
  G4double caloSizeXY = PLANE_SIZEXY;
  G4double cutPlane = PLANE_CUT;
  G4double planeThickness = PLANE_THICKNESS;
  G4double dist_blocks = DIST_CALOBLOCKS;
  
  G4double PCompPlaneThickness = PCOMPPLANE_THICKNESS;
  G4double PPoronThickness = PPORON_THICKNESS;
  G4double PWrappingThickness = PWRAPPING_THICKNESS;
  
  G4double caloBlock1_Thickness = PCompPlaneThickness + nofPlanes_Block1*(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness) + PPoronThickness + PCompPlaneThickness;
  G4double caloBlock2_Thickness = PCompPlaneThickness + nofPlanes_Block2*(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness) + PPoronThickness + PCompPlaneThickness;
  G4double caloBlock3_Thickness = PCompPlaneThickness + nofPlanes_Block3*(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness) + PPoronThickness + PCompPlaneThickness;
  G4double caloThickness = caloBlock1_Thickness + dist_blocks + caloBlock2_Thickness + dist_blocks + caloBlock3_Thickness;
  
  //Lyso cover
  G4double LysoCover_X = LYSOCOVER_X;
  G4double LysoCover_Y = LYSOCOVER_Y;
  G4double LysoCover_Z = LYSOCOVER_Z;
  G4double dist_lastplane_LysoCover = DIST_LASTPLANE_LYSOCOVER;
  
  //crystal
  G4int nofCrystals = NCRYSTALS;
  G4double crystalBarSizeX = CRYSTAL_SIZEX;
  G4double crystalBarSizeY = CRYSTAL_SIZEY;
  G4double crystalBarThickness = CRYSTAL_THICKNESS;
  G4double crystalGapZ = CRYSTALGAP_Z;
  
  G4double CWrappingThickness = CWRAPPING_THICKNESS;
  G4double CScotchTape_SizeY = SCOTCHTAPE_SIZEY;
  G4double CScotchTape_Thickness = SCOTCHTAPE_THICKNESS;
  G4double CScotchTape_dist = SCOTCHTAPE_DIST;
  
  G4double crystalGap = 2.*CWrappingThickness + CScotchTape_Thickness;
  //veto
  G4double VetoLatContainer_X = VETOLATCONT_X;
  G4double VetoLatContainer_Y = VETOLATCONT_Y;
  
  G4double vetoHoleX = VETO_HOLEX;
  G4double vetoHoleY = VETO_HOLEY;
  G4double VetoLat_X = VETOLAT_X;
  G4double VetoLat_Y = VETOLAT_Y;
  G4double VetoLat_Z = VETO_THICKNESS;
  G4double VetoLatShift_X = 13.*mm;
  G4double VetoLatShift_Y = 24.*mm;
  G4double VetoLatCover_Z = VETOLATCOVER_THICKNESS;
  G4double VetoLatPoron_Z = VPORON_THICKNESS;
  G4double VetoLatWrapping_Z = VWRAPPING_THICKNESS;
  
  //Rear veto bot plane
  G4double RearVetoBot_Z = REARVETOBOT_Z;
  G4double RearCover_dist = REARCOVER_DIST;
  
  //veto bot
  G4double vetoSizeXY = VETO_SIZEXY;
  G4double cutPlaneVeto = VETO_CUT;
  G4double VetoBot_Z = VETOBOT_Z;
  G4double VetoBotCover_Z = VETOBOTCOVER_Z;
  G4double VetoBotPoron_Z = VETOBOTPORON_Z;
  G4double VetoBotWrappingThickness = VWRAPPING_THICKNESS;
  
  //pmt
  G4double pmtInnerRadius = 0.*mm;
  G4double pmtOuterRadius = PMT_OUTERR;
  G4double pmtHeight = PMT_HEIGHT;
  G4double pmtStartAngle = 0.*deg;
  G4double pmtSpanAngle = 360.*deg;
  
  
  //world
  G4double worldSizeXY = 3.*caloSizeXY;
  G4double worldSizeZ  = 3.*caloThickness;
  
  // Get materials
  G4NistManager *manager = G4NistManager::Instance();
  manager->SetVerbose(0);
  G4Element* elC = manager->FindOrBuildElement(6);
  G4Element* elH = manager->FindOrBuildElement(1);
  G4Element* elLu = manager->FindOrBuildElement(71);
  G4Element* elY = manager->FindOrBuildElement(39);
  G4Element* elSi = manager->FindOrBuildElement(14);
  G4Element* elO  = manager->FindOrBuildElement(8);
  G4Element* elCe = manager->FindOrBuildElement(58);
  G4Element* elAl = manager->FindOrBuildElement(13);
  G4Element* elN = manager->FindOrBuildElement(7);
  
  G4Material* defaultMaterial = G4Material::GetMaterial("G4_Galactic");
  G4Material* alpideMaterial = G4Material::GetMaterial("G4_Si");
  G4Material* KaptonMaterial = G4Material::GetMaterial("G4_KAPTON");
  G4Material* CopperMaterial = G4Material::GetMaterial("G4_Cu");
  G4Material* MylarMaterial = G4Material::GetMaterial("G4_MYLAR");
  
  //aluminium material
  G4Material* AlMaterial = G4Material::GetMaterial("G4_Al");
  
  //pmt material
  G4Material *pmtMaterial = new G4Material("Aluminium_Opt", 13., 26.98*g/mole, 2.700*g/cm3);
  const G4int pmtMat_num = 3;
  G4double pmtMat_ENERGY[pmtMat_num] = {0.5*eV, 6.69*eV, 7.50*eV};
  G4double pmtMat_RIND[pmtMat_num];
  for(int i=0; i<pmtMat_num; i++) pmtMat_RIND[i] = 1.0972;
  G4double pmtMat_ABSL[pmtMat_num];
  for(int i=0; i<pmtMat_num; i++) pmtMat_ABSL[i] = 0.00000007*cm;
  G4double pmtMat_REFL[pmtMat_num];
  for(int i=0; i<pmtMat_num; i++) pmtMat_REFL[i] = 0.0003;
  pmtMat_MPT = new G4MaterialPropertiesTable();
  pmtMat_MPT->AddProperty("RINDEX", pmtMat_ENERGY, pmtMat_RIND, pmtMat_num);
  pmtMat_MPT->AddProperty("ABSLENGTH", pmtMat_ENERGY, pmtMat_ABSL, pmtMat_num);
  pmtMat_MPT->AddProperty("REFLECTIVITY", pmtMat_ENERGY, pmtMat_REFL, pmtMat_num);
  pmtMaterial->SetMaterialPropertiesTable(pmtMat_MPT);
  
  G4Material* absorberMaterial;
  G4Material* crystalMaterial;
  
  G4bool IsOpticsActivated = fOptics;
  
  if(IsOpticsActivated)
    {
      absorberMaterial = new G4Material("ScintillatorEJ200_Opt",1.032*g/cm3,2);
      crystalMaterial = new G4Material("LYSO_Opt", 7.1*g/cm3, 5, kStateSolid);
    }
  else
    {
      absorberMaterial = new G4Material("ScintillatorEJ200",1.032*g/cm3,2);
      crystalMaterial = new G4Material("LYSO", 7.1*g/cm3, 5, kStateSolid);
    }
  
  absorberMaterial->AddElement(elC,19);
  absorberMaterial->AddElement(elH,21);
  
  crystalMaterial->AddElement(elLu, 71.43*perCent);
  crystalMaterial->AddElement(elY, 4.03*perCent);
  crystalMaterial->AddElement(elSi, 6.37*perCent);
  crystalMaterial->AddElement(elO, 18.14*perCent);
  crystalMaterial->AddElement(elCe, 0.02*perCent);
  
  //carbon fiber material for Alpide
  G4Material *CarbonFiberAlpideMaterial = new G4Material("CarbonFiberAlpide",1.867*g/cm3,1);
  CarbonFiberAlpideMaterial->AddElement(elC,1);
  
  //glue Araldite 2011 material for Alpide
  G4Material *GlueMaterial = new G4Material("GlueMaterial",1.05*g/cm3,1);
  GlueMaterial->AddElement(elC,1);
  
  //carbon fiber material for Trigger and Calo
  G4Material *CarbonFiberCaloMaterial = new G4Material("CarbonFiberCalo",1.581*g/cm3,1);
  CarbonFiberCaloMaterial->AddElement(elC,1);
  
  //Aluminium mixture material
  G4Material *AlMixMaterial = new G4Material("AlMixMaterial",2.71*g/cm3,1);
  AlMixMaterial->AddElement(elAl,1);
  
  //Poron material
  G4Material *PoronMaterial = new G4Material("PoronMaterial",0.32*g/cm3,4);
  PoronMaterial->AddElement(elC,20*perCent);
  PoronMaterial->AddElement(elO,40*perCent);
  PoronMaterial->AddElement(elH,20*perCent);
  PoronMaterial->AddElement(elN,20*perCent);
  
  //Scotch tape material (silicone)
  G4Material *SiliconeMaterial = new G4Material("SiliconeMaterial",1.2*g/cm3,2);
  SiliconeMaterial->AddElement(elSi,1);
  SiliconeMaterial->AddElement(elO,1);
  
  //Light guide material
  G4Material *LightGuideMaterial = new G4Material("LightGuideMat",1.032*g/cm3,2);
  LightGuideMaterial->AddElement(elC,19);
  LightGuideMaterial->AddElement(elH,21);
  
  if(IsOpticsActivated)
    {
      //absorber scintillator material 
      absorberMaterial->GetIonisation()->SetBirksConstant(0.16*mm/MeV);
      const G4int absOptMat_num = 55;
      G4double absOptMat_ENERGY[absOptMat_num]={2.481*eV, 2.487*eV, 2.498*eV, 2.515*eV, 2.527*eV, 2.544*eV,
						2.558*eV, 2.572*eV, 2.585*eV, 2.594*eV, 2.608*eV, 2.622*eV,
						2.638*eV, 2.655*eV, 2.674*eV, 2.687*eV, 2.708*eV, 2.743*eV,
						2.762*eV, 2.77*eV, 2.787*eV, 2.798*eV, 2.807*eV, 2.822*eV,
						2.831*eV, 2.843*eV, 2.859*eV, 2.88*eV, 2.894*eV, 2.902*eV,
						2.916*eV, 2.926*eV, 2.935*eV, 2.94*eV, 2.947*eV, 2.952*eV,
						2.955*eV, 2.961*eV, 2.966*eV, 2.971*eV, 2.977*eV, 2.982*eV,
						2.989*eV, 2.996*eV, 3.002*eV, 3.007*eV, 3.018*eV, 3.023*eV,
						3.034*eV, 3.044*eV, 3.055*eV, 3.07*eV, 3.083*eV, 3.102*eV,
						3.124*eV};
      
      G4double absOptMat_SCINT[absOptMat_num] = {0.05845, 0.06153, 0.07076, 0.08307, 0.09845, 0.11691, 0.1323,
						 0.15383, 0.17537, 0.19691, 0.22767, 0.26152, 0.30767, 0.3569,
						 0.39997, 0.42151, 0.45227, 0.52303, 0.56918, 0.5938, 0.64918,
						 0.68302, 0.71686, 0.76917, 0.80609, 0.85224, 0.90147, 0.95069,
						 0.98147, 0.99685, 0.99992, 0.99377, 0.98147, 0.94762, 0.90762,
						 0.8707, 0.84301, 0.80301, 0.73841, 0.68918, 0.63687, 0.58765,
						 0.53226, 0.46458, 0.41843, 0.36305, 0.30459, 0.26152, 0.20306,
						 0.16614, 0.11076, 0.04615, 0.01846, 0.00923, 0.00308};
      G4double absOptMat_RIND[absOptMat_num];
      for(int i=0; i<absOptMat_num; i++) absOptMat_RIND[i] = 1.58;
      // Attenuation length: NIM A 552 (2005) 449
      G4double absOptMat_ABSL[absOptMat_num];
      for(int i=0; i<absOptMat_num; i++) absOptMat_ABSL[i] = 380.*cm;
      absOptMat_MPT = new G4MaterialPropertiesTable();
      absOptMat_MPT->AddProperty("FASTCOMPONENT", absOptMat_ENERGY, absOptMat_SCINT, absOptMat_num)->SetSpline(true);
      absOptMat_MPT->AddProperty("RINDEX", absOptMat_ENERGY, absOptMat_RIND, absOptMat_num)->SetSpline(true);
      absOptMat_MPT->AddProperty("ABSLENGTH", absOptMat_ENERGY, absOptMat_ABSL, absOptMat_num)->SetSpline(true);
      absOptMat_MPT->AddConstProperty("SCINTILLATIONYIELD", 10574./MeV);
      absOptMat_MPT->AddConstProperty("RESOLUTIONSCALE",1.0);
      absOptMat_MPT->AddConstProperty("FASTTIMECONSTANT",2.1*ns);
      absOptMat_MPT->AddConstProperty("SLOWTIMECONSTANT",2.1*ns);
      absOptMat_MPT->AddConstProperty("FASTSCINTILLATIONRISETIME",0.9*ns);
      absOptMat_MPT->AddConstProperty("SLOWSCINTILLATIONRISETIME",0.9*ns);
      absOptMat_MPT->AddConstProperty("YIELDRATIO",1.0);
      absorberMaterial->SetMaterialPropertiesTable(absOptMat_MPT);
      
      //crystal scintillator material
      //Koba, Iwamoto et al., "Scintillation Efficiency of Inorganic Scintillators for Intermediate-Energy Charged Particles", Progress in Nuclear Science and Technology, 2011
      crystalMaterial->GetIonisation()->SetBirksConstant(0.011*mm/MeV);
      const G4int cryOptMat_num = 19;
      G4double cryOptMat_ENERGY[cryOptMat_num]={1.91*eV,2.07*eV,2.16*eV,2.25*eV,2.37*eV,2.48*eV,2.68*eV,2.76*eV,2.86*eV,2.95*eV,2.97*eV,3.02*eV,3.05*eV,3.08*eV,3.16*eV,3.21*eV,3.28*eV,3.35*eV,3.54*eV};
      G4double cryOptMat_SCINT[cryOptMat_num] = {0,0.04,0.08,0.16,0.32,0.48,0.84,0.94,0.96,1,0.92,0.84,0.72,0.6,0.36,0.2,0.08,0.04,0.00};
      G4double cryOptMat_RIND[cryOptMat_num];
      for(int i=0; i<cryOptMat_num; i++) cryOptMat_RIND[i] = 1.81;
      //Attenuation length: L. Zhang et al., "LSO/LYSO Crystals for Calorimeters in Future HEP Experiments", IEEE Trans. on Nucl. Sci., 61 (2014)
      //J. Chen et al., "Large Size LSO and LYSO Crystals for Future High Energy Physics Experiments"", IEEE Trans. on Nucl. Sci., 54 (2007)
      G4double cryOptMat_ABSL[cryOptMat_num];
      for(int i=0; i<cryOptMat_num; i++) cryOptMat_ABSL[i] = 170.*cm;
      cryOptMat_MPT = new G4MaterialPropertiesTable();
      cryOptMat_MPT->AddProperty("FASTCOMPONENT", cryOptMat_ENERGY, cryOptMat_SCINT, cryOptMat_num);
      cryOptMat_MPT->AddProperty("RINDEX", cryOptMat_ENERGY, cryOptMat_RIND, cryOptMat_num);
      cryOptMat_MPT->AddProperty("ABSLENGTH", cryOptMat_ENERGY, cryOptMat_ABSL, cryOptMat_num);
      cryOptMat_MPT->AddConstProperty("SCINTILLATIONYIELD", 32000./MeV);
      cryOptMat_MPT->AddConstProperty("RESOLUTIONSCALE",1.0);
      cryOptMat_MPT->AddConstProperty("FASTTIMECONSTANT", 42.*ns);
      crystalMaterial->SetMaterialPropertiesTable(cryOptMat_MPT);
    } //end if(IsOpticsActivated)
  
  if ( !defaultMaterial || !absorberMaterial || !AlMaterial || !alpideMaterial || !crystalMaterial || !pmtMaterial || !KaptonMaterial || !CopperMaterial)
    {
      G4ExceptionDescription msg;
      msg << "Cannot retrieve materials already defined.";
      G4Exception("HEPD2MCDetectorConstruction::DefineVolumes()",
		  "MyCode0001", FatalException, msg);
    }
  
  //****************************************************************************************
  // WORLD
  G4VSolid* worldS = new G4Box("World", worldSizeXY, worldSizeXY, worldSizeZ);
  G4LogicalVolume* worldLV = new G4LogicalVolume(worldS, defaultMaterial, "World");
  worldPV = new G4PVPlacement(0, G4ThreeVector(), worldLV, "World", 0, false, 0, fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  // BLANKET
  G4VSolid* BlanketS = new G4Box("Blanket", Blanket_X/2., Blanket_Y/2., Blanket_Z/2.);
  G4LogicalVolume* BlanketLV = new G4LogicalVolume(BlanketS, MylarMaterial, "Blanket");
  fBlanketPV = new G4PVPlacement(0,G4ThreeVector(0.,0.,axes+Blanket_Z/2.),BlanketLV,"Blanket",worldLV,false,0,fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  // EXTERNAL WINDOW
  // Window container
  G4VSolid* WindowContainerS = new G4Box("WindowContainer", Wall_X/2., Wall_Y/2., (WallExternal_Z+WallHoneyComb_Z+WallExternal_Z)/2.);
  G4LogicalVolume* WindowContainerLV = new G4LogicalVolume(WindowContainerS, defaultMaterial, "WindowContainer");
  fWindowContainerPV = new G4PVPlacement(0, G4ThreeVector(-WallHole_X,-WallHole_Y,axes+blanket_dist+Blanket_Z+(windowOut_Z+windowIn_Z)/2.), WindowContainerLV, "WindowContainer", worldLV, false, 0, fCheckOverlaps);
  
  // WindowOut
  G4VSolid* WindowOutS = new G4Box("WindowOut", window_X/2., window_Y/2., windowOut_Z/2.);
  G4LogicalVolume* WindowOutLV = new G4LogicalVolume(WindowOutS, KaptonMaterial, "WindowOut");
  fWindowOutPV = new G4PVPlacement(0,G4ThreeVector(WallHole_X,WallHole_Y,-(windowOut_Z+windowIn_Z)/2.+windowOut_Z/2.), WindowOutLV,"WindowOut",WindowContainerLV,false,0,fCheckOverlaps);
  
  // WindowIn
  G4VSolid* WindowInS = new G4Box("WindowIn", window_X/2., window_Y/2., windowIn_Z/2.);
  G4LogicalVolume* WindowInLV = new G4LogicalVolume(WindowInS, CopperMaterial, "WindowIn");
  fWindowInPV = new G4PVPlacement(0,G4ThreeVector(WallHole_X,WallHole_Y,-(windowOut_Z+windowIn_Z)/2.+windowOut_Z+windowIn_Z/2.),WindowInLV,"WindowIn",WindowContainerLV,false,0,fCheckOverlaps);
  
  //Wall
  G4ThreeVector transWallHole(WallHole_X,WallHole_Y,0.);
  G4SubtractionSolid* WallHoneyCombS = new G4SubtractionSolid("WallHoneyComb", new G4Box("WallHoneyComb_1",Wall_X/2., Wall_Y/2., WallHoneyComb_Z/2.), new G4Box("WallHoneyComb_2",window_X/2., window_Y/2., WallHole_Z/2.), 0, transWallHole);
  G4LogicalVolume* WallHoneyCombLV = new G4LogicalVolume(WallHoneyCombS, AlMaterial,"WallHoneyComb");
  fWallHoneyCombPV = new G4PVPlacement(0,G4ThreeVector(0,0,0),WallHoneyCombLV,"WallHoneyComb",WindowContainerLV,false,0,fCheckOverlaps);
  
  G4SubtractionSolid* WallExternalS = new G4SubtractionSolid("WallExternal", new G4Box("WallExternal_1",Wall_X/2., Wall_Y/2., WallExternal_Z/2.), new G4Box("WallExternal_2",window_X/2., window_Y/2., WallHole_Z/2.), 0, transWallHole);
  G4LogicalVolume* WallExternalLV = new G4LogicalVolume(WallExternalS, AlMaterial,"WallExternal");
  fWallExternalOutPV = new G4PVPlacement(0,G4ThreeVector(0,0,-WallExternal_Z/2.-WallHoneyComb_Z/2.),WallExternalLV,"WallExternalOut",WindowContainerLV,false,0,fCheckOverlaps);
  fWallExternalInPV = new G4PVPlacement(0,G4ThreeVector(0,0,+WallExternal_Z/2.+WallHoneyComb_Z/2.),WallExternalLV,"WallExternalIn",WindowContainerLV,false,0,fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  // ALPIDE
  //Alpide container
  G4VSolid* AlpContS = new G4Box("AlpCont", ColdPlateSizeX/2., ((nofAlpideY/2)*(2*alpideSizeY+alpchip_gap+2.*alpideGap_Y+2*AlpRibsY)-2.*alpideGap_Y)/2., (CuSupportSizeZ+FPCSizeZ+3.*alpideSizeZ+3.*GlueFPC_SizeZ+3.*GlueColdPlate_SizeZ+2.*alpideGap+ColdPlateSizeZ+AlpRibsZ)/2.);
  G4LogicalVolume* AlpContLV = new G4LogicalVolume(AlpContS, defaultMaterial, "AlpCont");
  fAlpContPV = new G4PVPlacement(0, G4ThreeVector(-ColdPlateShift_X,0.,axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+(CuSupportSizeZ+FPCSizeZ+3.*alpideSizeZ+3.*GlueFPC_SizeZ+3.*GlueColdPlate_SizeZ+2.*alpideGap+ColdPlateSizeZ+AlpRibsZ)/2.), AlpContLV, "AlpCont", worldLV, false, 0, fCheckOverlaps);
  
  //Alpide tower
  G4VSolid* AlpTowerS = new G4Box("AlpTower", ColdPlateSizeX/2., (2*alpideSizeY+alpchip_gap+2.*alpideGap_Y+2*AlpRibsY)/2., (CuSupportSizeZ+FPCSizeZ+3.*alpideSizeZ+3.*GlueFPC_SizeZ+3.*GlueColdPlate_SizeZ+2.*alpideGap+ColdPlateSizeZ+AlpRibsZ)/2.);
  G4LogicalVolume* AlpTowerLV = new G4LogicalVolume(AlpTowerS, defaultMaterial, "AlpTower");
  fAlpTowerPV = new G4PVReplica("AlpTower", AlpTowerLV, AlpContLV, kYAxis, nofAlpideY/2, (2*alpideSizeY+2.*alpideGap_Y+2*AlpRibsY));
  
  //Alpide plane
  G4VSolid* AlpPlaneS = new G4Box("AlpPlane", (nofAlpideX*alpideSizeX+4.*alpchip_gap)/2., (2*alpideSizeY+alpchip_gap)/2., (alpideSizeZ)/2.);
  G4LogicalVolume* AlpPlaneLV = new G4LogicalVolume(AlpPlaneS, defaultMaterial, "AlpPlane");
  
  //Alpide double-sensor
  G4VSolid* AlpDoubleS = new G4Box("AlpDoubleS", alpideSizeX/2., (2.*alpideSizeY+alpchip_gap)/2., alpideSizeZ/2.);
  G4LogicalVolume* AlpDoubleLV = new G4LogicalVolume(AlpDoubleS, defaultMaterial, "AlpDouble");
  fAlpDoublePV = new G4PVReplica("AlpDouble", AlpDoubleLV, AlpPlaneLV, kXAxis, nofAlpideX, (alpideSizeX+alpchip_gap));
  
  //Alpide sensor
  G4VSolid* AlpS = new G4Box("Alp", alpideSizeX/2., alpideSizeY/2., alpideSizeZ/2.);
  G4LogicalVolume* Alp1LV = new G4LogicalVolume(AlpS, alpideMaterial, "Alp");
  
  fAlp1PV = new G4PVPlacement(0, G4ThreeVector(0.,alpchip_gap/2.+alpideSizeY/2.,0.),Alp1LV, "Alp1",AlpDoubleLV, false, 0, fCheckOverlaps);
  G4LogicalVolume* Alp2LV = new G4LogicalVolume(AlpS, alpideMaterial, "Alp");
  fAlp2PV = new G4PVPlacement(0, G4ThreeVector(0.,-alpchip_gap/2.-alpideSizeY/2.,0.),Alp2LV, "Alp2",AlpDoubleLV, false, 0, fCheckOverlaps);
  
  //Alpide active sensor
  G4VSolid* AlpActiveS = new G4Box("AlpActive", alpideActiveSizeX/2., alpideActiveSizeY/2., alpideActiveSizeZ/2.);
  G4LogicalVolume* AlpActiveLV = new G4LogicalVolume(AlpActiveS, alpideMaterial, "AlpActive");
  fAlpActive1PV = new G4PVPlacement(0, G4ThreeVector(0.,-(alpideSizeY-alpideActiveSizeY)/2.,0.),AlpActiveLV, "AlpActive1",Alp1LV, false, 0, fCheckOverlaps);
  fAlpActive2PV = new G4PVPlacement(0, G4ThreeVector(0.,+(alpideSizeY-alpideActiveSizeY)/2.,0.),AlpActiveLV, "AlpActive2",Alp2LV, false, 0, fCheckOverlaps);
  
  fAlpPlane1PV = new G4PVPlacement(0,G4ThreeVector(ColdPlateShift_X, 0., -(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ/2.), AlpPlaneLV, "AlpPlane1", AlpTowerLV, false, 0, fCheckOverlaps);
  fAlpPlane2PV = new G4PVPlacement(0,G4ThreeVector(ColdPlateShift_X, 0., -(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ+alpideGap+alpideSizeZ/2.), AlpPlaneLV, "AlpPlane2", AlpTowerLV, false, 0, fCheckOverlaps);
  fAlpPlane3PV = new G4PVPlacement(0,G4ThreeVector(ColdPlateShift_X, 0., -(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ+alpideGap+alpideSizeZ+alpideGap+alpideSizeZ/2.), AlpPlaneLV, "AlpPlane3", AlpTowerLV, false, 0, fCheckOverlaps);
  
  //copper support
  G4VSolid* CuSupport_S = new G4Box("CuSupport", CuSupportSizeX/2., CuSupportSizeY/2., CuSupportSizeZ/2.);
  G4LogicalVolume* CuSupport_LV = new G4LogicalVolume(CuSupport_S, CopperMaterial, "CuSupport");
  fCuSupport1_PV = new G4PVPlacement(0,G4ThreeVector(FPCShift_X-ColdPlateShift_X, 0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ/2.), CuSupport_LV, "CuSupport1", AlpTowerLV, false, 0, fCheckOverlaps);
  fCuSupport2_PV = new G4PVPlacement(0,G4ThreeVector(FPCShift_X-ColdPlateShift_X, 0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ/2.+alpideSizeZ+alpideGap), CuSupport_LV, "CuSupport2", AlpTowerLV, false, 0, fCheckOverlaps);
  fCuSupport3_PV = new G4PVPlacement(0,G4ThreeVector(FPCShift_X-ColdPlateShift_X, 0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ/2.+alpideSizeZ+alpideGap+alpideSizeZ+alpideGap), CuSupport_LV, "CuSupport3", AlpTowerLV, false, 0, fCheckOverlaps);
  
  //FPC
  G4VSolid* FPC_S = new G4Box("FPC", FPCSizeX/2., FPCSizeY/2., FPCSizeZ/2.);
  G4LogicalVolume* FPC_LV = new G4LogicalVolume(FPC_S, KaptonMaterial, "FPC");
  fFPC1_PV = new G4PVPlacement(0,G4ThreeVector(FPCShift_X-ColdPlateShift_X,0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ/2.), FPC_LV, "FPC1", AlpTowerLV, false, 0, fCheckOverlaps);
  fFPC2_PV = new G4PVPlacement(0,G4ThreeVector(FPCShift_X-ColdPlateShift_X,0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ/2.+alpideSizeZ+alpideGap), FPC_LV, "FPC2", AlpTowerLV, false, 0, fCheckOverlaps);
  fFPC3_PV = new G4PVPlacement(0,G4ThreeVector(FPCShift_X-ColdPlateShift_X,0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ/2.+alpideSizeZ+alpideGap+alpideSizeZ+alpideGap), FPC_LV, "FPC3", AlpTowerLV, false, 0, fCheckOverlaps);
  
  //Glue Araldite 2011 between FPC and chip
  G4VSolid* GlueBeforeAlpS = new G4Box("GlueBeforeAlp", GlueSizeX/2., GlueSizeY/2., GlueFPC_SizeZ/2.);
  G4LogicalVolume* GlueBeforeAlpLV = new G4LogicalVolume(GlueBeforeAlpS, GlueMaterial, "GlueBeforeAlp");
  fGlueBeforeAlp1_PV = new G4PVPlacement(0,G4ThreeVector(ColdPlateShift_X,0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ/2.), GlueBeforeAlpLV, "GlueBeforeAlp1", AlpTowerLV, false, 0, fCheckOverlaps);
  fGlueBeforeAlp2_PV = new G4PVPlacement(0,G4ThreeVector(ColdPlateShift_X,0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ/2.+alpideSizeZ+alpideGap), GlueBeforeAlpLV, "GlueBeforeAlp2", AlpTowerLV, false, 0, fCheckOverlaps);
  fGlueBeforeAlp3_PV = new G4PVPlacement(0,G4ThreeVector(ColdPlateShift_X,0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ/2.+alpideSizeZ+alpideGap+alpideSizeZ+alpideGap), GlueBeforeAlpLV, "GlueBeforeAlp3", AlpTowerLV, false, 0, fCheckOverlaps);
  
  //Glue Araldite 2011 between chip and cold plate
  G4VSolid* GlueAfterAlpS = new G4Box("GlueAfterAlp", GlueSizeX/2., GlueSizeY/2., GlueColdPlate_SizeZ/2.);
  G4LogicalVolume* GlueAfterAlpLV = new G4LogicalVolume(GlueAfterAlpS, GlueMaterial, "GlueAfterAlp");
  fGlueAfterAlp1_PV = new G4PVPlacement(0,G4ThreeVector(ColdPlateShift_X,0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ+GlueColdPlate_SizeZ/2.), GlueAfterAlpLV, "GlueAfterAlp1", AlpTowerLV, false, 0, fCheckOverlaps);
  fGlueAfterAlp2_PV = new G4PVPlacement(0,G4ThreeVector(ColdPlateShift_X,0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ+alpideGap+alpideSizeZ+GlueColdPlate_SizeZ/2.), GlueAfterAlpLV, "GlueAfterAlp2", AlpTowerLV, false, 0, fCheckOverlaps);
  fGlueAfterAlp3_PV = new G4PVPlacement(0,G4ThreeVector(ColdPlateShift_X,0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ+alpideGap+alpideSizeZ+alpideGap+alpideSizeZ+GlueColdPlate_SizeZ/2.), GlueAfterAlpLV, "GlueAfterAlp3", AlpTowerLV, false, 0, fCheckOverlaps);
  
  //cold plate
  G4VSolid* ColdPlateS = new G4Box("ColdPlate", ColdPlateSizeX/2., ColdPlateSizeY/2., ColdPlateSizeZ/2.);
  G4LogicalVolume* ColdPlateLV = new G4LogicalVolume(ColdPlateS, CarbonFiberAlpideMaterial, "ColdPlate");
  fColdPlate1_PV = new G4PVPlacement(0,G4ThreeVector(0.,0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ+GlueColdPlate_SizeZ+ColdPlateSizeZ/2.),ColdPlateLV,"ColdPlate1",AlpTowerLV, false, 0, fCheckOverlaps);
  fColdPlate2_PV = new G4PVPlacement(0,G4ThreeVector(0.,0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ+GlueColdPlate_SizeZ+alpideGap+alpideSizeZ+ColdPlateSizeZ/2.),ColdPlateLV,"ColdPlate2",AlpTowerLV, false, 0, fCheckOverlaps);
  fColdPlate3_PV = new G4PVPlacement(0,G4ThreeVector(0.,0.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ+GlueColdPlate_SizeZ+alpideGap+alpideSizeZ+alpideGap+alpideSizeZ+ColdPlateSizeZ/2.),ColdPlateLV,"ColdPlate3",AlpTowerLV, false, 0, fCheckOverlaps);
  
  //ribs
  G4VSolid* AlpRibsS = new G4Box("AlpRibs", AlpRibsX/2., AlpRibsY/2., AlpRibsZ/2.);
  G4LogicalVolume* AlpRibsLV = new G4LogicalVolume(AlpRibsS, CarbonFiberAlpideMaterial, "AlpRibs");
  fAlpRibs1_PV = new G4PVPlacement(0,G4ThreeVector(0., -ColdPlateSizeY/2.-AlpRibsY/2.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ+GlueColdPlate_SizeZ+AlpRibsZ/2.),AlpRibsLV,"AlpRibs", AlpTowerLV, false, 0, fCheckOverlaps);
  fAlpRibs2_PV = new G4PVPlacement(0,G4ThreeVector(0., +ColdPlateSizeY/2.+AlpRibsY/2.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ+GlueColdPlate_SizeZ+AlpRibsZ/2.),AlpRibsLV,"AlpRibs", AlpTowerLV, false, 0, fCheckOverlaps);
  fAlpRibs3_PV = new G4PVPlacement(0,G4ThreeVector(0., -ColdPlateSizeY/2.-AlpRibsY/2.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ+GlueColdPlate_SizeZ+alpideGap+alpideSizeZ+AlpRibsZ/2.),AlpRibsLV,"AlpRibs", AlpTowerLV, false, 0, fCheckOverlaps);
  fAlpRibs4_PV = new G4PVPlacement(0,G4ThreeVector(0., +ColdPlateSizeY/2.+AlpRibsY/2.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ+GlueColdPlate_SizeZ+alpideGap+alpideSizeZ+AlpRibsZ/2.),AlpRibsLV,"AlpRibs", AlpTowerLV, false, 0, fCheckOverlaps);
  fAlpRibs5_PV = new G4PVPlacement(0,G4ThreeVector(0., -ColdPlateSizeY/2.-AlpRibsY/2.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ+GlueColdPlate_SizeZ+alpideGap+alpideSizeZ+alpideGap+alpideSizeZ+AlpRibsZ/2.),AlpRibsLV,"AlpRibs", AlpTowerLV, false, 0, fCheckOverlaps);
  fAlpRibs6_PV = new G4PVPlacement(0,G4ThreeVector(0., +ColdPlateSizeY/2.+AlpRibsY/2.,-(CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ)/2.+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+alpideSizeZ+GlueColdPlate_SizeZ+alpideGap+alpideSizeZ+alpideGap+alpideSizeZ+AlpRibsZ/2.),AlpRibsLV,"AlpRibs", AlpTowerLV, false, 0, fCheckOverlaps);
  
  //Alpide interface plate (positioned between Alpide and T1)
  G4SubtractionSolid* AlpInterfacePlateS = new G4SubtractionSolid("AlpInterfacePlate", new G4Box("AlpInterfacePlate_1", (AlpInterfacePlate_X)/2., (AlpInterfacePlate_Y)/2., AlpInterfacePlate_Z/2.),new G4Box("AlpInterfacePlate_2", ColdPlateSizeX/2., 5.*(ColdPlateSizeY+2.*AlpRibsY+alpideGap_Y)/2., (AlpInterfacePlate_Z+1.*mm)/2.),0,G4ThreeVector(24.*mm,0,0));
  G4LogicalVolume* AlpInterfacePlateLV = new G4LogicalVolume(AlpInterfacePlateS, AlMixMaterial, "AlpInterfacePlate");
  fAlpInterfacePlatePV = new G4PVPlacement(0, G4ThreeVector(FPCShift_X,0,axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ+0.4*mm+AlpInterfacePlate_Z/2.), AlpInterfacePlateLV, "AlpInterfacePlate", worldLV, false, 0, fCheckOverlaps);  
  //****************************************************************************************
  
  //****************************************************************************************
  // TRIGGER T1
  // Trigger: container 1st plane and its structures
  G4VSolid* T1ContS = new G4Box("T1Cont", (trigger1SizeX+2.*LG_height+2.*FrameT1_X+2.*PmtFrameT1_dist)/2., (AlpInterfacePlate_Y)/2., FrameT1_Z/2.);
  G4LogicalVolume* T1ContLV = new G4LogicalVolume(T1ContS, defaultMaterial, "T1Cont");
  G4double T1_posZ = axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+CuSupportSizeZ+FPCSizeZ+GlueFPC_SizeZ+3.*alpideSizeZ+2.*alpideGap+GlueColdPlate_SizeZ+ColdPlateSizeZ+AlpRibsZ+0.4*mm+AlpInterfacePlate_Z+FrameT1_Z/2.;
  new G4PVPlacement(0, G4ThreeVector(0,0,T1_posZ), T1ContLV, "T1Cont", worldLV, false, 0, fCheckOverlaps);
  
  // Trigger: container 1st plane
  G4VSolid* triggerCont1S = new G4Box("triggerCont1", (trigger1SizeX+2.*pmtHeight+2.*LG_height)/2., trigger1SizeY/2., T1Ribs_Z/2.);
  G4LogicalVolume* triggerCont1LV = new G4LogicalVolume(triggerCont1S, defaultMaterial, "triggerCont1");
  new G4PVPlacement(0, G4ThreeVector(0,0,0), triggerCont1LV, "triggerCont1", T1ContLV, false, 0, fCheckOverlaps);
  
  // Trigger: bars 1st plane
  G4VSolid* trigger1S = new G4Box("T1", (trigger1SizeX+2.*pmtHeight+2.*LG_height)/2., (trigger1SizeY/nofBars - barsGap)/2., (trigger1Thickness+2.*T1PoronThickness+2.*T1WrappingThickness)/2.);
  G4LogicalVolume* trigger1LV = new G4LogicalVolume(trigger1S, defaultMaterial, "T1");
  ftrigger1_1PV = new G4PVPlacement(0, G4ThreeVector(0.,-2.*(trigger1SizeY/nofBars),0.), trigger1LV, "T1_1", triggerCont1LV, false, 0, fCheckOverlaps);
  ftrigger1_2PV = new G4PVPlacement(0, G4ThreeVector(0.,-1.*(trigger1SizeY/nofBars),0.), trigger1LV, "T1_2", triggerCont1LV, false, 0, fCheckOverlaps);
  ftrigger1_3PV = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), trigger1LV, "T1_3", triggerCont1LV, false, 0, fCheckOverlaps);
  ftrigger1_4PV = new G4PVPlacement(0, G4ThreeVector(0.,+1.*(trigger1SizeY/nofBars),0.), trigger1LV, "T1_4", triggerCont1LV, false, 0, fCheckOverlaps);
  ftrigger1_5PV = new G4PVPlacement(0, G4ThreeVector(0.,+2.*(trigger1SizeY/nofBars),0.), trigger1LV, "T1_5", triggerCont1LV, false, 0, fCheckOverlaps);
  
  // Trigger: bars 1st plane
  G4VSolid* bar1S = new G4Box("Bar1", trigger1SizeX/2., (trigger1SizeY/nofBars - barsGap)/2., trigger1Thickness/2.);
  G4LogicalVolume* bar1LV = new G4LogicalVolume(bar1S, absorberMaterial, "Bar1");
  fTBars1PV = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), bar1LV, "Bar1", trigger1LV, false, 0, fCheckOverlaps);
  
  // Trigger: poron 1st plane
  G4VSolid* T1PoronS = new G4Box("T1Poron", trigger1SizeX/2., (trigger1SizeY/nofBars - barsGap)/2., T1PoronThickness/2.);
  G4LogicalVolume* T1PoronLV = new G4LogicalVolume(T1PoronS, PoronMaterial, "T1Poron");
  fPoronBeforeT1PV = new G4PVPlacement(0, G4ThreeVector(0., 0., -trigger1Thickness/2.-T1WrappingThickness-T1PoronThickness/2.), T1PoronLV, "PoronBeforeT1", trigger1LV, false, 0, fCheckOverlaps);
  fPoronAfterT1PV = new G4PVPlacement(0, G4ThreeVector(0., 0., trigger1Thickness/2.+T1WrappingThickness+T1PoronThickness/2.), T1PoronLV, "PoronAfterT1", trigger1LV, false, 0, fCheckOverlaps);
  
  // Trigger: wrapping 1st plane
  G4VSolid* T1WrappingS = new G4Box("T1Wrapping", trigger1SizeX/2., (trigger1SizeY/nofBars - barsGap)/2., T1WrappingThickness/2.);
  G4LogicalVolume* T1WrappingLV = new G4LogicalVolume(T1WrappingS, PoronMaterial, "T1Wrapping");
  fWrappingBeforeT1PV = new G4PVPlacement(0, G4ThreeVector(0., 0., -trigger1Thickness/2.-T1WrappingThickness/2.), T1WrappingLV, "WrappingBeforeT1", trigger1LV, false, 0, fCheckOverlaps);
  fWrappingAfterT1PV = new G4PVPlacement(0, G4ThreeVector(0., 0., trigger1Thickness/2.+T1WrappingThickness/2.), T1WrappingLV, "WrappingAfterT1", trigger1LV, false, 0, fCheckOverlaps);
  
  //Comp planes before and after T1
  G4Box* T1CompPlaneS = new G4Box("T1CompPlane", (T1CompPlane_X+PmtFrameT1_dist)/2., T1CompPlane_Y/2., T1CompPlane_Z/2.);
  G4LogicalVolume* T1CompPlaneLV = new G4LogicalVolume(T1CompPlaneS, CarbonFiberCaloMaterial, "T1CompPlane");
  fCompPlaneBeforeT1PV = new G4PVPlacement(0, G4ThreeVector(0., 0.,-trigger1Thickness/2.-T1WrappingThickness-T1PoronThickness-T1CompPlane_Z/2.), T1CompPlaneLV, "CompPlaneBeforeT1", T1ContLV, false, 0, fCheckOverlaps);
  fCompPlaneAfterT1PV = new G4PVPlacement(0, G4ThreeVector(0., 0.,+trigger1Thickness/2.+T1WrappingThickness+T1PoronThickness+T1CompPlane_Z/2.), T1CompPlaneLV, "CompPlaneAfterT1", T1ContLV, false, 0, fCheckOverlaps);
  
  //Frame structure for T1
  G4SubtractionSolid* FrameT1S = new G4SubtractionSolid("FrameT1S", new G4Box("FrameT1_1", (trigger1SizeX+2.*LG_height+2.*FrameT1_X+2.*PmtFrameT1_dist)/2., (AlpInterfacePlate_Y)/2., FrameT1_Z/2.),new G4Box("FrameT1_2", (trigger1SizeX+2.*LG_height+PmtFrameT1_dist)/2., (AlpInterfacePlate_Y-2.*FrameT1_Y)/2., FrameT1_Z/2.));
  G4LogicalVolume* FrameT1LV = new G4LogicalVolume(FrameT1S, AlMixMaterial, "FrameT1");
  fFrameT1PV = new G4PVPlacement(0, G4ThreeVector(0,0,0), FrameT1LV, "FrameT1", T1ContLV, false, 0, fCheckOverlaps);
  
  //Support ribs between T1 bars
  G4Box* T1RibsS = new G4Box("T1Ribs", T1Ribs_X/2., T1Ribs_Y/2., T1Ribs_Z/2.);
  G4LogicalVolume* T1RibsLV = new G4LogicalVolume(T1RibsS, CarbonFiberCaloMaterial, "T1Ribs");
  fT1RibsPV_1 = new G4PVPlacement(0, G4ThreeVector(0.,+3.*(trigger1SizeY/nofBars)/2.,0), T1RibsLV, "T1Ribs", triggerCont1LV, false, 0, fCheckOverlaps);
  fT1RibsPV_2 = new G4PVPlacement(0, G4ThreeVector(0.,+(trigger1SizeY/nofBars)/2.,0), T1RibsLV, "T1Ribs", triggerCont1LV, false, 0, fCheckOverlaps);
  fT1RibsPV_3 = new G4PVPlacement(0, G4ThreeVector(0.,-(trigger1SizeY/nofBars)/2.,0), T1RibsLV, "T1Ribs", triggerCont1LV, false, 0, fCheckOverlaps);
  fT1RibsPV_4 = new G4PVPlacement(0, G4ThreeVector(0.,-3.*(trigger1SizeY/nofBars)/2.,0), T1RibsLV, "T1Ribs", triggerCont1LV, false, 0, fCheckOverlaps);
  
  //Light Guide for T1
  G4VSolid* LightGuide1S = new G4Trd("LightGuide1", ((trigger1SizeY)/2.)/nofBars-barsGap/2., LG_X/2., trigger1Thickness/2., LG_Y/2., LG_height/2.);
  G4LogicalVolume* LightGuide1LV = new G4LogicalVolume(LightGuide1S, LightGuideMaterial, "LightGuide1");
  G4RotationMatrix* LG1_rot1 = new G4RotationMatrix;
  LG1_rot1->rotateZ(+90.*deg);
  LG1_rot1->rotateX(+90.*deg);
  G4RotationMatrix* LG1_rot2 = new G4RotationMatrix;
  LG1_rot2->rotateZ(-90.*deg);
  LG1_rot2->rotateX(+90.*deg);
  new G4PVPlacement(LG1_rot1,G4ThreeVector(trigger1SizeX/2.+LG_height/2., 0., 0.), LightGuide1LV, "LightGuideT1_1", trigger1LV, false, 0, fCheckOverlaps);
  new G4PVPlacement(LG1_rot2,G4ThreeVector(-trigger1SizeX/2.-LG_height/2., 0., 0.), LightGuide1LV, "LightGuideT1_2", trigger1LV, false, 0, fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************  
  // TRIGGER T2
  // Trigger: container 2nd plane and its structures
  G4VSolid* T2ContS = new G4Box("T2Cont", trigger2SizeX/2., (trigger2SizeY+2.*pmtHeight)/2., (2.*T2PoronThickness + 2.*T2WrappingThickness + 2.*T2CompPlane_Z + trigger2Thickness)/2.);
  G4LogicalVolume* T2ContLV = new G4LogicalVolume(T2ContS, defaultMaterial, "T2Cont");
  G4double T2_posZ = T1_posZ + trigger1Thickness/2. + T1WrappingThickness + T1PoronThickness + triggerGap + T2CompPlane_Z + T2PoronThickness + T2WrappingThickness + trigger2Thickness/2.;
  new G4PVPlacement(0, G4ThreeVector(0,0,T2_posZ), T2ContLV, "T2Cont", worldLV, false, 0, fCheckOverlaps);
  
  // Trigger: container 2nd plane
  G4VSolid* triggerCont2S = new G4Box("triggerCont2", trigger2SizeX/2., (trigger2SizeY+2.*pmtHeight)/2., (trigger2Thickness+2.*T2PoronThickness+2.*T2WrappingThickness)/2.);
  G4LogicalVolume* triggerCont2LV = new G4LogicalVolume(triggerCont2S, defaultMaterial, "triggerCont2");
  new G4PVPlacement(0, G4ThreeVector(0,0,0), triggerCont2LV, "triggerCont2", T2ContLV, false, 0, fCheckOverlaps);
  
  // Trigger: bars 2nd plane
  G4VSolid* trigger2S = new G4Box("T2", (trigger2SizeX/nofBars - barsGap)/2., (trigger2SizeY+2.*pmtHeight)/2., (trigger2Thickness+2.*T2PoronThickness+2.*T2WrappingThickness)/2.);
  G4LogicalVolume* trigger2LV = new G4LogicalVolume(trigger2S, defaultMaterial, "T2");
  ftrigger2_1PV = new G4PVPlacement(0, G4ThreeVector(-2.*(trigger2SizeX/nofBars),0.,0.), trigger2LV, "T2_1", triggerCont2LV, false, 0, fCheckOverlaps);
  ftrigger2_2PV = new G4PVPlacement(0, G4ThreeVector(-1.*(trigger2SizeX/nofBars),0.,0.), trigger2LV, "T2_2", triggerCont2LV, false, 0, fCheckOverlaps);
  ftrigger2_3PV = new G4PVPlacement(0, G4ThreeVector(0.,0.), trigger2LV, "T2_3", triggerCont2LV, false, 0, fCheckOverlaps);
  ftrigger2_4PV = new G4PVPlacement(0, G4ThreeVector(+1.*(trigger2SizeX/nofBars),0.,0.), trigger2LV, "T2_4", triggerCont2LV, false, 0, fCheckOverlaps);
  ftrigger2_5PV = new G4PVPlacement(0, G4ThreeVector(+2.*(trigger2SizeX/nofBars),0.,0.), trigger2LV, "T2_5", triggerCont2LV, false, 0, fCheckOverlaps);
  
  // Trigger: bars 2nd plane
  G4VSolid* bar2S = new G4Box("Bar2", (trigger2SizeX/nofBars - barsGap)/2., trigger2SizeY/2., trigger2Thickness/2.);
  G4LogicalVolume* bar2LV = new G4LogicalVolume(bar2S, absorberMaterial, "Bar2");
  fTBars2PV = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), bar2LV, "Bar2", trigger2LV, false, 0, fCheckOverlaps);
  
  // Trigger: poron 2nd plane
  G4VSolid* T2PoronS = new G4Box("T2Poron", (trigger2SizeX/nofBars-barsGap)/2., trigger2SizeY/2., T2PoronThickness/2.);
  G4LogicalVolume* T2PoronLV = new G4LogicalVolume(T2PoronS, PoronMaterial, "T2Poron");
  fPoronBeforeT2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., -trigger2Thickness/2.-T2WrappingThickness-T2PoronThickness/2.), T2PoronLV, "PoronBeforeT2", trigger2LV, false, 0, fCheckOverlaps);
  fPoronAfterT2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., trigger2Thickness/2.+T2WrappingThickness+T2PoronThickness/2.), T2PoronLV, "PoronAfterT2", trigger2LV, false, 0, fCheckOverlaps);
  
  // Trigger: wrapping 2nd plane
  G4VSolid* T2WrappingS = new G4Box("T2Wrapping", (trigger2SizeX/nofBars-barsGap)/2., trigger2SizeY/2., T2WrappingThickness/2.);
  G4LogicalVolume* T2WrappingLV = new G4LogicalVolume(T2WrappingS, PoronMaterial, "T2Wrapping");
  fWrappingBeforeT2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., -trigger2Thickness/2.-T2WrappingThickness/2.), T2WrappingLV, "WrappingBeforeT2", trigger2LV, false, 0, fCheckOverlaps);
  fWrappingAfterT2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., trigger2Thickness/2.+T2WrappingThickness/2.), T2WrappingLV, "WrappingAfterT2", trigger2LV, false, 0, fCheckOverlaps);
  
  //Comp planes before and after T2
  G4Box* T2CompPlaneS = new G4Box("T2CompPlane", T2CompPlane_X/2., T2CompPlane_Y/2., T2CompPlane_Z/2.);
  G4LogicalVolume* T2CompPlaneLV = new G4LogicalVolume(T2CompPlaneS, CarbonFiberCaloMaterial, "T2CompPlane");
  fCompPlaneBeforeT2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., -trigger2Thickness/2.-T2PoronThickness-T2CompPlane_Z/2.-1.5*mm), T2CompPlaneLV, "CompPlaneBeforeT2", T2ContLV, false, 0, fCheckOverlaps);
  fCompPlaneAfterT2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., +trigger2Thickness/2.+T2PoronThickness+T2CompPlane_Z/2.+1.5*mm), T2CompPlaneLV, "CompPlaneAfterT2", T2ContLV, false, 0, fCheckOverlaps);
  
  //Support ribs between T2 bars
  G4Box* T2RibsS = new G4Box("T2Ribs", T2Ribs_X/2., T2Ribs_Y/2., T2Ribs_Z/2.);
  G4LogicalVolume* T2RibsLV = new G4LogicalVolume(T2RibsS, CarbonFiberCaloMaterial, "T2Ribs");
  fT2RibsPV_1 = new G4PVPlacement(0, G4ThreeVector(-3.*(trigger2SizeX/nofBars)/2.,0,0), T2RibsLV, "T2Ribs", triggerCont2LV, false, 0, fCheckOverlaps);
  fT2RibsPV_2 = new G4PVPlacement(0, G4ThreeVector(-(trigger2SizeX/nofBars)/2.,0,0), T2RibsLV, "T2Ribs", triggerCont2LV, false, 0, fCheckOverlaps);
  fT2RibsPV_3 = new G4PVPlacement(0, G4ThreeVector(+(trigger2SizeX/nofBars)/2.,0,0), T2RibsLV, "T2Ribs", triggerCont2LV, false, 0, fCheckOverlaps);
  fT2RibsPV_4 = new G4PVPlacement(0, G4ThreeVector(+3.*(trigger2SizeX/nofBars)/2.,0,0), T2RibsLV, "T2Ribs", triggerCont2LV, false, 0, fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  //CALORIMETER
  G4VSolid* calorimeterS = new G4Box("Calorimeter", caloSizeXY/2., caloSizeXY/2., caloThickness/2.);
  G4LogicalVolume* calorimeterLV = new G4LogicalVolume(calorimeterS, defaultMaterial, "Calorimeter");
  new G4PVPlacement(0, G4ThreeVector(0.,0.,T2_posZ+trigger2Thickness/2.+T2WrappingThickness+T2PoronThickness+T2CompPlane_Z+dist+caloThickness/2.), calorimeterLV, "Calorimeter", worldLV, false, 0, fCheckOverlaps);
  
  //Calo 1st block
  G4VSolid* calorimeterBlock1S = new G4Box("Calorimeter_Block1", caloSizeXY/2., caloSizeXY/2., caloBlock1_Thickness/2.);
  G4LogicalVolume* calorimeterBlock1LV = new G4LogicalVolume(calorimeterBlock1S, defaultMaterial, "Calorimeter_Block1");
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-caloThickness/2.+caloBlock1_Thickness/2.), calorimeterBlock1LV, "Calorimeter_Block1", calorimeterLV, false, 0, fCheckOverlaps);
  
  //Comp plane solid
  G4Box* PCompPlaneS_1 = new G4Box("PCompPlane_1", caloSizeXY/2.-cutPlane, caloSizeXY/2., PCompPlaneThickness/2.);
  G4Trd* PCompPlaneS_2 = new G4Trd("PCompPlane_2", caloSizeXY/2.-cutPlane, caloSizeXY/2., PCompPlaneThickness/2.,PCompPlaneThickness/2.,cutPlane/2.);
  
  G4RotationMatrix* rot1 = new G4RotationMatrix;
  rot1->rotateY(90.*deg);
  rot1->rotateZ(90.*deg);
  G4ThreeVector trans1;
  trans1.setX((caloSizeXY-cutPlane)/2.);
  trans1.setY(0.);
  trans1.setZ(0.);
  G4UnionSolid* PCompPlaneS_1and2 = new G4UnionSolid("PCompPlane_1and2", PCompPlaneS_1, PCompPlaneS_2, rot1, trans1);
  
  G4RotationMatrix* rot2 = new G4RotationMatrix;
  rot2->rotateY(-90.*deg);
  rot2->rotateZ(90.*deg);
  G4ThreeVector trans2;
  trans2.setX(-(caloSizeXY-cutPlane)/2.);
  trans2.setY(0.);
  trans2.setZ(0.);
  G4UnionSolid* PCompPlaneS = new G4UnionSolid("PCompPlane", PCompPlaneS_1and2, PCompPlaneS_2, rot2, trans2);
  
  G4LogicalVolume* PCompPlaneLV = new G4LogicalVolume(PCompPlaneS, CarbonFiberCaloMaterial, "PCompPlane");
  fPCompPlane1_Block1PV = new G4PVPlacement(0, G4ThreeVector(0., 0., -caloBlock1_Thickness/2.+PCompPlaneThickness/2.), PCompPlaneLV, "PCompPlane1_Block1", calorimeterBlock1LV, false, 0, fCheckOverlaps);
  fPCompPlane2_Block1PV = new G4PVPlacement(0, G4ThreeVector(0., 0., caloBlock1_Thickness/2.-PCompPlaneThickness/2.), PCompPlaneLV, "PCompPlane2_Block1", calorimeterBlock1LV, false, 0, fCheckOverlaps);
  
  //plane box (poron+wrapping+plane+wrapping)
  G4Box* PBoxS = new G4Box("PBox", caloSizeXY/2., caloSizeXY/2., (PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.);
  //NB: dx and sx for PMT position
  G4LogicalVolume* PBoxdxLV = new G4LogicalVolume(PBoxS, defaultMaterial, "PBoxdx");
  G4LogicalVolume* PBoxsxLV = new G4LogicalVolume(PBoxS, defaultMaterial, "PBoxsx");
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-caloBlock1_Thickness/2.+PCompPlaneThickness+(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.), PBoxdxLV, "PBoxdx1_Block1", calorimeterBlock1LV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-caloBlock1_Thickness/2.+PCompPlaneThickness+3.*(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.), PBoxsxLV, "PBoxsx2_Block1", calorimeterBlock1LV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-caloBlock1_Thickness/2.+PCompPlaneThickness+5.*(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.), PBoxdxLV, "PBoxdx3_Block1", calorimeterBlock1LV, false, 0, fCheckOverlaps);
  
  //poron
  G4Box* PPoronS_1 = new G4Box("PPoron_1", caloSizeXY/2.-cutPlane, caloSizeXY/2., PPoronThickness/2.);
  G4Trd* PPoronS_2 = new G4Trd("PPoron_2", caloSizeXY/2.-cutPlane, caloSizeXY/2., PPoronThickness/2., PPoronThickness/2.,cutPlane/2.);
  
  G4UnionSolid* PPoronS_1and2 = new G4UnionSolid("PPoron_1and2", PPoronS_1, PPoronS_2, rot1, trans1);
  G4UnionSolid* PPoronS = new G4UnionSolid("PPoron", PPoronS_1and2, PPoronS_2, rot2, trans2);
  
  G4LogicalVolume* PPoronLV = new G4LogicalVolume(PPoronS, PoronMaterial, "PPoron");
  fPPorondxPV = new G4PVPlacement(0, G4ThreeVector(0.,0.,-(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.+PPoronThickness/2.), PPoronLV, "PdxPoron", PBoxdxLV, false, 0, fCheckOverlaps);
  fPPoronsxPV = new G4PVPlacement(0, G4ThreeVector(0.,0.,-(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.+PPoronThickness/2.), PPoronLV, "PsxPoron", PBoxsxLV, false, 0, fCheckOverlaps);
  
  //wrapping
  G4Box* PWrappingS_1 = new G4Box("PWrapping_1", caloSizeXY/2.-cutPlane, caloSizeXY/2., PWrappingThickness/2.);
  G4Trd* PWrappingS_2 = new G4Trd("PWrapping_2", caloSizeXY/2.-cutPlane, caloSizeXY/2., PWrappingThickness/2., PWrappingThickness/2.,cutPlane/2.);
  
  G4UnionSolid* PWrappingS_1and2 = new G4UnionSolid("PWrapping_1and2", PWrappingS_1, PWrappingS_2, rot1, trans1);
  G4UnionSolid* PWrappingS = new G4UnionSolid("PWrapping", PWrappingS_1and2, PWrappingS_2, rot2, trans2);
  
  G4LogicalVolume* PWrappingLV = new G4LogicalVolume(PWrappingS, PoronMaterial, "PWrapping");
  fPWrappingdx1PV = new G4PVPlacement(0, G4ThreeVector(0.,0.,-(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.+PPoronThickness+PWrappingThickness/2.), PWrappingLV, "PdxWrapping1", PBoxdxLV, false, 0, fCheckOverlaps);
  fPWrappingdx2PV = new G4PVPlacement(0, G4ThreeVector(0.,0.,-(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.+PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness/2.), PWrappingLV, "PdxWrapping2", PBoxdxLV, false, 0, fCheckOverlaps);
  fPWrappingsx1PV = new G4PVPlacement(0, G4ThreeVector(0.,0.,-(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.+PPoronThickness+PWrappingThickness/2.), PWrappingLV, "PsxWrapping1", PBoxsxLV, false, 0, fCheckOverlaps);
  fPWrappingsx2PV = new G4PVPlacement(0, G4ThreeVector(0.,0.,-(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.+PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness/2.), PWrappingLV, "PsxWrapping2", PBoxsxLV, false, 0, fCheckOverlaps);
  
  //plane
  G4Box* PlaneS_1 = new G4Box("Plane_1", caloSizeXY/2.-cutPlane, caloSizeXY/2., planeThickness/2.);
  G4Trd* PlaneS_2 = new G4Trd("Plane_2", caloSizeXY/2.-cutPlane, caloSizeXY/2., planeThickness/2., planeThickness/2.,cutPlane/2.);
  
  G4UnionSolid* PlaneS_1and2 = new G4UnionSolid("Plane_1and2", PlaneS_1, PlaneS_2, rot1, trans1);
  G4UnionSolid* PlaneS = new G4UnionSolid("Plane", PlaneS_1and2, PlaneS_2, rot2, trans2);
  
  G4LogicalVolume* PlaneLV = new G4LogicalVolume(PlaneS, absorberMaterial, "Plane");
  fPlanedxPV = new G4PVPlacement(0, G4ThreeVector(0.,0.,-(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.+PPoronThickness+PWrappingThickness+planeThickness/2.), PlaneLV, "Planedx", PBoxdxLV, false, 0, fCheckOverlaps);
  fPlanesxPV = new G4PVPlacement(0, G4ThreeVector(0.,0.,-(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.+PPoronThickness+PWrappingThickness+planeThickness/2.), PlaneLV, "Planesx", PBoxsxLV, false, 0, fCheckOverlaps);
  
  //poron at the end of calorimeter block
  fPPoronEndBlock1PV = new G4PVPlacement(0, G4ThreeVector(0., 0., caloBlock1_Thickness/2.-PCompPlaneThickness-PPoronThickness/2.), PPoronLV, "PoronEndBlock1", calorimeterBlock1LV, false, 0, fCheckOverlaps);
  
  //Calo 2nd block
  G4VSolid* calorimeterBlock2S = new G4Box("Calorimeter_Block2", caloSizeXY/2., caloSizeXY/2., caloBlock2_Thickness/2.);
  G4LogicalVolume* calorimeterBlock2LV = new G4LogicalVolume(calorimeterBlock2S, defaultMaterial, "Calorimeter_Block2");
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-caloThickness/2.+caloBlock1_Thickness+dist_blocks+caloBlock2_Thickness/2.), calorimeterBlock2LV, "Calorimeter_Block2", calorimeterLV, false, 0, fCheckOverlaps);
  
  //Comp plane solid
  fPCompPlane1_Block2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., -caloBlock2_Thickness/2.+PCompPlaneThickness/2.), PCompPlaneLV, "PCompPlane1_Block2", calorimeterBlock2LV, false, 0, fCheckOverlaps);
  fPCompPlane2_Block2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., caloBlock2_Thickness/2.-PCompPlaneThickness/2.), PCompPlaneLV, "PCompPlane2_Block2", calorimeterBlock2LV, false, 0, fCheckOverlaps);
  
  //plane box (poron+wrapping+plane+wrapping)
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-caloBlock2_Thickness/2.+PCompPlaneThickness+(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.), PBoxdxLV, "PBoxdx1_Block2", calorimeterBlock2LV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-caloBlock2_Thickness/2.+PCompPlaneThickness+3.*(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.), PBoxsxLV, "PBoxsx2_Block2", calorimeterBlock2LV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-caloBlock2_Thickness/2.+PCompPlaneThickness+5.*(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.), PBoxdxLV, "PBoxdx3_Block2", calorimeterBlock2LV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-caloBlock2_Thickness/2.+PCompPlaneThickness+7.*(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.), PBoxsxLV, "PBoxsx4_Block2", calorimeterBlock2LV, false, 0, fCheckOverlaps);
  
  //poron at the end of calorimeter block
  fPPoronEndBlock2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., caloBlock2_Thickness/2.-PCompPlaneThickness-PPoronThickness/2.), PPoronLV, "PoronEndBlock2", calorimeterBlock2LV, false, 0, fCheckOverlaps);
  
  //Calo 3rd block
  G4VSolid* calorimeterBlock3S = new G4Box("Calorimeter_Block3", caloSizeXY/2., caloSizeXY/2., caloBlock3_Thickness/2.);
  G4LogicalVolume* calorimeterBlock3LV = new G4LogicalVolume(calorimeterBlock3S, defaultMaterial, "Calorimeter_Block3");
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-caloThickness/2.+caloBlock1_Thickness+dist_blocks+caloBlock2_Thickness+dist_blocks+caloBlock3_Thickness/2.), calorimeterBlock3LV, "Calorimeter_Block3", calorimeterLV, false, 0, fCheckOverlaps);
  
  //Comp plane solid
  fPCompPlane1_Block3PV = new G4PVPlacement(0, G4ThreeVector(0., 0., -caloBlock3_Thickness/2.+PCompPlaneThickness/2.), PCompPlaneLV, "PCompPlane1_Block3", calorimeterBlock3LV, false, 0, fCheckOverlaps);
  fPCompPlane2_Block3PV = new G4PVPlacement(0, G4ThreeVector(0., 0., caloBlock3_Thickness/2.-PCompPlaneThickness/2.), PCompPlaneLV, "PCompPlane2_Block3", calorimeterBlock3LV, false, 0, fCheckOverlaps);
  
  //plane box (poron+wrapping+plane+wrapping)
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-caloBlock3_Thickness/2.+PCompPlaneThickness+(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.), PBoxsxLV, "PBoxsx1_Block3", calorimeterBlock3LV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-caloBlock3_Thickness/2.+PCompPlaneThickness+3.*(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.), PBoxdxLV, "PBoxdx2_Block3", calorimeterBlock3LV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-caloBlock3_Thickness/2.+PCompPlaneThickness+5.*(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.), PBoxsxLV, "PBoxsx3_Block3", calorimeterBlock3LV, false, 0, fCheckOverlaps);
  new G4PVPlacement(0, G4ThreeVector(0.,0.,-caloBlock3_Thickness/2.+PCompPlaneThickness+7.*(PPoronThickness+PWrappingThickness+planeThickness+PWrappingThickness)/2.), PBoxdxLV, "PBoxdx4_Block3", calorimeterBlock3LV, false, 0, fCheckOverlaps);
  
  //poron at the end of calorimeter block
  fPPoronEndBlock3PV = new G4PVPlacement(0, G4ThreeVector(0., 0., caloBlock3_Thickness/2.-PCompPlaneThickness-PPoronThickness/2.), PPoronLV, "PoronEndBlock3", calorimeterBlock3LV, false, 0, fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  // LYSO COVER
  //LYSO cover plane between last plane of tower and lyso
  G4VSolid* LysoCoverS = new G4Box("LysoCover", LysoCover_X/2., LysoCover_Y/2., LysoCover_Z/2.);
  G4LogicalVolume* LysoCoverLV = new G4LogicalVolume(LysoCoverS, AlMaterial, "LysoCover");
  fLysoCoverPV = new G4PVPlacement(0, G4ThreeVector(0,0,T2_posZ+trigger2Thickness/2.+T2WrappingThickness+T2PoronThickness+T2CompPlane_Z+dist+caloThickness+dist_lastplane_LysoCover+LysoCover_Z/2.),LysoCoverLV,"LysoCover",worldLV,false, 0, fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  //CRYSTAL L1
  // container 1st plane
  G4VSolid* CrystalCont1S = new G4Box("CrystalCont1", (crystalBarSizeY+2.*pmtHeight)/2., (nofCrystals*crystalBarSizeX + 2.*crystalGap + 2.*CWrappingThickness)/2., (2.*CWrappingThickness + 2.*CScotchTape_Thickness + crystalBarThickness)/2.);
  G4LogicalVolume* CrystalCont1LV = new G4LogicalVolume(CrystalCont1S, defaultMaterial, "CrystalCont1");
    G4double L1_posZ = T2_posZ+trigger2Thickness/2.+T2WrappingThickness+T2PoronThickness+T2CompPlane_Z+dist+caloThickness+dist_lastplane_LysoCover+LysoCover_Z+(2.*CWrappingThickness + 2.*CScotchTape_Thickness + crystalBarThickness)/2.;
  new G4PVPlacement(0, G4ThreeVector(0,0, L1_posZ), CrystalCont1LV, "CrystalCont1", worldLV, false, 0, fCheckOverlaps);
  
  //bar container 1st plane
  G4VSolid* BarCont1S = new G4Box("BarCont1", (crystalBarSizeY+2.*pmtHeight)/2., (2.*CWrappingThickness + crystalBarSizeX)/2., (2.*CWrappingThickness + 2.*CScotchTape_Thickness + crystalBarThickness)/2.);
  G4LogicalVolume* BarCont1LV = new G4LogicalVolume(BarCont1S, defaultMaterial, "BarCont1");
  fBarCont1_plane1PV = new G4PVPlacement(0, G4ThreeVector(0.,(nofCrystals*crystalBarSizeX + 2.*crystalGap + 2.*CWrappingThickness)/2.-CWrappingThickness-crystalBarSizeX/2.,0.),BarCont1LV, "BarCont1_1", CrystalCont1LV, false, 0, fCheckOverlaps);
  fBarCont2_plane1PV = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.),BarCont1LV, "BarCont2_1", CrystalCont1LV, false, 0, fCheckOverlaps);
  fBarCont3_plane1PV = new G4PVPlacement(0, G4ThreeVector(0.,-(nofCrystals*crystalBarSizeX + 2.*crystalGap + 2.*CWrappingThickness)/2.+CWrappingThickness+crystalBarSizeX/2.,0.),BarCont1LV, "BarCont3_1", CrystalCont1LV, false, 0, fCheckOverlaps);
  
  //bars 1st plane
  G4VSolid* Crystal1S = new G4Box("Crystal1", crystalBarSizeY/2., crystalBarSizeX/2., crystalBarThickness/2.);
  G4LogicalVolume* Crystal1LV = new G4LogicalVolume(Crystal1S, crystalMaterial, "Crystal1");
  fCrystal1PV = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.),Crystal1LV, "Crystal1", BarCont1LV, false, 0,fCheckOverlaps);
  
  //wrapping 1st plane - lateral
  G4Box* CWrappingLat1S = new G4Box("CWrappinglat1", crystalBarSizeY/2., CWrappingThickness/2., crystalBarThickness/2.);
  G4LogicalVolume* CWrappingLat1LV = new G4LogicalVolume(CWrappingLat1S, PoronMaterial, "CWrappinglat1");
  fCWrappingLat1_plane1PV = new G4PVPlacement(0, G4ThreeVector(0.,CWrappingThickness/2.+crystalBarSizeX/2.,0.), CWrappingLat1LV, "CWrappinglat1", BarCont1LV, false, 0, fCheckOverlaps);
  fCWrappingLat2_plane1PV = new G4PVPlacement(0, G4ThreeVector(0.,-CWrappingThickness/2.-crystalBarSizeX/2.,0.), CWrappingLat1LV, "CWrappinglat2", BarCont1LV, false, 0, fCheckOverlaps);
  
  //wrapping 1st plane - frontal
  G4Box* CWrapping1S = new G4Box("CWrapping1", crystalBarSizeY/2., crystalBarSizeX/2., CWrappingThickness/2.);
  G4LogicalVolume* CWrapping1LV = new G4LogicalVolume(CWrapping1S, PoronMaterial, "CWrapping1");
  fCWrapping1_plane1PV = new G4PVPlacement(0, G4ThreeVector(0.,0.,-crystalBarThickness/2.-CWrappingThickness/2.), CWrapping1LV, "CWrapping1", BarCont1LV, false, 0, fCheckOverlaps);
  fCWrapping2_plane1PV = new G4PVPlacement(0, G4ThreeVector(0.,0.,crystalBarThickness/2.+CWrappingThickness/2.), CWrapping1LV, "CWrapping2", BarCont1LV, false, 0, fCheckOverlaps);
  
  //scotch tape 1st plane - lateral
  G4Box* CScotchTapeLat1S = new G4Box("CScotchTapelat1", crystalBarSizeY/2., CScotchTape_Thickness/2., crystalBarThickness/2.);
  G4LogicalVolume* CScotchTapeLat1LV = new G4LogicalVolume(CScotchTapeLat1S, SiliconeMaterial, "CScotchTapelat1");
  fCScotchTapeLat1_plane1PV = new G4PVPlacement(0, G4ThreeVector(0.,crystalBarSizeX/2.+CWrappingThickness+CScotchTape_Thickness/2.,0.), CScotchTapeLat1LV, "CScotchTapelat1_1", CrystalCont1LV, false, 0, fCheckOverlaps);
  fCScotchTapeLat2_plane1PV = new G4PVPlacement(0, G4ThreeVector(0.,-crystalBarSizeX/2.-CWrappingThickness-CScotchTape_Thickness/2.,0.), CScotchTapeLat1LV, "CScotchTapelat2_1", CrystalCont1LV, false, 0, fCheckOverlaps);
  
  //scotch tape 1st plane - frontal
  G4Box* CScotchTape1S = new G4Box("CScotchTape1", crystalBarSizeY/2., CScotchTape_SizeY/2., CScotchTape_Thickness/2.);
  G4LogicalVolume* CScotchTape1LV = new G4LogicalVolume(CScotchTape1S, SiliconeMaterial, "CScotchTape1");
  fCScotchTape1_plane1PV = new G4PVPlacement(0, G4ThreeVector(0.,(CScotchTape_dist+CScotchTape_SizeY)/2.,-crystalBarThickness/2.-CWrappingThickness-CScotchTape_Thickness/2.), CScotchTape1LV, "CScotchTape1", BarCont1LV, false, 0, fCheckOverlaps);
  fCScotchTape2_plane1PV = new G4PVPlacement(0, G4ThreeVector(0.,-(CScotchTape_dist+CScotchTape_SizeY)/2.,-crystalBarThickness/2.-CWrappingThickness-CScotchTape_Thickness/2.), CScotchTape1LV, "CScotchTape2", BarCont1LV, false, 0, fCheckOverlaps);
  fCScotchTape3_plane1PV = new G4PVPlacement(0, G4ThreeVector(0.,(CScotchTape_dist+CScotchTape_SizeY)/2.,crystalBarThickness/2.+CWrappingThickness+CScotchTape_Thickness/2.), CScotchTape1LV, "CScotchTape3", BarCont1LV, false, 0, fCheckOverlaps);
  fCScotchTape4_plane1PV = new G4PVPlacement(0, G4ThreeVector(0.,-(CScotchTape_dist+CScotchTape_SizeY)/2.,crystalBarThickness/2.+CWrappingThickness+CScotchTape_Thickness/2.), CScotchTape1LV, "CScotchTape4", BarCont1LV, false, 0, fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  //CRYSTAL L2
  // container 2nd plane
  G4VSolid* CrystalCont2S = new G4Box("CrystalCont2", (nofCrystals*crystalBarSizeX + 2.*crystalGap + 2.*CWrappingThickness)/2., (crystalBarSizeY+2.*pmtHeight)/2., (2.*CWrappingThickness + 2.*CScotchTape_Thickness + crystalBarThickness)/2.);
  G4LogicalVolume* CrystalCont2LV = new G4LogicalVolume(CrystalCont2S, defaultMaterial, "CrystalCont2");
  G4double L2_posZ = L1_posZ + crystalBarThickness/2. + CWrappingThickness + CScotchTape_Thickness + crystalGapZ + CScotchTape_Thickness + CWrappingThickness + crystalBarThickness/2.;
  new G4PVPlacement(0, G4ThreeVector(0,0, L2_posZ), CrystalCont2LV, "CrystalCont2", worldLV, false, 0, fCheckOverlaps);
  
  //bar container 2nd plane
  G4VSolid* BarCont2S = new G4Box("BarCont2", (2.*CWrappingThickness + crystalBarSizeX)/2., (crystalBarSizeY+2.*pmtHeight)/2., (2.*CWrappingThickness + 2.*CScotchTape_Thickness + crystalBarThickness)/2.);
  G4LogicalVolume* BarCont2LV = new G4LogicalVolume(BarCont2S, defaultMaterial, "BarCont2");
  fBarCont1_plane2PV = new G4PVPlacement(0, G4ThreeVector(-(nofCrystals*crystalBarSizeX + 2.*crystalGap + 2.*CWrappingThickness)/2.+CWrappingThickness+crystalBarSizeX/2.,0.,0.),BarCont2LV, "BarCont1_2", CrystalCont2LV, false, 0, fCheckOverlaps);
  fBarCont2_plane2PV = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.),BarCont2LV, "BarCont2_2", CrystalCont2LV, false, 0, fCheckOverlaps);
  fBarCont3_plane2PV = new G4PVPlacement(0, G4ThreeVector(+(nofCrystals*crystalBarSizeX + 2.*crystalGap + 2.*CWrappingThickness)/2.-CWrappingThickness-crystalBarSizeX/2.,0.,0.),BarCont2LV, "BarCont3_2", CrystalCont2LV, false, 0, fCheckOverlaps);
  
  //bars 2nd plane
  G4VSolid* Crystal2S = new G4Box("Crystal2", crystalBarSizeX/2., crystalBarSizeY/2., crystalBarThickness/2.);
  G4LogicalVolume* Crystal2LV = new G4LogicalVolume(Crystal2S, crystalMaterial, "Crystal2");
  fCrystal2PV = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.),Crystal2LV, "Crystal2", BarCont2LV, false, 0, fCheckOverlaps);
  
  //wrapping 2nd plane - lateral
  G4Box* CWrappingLat2S = new G4Box("CWrappinglat2", CWrappingThickness/2., crystalBarSizeY/2., crystalBarThickness/2.);
  G4LogicalVolume* CWrappingLat2LV = new G4LogicalVolume(CWrappingLat2S, PoronMaterial, "CWrappinglat2");
  fCWrappingLat1_plane2PV = new G4PVPlacement(0, G4ThreeVector(-CWrappingThickness/2.-crystalBarSizeX/2.,0.,0.), CWrappingLat2LV, "CWrappinglat1", BarCont2LV, false, 0, fCheckOverlaps);
  fCWrappingLat2_plane2PV = new G4PVPlacement(0, G4ThreeVector(CWrappingThickness/2.+crystalBarSizeX/2.,0.,0.), CWrappingLat2LV, "CWrappinglat2", BarCont2LV, false, 0, fCheckOverlaps);
  
  //wrapping 2nd plane - frontal
  G4Box* CWrapping2S = new G4Box("CWrapping2", crystalBarSizeX/2., crystalBarSizeY/2., CWrappingThickness/2.);
  G4LogicalVolume* CWrapping2LV = new G4LogicalVolume(CWrapping2S, PoronMaterial, "CWrapping2");
  fCWrapping1_plane2PV = new G4PVPlacement(0, G4ThreeVector(0.,0.,-crystalBarThickness/2.-CWrappingThickness/2.), CWrapping2LV, "CWrapping1", BarCont2LV, false, 0, fCheckOverlaps);
  fCWrapping2_plane2PV = new G4PVPlacement(0, G4ThreeVector(0.,0.,crystalBarThickness/2.+CWrappingThickness/2.), CWrapping2LV, "CWrapping2", BarCont2LV, false, 0, fCheckOverlaps);
  
  //scotch tape 2nd plane - lateral
  G4Box* CScotchTapeLat2S = new G4Box("CScotchTapelat2", CScotchTape_Thickness/2., crystalBarSizeY/2., crystalBarThickness/2.);
  G4LogicalVolume* CScotchTapeLat2LV = new G4LogicalVolume(CScotchTapeLat2S, SiliconeMaterial, "CScotchTapelat2");
  fCScotchTapeLat1_plane2PV = new G4PVPlacement(0, G4ThreeVector(-crystalBarSizeX/2.-CWrappingThickness-CScotchTape_Thickness/2.,0.,0.), CScotchTapeLat2LV, "CScotchTapelat1_2", CrystalCont2LV, false, 0, fCheckOverlaps);
  fCScotchTapeLat2_plane2PV = new G4PVPlacement(0, G4ThreeVector(crystalBarSizeX/2.+CWrappingThickness+CScotchTape_Thickness/2.,0.,0.), CScotchTapeLat2LV, "CScotchTapelat2_2", CrystalCont2LV, false, 0, fCheckOverlaps);
  
  //scotch tape 2nd plane - frontal
  G4Box* CScotchTape2S = new G4Box("CScotchTape2", CScotchTape_SizeY/2., crystalBarSizeY/2., CScotchTape_Thickness/2.);
  G4LogicalVolume* CScotchTape2LV = new G4LogicalVolume(CScotchTape2S, SiliconeMaterial, "CScotchTape2");
  fCScotchTape1_plane2PV = new G4PVPlacement(0, G4ThreeVector(-(CScotchTape_dist+CScotchTape_SizeY)/2.,0.,-crystalBarThickness/2.-CWrappingThickness-CScotchTape_Thickness/2.), CScotchTape2LV, "CScotchTape1", BarCont2LV, false, 0, fCheckOverlaps);
  fCScotchTape2_plane2PV = new G4PVPlacement(0, G4ThreeVector((CScotchTape_dist+CScotchTape_SizeY)/2.,0.,-crystalBarThickness/2.-CWrappingThickness-CScotchTape_Thickness/2.), CScotchTape2LV, "CScotchTape2", BarCont2LV, false, 0, fCheckOverlaps);
  fCScotchTape3_plane2PV = new G4PVPlacement(0, G4ThreeVector(-(CScotchTape_dist+CScotchTape_SizeY)/2.,0.,crystalBarThickness/2.+CWrappingThickness+CScotchTape_Thickness/2.), CScotchTape2LV, "CScotchTape3", BarCont2LV, false, 0, fCheckOverlaps);
  fCScotchTape4_plane2PV = new G4PVPlacement(0, G4ThreeVector((CScotchTape_dist+CScotchTape_SizeY)/2.,0.,crystalBarThickness/2.+CWrappingThickness+CScotchTape_Thickness/2.), CScotchTape2LV, "CScotchTape4", BarCont2LV, false, 0, fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  // VETO
  // Veto bottom  
  G4VSolid* VetoBotContS = new G4Box("VetoBotCont", (vetoSizeXY+cutPlaneVeto)/2., (vetoSizeXY+cutPlaneVeto)/2., (RearVetoBot_Z + RearCover_dist + VetoBotCover_Z + VetoBotPoron_Z + VetoBotWrappingThickness + VetoBot_Z)/2.);
  G4LogicalVolume* VetoBotContLV = new G4LogicalVolume(VetoBotContS, defaultMaterial, "VetoBotCont");
  G4double VB_posZ = L2_posZ+crystalBarThickness/2. + CWrappingThickness + CScotchTape_Thickness + (RearVetoBot_Z + RearCover_dist + VetoBotCover_Z + VetoBotPoron_Z + VetoBotWrappingThickness + VetoBot_Z)/2.;
  fVetoBotContPV = new G4PVPlacement(0, G4ThreeVector(0.,0.,VB_posZ), VetoBotContLV, "VetoBotCont", worldLV, false, 0, fCheckOverlaps);
  
  G4VSolid* RearVetoBotS = new G4Box("RearVetoBot", (vetoSizeXY+cutPlaneVeto)/2., (vetoSizeXY+cutPlaneVeto)/2., RearVetoBot_Z/2.);
  G4LogicalVolume *RearVetoBotLV = new G4LogicalVolume(RearVetoBotS, AlMaterial, "RearVetoBot");
  fRearVetoBotPV = new G4PVPlacement(0, G4ThreeVector(0., 0., -(RearVetoBot_Z + RearCover_dist + VetoBotCover_Z + VetoBotPoron_Z + VetoBotWrappingThickness + VetoBot_Z)/2. + RearVetoBot_Z/2.), RearVetoBotLV, "RearVetoBot", VetoBotContLV, false, 0, fCheckOverlaps);
  
  G4VSolid* VetoBotCoverS = new G4Box("VetoBotCover", (vetoSizeXY+cutPlaneVeto)/2., (vetoSizeXY+cutPlaneVeto)/2., VetoBotCover_Z/2.);
  G4LogicalVolume *VetoBotCoverLV = new G4LogicalVolume(VetoBotCoverS, CarbonFiberCaloMaterial, "VetoBotCover");
  fVetoBotCoverPV = new G4PVPlacement(0, G4ThreeVector(0., 0., -(RearVetoBot_Z + RearCover_dist + VetoBotCover_Z + VetoBotPoron_Z + VetoBotWrappingThickness + VetoBot_Z)/2. + RearVetoBot_Z + RearCover_dist + VetoBotCover_Z/2.), VetoBotCoverLV, "VetoBotCover", VetoBotContLV, false, 0, fCheckOverlaps);
  
  G4VSolid* VetoBotPoronS = new G4Box("VetoBotPoron", (vetoSizeXY+cutPlaneVeto)/2., (vetoSizeXY+cutPlaneVeto)/2., VetoBotPoron_Z/2.);
  G4LogicalVolume *VetoBotPoronLV = new G4LogicalVolume(VetoBotPoronS, PoronMaterial, "VetoBotPoron");
  fVetoBotPoronPV = new G4PVPlacement(0, G4ThreeVector(0., 0., -(RearVetoBot_Z + RearCover_dist + VetoBotCover_Z + VetoBotPoron_Z + VetoBotWrappingThickness + VetoBot_Z)/2. + RearVetoBot_Z + RearCover_dist + VetoBotCover_Z + VetoBotPoron_Z/2.), VetoBotPoronLV, "VetoBotPoron", VetoBotContLV, false, 0, fCheckOverlaps);
  
  G4VSolid* VetoBotWrappingS = new G4Box("VetoBotWrapping", (vetoSizeXY+cutPlaneVeto)/2., (vetoSizeXY+cutPlaneVeto)/2., VetoBotWrappingThickness/2.);
  G4LogicalVolume *VetoBotWrappingLV = new G4LogicalVolume(VetoBotWrappingS, PoronMaterial, "VetoBotWrapping");
  fVetoBotWrappingPV = new G4PVPlacement(0, G4ThreeVector(0., 0., -(RearVetoBot_Z + RearCover_dist + VetoBotCover_Z + VetoBotPoron_Z + VetoBotWrappingThickness + VetoBot_Z)/2. + RearVetoBot_Z + RearCover_dist + VetoBotCover_Z + VetoBotPoron_Z + VetoBotWrappingThickness/2.), VetoBotWrappingLV, "VetoBotWrapping", VetoBotContLV, false, 0, fCheckOverlaps);
  
  G4Box* vetobS_1 = new G4Box("Vetob_1", vetoSizeXY/2.-cutPlaneVeto, vetoSizeXY/2., VetoBot_Z/2.);
  G4Trd* vetobS_2 = new G4Trd("Vetob_2", vetoSizeXY/2.-cutPlaneVeto, vetoSizeXY/2., VetoBot_Z/2.,VetoBot_Z/2.,cutPlaneVeto/2.);
  
  G4RotationMatrix* rot1Veto = new G4RotationMatrix;
  rot1Veto->rotateY(90.*deg);
  rot1Veto->rotateZ(90.*deg);
  G4ThreeVector trans1Veto;
  trans1Veto.setX((vetoSizeXY-cutPlaneVeto)/2.);
  trans1Veto.setY(0.);
  trans1Veto.setZ(0.);
  
  G4UnionSolid* vetobS_1and2 = new G4UnionSolid("Vetob_1and2", vetobS_1, vetobS_2, rot1Veto, trans1Veto);
  
  G4RotationMatrix* rot2Veto = new G4RotationMatrix;
  rot2Veto->rotateY(-90.*deg);
  rot2Veto->rotateZ(90.*deg);
  G4ThreeVector trans2Veto;
  trans2Veto.setX(-(vetoSizeXY-cutPlaneVeto)/2.);
  trans2Veto.setY(0.);
  trans2Veto.setZ(0.);
  
  G4UnionSolid* vetobS = new G4UnionSolid("Vetob", vetobS_1and2, vetobS_2, rot2Veto, trans2Veto);
  
  G4LogicalVolume* vetobLV = new G4LogicalVolume(vetobS, absorberMaterial, "Vetob");
  
  fVetobPV = new G4PVPlacement(0, G4ThreeVector(0., 0., -(RearVetoBot_Z + RearCover_dist + VetoBotCover_Z + VetoBotPoron_Z + VetoBotWrappingThickness + VetoBot_Z)/2. + RearVetoBot_Z + RearCover_dist + VetoBotCover_Z + VetoBotPoron_Z + VetoBotWrappingThickness + VetoBot_Z/2.), vetobLV, "Vetob", VetoBotContLV, false, 0, fCheckOverlaps);
  
  // Veto lateral
  G4double V_posZ = T1_posZ + FrameT1_Z/2. + VetoLatContainer_Y/2.;
  
  G4VSolid* VetoLatContainerS = new G4Box("VetoLatContainer",VetoLatContainer_X/2., (2.*VetoLatPoron_Z + 2.*VetoLatWrapping_Z + VetoLat_Z + VetoLatCover_Z)/2., VetoLatContainer_Y/2.);
  
  G4LogicalVolume *VetoLatContainerLV = new G4LogicalVolume(VetoLatContainerS, defaultMaterial, "VetoLatContainer");
  
  G4RotationMatrix* Veto1rm = new G4RotationMatrix();
  Veto1rm->set(0.*deg, 0.*deg, 0.*deg);
  fVetoLatContainer1PV = new G4PVPlacement(Veto1rm, G4ThreeVector(+VetoLatShift_Y/2., trigger2SizeX/2.+VetoLatShift_X+(2.*VetoLatPoron_Z + 2. *VetoLatWrapping_Z + VetoLat_Z + VetoLatCover_Z)/2., V_posZ), VetoLatContainerLV, "VetoLatContainer1", worldLV, false, 0, fCheckOverlaps);
  G4RotationMatrix* Veto2rm = new G4RotationMatrix();
  Veto2rm->set(90.*deg, 0.*deg, 0.*deg);
  fVetoLatContainer2PV = new G4PVPlacement(Veto2rm, G4ThreeVector(-trigger2SizeY/2.-VetoLatShift_Y-(2.*VetoLatPoron_Z + 2.*VetoLatWrapping_Z + VetoLat_Z + VetoLatCover_Z)/2., +VetoLatShift_X, V_posZ), VetoLatContainerLV, "VetoLatContainer2", worldLV, false, 0, fCheckOverlaps);
  G4RotationMatrix* Veto3rm = new G4RotationMatrix();
  Veto3rm->set(180.*deg, 0.*deg, 0.*deg);
  fVetoLatContainer3PV = new G4PVPlacement(Veto3rm, G4ThreeVector(-VetoLatShift_Y/2., -trigger2SizeX/2.-VetoLatShift_X-(2.*VetoLatPoron_Z + 2.*VetoLatWrapping_Z + VetoLat_Z + VetoLatCover_Z)/2., V_posZ), VetoLatContainerLV, "VetoLatContainer3", worldLV, false, 0, fCheckOverlaps);
  G4RotationMatrix* Veto4rm = new G4RotationMatrix();
  Veto4rm->set(270.*deg, 0.*deg, 0.*deg);
  fVetoLatContainer4PV = new G4PVPlacement(Veto4rm, G4ThreeVector(trigger2SizeY/2.+VetoLatShift_Y+(2.*VetoLatPoron_Z + 2.*VetoLatWrapping_Z + VetoLat_Z + VetoLatCover_Z)/2., -VetoLatShift_X, V_posZ), VetoLatContainerLV, "VetoLatContainer4", worldLV, false, 0, fCheckOverlaps);
  G4VSolid* VetoLatCoverS = new G4Box("VetoLatCover", VetoLatContainer_X/2., VetoLatCover_Z/2., VetoLatContainer_Y/2.);
  G4LogicalVolume *VetoLatCoverLV = new G4LogicalVolume(VetoLatCoverS, CarbonFiberCaloMaterial, "VetoLatCover");
  fVetoLatCoverPV = new G4PVPlacement(0, G4ThreeVector(0., -(2.*VetoLatPoron_Z + 2.*VetoLatWrapping_Z + VetoLat_Z + VetoLatCover_Z)/2.+VetoLatCover_Z/2., 0.), VetoLatCoverLV, "VetoLatCover", VetoLatContainerLV, false, 0, fCheckOverlaps);
  
  G4VSolid* VetoLatPoronS_1 = new G4Box("VetoLatPoron_1", VetoLat_X/2., VetoLatPoron_Z/2., VetoLat_Y/2.);
  G4SubtractionSolid *VetoLatPoronS_2 = new G4SubtractionSolid("VetoLatPoron_2", VetoLatPoronS_1, new G4Box("VetoLatPoron_sub1", vetoHoleX/2., (VetoLatPoron_Z+0.01)*mm/2., (vetoHoleY +0.01)*mm/2.), 0, G4ThreeVector(VetoLat_X/2.-vetoHoleX/2.,0.,-VetoLat_Y/2.+vetoHoleY/2.));
  G4SubtractionSolid *VetoLatPoronS = new G4SubtractionSolid("VetoLatPoron", VetoLatPoronS_2, new G4Box("VetoLatPoron_sub2", vetoHoleX/2., (VetoLatPoron_Z+0.01)*mm/2., (vetoHoleY+0.01)*mm/2.), 0, G4ThreeVector(-VetoLat_X/2.+vetoHoleX/2.,0.,+VetoLat_Y/2.-vetoHoleY/2.));
  G4LogicalVolume *VetoLatPoronLV = new G4LogicalVolume(VetoLatPoronS, PoronMaterial, "VetoLatPoron");
  fVetoLatPoronIntPV = new G4PVPlacement(0, G4ThreeVector(0., -(2.*VetoLatPoron_Z + 2.*VetoLatWrapping_Z + VetoLat_Z + VetoLatCover_Z)/2.+VetoLatCover_Z+VetoLatPoron_Z/2., 0.), VetoLatPoronLV, "VetoLatPoronInt", VetoLatContainerLV, false, 0, fCheckOverlaps);
  fVetoLatPoronExtPV = new G4PVPlacement(0, G4ThreeVector(0., -(2.*VetoLatPoron_Z + 2.*VetoLatWrapping_Z + VetoLat_Z + VetoLatCover_Z)/2.+VetoLatCover_Z+VetoLatPoron_Z+VetoLatWrapping_Z + VetoLat_Z+VetoLatWrapping_Z+VetoLatPoron_Z/2., 0.), VetoLatPoronLV, "VetoLatPoronExt", VetoLatContainerLV, false, 0, fCheckOverlaps);
  
  G4VSolid* VetoLatWrappingS_1 = new G4Box("VetoLatWrapping_1", VetoLat_X/2., VetoLatWrapping_Z/2., VetoLat_Y/2.);
  G4SubtractionSolid *VetoLatWrappingS_2 = new G4SubtractionSolid("VetoLatWrapping_2", VetoLatWrappingS_1, new G4Box("VetoLatWrapping_sub1", vetoHoleX/2., (VetoLatWrapping_Z+0.01)*mm /2., (vetoHoleY+0.01)*mm/2.), 0, G4ThreeVector(VetoLat_X/2.-vetoHoleX/2.,0.,-VetoLat_Y/2.+vetoHoleY/2.));
  G4SubtractionSolid *VetoLatWrappingS = new G4SubtractionSolid("VetoLatWrapping", VetoLatWrappingS_2, new G4Box("VetoLatWrapping_sub2", vetoHoleX/2., (VetoLatWrapping_Z+0.01)*mm/2.,(vetoHoleY+0.01)*mm/2.), 0, G4ThreeVector(-VetoLat_X/2.+vetoHoleX/2.,0.,+VetoLat_Y/2.-vetoHoleY/2.));
  G4LogicalVolume *VetoLatWrappingLV = new G4LogicalVolume(VetoLatWrappingS, PoronMaterial, "VetoLatWrapping");
  fVetoLatWrappingIntPV = new G4PVPlacement(0, G4ThreeVector(0., -(2.*VetoLatPoron_Z + 2.*VetoLatWrapping_Z + VetoLat_Z + VetoLatCover_Z)/2.+VetoLatCover_Z+VetoLatPoron_Z+VetoLatWrapping_Z/2., 0.), VetoLatWrappingLV, "VetoLatWrappingInt", VetoLatContainerLV, false, 0, fCheckOverlaps);
  fVetoLatWrappingExtPV = new G4PVPlacement(0, G4ThreeVector(0., -(2.*VetoLatPoron_Z + 2.*VetoLatWrapping_Z + VetoLat_Z + VetoLatCover_Z)/2.+VetoLatCover_Z+VetoLatPoron_Z+VetoLatWrapping_Z + VetoLat_Z+VetoLatWrapping_Z/2., 0.), VetoLatWrappingLV, "VetoLatWrappingExt", VetoLatContainerLV, false, 0, fCheckOverlaps);
  
  G4VSolid* VetoLatS_1 = new G4Box("VetoLat_1", VetoLat_X/2., VetoLat_Z/2., VetoLat_Y/2.);
  G4SubtractionSolid *VetoLatS_2 = new G4SubtractionSolid("VetoLat_2", VetoLatS_1, new G4Box("VetoLat_sub1", vetoHoleX/2., (VetoLat_Z+0.01)*mm/2., (vetoHoleY+0.01)*mm/2.), 0, G4ThreeVector(+VetoLat_X/2.-vetoHoleX/2.,0.,-VetoLat_Y/2.+vetoHoleY/2.));
  G4SubtractionSolid *VetoLatS = new G4SubtractionSolid("VetoLat", VetoLatS_2, new G4Box("VetoLat_sub2", vetoHoleX/2., (VetoLat_Z+0.01)*mm/2., (vetoHoleY+0.01)*mm/2.), 0, G4ThreeVector(-VetoLat_X/2.+vetoHoleX/2.,0.,+VetoLat_Y/2.-vetoHoleY/2.));
  G4LogicalVolume *VetoLatLV = new G4LogicalVolume(VetoLatS, absorberMaterial, "VetoLat");
  fVetoLatPV = new G4PVPlacement(0, G4ThreeVector(0., -(2.*VetoLatPoron_Z + 2.*VetoLatWrapping_Z + VetoLat_Z + VetoLatCover_Z)/2.+VetoLatCover_Z+VetoLatPoron_Z+VetoLatWrapping_Z+VetoLat_Z/2., 0.), VetoLatLV, "VetoLat", VetoLatContainerLV, false, 0, fCheckOverlaps);
  
  //****************************************************************************************
  
  //****************************************************************************************
  // PMT
  G4VSolid* pmtS = new G4Tubs("Pmt", pmtInnerRadius, pmtOuterRadius, pmtHeight/2., pmtStartAngle, pmtSpanAngle);
  G4LogicalVolume* pmtLV = new G4LogicalVolume(pmtS, pmtMaterial, "Pmt");
  
  G4RotationMatrix* T1rm = new G4RotationMatrix();
  T1rm->set(90.*deg, 90.*deg, 0.*deg);
  new G4PVPlacement(T1rm, G4ThreeVector(trigger1SizeX/2.+pmtHeight/2.+LG_height, 0., 0.), pmtLV,"PmtT1_1", trigger1LV, false, 0, fCheckOverlaps);
  new G4PVPlacement(T1rm, G4ThreeVector(-trigger1SizeX/2.-pmtHeight/2.-LG_height,0., 0.), pmtLV,"PmtT1_2", trigger1LV, false, 0, fCheckOverlaps);
  
  G4RotationMatrix* T2rm = new G4RotationMatrix();
  T2rm->set(0.*deg, 90.*deg, 0.*deg);
  new G4PVPlacement(T2rm, G4ThreeVector(0., -trigger2SizeY/2.-pmtHeight/2.,0.), pmtLV,"PmtT2_1", trigger2LV, false, 0, fCheckOverlaps);
  new G4PVPlacement(T2rm, G4ThreeVector(0., +trigger2SizeY/2.+pmtHeight/2.,0.), pmtLV,"PmtT2_2", trigger2LV, false, 0, fCheckOverlaps);
  
  G4RotationMatrix* P1rm = new G4RotationMatrix();
  P1rm->set(-45.*deg, 90.*deg, 0.*deg);
  new G4PVPlacement(P1rm, G4ThreeVector(+caloSizeXY/2.-cutPlane/2.+pmtHeight/(2.*sqrt(2.)),+caloSizeXY/2.-cutPlane/2.+pmtHeight/(2.*sqrt(2.)),0.), pmtLV,"PmtPdx_1", PBoxdxLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(P1rm, G4ThreeVector(-caloSizeXY/2.+cutPlane/2.-pmtHeight/(2.*sqrt(2.)),-caloSizeXY/2.+cutPlane/2.-pmtHeight/(2.*sqrt(2.)),0.), pmtLV,"PmtPdx_2", PBoxdxLV, false, 0, fCheckOverlaps);
  
  G4RotationMatrix* P2rm = new G4RotationMatrix();
  P2rm->set(+45.*deg, 90.*deg, 0.*deg);
  new G4PVPlacement(P2rm, G4ThreeVector(-caloSizeXY/2.+cutPlane/2.-pmtHeight/(2.*sqrt(2.)),+caloSizeXY/2.-cutPlane/2.+pmtHeight/(2.*sqrt(2.)),0.), pmtLV,"PmtPsx_1", PBoxsxLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(P2rm, G4ThreeVector(+caloSizeXY/2.-cutPlane/2.+pmtHeight/(2.*sqrt(2.)),-caloSizeXY/2.+cutPlane/2.-pmtHeight/(2.*sqrt(2.)),0.), pmtLV,"PmtPsx_2", PBoxsxLV, false, 0, fCheckOverlaps);
  
  G4RotationMatrix* L1rm = new G4RotationMatrix();
  L1rm->set(90.*deg, 90.*deg, 0.*deg);
  new G4PVPlacement(L1rm, G4ThreeVector(crystalBarSizeY/2.+pmtHeight/2.,0.,0.), pmtLV,"PmtL1_1", BarCont1LV, false, fCheckOverlaps);
  new G4PVPlacement(L1rm, G4ThreeVector(-crystalBarSizeY/2.-pmtHeight/2.,0.,0.), pmtLV,"PmtL1_2", BarCont1LV, false, fCheckOverlaps);  
  
  G4RotationMatrix* L2rm = new G4RotationMatrix();
  L2rm->set(0.*deg, 90.*deg, 0.*deg);
  new G4PVPlacement(L2rm, G4ThreeVector(0.,crystalBarSizeY/2.+pmtHeight/2.,0.), pmtLV,"PmtL2_1", BarCont2LV, false, fCheckOverlaps);
  new G4PVPlacement(L2rm, G4ThreeVector(0.,-crystalBarSizeY/2.-pmtHeight/2.,0.), pmtLV,"PmtL2_2", BarCont2LV, false, fCheckOverlaps);
  
  G4RotationMatrix* VLatrm = new G4RotationMatrix();
  VLatrm->set(90.*deg, 90.*deg, 0.*deg);
  new G4PVPlacement(VLatrm, G4ThreeVector(VetoLat_X/2.-vetoHoleX+pmtHeight/2.,0.,-VetoLat_Y/2.+vetoHoleY/2.), pmtLV,"PmtVLat_1", VetoLatContainerLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(VLatrm, G4ThreeVector(-VetoLat_X/2.+vetoHoleX-pmtHeight/2.,0.,VetoLat_Y/2.-vetoHoleY/2.), pmtLV,"PmtVLat_2", VetoLatContainerLV, false, 0, fCheckOverlaps);
  
  G4RotationMatrix* VBotrm = new G4RotationMatrix();
  VBotrm->set(45.*deg, 90.*deg, 0.*deg);
  new G4PVPlacement(VBotrm, G4ThreeVector(-vetoSizeXY/2.+cutPlaneVeto/2.-pmtHeight/(2.*sqrt(2.)),vetoSizeXY/2.-cutPlaneVeto/2.+pmtHeight/(2.*sqrt(2.)),-(RearVetoBot_Z + RearCover_dist + VetoBotCover_Z + VetoBotPoron_Z + VetoBotWrappingThickness + VetoBot_Z)/2. + RearVetoBot_Z + RearCover_dist + VetoBotCover_Z + VetoBotPoron_Z + VetoBotWrappingThickness + VetoBot_Z/2.), pmtLV,"PmtVBot_1", VetoBotContLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(VBotrm, G4ThreeVector(+vetoSizeXY/2.-cutPlaneVeto/2.+pmtHeight/(2.*sqrt(2.)),-vetoSizeXY/2.+cutPlaneVeto/2.-pmtHeight/(2.*sqrt(2.)),-(RearVetoBot_Z + RearCover_dist + VetoBotCover_Z + VetoBotPoron_Z + VetoBotWrappingThickness + VetoBot_Z)/2. + RearVetoBot_Z + RearCover_dist + VetoBotCover_Z + VetoBotPoron_Z + VetoBotWrappingThickness + VetoBot_Z/2.), pmtLV,"PmtVBot_2", VetoBotContLV, false, 0, fCheckOverlaps);
  
  //Optical surfaces
  G4OpticalSurface* MylarSurfaceMat = new G4OpticalSurface("MylarSurface");
  MylarSurfaceMat->SetModel(glisur);
  MylarSurfaceMat->SetFinish(ground);
  MylarSurfaceMat->SetType(dielectric_metal);
  
  G4MaterialPropertiesTable* MylarSurfaceMat_MPT = new G4MaterialPropertiesTable();
  const G4int MylarSurfaceMat_num = 121;
  //NUMBERS from ("Electron Exposure Measurements of Candidate Solar Sail Materials", L. Tesia et al., J. Sol. Energy Eng 127(1), 125-130)
  G4double MylarSurfaceMat_ENERGY[MylarSurfaceMat_num] = {1.692*eV, 1.695*eV, 1.698*eV, 1.701*eV, 1.704*eV,
							  1.710*eV, 1.716*eV, 1.725*eV, 1.728*eV, 1.732*eV,
							  1.741*eV, 1.744*eV, 1.751*eV, 1.757*eV, 1.764*eV,
							  1.767*eV, 1.777*eV, 1.780*eV, 1.784*eV, 1.790*eV,
							  1.801*eV, 1.807*eV, 1.811*eV, 1.821*eV, 1.825*eV,
							  1.828*eV, 1.835*eV, 1.839*eV, 1.846*eV, 1.850*eV,
							  1.860*eV, 1.883*eV, 1.890*eV, 1.901*eV, 1.909*eV,
							  1.921*eV, 1.928*eV, 1.936*eV, 1.948*eV, 1.956*eV,
							  1.976*eV, 1.993*eV, 2.006*eV, 2.018*eV, 2.036*eV,
							  2.053*eV, 2.076*eV, 2.094*eV, 2.113*eV, 2.127*eV,
							  2.146*eV, 2.180*eV, 2.211*eV, 2.232*eV, 2.258*eV,
							  2.280*eV, 2.302*eV, 2.324*eV, 2.342*eV, 2.359*eV,
							  2.365*eV, 2.383*eV, 2.389*eV, 2.401*eV, 2.431*eV,
							  2.450*eV, 2.476*eV, 2.508*eV, 2.542*eV, 2.562*eV,
							  2.583*eV, 2.612*eV, 2.648*eV, 2.678*eV, 2.708*eV,
							  2.740*eV, 2.796*eV, 2.846*eV, 2.890*eV, 2.943*eV,
							  2.999*eV, 3.067*eV, 3.138*eV, 3.223*eV, 3.290*eV,
							  3.383*eV, 3.470*eV, 3.547*eV, 3.628*eV, 3.743*eV,
							  3.818*eV, 3.912*eV, 3.994*eV, 4.045*eV, 4.115*eV,
							  4.188*eV, 4.263*eV, 4.321*eV, 4.361*eV, 4.442*eV,
							  4.527*eV, 4.571*eV, 4.637*eV, 4.683*eV, 4.730*eV,
							  4.801*eV, 4.826*eV, 4.900*eV, 4.951*eV, 4.977*eV,
							  5.030*eV, 5.057*eV, 5.111*eV, 5.139*eV, 5.195*eV,
							  5.223*eV, 5.252*eV, 5.281*eV, 5.311*eV, 5.371*eV,
							  5.402*eV};
  
  //NUMBERS from ("Electron Exposure Measurements of Candidate Solar Sail Materials", L. Tesia et al., J. Sol. Energy Eng 127(1), 125-130)
  G4double MylarSurfaceMat_REFL[MylarSurfaceMat_num] = {0.882, 0.882, 0.882, 0.882, 0.884,
							0.886, 0.886, 0.886, 0.887, 0.887,
							0.888, 0.888, 0.889, 0.889, 0.890,
							0.890, 0.891, 0.891, 0.892, 0.893,
							0.893, 0.893, 0.894, 0.894, 0.895,
							0.896, 0.896, 0.897, 0.898, 0.899,
							0.899, 0.899, 0.900, 0.900, 0.901,
							0.901, 0.902, 0.902, 0.902, 0.902,
							0.902, 0.902, 0.903, 0.903, 0.904,
							0.905, 0.906, 0.907, 0.908, 0.909,
							0.910, 0.910, 0.910, 0.910, 0.911,
							0.911, 0.912, 0.912, 0.912, 0.912,
							0.912, 0.912, 0.912, 0.913, 0.913,
							0.913, 0.913, 0.913, 0.913, 0.913,
							0.913, 0.913, 0.913, 0.913, 0.912,
							0.911, 0.911, 0.910, 0.909, 0.909,
							0.908, 0.906, 0.905, 0.903, 0.902,
							0.902, 0.902, 0.901, 0.901, 0.901,
							0.901, 0.901, 0.900, 0.900, 0.900,
							0.900, 0.899, 0.899, 0.899, 0.898,
							0.897, 0.896, 0.895, 0.894, 0.894,
							0.893, 0.893, 0.893, 0.892, 0.892,
							0.892, 0.891, 0.891, 0.890, 0.890,
							0.889, 0.889, 0.889, 0.888, 0.888,
							0.888};
  G4double MylarSurfaceMat_EFF[MylarSurfaceMat_num];
  for (int i=0; i<MylarSurfaceMat_num; i++)
    {
      MylarSurfaceMat_EFF[i]=0.0;
    }
  
  for (int i=0; i<MylarSurfaceMat_num; i++)
    {
      MylarSurfaceMat_REFL[i]=0.98;
    }
  
  MylarSurfaceMat_MPT->AddProperty("REFLECTIVITY",MylarSurfaceMat_ENERGY,MylarSurfaceMat_REFL,MylarSurfaceMat_num);
  MylarSurfaceMat_MPT->AddProperty("EFFICIENCY",MylarSurfaceMat_ENERGY,MylarSurfaceMat_EFF,MylarSurfaceMat_num);
  MylarSurfaceMat->SetMaterialPropertiesTable(MylarSurfaceMat_MPT);
  
  new G4LogicalSkinSurface("T1scintWrapping", bar1LV, MylarSurfaceMat);
  new G4LogicalSkinSurface("T2scintWrapping", bar2LV, MylarSurfaceMat);
  new G4LogicalSkinSurface("PscintWrapping", PlaneLV, MylarSurfaceMat);
  new G4LogicalSkinSurface("V1scintWrapping", VetoLatLV, MylarSurfaceMat);
  new G4LogicalSkinSurface("VBscintWrapping", vetobLV, MylarSurfaceMat);
  new G4LogicalSkinSurface("LBar1scintWrapping", Crystal1LV, MylarSurfaceMat);
  new G4LogicalSkinSurface("LBar2scintWrapping", Crystal2LV, MylarSurfaceMat);
  //****************************************************************************************
  
  // VISUALIZATION ATTRIBUTES
  worldLV->SetVisAttributes (G4VisAttributes::Invisible);
  
  //BLUE
  G4VisAttributes* attBlue = new G4VisAttributes(G4Colour::Blue());
  attBlue->SetVisibility(true);
  attBlue->SetForceAuxEdgeVisible(true);
  Crystal1LV->SetVisAttributes(attBlue);
  Crystal2LV->SetVisAttributes(attBlue);
  
  //GREEN
  G4VisAttributes* attGreen = new G4VisAttributes(G4Colour::Green());
  attGreen->SetVisibility(true);
  attGreen->SetForceAuxEdgeVisible(true);
  PlaneLV->SetVisAttributes(attGreen);
  
  //CYAN
  G4VisAttributes* attCyan = new G4VisAttributes(G4Colour::Cyan());
  attCyan->SetVisibility(true);
  attCyan->SetForceAuxEdgeVisible(true);
  GlueBeforeAlpLV->SetVisAttributes(attCyan);
  GlueAfterAlpLV->SetVisAttributes(attCyan);
  bar1LV->SetVisAttributes(attCyan);
  bar2LV->SetVisAttributes(attCyan);
  LightGuide1LV->SetVisAttributes(attCyan);
  vetobLV->SetVisAttributes(attCyan);
  VetoLatLV->SetVisAttributes(attCyan);
  
  //BROWN
  G4VisAttributes* attBrown = new G4VisAttributes(G4Colour::Brown());
  attBrown->SetVisibility(true);
  attBrown->SetForceAuxEdgeVisible(true);
  T1CompPlaneLV->SetVisAttributes(attBrown);
  T2CompPlaneLV->SetVisAttributes(attBrown);
  T1RibsLV->SetVisAttributes(attBrown);
  T2RibsLV->SetVisAttributes(attBrown);
  FrameT1LV->SetVisAttributes(attBrown);
  AlpInterfacePlateLV->SetVisAttributes(attBrown);
  ColdPlateLV->SetVisAttributes(attBrown);
  AlpRibsLV->SetVisAttributes(attBrown);
  PCompPlaneLV->SetVisAttributes(attBrown);
  VetoLatCoverLV->SetVisAttributes(attBrown);
  VetoBotCoverLV->SetVisAttributes(attBrown);
  
  //YELLOW
  G4VisAttributes* attYellow = new G4VisAttributes(G4Colour::Yellow());
  attYellow->SetVisibility(true);
  attYellow->SetForceAuxEdgeVisible(true);
  T1PoronLV->SetVisAttributes(attYellow);
  T2PoronLV->SetVisAttributes(attYellow);
  PPoronLV->SetVisAttributes(attYellow);
  VetoLatPoronLV->SetVisAttributes(attYellow);
  VetoBotPoronLV->SetVisAttributes(attYellow);
  
  //MAGENTA
  G4VisAttributes* attMagenta = new G4VisAttributes(G4Colour::Magenta());
  attMagenta->SetVisibility(true);
  attMagenta->SetForceAuxEdgeVisible(true);
  AlpActiveLV->SetVisAttributes(attMagenta);
  
  //BLACK
  G4VisAttributes* attBlack = new G4VisAttributes(G4Colour::Black());
  attBlack->SetVisibility(true);
  attBlack->SetForceAuxEdgeVisible(true);
  FPC_LV->SetVisAttributes(attBlack);
  CScotchTapeLat1LV->SetVisAttributes(attBlack);
  CScotchTape1LV->SetVisAttributes(attBlack);
  CScotchTapeLat2LV->SetVisAttributes(attBlack);
  CScotchTape2LV->SetVisAttributes(attBlack);
  
  //RED
  G4VisAttributes* attRed = new G4VisAttributes(G4Colour::Red());
  attRed->SetVisibility(true);
  attRed->SetForceAuxEdgeVisible(true);
  WindowOutLV->SetVisAttributes(attRed);
  WindowInLV->SetVisAttributes(attRed);
  CuSupport_LV->SetVisAttributes(attRed);
  WallHoneyCombLV->SetVisAttributes(attRed);
  WallExternalLV->SetVisAttributes(attRed);
  
  //GREY
  G4VisAttributes* attGrey = new G4VisAttributes(G4Colour::Grey());
  pmtLV->SetVisAttributes (attGrey);
  attGrey->SetVisibility(true);
  attGrey->SetForceAuxEdgeVisible(true);
  LysoCoverLV->SetVisAttributes (attGrey);
  BlanketLV->SetVisAttributes (attGrey);
  T1WrappingLV->SetVisAttributes (attGrey);
  T2WrappingLV->SetVisAttributes (attGrey);
  PWrappingLV->SetVisAttributes (attGrey);
  CWrappingLat1LV->SetVisAttributes (attGrey);
  CWrapping1LV->SetVisAttributes (attGrey);
  CWrappingLat2LV->SetVisAttributes (attGrey);
  CWrapping2LV->SetVisAttributes (attGrey);
  VetoLatWrappingLV->SetVisAttributes(attGrey);
  VetoBotWrappingLV->SetVisAttributes(attGrey);
  RearVetoBotLV->SetVisAttributes (attGrey);
  
  
  //INVISIBLE
  WindowContainerLV->SetVisAttributes (G4VisAttributes::Invisible);
  AlpContLV->SetVisAttributes (G4VisAttributes::Invisible);
  AlpTowerLV->SetVisAttributes (G4VisAttributes::Invisible);
  AlpPlaneLV->SetVisAttributes (G4VisAttributes::Invisible);
  AlpDoubleLV->SetVisAttributes (G4VisAttributes::Invisible);
  Alp1LV->SetVisAttributes (G4VisAttributes::Invisible);
  Alp2LV->SetVisAttributes (G4VisAttributes::Invisible);
  T1ContLV->SetVisAttributes (G4VisAttributes::Invisible);
  triggerCont1LV->SetVisAttributes (G4VisAttributes::Invisible);
  trigger1LV->SetVisAttributes (G4VisAttributes::Invisible);
  BarCont1LV->SetVisAttributes (G4VisAttributes::Invisible);
  T2ContLV->SetVisAttributes (G4VisAttributes::Invisible);
  triggerCont2LV->SetVisAttributes (G4VisAttributes::Invisible);
  trigger2LV->SetVisAttributes (G4VisAttributes::Invisible);
  BarCont2LV->SetVisAttributes (G4VisAttributes::Invisible);
  calorimeterLV->SetVisAttributes (G4VisAttributes::Invisible);
  calorimeterBlock1LV->SetVisAttributes (G4VisAttributes::Invisible);
  calorimeterBlock2LV->SetVisAttributes (G4VisAttributes::Invisible);
  calorimeterBlock3LV->SetVisAttributes (G4VisAttributes::Invisible);
  PBoxdxLV->SetVisAttributes (G4VisAttributes::Invisible);
  PBoxsxLV->SetVisAttributes (G4VisAttributes::Invisible);
  CrystalCont1LV->SetVisAttributes (G4VisAttributes::Invisible);
  CrystalCont2LV->SetVisAttributes (G4VisAttributes::Invisible);
  VetoLatContainerLV->SetVisAttributes (G4VisAttributes::Invisible);
  VetoBotContLV->SetVisAttributes (G4VisAttributes::Invisible);
  
  return worldPV;
}


void HEPD2MCDetectorConstruction::ActivateOptics(G4bool optics)
{
  fOptics = optics;
}
