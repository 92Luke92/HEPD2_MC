

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

#include "HEPD2MCTrackerDimDB.hh" 

bool fCheckOverlaps=true;


void TrackerDims(){
    // Sensor
	TrackerDimDB::AddMeas("AlpideSizeX",30*mm);
	TrackerDimDB::AddMeas("AlpideSizeY",15*mm);
	TrackerDimDB::AddMeas("AlpideSizeZ",0.05*mm);
	TrackerDimDB::AddMeas("AlpideSizeActX",29.7*mm);
	TrackerDimDB::AddMeas("AlpideSizeActY",14.7*mm);
	TrackerDimDB::AddMeas("AlpideSizeActZ",0.05*mm);

	//Cold Plate
	TrackerDimDB::AddMeas("AlColdPlateSizeX",196*mm);
	TrackerDimDB::AddMeas("AlColdPlateSizeY",34.4*mm);
	TrackerDimDB::AddMeas("AlColdPlateSizeZ",7*mm);
	TrackerDimDB::AddMeas("AlColdPlateThick",0.4*mm);
	TrackerDimDB::AddMeas("AlColdPlateRib",  2*mm);

		// FPC 
	TrackerDimDB::AddMeas("AlFpcSizeX",190*mm);
	TrackerDimDB::AddMeas("AlFpcSizeY", 34*mm);
	TrackerDimDB::AddMeas("AlFpcPlasticZ",  0.14*mm);
	TrackerDimDB::AddMeas("AlCopperZ" ,  0.04*mm);
	TrackerDimDB::AddMeas("AlFpcGlueZ",  0.05*mm);

	TrackerDimDB::AddMeas("AlGapX",0.150*mm);
	TrackerDimDB::AddMeas("AlGapY",0.150*mm);
	TrackerDimDB::AddMeas("AlGlueZ",0.050*mm);

	// Stave Front Head
	TrackerDimDB::AddMeas("AlHeadF_B1_SizeX",13.5*mm);
	TrackerDimDB::AddMeas("AlHeadF_B1_SizeY",34.9*mm);
	TrackerDimDB::AddMeas("AlHeadF_B1_SizeZ",8.6*mm);

	TrackerDimDB::AddMeas("AlHeadF_B2_SizeX",7.5*mm);
	TrackerDimDB::AddMeas("AlHeadF_B2_SizeY",15*mm);
	TrackerDimDB::AddMeas("AlHeadF_B2_SizeZ",8.6*mm);

	TrackerDimDB::AddMeas("AlHeadF_B3_SizeX",3*mm);
	TrackerDimDB::AddMeas("AlHeadF_B3_SizeY",10*mm);
	TrackerDimDB::AddMeas("AlHeadF_B3_SizeZ",8.6*mm);

	TrackerDimDB::AddMeas("AlHeadF_B4_SizeX",7.5*mm);
	TrackerDimDB::AddMeas("AlHeadF_B4_SizeY",30.2*mm);

	TrackerDimDB::AddMeas("AlHeadF_B4_SizeZ",5.4*mm);


	// Stave Back Head
	TrackerDimDB::AddMeas("AlHeadB_B1_SizeX",11.*mm);
	TrackerDimDB::AddMeas("AlHeadB_B1_SizeY",34.9*mm);
	TrackerDimDB::AddMeas("AlHeadB_B1_SizeZ",8.6*mm);

	TrackerDimDB::AddMeas("AlHeadB_B2_SizeX",6.5*mm);
	TrackerDimDB::AddMeas("AlHeadB_B2_SizeY",30.2*mm);
	TrackerDimDB::AddMeas("AlHeadB_B2_SizeZ",7*mm);

}


