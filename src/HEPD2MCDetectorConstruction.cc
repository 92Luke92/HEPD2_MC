/////////////////////////////////////////////
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
    fDoubleLayerPV(0),
    fLayer1PV(0),
    fLayer2PV(0),
    fAbsorber1PV(0),
    fAbsorber2PV(0),
    fGap1PV(0),
    fGap2PV(0),
    fCrystal1PV(0),
    fCBars1PV(0),
    fCrystal2PV(0),
    fCBars2PV(0),
    fVetobPV(0), 
    fLveto1PV(0),
    fLveto2PV(0),
    fLveto3PV(0),
    fLveto4PV(0),
    ftrigger1PV(0),
    fTBars1PV(0),
    ftrigger2PV(0),
    fTBars2PV(0),
    fCFplaneBeforeT1PV(0),
    fCFplaneAfterT1PV(0),
    fCFplaneBeforeT2PV(0),
    fCFplaneAfterT2PV(0),
    fGrk1PV(0),
    fGrk2PV(0),
    fAlumPlanePV(0),
    fAlpContPV(0),
    fAlpTowerPV(0),
    fAlpPlane1PV(0),
    fAlpPlane2PV(0),
    fAlpPlane3PV(0),
    fAlpHPlanePV(0),
    fAlpPV(0),
    fCuSupport1_PV(0),
    fCuSupport2_PV(0),
    fCuSupport3_PV(0),
    fFPC1_PV(0),
    fFPC2_PV(0),
    fFPC3_PV(0),
    fColdPlate1_PV(0),
    fColdPlate2_PV(0),
    fColdPlate3_PV(0),
    fRibs1_PV(0),
    fRibs2_PV(0),
    fRibs3_PV(0),
    fRibs4_PV(0),
    fRibs5_PV(0),
    fRibs6_PV(0),
    fWindowOutPV(0),
    fWindowInPV(0),
    fWallHoneyCombPV(0),
    fWallExternalOutPV(0),
    fWallExternalInPV(0),
    
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
  
  
  // Print materials
  //G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume* HEPD2MCDetectorConstruction::DefineVolumes()
{
  // Geometry parameters
  G4int nofPlanes = NCOUPLEDPLANES;
  G4double planeThickness = PLANE_THICKNESS;
  G4double planeGap = PLANE_GAP;
  G4double caloSizeXY = PLANE_SIZEXY;
  G4double cutPlane = PLANE_CUT;
  
  G4double ext_dist = CRYSTALVETO_DIST;
  
  //crystal
  //G4double crystalThickness = CRYSTAL_THICKNESS;
  //G4double crystalSizeXY = CRYSTAL_SIZEXY;
  G4double crystalBarSizeX = CRYSTAL_SIZEX;
  G4double crystalBarSizeY = CRYSTAL_SIZEY;
  G4double crystalBarThickness = CRYSTAL_THICKNESS;
  G4int nofCrystals = NCRYSTALS;
  G4double crystalGap = CRYSTAL_GAP;
  G4double crystalGapZ = CRYSTALGAP_Z;
  
  //Trigger
  G4double triggerThickness = TRIGGER_THICKNESS;
  G4int nofBars = NBARS;
  G4double trigger1SizeX = TRIGGER1_SIZEX;
  G4double trigger1SizeY = TRIGGER1_SIZEY;
  G4double trigger2SizeX = TRIGGER2_SIZEX;
  G4double trigger2SizeY = TRIGGER2_SIZEY;
  
  G4double dist = TRIGPLANE_DIST;
  G4double triggerGap = TRIGGER_GAP;
  G4double barsGap = GRK_THICKNESS;
  
  //Light guide
  G4double LG_X = LGEXIT_X;
  G4double LG_Y = LGEXIT_Y;
  G4double LG_height = LG_HEIGHT;
  
  //CF plane T1
  G4double CFplaneT1_X = TRIGGER1_SIZEX;
  G4double CFplaneT1_Y = TRIGGER1_SIZEY;
  G4double CFplaneT1_Z = CFPLANE_THICKNESS;
  
  //CF plane T2
  G4double CFplaneT2_X = TRIGGER2_SIZEX;
  G4double CFplaneT2_Y = TRIGGER2_SIZEY;
  G4double CFplaneT2_Z = CFPLANE_THICKNESS;
  
  //Greek structure
  G4double Grk1_Y = TRIGGER1_SIZEY;
  G4double Grk_Z = GRK_THICKNESS;
  G4double Grk1Long_X = TRIGGER1_SIZEX/NBARS + GRK_THICKNESS;
  G4double Grk1Short_X = TRIGGER_THICKNESS;
  
  G4double Grk2_Y = TRIGGER2_SIZEX;
  G4double Grk2Long_X = TRIGGER2_SIZEY/NBARS + GRK_THICKNESS;
  G4double Grk2Short_X = TRIGGER_THICKNESS;
  
  //Aluminium plane
  double AlumPlane_X = ALUMPLANE_X;
  double AlumPlane_Y = ALUMPLANE_Y;
  double AlumPlane_Z = ALUMPLANE_Z;
  
  //alpide
  G4double alpideGap = ALPIDE_GAP;
  G4double alpideGap_X = ALPIDE_GAPX;
  
  G4int nofAlpideX = NALPIDEX;
  G4int nofAlpideY = NALPIDEY;
  
  G4double alpideSizeX = ALPIDE_SIZEX;
  G4double alpideSizeY = ALPIDE_SIZEY;
  G4double alpideSizeZ = ALPIDE_SIZEZ;
  
  G4double alp_dist = ALPIDETRIG_DIST;
  
  //Copper support alpide
  G4double CuSupportSizeX = CUSUPP_SIZEX;
  G4double CuSupportSizeY = CUSUPP_SIZEY;
  G4double CuSupportSizeZ = CUSUPP_SIZEZ;
  
  //FPC
  G4double FPCSizeX = FPC_SIZEX;
  G4double FPCSizeY = FPC_SIZEY;
  G4double FPCSizeZ = FPC_SIZEZ;
  
  //Cold plate
  G4double ColdPlateSizeX = COLDPLATE_SIZEX;
  G4double ColdPlateSizeY = COLDPLATE_SIZEY;
  G4double ColdPlateSizeZ = COLDPLATE_SIZEZ;
  
  //Ribs
  G4double RibsX = RIBS_SIZEX;
  G4double RibsY = RIBS_SIZEY;
  G4double RibsZ = RIBS_SIZEZ;
  
  //veto
  G4double vetoThickness = VETO_THICKNESS;
  G4double vetoSizeXY = VETO_SIZEXY;
  
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
  
  G4double WallHole_Z = 6.*mm; //must be greater than WALLHONEYCOMB_THICKNESS
  G4double WallHole_X = Wall_X/2.-window_X/2.-44.*mm; //from HEPD1
  G4double WallHole_Y = Wall_Y/2.-window_Y/2.-68.5*mm; //from HEPD1
  
  //pmt
  G4double pmtInnerRadius = 0.*mm;
  G4double pmtOuterRadius = PMT_OUTERR;
  G4double pmtHeight = PMT_HEIGHT;
  G4double pmtStartAngle = 0.*deg;
  G4double pmtSpanAngle = 360.*deg;
  
  //axes
  G4double axes = AXESBLANKET_DIST;
  
  G4double layerThickness = planeThickness + planeGap;
  G4double caloThickness = nofPlanes * layerThickness;
  
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
  G4Material *CarbonFiberAlpideMaterial = new G4Material("CarbonFiberAlpide",1.9*g/cm3,1);
  CarbonFiberAlpideMaterial->AddElement(elC,1);
  
  //carbon fiber material for Trigger and Calo
  G4Material *CarbonFiberCaloMaterial = new G4Material("CarbonFiberCalo",2.3*g/cm3,1);
  CarbonFiberCaloMaterial->AddElement(elC,1);
  
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
      //Attenuation length: "Optimization of the effective light attenuation length of YAP:Ce and LYSO:Ce crystals for a novel geometrical PET concept"
      G4double cryOptMat_ABSL[cryOptMat_num];
      for(int i=0; i<cryOptMat_num; i++) cryOptMat_ABSL[i] = 20.*cm;
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
  G4VPhysicalVolume* worldPV = new G4PVPlacement(0, G4ThreeVector(), worldLV, "World", 0, false, 0, fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  // CALORIMETER
  G4VSolid* calorimeterS = new G4Box("Calorimeter", caloSizeXY/2., caloSizeXY/2., (caloThickness)/2.);
  G4LogicalVolume* caloLV = new G4LogicalVolume(calorimeterS, defaultMaterial, "Calorimeter");
  new G4PVPlacement(0, G4ThreeVector(0.,0.,caloThickness/2.+dist+2.*triggerThickness+triggerGap+alp_dist+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2.*alpideGap+axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist), caloLV, "Calorimeter", worldLV, false, 0, fCheckOverlaps);
  
  // Calorimeter: DoubleLayer
  G4Box* doublelayerS = new G4Box("DoubleLayer", caloSizeXY/2., caloSizeXY/2., 2.*layerThickness/2.);
  G4LogicalVolume* doublelayerLV = new G4LogicalVolume(doublelayerS, defaultMaterial, "DoubleLayer");
  fDoubleLayerPV = new G4PVReplica("DoubleLayer", doublelayerLV, caloLV, kZAxis, nofPlanes/2, 2.*layerThickness);
  
  // Calorimeter: Layer
  G4Box* layerS = new G4Box("Layer", caloSizeXY/2., caloSizeXY/2., layerThickness/2.);
  G4LogicalVolume* layer1LV = new G4LogicalVolume(layerS, defaultMaterial, "Layer1");
  G4LogicalVolume* layer2LV = new G4LogicalVolume(layerS, defaultMaterial, "Layer2");
  fLayer1PV = new G4PVPlacement(0,G4ThreeVector(0.,0.,-layerThickness/2.), layer1LV, "Layer1", doublelayerLV, false, 0, fCheckOverlaps);
  fLayer2PV = new G4PVPlacement(0,G4ThreeVector(0.,0.,+layerThickness/2.), layer2LV, "Layer2", doublelayerLV, false, 0, fCheckOverlaps);
  
  // Calorimeter: Absorber
  G4Box* absorberS_1 = new G4Box("Abso_1",caloSizeXY/2., caloSizeXY/2.-cutPlane, planeThickness/2.);
  G4Trd* absorberS_2 = new G4Trd("Abso_2", caloSizeXY/2.,caloSizeXY/2.-cutPlane,planeThickness/2.,planeThickness/2.,cutPlane/2.);
  
  G4RotationMatrix* rot1 = new G4RotationMatrix;
  rot1->rotateX(90.*deg);
  G4ThreeVector trans1;
  trans1.setX(0.);
  trans1.setY((caloSizeXY-cutPlane)/2.);
  trans1.setZ(0.);
  
  G4UnionSolid* absorberS_1and2 = new G4UnionSolid("Abso_1and2", absorberS_1, absorberS_2, rot1, trans1);
  
  G4RotationMatrix* rot2 = new G4RotationMatrix;
  rot2->rotateX(-90.*deg);
  G4ThreeVector trans2;
  trans2.setX(0.);
  trans2.setY(-(caloSizeXY-cutPlane)/2.);
  trans2.setZ(0.);
  
  G4UnionSolid* absorberS = new G4UnionSolid("Abso", absorberS_1and2, absorberS_2, rot2, trans2);
  
  G4LogicalVolume* absorberLV = new G4LogicalVolume(absorberS, absorberMaterial, "Abso");
  fAbsorber1PV = new G4PVPlacement(0, G4ThreeVector(0., 0., planeGap/2.), absorberLV, "Abso1", layer1LV, false, 0, fCheckOverlaps);
  fAbsorber2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., planeGap/2.), absorberLV, "Abso2", layer2LV, false, 0, fCheckOverlaps);
  
  // Calorimeter: Gap
  G4Box* gapS = new G4Box("Gap", caloSizeXY/2., caloSizeXY/2., planeGap/2.);
  G4LogicalVolume* gapLV = new G4LogicalVolume(gapS, CarbonFiberCaloMaterial, "Gap");
  fGap1PV = new G4PVPlacement(0, G4ThreeVector(0., 0., -planeThickness/2.), gapLV, "Gap1", layer1LV, false, 0, fCheckOverlaps);
  fGap2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., -planeThickness/2.), gapLV, "Gap2", layer2LV, false, 0, fCheckOverlaps);
  
  // Calorimeter: last plane
  G4Box* lastlayerS = new G4Box("LastLayer", caloSizeXY/2., caloSizeXY/2., layerThickness/2.);
  G4LogicalVolume* lastlayerLV = new G4LogicalVolume(lastlayerS, defaultMaterial, "LastLayer");
  fLastLayerPV = new G4PVPlacement(0,G4ThreeVector(0.,0.,axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+2.*alpideGap+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+alp_dist+triggerGap+2.*triggerThickness+dist+caloThickness+layerThickness/2.), lastlayerLV, "LastLayer", worldLV, false, 0, fCheckOverlaps);
  // Calorimeter: Last absorber
  fLastAbsorberPV = new G4PVPlacement(0, G4ThreeVector(0., 0., planeGap/2.), absorberLV, "LastAbso", lastlayerLV, false, 0, fCheckOverlaps);
  // Calorimeter: Last gap
  fLastGapPV = new G4PVPlacement(0, G4ThreeVector(0., 0., -planeThickness/2.), gapLV, "LastGap", lastlayerLV, false, 0, fCheckOverlaps);
  
  //****************************************************************************************
  
  //****************************************************************************************
  // CRYSTAL
  // Crystal: container 1st plane
  G4VSolid* crystalCont1S = new G4Box("crystalCont1", nofCrystals*crystalBarSizeX/2., crystalBarSizeY/2., crystalBarThickness/2.);
  G4LogicalVolume* crystalCont1LV = new G4LogicalVolume(crystalCont1S, defaultMaterial, "crystalBar1");
  G4double L1_posZ = axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+2.*alpideGap+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+alp_dist+triggerGap+2.*triggerThickness+dist+caloThickness+layerThickness+crystalBarThickness/2.+AlumPlane_Z;
  new G4PVPlacement(0, G4ThreeVector(0,0, L1_posZ), crystalCont1LV, "crystalCont1", worldLV, false, 0, fCheckOverlaps);
  
  // Crystal: bars 1st plane
  G4VSolid* crystal1S = new G4Box("L1", crystalBarSizeX/2., crystalBarSizeY/2., crystalBarThickness/2.);
  G4LogicalVolume* crystal1LV = new G4LogicalVolume(crystal1S, defaultMaterial, "L1");
  fCrystal1PV = new G4PVReplica("L1", crystal1LV, crystalCont1LV, kXAxis, nofCrystals, crystalBarSizeX);
  
  // Crystal: bars 1st plane
  G4VSolid* Cbar1S = new G4Box("CBar1", (crystalBarSizeX - crystalGap)/2., crystalBarSizeY/2., crystalBarThickness/2.);
  G4LogicalVolume* Cbar1LV = new G4LogicalVolume(Cbar1S, crystalMaterial, "CBar1");
  fCBars1PV = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), Cbar1LV, "CBar1", crystal1LV, false, 0, fCheckOverlaps);
  
  // Crystal: container 2nd plane
  G4VSolid* crystalCont2S = new G4Box("crystalCont2", crystalBarSizeY/2., nofCrystals*crystalBarSizeX/2., crystalBarThickness/2.);
  G4LogicalVolume* crystalCont2LV = new G4LogicalVolume(crystalCont2S, defaultMaterial, "crystalBar2");
  G4double L2_posZ = axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+2.*alpideGap+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+alp_dist+triggerGap+2.*triggerThickness+dist+caloThickness+layerThickness+crystalBarThickness/2.+AlumPlane_Z+crystalGapZ+crystalBarThickness;
  new G4PVPlacement(0, G4ThreeVector(0,0, L2_posZ), crystalCont2LV, "crystalCont2", worldLV, false, 0, fCheckOverlaps);
  
  // Crystal: bars 2nd plane
  G4VSolid* crystal2S = new G4Box("L2", crystalBarSizeY/2., crystalBarSizeX/2., crystalBarThickness/2.);
  G4LogicalVolume* crystal2LV = new G4LogicalVolume(crystal2S, defaultMaterial, "L2");
  fCrystal2PV = new G4PVReplica("L2", crystal2LV, crystalCont2LV, kYAxis, nofCrystals, crystalBarSizeX);
  
  // Crystal: bars 2nd plane
  G4VSolid* Cbar2S = new G4Box("CBar2", crystalBarSizeY/2., (crystalBarSizeX - crystalGap)/2., crystalBarThickness/2.);
  G4LogicalVolume* Cbar2LV = new G4LogicalVolume(Cbar2S, crystalMaterial, "CBar2");
  fCBars2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), Cbar2LV, "CBar2", crystal2LV, false, 0, fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  // AL PLANE
  //Aluminium plane between last plane and lyso
  G4VSolid* AlumPlaneS = new G4Box("AlumPlane", AlumPlane_X/2., AlumPlane_Y/2., AlumPlane_Z/2.);
  G4LogicalVolume* AlumPlaneLV = new G4LogicalVolume(AlumPlaneS, AlMaterial, "AlumPlane");
  fAlumPlanePV = new G4PVPlacement(0, G4ThreeVector(0,0,axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+2.*alpideGap+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+alp_dist+triggerGap+2.*triggerThickness+dist+caloThickness+layerThickness+AlumPlane_Z/2.),AlumPlaneLV,"AlumPlane",worldLV,false, 0, fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  // TRIGGER
  // Trigger: container 1st plane
  G4VSolid* triggerCont1S = new G4Box("triggerCont1", trigger1SizeX/2., trigger1SizeY/2., triggerThickness/2.);
  G4LogicalVolume* triggerCont1LV = new G4LogicalVolume(triggerCont1S, defaultMaterial, "triggerCont1");
  G4double T1_posZ = axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+2.*alpideGap+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+alp_dist+triggerThickness/2.;
  new G4PVPlacement(0, G4ThreeVector(0,0, T1_posZ), triggerCont1LV, "triggerCont1", worldLV, false, 0, fCheckOverlaps);  
  
  // Trigger: bars 1st plane
  G4VSolid* trigger1S = new G4Box("T1",(trigger1SizeX/2.)/nofBars, trigger1SizeY/2., triggerThickness/2.);
  G4LogicalVolume* trigger1LV = new G4LogicalVolume(trigger1S, defaultMaterial, "T1");
  ftrigger1PV = new G4PVReplica("T1", trigger1LV, triggerCont1LV, kXAxis, nofBars, trigger1SizeX/nofBars);
  
  // Trigger: bars 1st plane
  G4VSolid* bar1S = new G4Box("Bar1", (trigger1SizeX/nofBars - barsGap)/2., trigger1SizeY/2., triggerThickness/2.);
  G4LogicalVolume* bar1LV = new G4LogicalVolume(bar1S, absorberMaterial, "Bar1");
  fTBars1PV = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), bar1LV, "Bar1", trigger1LV, false, 0, fCheckOverlaps);
  
  // Trigger: container 2nd plane
  G4VSolid* triggerCont2S = new G4Box("triggerCont2", trigger2SizeX/2., trigger2SizeY/2., triggerThickness/2.);
  G4LogicalVolume* triggerCont2LV = new G4LogicalVolume(triggerCont2S, defaultMaterial, "triggerCont2");
    G4double T2_posZ = axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+2.*alpideGap+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+alp_dist+triggerGap+triggerThickness+triggerThickness/2.;
  new G4PVPlacement(0, G4ThreeVector(0,0, T2_posZ), triggerCont2LV, "triggerCont2", worldLV, false, 0, fCheckOverlaps);
  
  // Trigger: bars 2nd plane
  G4VSolid* trigger2S = new G4Box("T2",trigger2SizeX/2., (trigger2SizeY/2.)/nofBars, triggerThickness/2.);
  G4LogicalVolume* trigger2LV = new G4LogicalVolume(trigger2S, defaultMaterial, "T2");
  ftrigger2PV = new G4PVReplica("T2", trigger2LV, triggerCont2LV, kYAxis, nofBars, trigger2SizeY/nofBars);
  
  // Trigger: bars 2nd plane
  G4VSolid* bar2S = new G4Box("Bar2", trigger2SizeX/2., (trigger2SizeY/nofBars - barsGap)/2., triggerThickness/2.);
  G4LogicalVolume* bar2LV = new G4LogicalVolume(bar2S, absorberMaterial, "Bar2");
  fTBars2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), bar2LV, "Bar2", trigger2LV, false, 0, fCheckOverlaps);
  
  //Planes carbon fiber for T1
  G4Box* CFplaneT1S = new G4Box("CFplaneT1", CFplaneT1_X/2., CFplaneT1_Y/2., CFplaneT1_Z/2.);
  G4LogicalVolume* CFplaneT1LV = new G4LogicalVolume(CFplaneT1S, CarbonFiberCaloMaterial, "CFplaneT1");
  fCFplaneBeforeT1PV = new G4PVPlacement(0, G4ThreeVector(0., 0., T1_posZ-triggerThickness/2.-Grk_Z-CFplaneT1_Z/2.), CFplaneT1LV, "CFplaneBeforeT1", worldLV, false, 0, fCheckOverlaps);
  fCFplaneAfterT1PV = new G4PVPlacement(0, G4ThreeVector(0., 0., T1_posZ+triggerThickness/2.+Grk_Z+CFplaneT1_Z/2.), CFplaneT1LV, "CFplaneAfterT1", worldLV, false, 0, fCheckOverlaps);
  
  //Planes carbon fiber for T2
  G4Box* CFplaneT2S = new G4Box("CFplaneT1", CFplaneT2_X/2., CFplaneT2_Y/2., CFplaneT2_Z/2.);
  G4LogicalVolume* CFplaneT2LV = new G4LogicalVolume(CFplaneT2S, CarbonFiberCaloMaterial, "CFplaneT2");
  fCFplaneBeforeT2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., T2_posZ-triggerThickness/2.-Grk_Z-CFplaneT1_Z/2.), CFplaneT2LV, "CFplaneBeforeT2", worldLV, false, 0, fCheckOverlaps);
  fCFplaneAfterT2PV = new G4PVPlacement(0, G4ThreeVector(0., 0., T2_posZ+triggerThickness/2.+Grk_Z+CFplaneT1_Z/2.), CFplaneT2LV, "CFplaneAfterT2", worldLV, false, 0, fCheckOverlaps);
  
  // Trigger: 1st Greek carbon fiber
  G4Box* Grk1ShortS = new G4Box("Grk1", Grk1Short_X/2., Grk1_Y/2., Grk_Z/2.);
  G4Box* Grk1LongS = new G4Box("Grk1", Grk1Long_X/2., Grk1_Y/2., Grk_Z/2.);
  
  G4RotationMatrix* Grk1rot = new G4RotationMatrix;
  Grk1rot->rotateY(90.*deg);
  
  G4ThreeVector Grk1trans_1;
  Grk1trans_1.setX(Grk1Long_X/2.-Grk_Z/2.);
  Grk1trans_1.setY(0.);
  Grk1trans_1.setZ(-Grk1Short_X/2.-Grk_Z/2.);
  G4UnionSolid* Grk1_1 = new G4UnionSolid("Grk1_1", Grk1LongS, Grk1ShortS, Grk1rot, Grk1trans_1);
  
  G4ThreeVector Grk1trans_2;
  Grk1trans_2.setX(-Grk1Long_X/2.+Grk_Z/2.);
  Grk1trans_2.setY(0.);
  Grk1trans_2.setZ(-Grk1Short_X/2.-Grk_Z/2.);
  G4UnionSolid* Grk1_2 = new G4UnionSolid("Grk1_2", Grk1_1, Grk1ShortS, Grk1rot, Grk1trans_2);
  
  G4ThreeVector Grk1trans_3;
  Grk1trans_3.setX(Grk1Long_X-Grk_Z);
  Grk1trans_3.setY(0.);
  Grk1trans_3.setZ(-Grk1Short_X-Grk_Z);
  G4UnionSolid* Grk1_3 = new G4UnionSolid("Grk1_3", Grk1_2, Grk1LongS, 0, Grk1trans_3);
  
  G4ThreeVector Grk1trans_4;
  Grk1trans_4.setX(3./2.*Grk1Long_X-3./2.*Grk_Z);
  Grk1trans_4.setY(0.);
  Grk1trans_4.setZ(-Grk1Short_X/2.-Grk_Z/2.);
  G4UnionSolid* Grk1_4 = new G4UnionSolid("Grk1_4", Grk1_3, Grk1ShortS, Grk1rot, Grk1trans_4);
  
  G4ThreeVector Grk1trans_5;
  Grk1trans_5.setX(2.*Grk1Long_X-2.*Grk_Z);
  Grk1trans_5.setY(0.);
  Grk1trans_5.setZ(0.);
  G4UnionSolid* Grk1_5 = new G4UnionSolid("Grk1_5", Grk1_4, Grk1LongS, 0, Grk1trans_5);

  G4ThreeVector Grk1trans_6;
  Grk1trans_6.setX(5./2.*Grk1Long_X-5./2.*Grk_Z);
  Grk1trans_6.setY(0.);
  Grk1trans_6.setZ(-Grk1Short_X/2.-Grk_Z/2.);
  G4UnionSolid* Grk1_6 = new G4UnionSolid("Grk1_6", Grk1_5, Grk1ShortS, Grk1rot, Grk1trans_6);
  
  G4ThreeVector Grk1trans_7;
  Grk1trans_7.setX(-Grk1Long_X+Grk_Z);
  Grk1trans_7.setY(0.);
  Grk1trans_7.setZ(-Grk1Short_X-Grk_Z);
  G4UnionSolid* Grk1_7 = new G4UnionSolid("Grk1_7", Grk1_6, Grk1LongS, 0, Grk1trans_7);

  G4ThreeVector Grk1trans_8;
  Grk1trans_8.setX(-3./2.*Grk1Long_X+3./2.*Grk_Z);
  Grk1trans_8.setY(0.);
  Grk1trans_8.setZ(-Grk1Short_X/2.-Grk_Z/2.);
  G4UnionSolid* Grk1_8 = new G4UnionSolid("Grk1_8", Grk1_7, Grk1ShortS, Grk1rot, Grk1trans_8);
  
  G4ThreeVector Grk1trans_9;
  Grk1trans_9.setX(-2.*Grk1Long_X+2.*Grk_Z);
  Grk1trans_9.setY(0.);
  Grk1trans_9.setZ(0.);
  G4UnionSolid* Grk1_9 = new G4UnionSolid("Grk1_9", Grk1_8, Grk1LongS, 0, Grk1trans_9);

  G4ThreeVector Grk1trans_10;
  Grk1trans_10.setX(-5./2.*Grk1Long_X+5./2.*Grk_Z);
  Grk1trans_10.setY(0.);
  Grk1trans_10.setZ(-Grk1Short_X/2.-Grk_Z/2.);
  G4UnionSolid* Grk1 = new G4UnionSolid("Grk1", Grk1_9, Grk1ShortS, Grk1rot, Grk1trans_10);
  
  G4LogicalVolume* Grk1LV = new G4LogicalVolume(Grk1, CarbonFiberCaloMaterial, "Grk1");
  fGrk1PV = new G4PVPlacement(0,G4ThreeVector(0., 0., T1_posZ+triggerThickness/2.+Grk_Z/2.), Grk1LV, "Grk1", worldLV, false, 0, fCheckOverlaps);
  
  // Trigger: 2nd Greek carbon fiber
  G4Box* Grk2ShortS = new G4Box("Grk2", Grk2Short_X/2., Grk2_Y/2., Grk_Z/2.);
  G4Box* Grk2LongS = new G4Box("Grk2", Grk2Long_X/2., Grk2_Y/2., Grk_Z/2.);
  
  G4RotationMatrix* Grk2rot = new G4RotationMatrix;
  Grk2rot->rotateY(90.*deg);
  
  G4ThreeVector Grk2trans_1;
  Grk2trans_1.setX(Grk2Long_X/2.-Grk_Z/2.);
  Grk2trans_1.setY(0.);
  Grk2trans_1.setZ(-Grk2Short_X/2.-Grk_Z/2.);
  G4UnionSolid* Grk2_1 = new G4UnionSolid("Grk2_1", Grk2LongS, Grk2ShortS, Grk2rot, Grk2trans_1);
  
  G4ThreeVector Grk2trans_2;
  Grk2trans_2.setX(-Grk2Long_X/2.+Grk_Z/2.);
  Grk2trans_2.setY(0.);
  Grk2trans_2.setZ(-Grk2Short_X/2.-Grk_Z/2.);
  G4UnionSolid* Grk2_2 = new G4UnionSolid("Grk2_2", Grk2_1, Grk2ShortS, Grk2rot, Grk2trans_2);
  
  G4ThreeVector Grk2trans_3;
  Grk2trans_3.setX(Grk2Long_X-Grk_Z);
  Grk2trans_3.setY(0.);
  Grk2trans_3.setZ(-Grk2Short_X-Grk_Z);
  G4UnionSolid* Grk2_3 = new G4UnionSolid("Grk2_3", Grk2_2, Grk2LongS, 0, Grk2trans_3);
  
  G4ThreeVector Grk2trans_4;
  Grk2trans_4.setX(3./2.*Grk2Long_X-3./2.*Grk_Z);
  Grk2trans_4.setY(0.);
  Grk2trans_4.setZ(-Grk2Short_X/2.-Grk_Z/2.);
  G4UnionSolid* Grk2_4 = new G4UnionSolid("Grk2_4", Grk2_3, Grk2ShortS, Grk2rot, Grk2trans_4);
  
  G4ThreeVector Grk2trans_5;
  Grk2trans_5.setX(2.*Grk2Long_X-2.*Grk_Z);
  Grk2trans_5.setY(0.);
  Grk2trans_5.setZ(0.);
  G4UnionSolid* Grk2_5 = new G4UnionSolid("Grk2_5", Grk2_4, Grk2LongS, 0, Grk2trans_5);

  G4ThreeVector Grk2trans_6;
  Grk2trans_6.setX(5./2.*Grk2Long_X-5./2.*Grk_Z);
  Grk2trans_6.setY(0.);
  Grk2trans_6.setZ(-Grk2Short_X/2.-Grk_Z/2.);
  G4UnionSolid* Grk2_6 = new G4UnionSolid("Grk2_6", Grk2_5, Grk2ShortS, Grk2rot, Grk2trans_6);
  
  G4ThreeVector Grk2trans_7;
  Grk2trans_7.setX(-Grk2Long_X+Grk_Z);
  Grk2trans_7.setY(0.);
  Grk2trans_7.setZ(-Grk2Short_X-Grk_Z);
  G4UnionSolid* Grk2_7 = new G4UnionSolid("Grk2_7", Grk2_6, Grk2LongS, 0, Grk2trans_7);

  G4ThreeVector Grk2trans_8;
  Grk2trans_8.setX(-3./2.*Grk2Long_X+3./2.*Grk_Z);
  Grk2trans_8.setY(0.);
  Grk2trans_8.setZ(-Grk2Short_X/2.-Grk_Z/2.);
  G4UnionSolid* Grk2_8 = new G4UnionSolid("Grk2_8", Grk2_7, Grk2ShortS, Grk2rot, Grk2trans_8);
  
  G4ThreeVector Grk2trans_9;
  Grk2trans_9.setX(-2.*Grk2Long_X+2.*Grk_Z);
  Grk2trans_9.setY(0.);
  Grk2trans_9.setZ(0.);
  G4UnionSolid* Grk2_9 = new G4UnionSolid("Grk2_9", Grk2_8, Grk2LongS, 0, Grk2trans_9);

  G4ThreeVector Grk2trans_10;
  Grk2trans_10.setX(-5./2.*Grk2Long_X+5./2.*Grk_Z);
  Grk2trans_10.setY(0.);
  Grk2trans_10.setZ(-Grk2Short_X/2.-Grk_Z/2.);
  G4UnionSolid* Grk2 = new G4UnionSolid("Grk2", Grk2_9, Grk2ShortS, Grk2rot, Grk2trans_10);
  
  G4LogicalVolume* Grk2LV = new G4LogicalVolume(Grk2, CarbonFiberCaloMaterial, "Grk2");
  
  G4RotationMatrix* Grk2rot_tot = new G4RotationMatrix;
  Grk2rot_tot->rotateZ(90.*deg);
  fGrk2PV = new G4PVPlacement(Grk2rot_tot,G4ThreeVector(0., 0., T2_posZ+triggerThickness/2.+Grk_Z/2.), Grk2LV, "Grk2", worldLV, false, 0, fCheckOverlaps);
  
  //Light Guide
  G4VSolid* LightGuide1S = new G4Trd("LightGuide1", ((trigger1SizeX)/2.)/nofBars-barsGap/2., LG_X/2., triggerThickness/2., LG_Y/2., LG_height/2.);
  G4LogicalVolume* LightGuide1LV = new G4LogicalVolume(LightGuide1S, LightGuideMaterial, "LightGuide1");
  G4RotationMatrix* LG1_rot1 = new G4RotationMatrix;
  LG1_rot1->rotateX(90.*deg);
  G4RotationMatrix* LG1_rot2 = new G4RotationMatrix;
  LG1_rot2->rotateX(-90.*deg);
  G4VSolid* LightGuide2S = new G4Trd("LightGuide2", ((trigger2SizeY)/2.)/nofBars-barsGap/2., LG_X/2., triggerThickness/2., LG_Y/2., LG_height/2.);
  G4LogicalVolume* LightGuide2LV = new G4LogicalVolume(LightGuide2S, LightGuideMaterial, "LightGuide2");
  G4RotationMatrix* LG2_rot1 = new G4RotationMatrix;
  LG2_rot1->rotateY(-90.*deg);
  LG2_rot1->rotateZ(90.*deg);
  G4RotationMatrix* LG2_rot2 = new G4RotationMatrix;
  LG2_rot2->rotateY(90.*deg);
  LG2_rot2->rotateZ(90.*deg);
  for(G4int copyNo=0; copyNo<nofBars; copyNo++)
    {
      new G4PVPlacement(LG1_rot1,G4ThreeVector(-(nofBars-1)*((trigger1SizeX/2.)/nofBars)+2.*copyNo*((trigger1SizeX/2.)/nofBars), trigger1SizeY/2.+LG_height/2., T1_posZ), LightGuide1LV, "LightGuide_T1", worldLV, false, 0, fCheckOverlaps);
      new G4PVPlacement(LG1_rot2,G4ThreeVector(-(nofBars-1)*((trigger1SizeX/2.)/nofBars)+2.*copyNo*((trigger1SizeX/2.)/nofBars), -trigger1SizeY/2.-LG_height/2., T1_posZ), LightGuide1LV, "LightGuide_T1", worldLV, false, 0, fCheckOverlaps);
      new G4PVPlacement(LG2_rot1,G4ThreeVector(trigger2SizeX/2.+LG_height/2., -(nofBars-1)*((trigger2SizeY/2.)/nofBars)+2.*copyNo*((trigger2SizeY/2.)/nofBars), T2_posZ), LightGuide2LV, "LightGuide_T2", worldLV, false, 0, fCheckOverlaps);
      new G4PVPlacement(LG2_rot2,G4ThreeVector( -trigger2SizeX/2.-LG_height/2., -(nofBars-1)*((trigger2SizeY/2.)/nofBars)+2.*copyNo*((trigger2SizeY/2.)/nofBars), T2_posZ), LightGuide2LV, "LightGuide_T2", worldLV, false, 0, fCheckOverlaps);
    }
  //****************************************************************************************
  
  //****************************************************************************************
  // ALPIDE
  //Alpide container
  G4VSolid* AlpContS = new G4Box("AlpCont", (nofAlpideX/2.)*(2*alpideSizeX+alpideGap_X+2*RibsX)/2., (nofAlpideY*alpideSizeY+alpideGap_X)/2., (3*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2*alpideGap)/2.);
  G4LogicalVolume* AlpContLV = new G4LogicalVolume(AlpContS, defaultMaterial, "AlpTower");
  fAlpContPV = new G4PVPlacement(0, G4ThreeVector(0.,0.,axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+(3*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2*alpideGap)/2.), AlpContLV, "AlpCont", worldLV, false, 0, fCheckOverlaps);
  
  //Alpide tower
  G4VSolid* AlpTowerS = new G4Box("AlpTower", (2*alpideSizeX+alpideGap_X+2*RibsX)/2., (nofAlpideY*alpideSizeY+alpideGap_X)/2., (3.*CuSupportSizeZ+3*FPCSizeZ+3*ColdPlateSizeZ+3*alpideSizeZ+3.*ColdPlateSizeZ+2*alpideGap)/2.);
  G4LogicalVolume* AlpTowerLV = new G4LogicalVolume(AlpTowerS, defaultMaterial, "AlpTower");
  fAlpTowerPV = new G4PVReplica("AlpTower", AlpTowerLV, AlpContLV, kXAxis, nofAlpideX/2, (2*alpideSizeX+alpideGap_X+2*RibsX));
  
  //Alpide plane
  G4VSolid* AlpPlaneS = new G4Box("AlpPlane", (2*alpideSizeX)/2., (nofAlpideY*alpideSizeY)/2., (alpideSizeZ)/2.);
  G4LogicalVolume* AlpPlaneLV = new G4LogicalVolume(AlpPlaneS, defaultMaterial, "AlpPlane");  
  
  //Alpide half plane
  G4VSolid* AlpHPlaneS = new G4Box("AlpHPlane", alpideSizeX/2., nofAlpideY*alpideSizeY/2., alpideSizeZ/2.);
  G4LogicalVolume* AlpHPlaneLV = new G4LogicalVolume(AlpHPlaneS, defaultMaterial, "AlpHPlane");
  fAlpHPlanePV = new G4PVReplica("AlpHPlane", AlpHPlaneLV, AlpPlaneLV, kXAxis, 2, alpideSizeX);
  
  //Alpide sensor
  G4VSolid* AlpS = new G4Box("Alp", alpideSizeX/2., alpideSizeY/2., alpideSizeZ/2.);
  G4LogicalVolume* AlpLV = new G4LogicalVolume(AlpS, alpideMaterial, "Alp");
  fAlpPV = new G4PVReplica("Alp", AlpLV, AlpHPlaneLV, kYAxis, nofAlpideY, alpideSizeY);
  
  fAlpPlane1PV = new G4PVPlacement(0,G4ThreeVector(0., 0., -alpideGap-alpideSizeZ/2.), AlpPlaneLV, "AlpPlane1", AlpTowerLV, false, 0, fCheckOverlaps);
  fAlpPlane2PV = new G4PVPlacement(0,G4ThreeVector(0., 0., 0.), AlpPlaneLV, "AlpPlane2", AlpTowerLV, false, 0, fCheckOverlaps);
  fAlpPlane3PV = new G4PVPlacement(0,G4ThreeVector(0., 0., alpideGap+CuSupportSizeZ+FPCSizeZ+alpideSizeZ/2.), AlpPlaneLV, "AlpPlane3", AlpTowerLV, false, 0, fCheckOverlaps);
  
  //copper support
  G4VSolid* CuSupport_S = new G4Box("CuSupport", CuSupportSizeX/2., CuSupportSizeY/2., CuSupportSizeZ/2.);
  G4LogicalVolume* CuSupport_LV = new G4LogicalVolume(CuSupport_S, CopperMaterial, "CuSupport");
  fCuSupport1_PV = new G4PVPlacement(0,G4ThreeVector(0.,0.,-alpideGap-alpideSizeZ-FPCSizeZ-CuSupportSizeZ/2.), CuSupport_LV, "CuSupport1", AlpTowerLV, false, 0, fCheckOverlaps);
  fCuSupport2_PV = new G4PVPlacement(0,G4ThreeVector(0.,0.,-alpideSizeZ/2.-FPCSizeZ-CuSupportSizeZ/2.), CuSupport_LV, "CuSupport2", AlpTowerLV, false, 0, fCheckOverlaps);
  fCuSupport3_PV = new G4PVPlacement(0,G4ThreeVector(0.,0.,alpideGap+CuSupportSizeZ/2.), CuSupport_LV, "CuSupport3", AlpTowerLV, false, 0, fCheckOverlaps);
  
  //FPC
  G4VSolid* FPC_S = new G4Box("FPC", FPCSizeX/2., FPCSizeY/2., FPCSizeZ/2.);
  G4LogicalVolume* FPC_LV = new G4LogicalVolume(FPC_S, KaptonMaterial, "FPC");
  fFPC1_PV = new G4PVPlacement(0,G4ThreeVector(0.,0.,-alpideGap-alpideSizeZ-FPCSizeZ/2.), FPC_LV, "FPC1", AlpTowerLV, false, 0, fCheckOverlaps);
  fFPC2_PV = new G4PVPlacement(0,G4ThreeVector(0.,0.,-alpideSizeZ/2.-FPCSizeZ/2.), FPC_LV, "FPC2", AlpTowerLV, false, 0, fCheckOverlaps);
  fFPC3_PV = new G4PVPlacement(0,G4ThreeVector(0.,0.,alpideGap+CuSupportSizeZ+FPCSizeZ/2.), FPC_LV, "FPC3", AlpTowerLV, false, 0, fCheckOverlaps);
  
  //cold plate
  G4VSolid* ColdPlateS = new G4Box("ColdPlate", ColdPlateSizeX/2., ColdPlateSizeY/2., ColdPlateSizeZ/2.);
  G4LogicalVolume* ColdPlateLV = new G4LogicalVolume(ColdPlateS, CarbonFiberAlpideMaterial, "ColdPlate");
  fColdPlate1_PV = new G4PVPlacement(0,G4ThreeVector(0.,0.,-alpideGap+ColdPlateSizeZ/2.),ColdPlateLV,"ColdPlate1",AlpTowerLV, false, 0, fCheckOverlaps);
  fColdPlate2_PV = new G4PVPlacement(0,G4ThreeVector(0.,0.,alpideSizeZ/2.+ColdPlateSizeZ/2.),ColdPlateLV,"ColdPlate2",AlpTowerLV, false, 0, fCheckOverlaps);
  fColdPlate3_PV = new G4PVPlacement(0,G4ThreeVector(0.,0.,alpideGap+CuSupportSizeZ+FPCSizeZ+alpideSizeZ+ColdPlateSizeZ/2.),ColdPlateLV,"ColdPlate3",AlpTowerLV, false, 0, fCheckOverlaps);
  
  //ribs
  G4VSolid* RibsS = new G4Box("Ribs", RibsX/2., RibsY/2., RibsZ/2.);
  G4LogicalVolume* RibsLV = new G4LogicalVolume(RibsS, CarbonFiberAlpideMaterial, "Ribs");
  fRibs1_PV = new G4PVPlacement(0,G4ThreeVector(ColdPlateSizeX/2.+RibsX/2.,0.,alpideGap+CuSupportSizeZ+FPCSizeZ+alpideSizeZ+ColdPlateSizeZ-RibsZ/2.),RibsLV,"Ribs", AlpTowerLV, false, 0, fCheckOverlaps);
  fRibs2_PV = new G4PVPlacement(0,G4ThreeVector(-ColdPlateSizeX/2.-RibsX/2.,0.,alpideGap+CuSupportSizeZ+FPCSizeZ+alpideSizeZ+ColdPlateSizeZ-RibsZ/2.),RibsLV,"Ribs", AlpTowerLV, false, 0, fCheckOverlaps);
  fRibs3_PV = new G4PVPlacement(0,G4ThreeVector(ColdPlateSizeX/2.+RibsX/2.,0.,alpideSizeZ/2.+ColdPlateSizeZ-RibsZ/2.),RibsLV,"Ribs", AlpTowerLV, false, 0, fCheckOverlaps);
  fRibs4_PV = new G4PVPlacement(0,G4ThreeVector(-ColdPlateSizeX/2.-RibsX/2.,0.,alpideSizeZ/2.+ColdPlateSizeZ-RibsZ/2.),RibsLV,"Ribs", AlpTowerLV, false, 0, fCheckOverlaps);
  fRibs5_PV = new G4PVPlacement(0,G4ThreeVector(ColdPlateSizeX/2.+RibsX/2.,0.,-alpideGap+ColdPlateSizeZ-RibsZ/2.),RibsLV,"Ribs", AlpTowerLV, false, 0, fCheckOverlaps);
  fRibs6_PV = new G4PVPlacement(0,G4ThreeVector(-ColdPlateSizeX/2.-RibsX/2.,0.,-alpideGap+ColdPlateSizeZ-RibsZ/2.),RibsLV,"Ribs", AlpTowerLV, false, 0, fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  // VETO
  // Veto bottom
  G4VSolid* vetobS = new G4Box("Vetob", vetoSizeXY/2.+ext_dist, vetoSizeXY/2.+ext_dist, vetoThickness/2.);
  G4LogicalVolume* vetobLV = new G4LogicalVolume(vetobS, absorberMaterial, "Vetob");
  fVetobPV = new G4PVPlacement(0, G4ThreeVector(0,0,axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+2.*alpideGap+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+alp_dist+triggerGap+2.*triggerThickness+dist+caloThickness+layerThickness + 2.*crystalBarThickness + crystalGapZ + vetoThickness/2. + ext_dist+AlumPlane_Z), vetobLV, "Vetob", worldLV, false, 0, fCheckOverlaps);
  
  // Veto Lateral 1
  G4VSolid* vetol1S = new G4Box("Vetol1", vetoSizeXY/2.+2*ext_dist+vetoThickness, vetoThickness/2., (caloThickness+layerThickness + 2.*crystalBarThickness + crystalGapZ + AlumPlane_Z + vetoThickness + 2.*triggerThickness + dist + triggerGap + ext_dist+alp_dist+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2.*alpideGap+RibsZ)/2.);
  G4LogicalVolume* vetol1LV = new G4LogicalVolume(vetol1S, absorberMaterial, "Vetol1");
  fLveto1PV = new G4PVPlacement(0, G4ThreeVector(0, vetoSizeXY/2. + vetoThickness/2. + 2*ext_dist, axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+(caloThickness+layerThickness+dist+2.*triggerThickness+triggerGap+2.*crystalBarThickness+crystalGapZ+AlumPlane_Z+vetoThickness+ext_dist+alp_dist+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2.*alpideGap-RibsZ)/2.), vetol1LV, "Vetol1", worldLV, false, 0, fCheckOverlaps);
  
  // Veto Lateral 2
  G4VSolid* vetol2S = new G4Box("Vetol2", vetoSizeXY/2. + 2*ext_dist+vetoThickness, vetoThickness/2. , (caloThickness+layerThickness + 2.*crystalBarThickness + crystalGapZ + AlumPlane_Z + vetoThickness + 2.*triggerThickness + dist + triggerGap + ext_dist+alp_dist+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2.*alpideGap+RibsZ)/2.);
  G4LogicalVolume* vetol2LV = new G4LogicalVolume( vetol2S, absorberMaterial, "Vetol2");
  fLveto2PV = new G4PVPlacement(0, G4ThreeVector(0, -vetoSizeXY/2. - vetoThickness/2. - 2*ext_dist, axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+(caloThickness+layerThickness+dist+2.*triggerThickness+triggerGap+2.*crystalBarThickness+crystalGapZ+AlumPlane_Z+vetoThickness+ext_dist+alp_dist+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2.*alpideGap-RibsZ)/2.), vetol2LV, "Vetol2", worldLV, false, 0, fCheckOverlaps);
  
  // Veto Lateral 3
  G4VSolid* vetol3S = new G4Box("Vetol3", vetoThickness/2., vetoSizeXY/2.+ext_dist, (caloThickness+layerThickness + 2.*crystalBarThickness +crystalGapZ + AlumPlane_Z + vetoThickness + 2.*triggerThickness + dist + triggerGap + ext_dist+alp_dist+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2.*alpideGap+RibsZ)/2.);
  G4LogicalVolume* vetol3LV = new G4LogicalVolume(vetol3S,absorberMaterial,"Vetol3");
  fLveto3PV = new G4PVPlacement(0, G4ThreeVector(vetoSizeXY/2. + vetoThickness/2. + 2*ext_dist, 0, axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+(caloThickness+layerThickness+dist+2.*triggerThickness+triggerGap+2.*crystalBarThickness+crystalGapZ+AlumPlane_Z+vetoThickness+ext_dist+alp_dist+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2.*alpideGap-RibsZ)/2.), vetol3LV, "Vetol3", worldLV, false, 0, fCheckOverlaps);
  
  // Veto Lateral 4
  G4VSolid* vetol4S = new G4Box("Vetol4", vetoThickness/2., vetoSizeXY/2.+ext_dist, (caloThickness+layerThickness + 2.*crystalBarThickness+crystalGapZ + AlumPlane_Z + vetoThickness + 2.*triggerThickness + dist + triggerGap + ext_dist+alp_dist+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2.*alpideGap+RibsZ)/2.);
  G4LogicalVolume* vetol4LV = new G4LogicalVolume(vetol4S, absorberMaterial, "Vetol4");
  fLveto4PV = new G4PVPlacement(0, G4ThreeVector(-vetoSizeXY/2. - vetoThickness/2.-2*ext_dist, 0, axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+(caloThickness+layerThickness+dist+2.*triggerThickness+triggerGap+2.*crystalBarThickness+crystalGapZ+AlumPlane_Z+vetoThickness+ext_dist+alp_dist+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2.*alpideGap-RibsZ)/2.), vetol4LV, "Vetol4", worldLV, false, 0, fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  // BLANKET
  G4VSolid* BlanketS = new G4Box("Blanket", Blanket_X/2., Blanket_Y/2., Blanket_Z/2.);
  G4LogicalVolume* BlanketLV = new G4LogicalVolume(BlanketS, MylarMaterial, "Blanket");
  fBlanketPV = new G4PVPlacement(0,G4ThreeVector(0.,0.,axes+Blanket_Z/2.),BlanketLV,"Blanket",worldLV,false,0,fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  // EXTERNAL WINDOW
  // WindowOut
  G4VSolid* WindowOutS = new G4Box("WindowOut", window_X/2., window_Y/2., windowOut_Z/2.);
  G4LogicalVolume* WindowOutLV = new G4LogicalVolume(WindowOutS, KaptonMaterial, "WindowOut");
  fWindowOutPV = new G4PVPlacement(0,G4ThreeVector(0.,0.,axes+blanket_dist+Blanket_Z+windowOut_Z/2.),WindowOutLV,"WindowOut",worldLV,false,0,fCheckOverlaps);
  
  // WindowIn
  G4VSolid* WindowInS = new G4Box("WindowIn", window_X/2., window_Y/2., windowIn_Z/2.);
  G4LogicalVolume* WindowInLV = new G4LogicalVolume(WindowInS, CopperMaterial, "WindowIn");
  fWindowInPV = new G4PVPlacement(0,G4ThreeVector(0.,0.,axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z/2.),WindowInLV,"WindowIn",worldLV,false,0,fCheckOverlaps);
  
  //Wall
  G4ThreeVector transWallHole(WallHole_X,WallHole_Y,0.);
  G4SubtractionSolid* WallHoneyCombS = new G4SubtractionSolid("WallHoneyComb", new G4Box("WallHoneyComb_1",Wall_X/2., Wall_Y/2., WallHoneyComb_Z/2.), new G4Box("WallHoneyComb_2",window_X/2., window_Y/2., WallHole_Z/2.), 0, transWallHole);
  G4LogicalVolume* WallHoneyCombLV = new G4LogicalVolume(WallHoneyCombS, AlMaterial,"WallHoneyComb");
  fWallHoneyCombPV = new G4PVPlacement(0,G4ThreeVector(-WallHole_X,-WallHole_Y,axes+blanket_dist+Blanket_Z+windowOut_Z/2.),WallHoneyCombLV,"WallHoneyComb",worldLV,false,0,fCheckOverlaps);
  
  G4SubtractionSolid* WallExternalS = new G4SubtractionSolid("WallExternal", new G4Box("WallExternal_1",Wall_X/2., Wall_Y/2., WallExternal_Z/2.), new G4Box("WallExternal_2",window_X/2., window_Y/2., WallHole_Z/2.), 0, transWallHole);
  G4LogicalVolume* WallExternalLV = new G4LogicalVolume(WallExternalS, AlMaterial,"WallExternal");
  fWallExternalOutPV = new G4PVPlacement(0,G4ThreeVector(-WallHole_X,-WallHole_Y,axes+blanket_dist+Blanket_Z+windowOut_Z/2.-WallHoneyComb_Z/2.-WallExternal_Z/2.),WallExternalLV,"WallExternalOut",worldLV,false,0,fCheckOverlaps);
  fWallExternalInPV = new G4PVPlacement(0,G4ThreeVector(-WallHole_X,-WallHole_Y,axes+blanket_dist+Blanket_Z+windowOut_Z/2.+WallHoneyComb_Z/2.+WallExternal_Z/2.),WallExternalLV,"WallExternalIn",worldLV,false,0,fCheckOverlaps);
  //****************************************************************************************
  
  //****************************************************************************************
  // PMT
  G4VSolid* pmtS = new G4Tubs("Pmt", pmtInnerRadius, pmtOuterRadius, pmtHeight/2., pmtStartAngle, pmtSpanAngle);
  G4LogicalVolume* pmtLV = new G4LogicalVolume(pmtS, pmtMaterial, "Pmt");
  
  G4RotationMatrix* T1rm = new G4RotationMatrix();
  T1rm->set(0.*deg, 90.*deg, 0.*deg);
  G4RotationMatrix* T2rm = new G4RotationMatrix();
  T2rm->set(90.*deg, 90.*deg, 0.*deg);
  for(G4int copyNo=0; copyNo<nofBars; copyNo++){    
    new G4PVPlacement(T1rm, G4ThreeVector(-(nofBars-1)*((trigger1SizeX/2.)/nofBars)+2.*copyNo*((trigger1SizeX/2.)/nofBars), trigger1SizeY/2.+pmtHeight/2.+LG_height, T1_posZ), pmtLV,"PmtT1_1", worldLV, false, copyNo, fCheckOverlaps);
    new G4PVPlacement(T1rm, G4ThreeVector(-(nofBars-1)*((trigger1SizeX/2.)/nofBars)+2.*copyNo*((trigger1SizeX/2.)/nofBars),-trigger1SizeY/2.-pmtHeight/2.-LG_height,T1_posZ), pmtLV,"PmtT1_2", worldLV, false, copyNo, fCheckOverlaps);
    new G4PVPlacement(T2rm, G4ThreeVector(trigger2SizeX/2.+pmtHeight/2.+LG_height,-(nofBars-1)*((trigger2SizeY/2.)/nofBars)+2.*copyNo*((trigger2SizeY/2.)/nofBars),T2_posZ), pmtLV,"PmtT2_1", worldLV, false, copyNo, fCheckOverlaps);
    new G4PVPlacement(T2rm, G4ThreeVector(-trigger2SizeX/2.-pmtHeight/2.-LG_height,-(nofBars-1)*((trigger2SizeY/2.)/nofBars)+2.*copyNo*((trigger2SizeY/2.)/nofBars),T2_posZ), pmtLV,"PmtT2_2", worldLV, false, copyNo, fCheckOverlaps);
  }
  
  G4double scintx = caloSizeXY/2.-cutPlane/2.+pmtHeight/(2.*sqrt(2.));
  G4double scinty = caloSizeXY/2.-cutPlane/2.+pmtHeight/(2.*sqrt(2.));
  
  G4RotationMatrix* P1rm = new G4RotationMatrix();
  P1rm->set(45.*deg, 90.*deg, 0.*deg);
  G4RotationMatrix* P2rm = new G4RotationMatrix();
  P2rm->set(-45.*deg, 90.*deg, 0.*deg);
  
  new G4PVPlacement(P1rm, G4ThreeVector(-scintx,scinty,-planeGap/2.), pmtLV,"PmtP1_1", layer1LV, false, 0, fCheckOverlaps);
  new G4PVPlacement(P1rm, G4ThreeVector(scintx,-scinty,-planeGap/2.), pmtLV,"PmtP1_2", layer1LV, false, 1, fCheckOverlaps);
  new G4PVPlacement(P2rm, G4ThreeVector(scintx,scinty, -planeGap/2.), pmtLV,"PmtP2_1", layer2LV, false, 2, fCheckOverlaps);
  new G4PVPlacement(P2rm, G4ThreeVector(-scintx,-scinty, -planeGap/2.), pmtLV,"PmtP2_2", layer2LV, false, 3, fCheckOverlaps);
  
  new G4PVPlacement(P1rm, G4ThreeVector(-scintx,scinty,-planeGap/2.), pmtLV,"PmtLastP_1", lastlayerLV, false, 0, fCheckOverlaps);
  new G4PVPlacement(P1rm, G4ThreeVector(scintx,-scinty,-planeGap/2.), pmtLV,"PmtLastP_2", lastlayerLV, false, 1, fCheckOverlaps);
  
  G4RotationMatrix* L1rm = new G4RotationMatrix();
  L1rm->set(0.*deg, 90.*deg, 0.*deg);
  for(int copyNo1=0; copyNo1<nofCrystals; copyNo1++)
    {
      new G4PVPlacement(L1rm, G4ThreeVector(-crystalBarSizeX-crystalGap+copyNo1*(crystalBarSizeX+crystalGap),-crystalBarSizeY/2.-pmtHeight/2.,axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2.*alpideGap+alp_dist+2.*triggerThickness+triggerGap+dist+caloThickness+layerThickness+crystalBarThickness/2.+AlumPlane_Z), pmtLV,"PmtL", worldLV, false, fCheckOverlaps);
      new G4PVPlacement(L1rm, G4ThreeVector(-crystalBarSizeX-crystalGap+copyNo1*(crystalBarSizeX+crystalGap),crystalBarSizeY/2.+pmtHeight/2.,axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2.*alpideGap+alp_dist+2.*triggerThickness+triggerGap+dist+caloThickness+layerThickness+crystalBarThickness/2.+AlumPlane_Z), pmtLV,"PmtL", worldLV, false, fCheckOverlaps);
    }
  
  G4RotationMatrix* L2rm = new G4RotationMatrix();
  L2rm->set(90.*deg, 90.*deg, 0.*deg);
  for(int copyNo2=0; copyNo2<nofCrystals; copyNo2++)
    {
      new G4PVPlacement(L2rm, G4ThreeVector(-crystalBarSizeY/2.-pmtHeight/2.,-crystalBarSizeX-crystalGap+copyNo2*(crystalBarSizeX+crystalGap),axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2.*alpideGap+alp_dist+2.*triggerThickness+triggerGap+dist+caloThickness+layerThickness+3.*crystalBarThickness/2.+crystalGapZ+AlumPlane_Z), pmtLV,"PmtL", worldLV, false, fCheckOverlaps);
      new G4PVPlacement(L2rm, G4ThreeVector(crystalBarSizeY/2.+pmtHeight/2.,-crystalBarSizeX-crystalGap+copyNo2*(crystalBarSizeX+crystalGap),axes+blanket_dist+Blanket_Z+windowOut_Z+windowIn_Z+window_dist+3.*alpideSizeZ+3.*CuSupportSizeZ+3.*FPCSizeZ+3.*ColdPlateSizeZ+2.*alpideGap+alp_dist+2.*triggerThickness+triggerGap+dist+caloThickness+layerThickness+3.*crystalBarThickness/2.+crystalGapZ+AlumPlane_Z), pmtLV,"PmtL", worldLV, false, fCheckOverlaps);
    }
  
  
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
  
  MylarSurfaceMat_MPT->AddProperty("REFLECTIVITY",MylarSurfaceMat_ENERGY,MylarSurfaceMat_REFL,MylarSurfaceMat_num);
  MylarSurfaceMat_MPT->AddProperty("EFFICIENCY",MylarSurfaceMat_ENERGY,MylarSurfaceMat_EFF,MylarSurfaceMat_num);
  MylarSurfaceMat->SetMaterialPropertiesTable(MylarSurfaceMat_MPT);
  
  new G4LogicalSkinSurface("T1scintWrapping", bar1LV, MylarSurfaceMat);
  new G4LogicalSkinSurface("T2scintWrapping", bar2LV, MylarSurfaceMat);
  new G4LogicalSkinSurface("PscintWrapping", absorberLV, MylarSurfaceMat);
  new G4LogicalSkinSurface("V1scintWrapping", vetol1LV, MylarSurfaceMat);
  new G4LogicalSkinSurface("V2scintWrapping", vetol2LV, MylarSurfaceMat);
  new G4LogicalSkinSurface("V3scintWrapping", vetol3LV, MylarSurfaceMat);
  new G4LogicalSkinSurface("V4scintWrapping", vetol4LV, MylarSurfaceMat);
  new G4LogicalSkinSurface("VBscintWrapping", vetobLV, MylarSurfaceMat);
  new G4LogicalSkinSurface("LBar1scintWrapping", Cbar1LV, MylarSurfaceMat);
  new G4LogicalSkinSurface("LBar2scintWrapping", Cbar2LV, MylarSurfaceMat);
  //****************************************************************************************
  
  
  // VISUALIZATION ATTRIBUTES
  worldLV->SetVisAttributes (G4VisAttributes::Invisible);
  
  // Crystal
  G4VisAttributes* attBlue = new G4VisAttributes(G4Colour::Blue());
  attBlue->SetVisibility(true);
  attBlue->SetForceAuxEdgeVisible(true);
  Cbar1LV->SetVisAttributes(attBlue);
  Cbar2LV->SetVisAttributes(attBlue);
  
  //Trigger, calorimeter, veto
  G4VisAttributes* attGreen = new G4VisAttributes(G4Colour::Green());
  attGreen->SetVisibility(true);
  attGreen->SetForceAuxEdgeVisible(true);
  absorberLV->SetVisAttributes(attGreen);
  bar1LV->SetVisAttributes(attGreen);
  bar2LV->SetVisAttributes(attGreen);
  vetobLV->SetVisAttributes(attGreen);
  vetol1LV->SetVisAttributes(attGreen);
  vetol2LV->SetVisAttributes(attGreen);
  vetol3LV->SetVisAttributes(attGreen);
  vetol4LV->SetVisAttributes(attGreen);
  LightGuide1LV->SetVisAttributes(attGreen);
  LightGuide2LV->SetVisAttributes(attGreen);
  
  //carbon fiber
  G4VisAttributes* attBrown = new G4VisAttributes(G4Colour::Brown());
  attBrown->SetVisibility(true);
  attBrown->SetForceAuxEdgeVisible(true);
  Grk1LV->SetVisAttributes(attBrown);
  Grk2LV->SetVisAttributes(attBrown);
  CFplaneT1LV->SetVisAttributes(attBrown);
  CFplaneT2LV->SetVisAttributes(attBrown);
  gapLV->SetVisAttributes (attBrown);
  ColdPlateLV->SetVisAttributes(attBrown);
  RibsLV->SetVisAttributes(attBrown);
  
  //Alpide
  G4VisAttributes* attMagenta = new G4VisAttributes(G4Colour::Magenta());
  AlpLV->SetVisAttributes(attMagenta);
  
  //FPC
  G4VisAttributes* attBlack = new G4VisAttributes(G4Colour::Black());
  FPC_LV->SetVisAttributes(attBlack);
  
  //Window
  G4VisAttributes* attRed = new G4VisAttributes(G4Colour::Red());
  WindowOutLV->SetVisAttributes(attRed);
  WindowInLV->SetVisAttributes(attRed);
  
  //Cu supp
  CuSupport_LV->SetVisAttributes(attRed);
  
  //Wall
  WallHoneyCombLV->SetVisAttributes(attRed);
  WallExternalLV->SetVisAttributes(attRed);
  
  //Pmt
  G4VisAttributes* attGrey = new G4VisAttributes(G4Colour::Grey());
  pmtLV->SetVisAttributes (attGrey);
  AlumPlaneLV->SetVisAttributes (attGrey);
  BlanketLV->SetVisAttributes (attGrey);
  
  caloLV->SetVisAttributes (G4VisAttributes::Invisible);
  layer1LV->SetVisAttributes (G4VisAttributes::Invisible);
  layer2LV->SetVisAttributes (G4VisAttributes::Invisible);
  trigger1LV->SetVisAttributes (G4VisAttributes::Invisible);
  triggerCont1LV->SetVisAttributes (G4VisAttributes::Invisible);
  trigger2LV->SetVisAttributes (G4VisAttributes::Invisible);
  triggerCont2LV->SetVisAttributes (G4VisAttributes::Invisible);
  crystal1LV->SetVisAttributes (G4VisAttributes::Invisible);
  crystalCont1LV->SetVisAttributes (G4VisAttributes::Invisible);
  crystal2LV->SetVisAttributes (G4VisAttributes::Invisible);
  crystalCont2LV->SetVisAttributes (G4VisAttributes::Invisible);
  AlpContLV->SetVisAttributes (G4VisAttributes::Invisible);
  AlpTowerLV->SetVisAttributes (G4VisAttributes::Invisible);
  AlpPlaneLV->SetVisAttributes (G4VisAttributes::Invisible);
  AlpHPlaneLV->SetVisAttributes (G4VisAttributes::Invisible);

  return worldPV;
}


void HEPD2MCDetectorConstruction::ActivateOptics(G4bool optics)
{
  fOptics = optics;
}