G4LogicalVolume * GetAlSensorLV(){
	G4double AlpideSizeX=TrackerDimDB::GetMeas("AlpideSizeX");
	G4double AlpideSizeY=TrackerDimDB::GetMeas("AlpideSizeY");
	G4double AlpideSizeZ=TrackerDimDB::GetMeas("AlpideSizeZ");

    G4Material* alpideMaterial = G4Material::GetMaterial("G4_Si");

    //Alpide sensor
    G4VSolid* AlpideS = new G4Box("Alpide", AlpideSizeX/2., AlpideSizeY/2., AlpideSizeZ/2.);
    G4LogicalVolume* AlpideLV = new G4LogicalVolume(AlpideS, alpideMaterial, "Alpide");

	// Active 
	G4double AlpideSizeActX=TrackerDimDB::GetMeas("AlpideSizeActX");
	G4double AlpideSizeActY=TrackerDimDB::GetMeas("AlpideSizeActY");
	G4double AlpideSizeActZ=TrackerDimDB::GetMeas("AlpideSizeActZ");



    //Alpide sensor
    G4VSolid* AlpActiveS = new G4Box("AlpActiveS", AlpideSizeActX/2., AlpideSizeActY/2., AlpideSizeActZ/2.);
    G4LogicalVolume* AlpActiveLV = new G4LogicalVolume(AlpActiveS, alpideMaterial, "AlpActiveLV");

	new G4PVPlacement(0,G4ThreeVector(),AlpActiveLV, "AlpActive",AlpideLV, false, 0, fCheckOverlaps);


    // Visibility
    G4VisAttributes* attYellow = new G4VisAttributes(G4Colour::Yellow());
    attYellow->SetVisibility(true);
    // attYellow->SetForceAuxEdgeVisible(true);
    AlpideLV->SetVisAttributes(attYellow);





    return AlpideLV;
}

G4LogicalVolume* GetAlColdPlateLV(){

	G4Material *CarbonFiberAlpideMaterial =G4Material::GetMaterial("CarbonFiberAlpide");
 
	G4double AlColdPlateSizeX=TrackerDimDB::GetMeas("AlColdPlateSizeX");
	G4double AlColdPlateSizeY=TrackerDimDB::GetMeas("AlColdPlateSizeY");
	G4double AlColdPlateSizeZ=TrackerDimDB::GetMeas("AlColdPlateSizeZ");
	G4double AlColdPlateThick=TrackerDimDB::GetMeas("AlColdPlateThick");
	G4double AlColdPlateRib  =TrackerDimDB::GetMeas("AlColdPlateRib");
   
   	G4VSolid* box1=new G4Box("AlColdPlate_full",AlColdPlateSizeX/2.,AlColdPlateSizeY/2.,AlColdPlateSizeZ/2.);

  	G4VSolid* box2=new G4Box("AlColdPlate_hole",AlColdPlateSizeX/2.,(AlColdPlateSizeY-2*AlColdPlateRib)/2.,(AlColdPlateSizeZ-AlColdPlateThick)/2.);

  	G4VSolid* AlColdPlateS=new G4SubtractionSolid("AlColdPlateS",box1,box2,0,
  		G4ThreeVector(0,0,-AlColdPlateThick/2.-0.02));

  	G4LogicalVolume* AlColdPlateLV= new G4LogicalVolume(AlColdPlateS,CarbonFiberAlpideMaterial, "AlColdPlate");

    // Visibility
    G4VisAttributes* attMagenta = new G4VisAttributes(G4Colour::Magenta());
    attMagenta->SetVisibility(true);
    //attMagenta->SetForceAuxEdgeVisible(true);
    AlColdPlateLV->SetVisAttributes(attMagenta);


  	return AlColdPlateLV;
}


G4LogicalVolume* GetAlFpcLV(){
	

	G4double AlCopperZ=TrackerDimDB::GetMeas("AlCopperZ");
	G4double AlFpcGlueZ=TrackerDimDB::GetMeas("AlFpcGlueZ");
	G4double AlFpcPlasticZ=TrackerDimDB::GetMeas("AlFpcPlasticZ");

	G4double AlFpcSizeX=TrackerDimDB::GetMeas("AlFpcSizeX");
	G4double AlFpcSizeY=TrackerDimDB::GetMeas("AlFpcSizeY");
	G4double AlFpcSizeZ=AlCopperZ+AlFpcGlueZ+AlFpcPlasticZ;


	G4Material * KaptonMaterial=G4Material::GetMaterial("G4_KAPTON");
	G4Material * CopperMaterial=G4Material::GetMaterial("G4_Cu");
	G4Material * GlueMaterial  = G4Material::GetMaterial("GlueMaterial");

	G4VSolid* FpcPlasticS= new G4Box("FpcPlasticS",AlFpcSizeX/2.,AlFpcSizeY/2.,AlFpcPlasticZ/2.);
	G4LogicalVolume * FpcPlasticLV= new G4LogicalVolume(FpcPlasticS,KaptonMaterial,"FPC_P");
	
	G4VSolid* FpcCopperS= new G4Box("FpcCopperS",AlFpcSizeX/2.,AlFpcSizeY/2.,AlCopperZ/2);
	G4LogicalVolume * FpcCopperLV= new G4LogicalVolume(FpcCopperS,CopperMaterial,"FPC_C");

	G4VSolid* FpcGlueS= new G4Box("FpcGlueS",AlFpcSizeX/2.,AlFpcSizeY/2.,AlFpcGlueZ/2);
	G4LogicalVolume * FpcGlueLV= new G4LogicalVolume(FpcGlueS,GlueMaterial,"FPC_G");

	G4VSolid* FpcS= new G4Box("FpcS",AlFpcSizeX/2.,AlFpcSizeY/2.,(AlFpcSizeZ+AlCopperZ+AlFpcGlueZ)/2);

	G4LogicalVolume* FpcLV=  new G4LogicalVolume(FpcS,G4Material::GetMaterial("G4_Galactic"),"FPC");

	// Stack is from below: Glue Copper Plastic
	// GLUE
	new G4PVPlacement(0,G4ThreeVector(0,0,+(-AlFpcSizeZ+AlFpcGlueZ)/2),
			FpcGlueLV,"FPCGlue",FpcLV,false,0,fCheckOverlaps);
	// Copper
	new G4PVPlacement(0,G4ThreeVector(0,0,-AlFpcSizeZ/2.+AlFpcGlueZ+AlCopperZ/2.),
			FpcCopperLV,"FPCCopper",FpcLV,false,0,fCheckOverlaps);
	
	// Plastic
	new G4PVPlacement(0,G4ThreeVector(0,0,-AlFpcSizeZ/2.+(AlCopperZ+AlFpcGlueZ)+AlFpcPlasticZ/2),
			FpcPlasticLV,"FPCPlastic",FpcLV,false,0,fCheckOverlaps);
	
    // Visibility
    //  G4VisAttributes* attGreen = new G4VisAttributes(G4Colour::Green());
    // attGreen->SetVisibility(true);
    //  attGreen->SetForceAuxEdgeVisible(true);
	FpcPlasticLV->SetVisAttributes(G4Color::Green());
	FpcCopperLV->SetVisAttributes(G4Color::Red());
	FpcGlueLV->SetVisAttributes(G4Color::Magenta());
    FpcLV->SetVisAttributes(G4VisAttributes::Invisible);

	return FpcLV;
}


G4LogicalVolume* GetAlSensorStaveLV(){

	G4LogicalVolume* Sensor=GetAlSensorLV();

	G4double sensX=((G4Box*)(Sensor->GetSolid()))->GetXHalfLength()*2;
	G4double sensY=((G4Box*)(Sensor->GetSolid()))->GetYHalfLength()*2;
	G4double sensZ=((G4Box*)(Sensor->GetSolid()))->GetZHalfLength()*2;

	G4double AlGapX=TrackerDimDB::GetMeas("AlGapX");
	G4double AlGapY=TrackerDimDB::GetMeas("AlGapY");


	G4double GlueZ=TrackerDimDB::GetMeas("AlGlueZ");

	G4VSolid* AlSensorStaveS= new G4Box("AlSensorStaveS",(5.*sensX+4*AlGapX)/2.,(2.*sensY+AlGapY)/2.,(sensZ+GlueZ)/2.);

	G4LogicalVolume* AlSensorStaveLV= new G4LogicalVolume(AlSensorStaveS,G4Material::GetMaterial("G4_Galactic"),"AlSensorStave");

	G4VSolid* AlSensorStaveGlueS= new G4Box("AlSensorStaveGlueS",(5*sensX+4*AlGapX)/2.,(2*sensY+AlGapY)/2.,(GlueZ)/2.);
	G4LogicalVolume* AlSensorStaveGlueLV= new G4LogicalVolume(AlSensorStaveGlueS,G4Material::GetMaterial("GlueMaterial"),"AlSensorStaveGlue");


	for (int jj=0;jj<2;jj++)
		for(int ii=0;ii<5;ii++){
			int sig=(jj==0)?-1:1;
			new G4PVPlacement(0,G4ThreeVector(
											(ii-2)*(sensX+AlGapX),
											sig*(sensY/2+AlGapY/2),
											GlueZ/2),
				Sensor,"AlSensorStave",AlSensorStaveLV,false,ii+jj*5,fCheckOverlaps);

		}


    new G4PVPlacement(0,G4ThreeVector(0,0,-sensZ/2),
    					AlSensorStaveGlueLV,"AlSensorStave",AlSensorStaveLV,false,0,fCheckOverlaps);

 	AlSensorStaveLV->SetVisAttributes(G4VisAttributes::Invisible);
    return AlSensorStaveLV;

}



G4LogicalVolume* GetAlStaveHeadFLV(){

	G4double AlHeadF_B1_SizeX=TrackerDimDB::GetMeas("AlHeadF_B1_SizeX");
	G4double AlHeadF_B1_SizeY=TrackerDimDB::GetMeas("AlHeadF_B1_SizeY");
	G4double AlHeadF_B1_SizeZ=TrackerDimDB::GetMeas("AlHeadF_B1_SizeZ");

	G4VSolid * AlHeadF_B1S= new G4Box("AlHeadF_B1S",AlHeadF_B1_SizeX/2.,AlHeadF_B1_SizeY/2.,AlHeadF_B1_SizeZ/2.);

	G4double AlHeadF_B2_SizeX=TrackerDimDB::GetMeas("AlHeadF_B2_SizeX");
	G4double AlHeadF_B2_SizeY=TrackerDimDB::GetMeas("AlHeadF_B2_SizeY");
	G4double AlHeadF_B2_SizeZ=TrackerDimDB::GetMeas("AlHeadF_B2_SizeZ")+0.02;

	G4VSolid * AlHeadF_B2S= new G4Box("AlHeadF_B2S",AlHeadF_B2_SizeX/2.,AlHeadF_B2_SizeY/2.,AlHeadF_B2_SizeZ/2.);



	G4double AlHeadF_B3_SizeX=TrackerDimDB::GetMeas("AlHeadF_B3_SizeX");
	G4double AlHeadF_B3_SizeY=TrackerDimDB::GetMeas("AlHeadF_B3_SizeY");
	G4double AlHeadF_B3_SizeZ=TrackerDimDB::GetMeas("AlHeadF_B3_SizeZ")+0.02;

	G4VSolid * AlHeadF_B3S= new G4Box("AlHeadF_B3S",AlHeadF_B3_SizeX/2.,AlHeadF_B3_SizeY/2.,AlHeadF_B3_SizeZ/2.);

	G4double AlHeadF_B4_SizeX=TrackerDimDB::GetMeas("AlHeadF_B4_SizeX");
	G4double AlHeadF_B4_SizeY=TrackerDimDB::GetMeas("AlHeadF_B4_SizeY");
	G4double AlHeadF_B4_SizeZ=TrackerDimDB::GetMeas("AlHeadF_B4_SizeZ");
	G4VSolid * AlHeadF_B4S= new G4Box("AlHeadF_B4S",AlHeadF_B4_SizeX/2.,AlHeadF_B4_SizeY/2.,AlHeadF_B4_SizeZ/2.);


	G4VSolid* AlHeadF_C1= new G4SubtractionSolid("AlC1",AlHeadF_B1S,AlHeadF_B2S,0,G4ThreeVector((AlHeadF_B1_SizeX- AlHeadF_B2_SizeX)/2.,0,0.));

	G4VSolid* AlHeadF_C2= new G4SubtractionSolid("AlC2",AlHeadF_C1,AlHeadF_B3S,0,G4ThreeVector(AlHeadF_B1_SizeX/2-AlHeadF_B2_SizeX-AlHeadF_B3_SizeX/2.,0,0));

	G4VSolid *AlStaveHeadFS= new G4UnionSolid("AlStaveHeadFS",AlHeadF_C2,AlHeadF_B4S,0,G4ThreeVector(-AlHeadF_B1_SizeX/2-AlHeadF_B4_SizeX/2.,0,0));


	G4LogicalVolume* AlStaveHeadFLV= new G4LogicalVolume(AlStaveHeadFS,G4Material::GetMaterial("AlMixMaterial"),"AlStaveHeadFLV");
	//G4LogicalVolume* AlStaveHeadFLV= new G4LogicalVolume(AlHeadF_B1S,G4Material::GetMaterial("AlMixMaterial"),"AlStaveHeadFLV");

    // Visibility
    G4VisAttributes* attGray = new G4VisAttributes(G4Colour::Gray());
    attGray->SetVisibility(true);
    //  attGray->SetForceAuxEdgeVisible(true);
    AlStaveHeadFLV->SetVisAttributes(attGray);
	return AlStaveHeadFLV;
}

G4LogicalVolume* GetAlStaveHeadBLV(){

	G4double AlHeadB_B1_SizeX=TrackerDimDB::GetMeas("AlHeadB_B1_SizeX");
	G4double AlHeadB_B1_SizeY=TrackerDimDB::GetMeas("AlHeadB_B1_SizeY");
	G4double AlHeadB_B1_SizeZ=TrackerDimDB::GetMeas("AlHeadB_B1_SizeZ");


	G4VSolid * AlHeadB_B1S= new G4Box("AlHeadF_B1S",AlHeadB_B1_SizeX/2.,AlHeadB_B1_SizeY/2.,AlHeadB_B1_SizeZ/2.);

	G4double AlHeadB_B2_SizeX=TrackerDimDB::GetMeas("AlHeadB_B2_SizeX");
	G4double AlHeadB_B2_SizeY=TrackerDimDB::GetMeas("AlHeadB_B2_SizeY");
	G4double AlHeadB_B2_SizeZ=TrackerDimDB::GetMeas("AlHeadB_B2_SizeZ");

	G4VSolid * AlHeadB_B2S= new G4Box("AlHeadF_B2S",AlHeadB_B2_SizeX/2.,AlHeadB_B2_SizeY/2.,AlHeadB_B2_SizeZ/2.);
	
	G4VSolid *AlStaveHeadBS= new G4UnionSolid("AlStaveHeadBS",AlHeadB_B1S,AlHeadB_B2S,0,G4ThreeVector(-AlHeadB_B1_SizeX/2-AlHeadB_B2_SizeX/2.,0,-(AlHeadB_B1_SizeZ/2-AlHeadB_B2_SizeZ/2)));


	G4LogicalVolume* AlStaveHeadBLV= new G4LogicalVolume(AlStaveHeadBS,G4Material::GetMaterial("AlMixMaterial"),"AlStaveHeadBLV");

    // Visibility
    G4VisAttributes* attGray = new G4VisAttributes(G4Colour::Grey());
    attGray->SetVisibility(true);
    //  attGray->SetForceAuxEdgeVisible(true);
    AlStaveHeadBLV->SetVisAttributes(attGray);

	return AlStaveHeadBLV;
}






G4LogicalVolume* GetAlStaveContLV(){

	
	G4double AlStaveContX=TrackerDimDB::GetMeas("AlHeadF_B1_SizeX")+TrackerDimDB::GetMeas("AlHeadB_B1_SizeX")+TrackerDimDB::GetMeas("AlColdPlateSizeX");
	G4double AlStaveContY=TrackerDimDB::GetMeas("AlHeadB_B1_SizeY");
	G4double AlStaveContZ=TrackerDimDB::GetMeas("AlHeadB_B1_SizeZ");


	G4VSolid * AlStaveContS   = new G4Box("AlStaveContS",AlStaveContX/2,AlStaveContY/2,AlStaveContZ/2);
	
	G4LogicalVolume * AlStaveContLV  = new G4LogicalVolume(AlStaveContS,G4Material::GetMaterial("G4_Galactic"),"AlStaveContLV");


	G4LogicalVolume* AlColdPlateLV= GetAlColdPlateLV();
	G4LogicalVolume* AlStaveHeadFLV= GetAlStaveHeadFLV();
	G4LogicalVolume* AlStaveHeadBLV= GetAlStaveHeadBLV();


	// Head Front
	G4RotationMatrix* FHR=new G4RotationMatrix();
	FHR->rotateY(M_PI*rad);
 	new G4PVPlacement(G4Transform3D(*FHR,G4ThreeVector(-AlStaveContX/2.+TrackerDimDB::GetMeas("AlHeadF_B1_SizeX")/2.,0,0)),
	 					  AlStaveHeadFLV,"AlStaveHeadFPV",AlStaveContLV,false,0,fCheckOverlaps);

	// Head Back
 	new G4PVPlacement(0,G4ThreeVector(+AlStaveContX/2.-TrackerDimDB::GetMeas("AlHeadB_B1_SizeX")/2.,0,0),
 					  AlStaveHeadBLV,"AlStaveHeadBPV",AlStaveContLV,false,0,fCheckOverlaps);


	// Cold Plate
	G4double OffColdX=-AlStaveContX/2+TrackerDimDB::GetMeas("AlHeadF_B1_SizeX");
	G4double OffColdZ=TrackerDimDB::GetMeas("AlHeadF_B4_SizeZ")/2.-(TrackerDimDB::GetMeas("AlColdPlateSizeZ")/2 - TrackerDimDB::GetMeas("AlColdPlateThick"))+0.022;

	
	new G4PVPlacement(0,G4ThreeVector(OffColdX+TrackerDimDB::GetMeas("AlColdPlateSizeX")/2.,0,OffColdZ),
					AlColdPlateLV,"AlStaveColdPlatePV",AlStaveContLV,false,0,fCheckOverlaps);


	// Sensors
	G4LogicalVolume* AlSensorStaveLV= GetAlSensorStaveLV();
	
	G4double OffSensZ=OffColdZ+TrackerDimDB::GetMeas("AlColdPlateSizeZ")/2+((G4Box*)AlSensorStaveLV->GetSolid())->GetZHalfLength();
	G4double OffSensX=10*mm;


	

		new G4PVPlacement(0,G4ThreeVector(OffSensX,0,OffSensZ),AlSensorStaveLV,"AlSensorsPV",AlStaveContLV,false,0,fCheckOverlaps);


	// FPC
	G4LogicalVolume* AlFpcLV=GetAlFpcLV();

	G4double OffFpcZ= OffSensZ +((G4Box*)AlSensorStaveLV->GetSolid())->GetZHalfLength()+ ((G4Box*)AlFpcLV->GetSolid())->GetZHalfLength();
	
	G4double OffFpcX=OffColdX+(((G4Box*)AlFpcLV->GetSolid())->GetXHalfLength())+
	(TrackerDimDB::GetMeas("AlColdPlateSizeX")/2-((G4Box*)AlFpcLV->GetSolid())->GetXHalfLength());

	new G4PVPlacement(0,G4ThreeVector(OffFpcX,0,OffFpcZ),AlFpcLV,"AlFpcPV",AlStaveContLV,false,0,fCheckOverlaps);


    AlStaveContLV->SetVisAttributes(G4VisAttributes::Invisible);
	return AlStaveContLV;

}


G4LogicalVolume * GetAlTowerLV(){

	G4LogicalVolume* staveLV= GetAlStaveContLV();

	G4double SX= ((G4Box*)staveLV->GetSolid())->GetXHalfLength();
	G4double SY= ((G4Box*)staveLV->GetSolid())->GetYHalfLength();
	G4double SZ= ((G4Box*)staveLV->GetSolid())->GetZHalfLength();

	G4VSolid * AlTowerS= new G4Box("AlTowerS",SX,SY,3*SZ);
	G4LogicalVolume * AlTowerLV= new G4LogicalVolume(AlTowerS,G4Material::GetMaterial("G4_Galactic"),"AlTowerLV");

	new G4PVPlacement(0,G4ThreeVector(0,0,-2*SZ),staveLV,"AlStaveCont0",AlTowerLV,false,0,fCheckOverlaps);
	new G4PVPlacement(0,G4ThreeVector(0,0,    0),staveLV,"AlStaveCont1",AlTowerLV,false,1,fCheckOverlaps);
	new G4PVPlacement(0,G4ThreeVector(0,0,+2*SZ),staveLV,"AlStaveCont2",AlTowerLV,false,2,fCheckOverlaps);

	AlTowerLV->SetVisAttributes(G4VisAttributes::Invisible);
	return AlTowerLV;

}

G4LogicalVolume * GetAlTracker(){

	TrackerDims();

	G4LogicalVolume* AlTowerLV= GetAlTowerLV();

	G4double SX= ((G4Box*)AlTowerLV->GetSolid())->GetXHalfLength();
	G4double SY= ((G4Box*)AlTowerLV->GetSolid())->GetYHalfLength();
	G4double SZ= ((G4Box*)AlTowerLV->GetSolid())->GetZHalfLength();
	G4double Gap= 0.1;

	G4VSolid * AlTrackerS= new G4Box("AlTrackerS",SX,SY*5+4*Gap,SZ);

       

	G4LogicalVolume *AlTrackerLV= new G4LogicalVolume(AlTrackerS,G4Material::GetMaterial("G4_Galactic"),"AlTrackerLV");

	new G4PVPlacement(0,G4ThreeVector(0,-(2*SY+Gap)*2,0),AlTowerLV,"AlTower0",AlTrackerLV,false,0,fCheckOverlaps);
	new G4PVPlacement(0,G4ThreeVector(0,-(2*SY+Gap)*1,0),AlTowerLV,"AlTower1",AlTrackerLV,false,1,fCheckOverlaps);
	new G4PVPlacement(0,G4ThreeVector(0,+(2*SY+Gap)*0,0),AlTowerLV,"AlTower2",AlTrackerLV,false,2,fCheckOverlaps);
	new G4PVPlacement(0,G4ThreeVector(0,+(2*SY+Gap)*1,0),AlTowerLV,"AlTower3",AlTrackerLV,false,3,fCheckOverlaps);
	new G4PVPlacement(0,G4ThreeVector(0,+(2*SY+Gap)*2,0),AlTowerLV,"AlTower4",AlTrackerLV,false,4,fCheckOverlaps);

	AlTrackerLV->SetVisAttributes(G4VisAttributes::Invisible);
	return AlTrackerLV;


}











