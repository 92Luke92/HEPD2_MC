/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCSteppingAction.cc file           //
//                                         //
/////////////////////////////////////////////

#include "HEPD2MCSteppingAction.hh"
#include "HEPD2MCEventAction.hh"
#include "HEPD2MCDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

HEPD2MCSteppingAction::HEPD2MCSteppingAction(const HEPD2MCDetectorConstruction* detectorConstruction, HEPD2MCEventAction* eventAction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction)
{
}

HEPD2MCSteppingAction::~HEPD2MCSteppingAction()
{
}

void HEPD2MCSteppingAction::UserSteppingAction(const G4Step* step)
{
  
  G4VPhysicalVolume * volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  G4VPhysicalVolume *PreStepVolume = volume;
  G4VPhysicalVolume *PostStepVolume = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
  
  G4StepPoint* pre=step->GetPreStepPoint();
  G4StepPoint* post=step->GetPostStepPoint();
   //energy deposit
  G4double edep = step->GetTotalEnergyDeposit();
// printf("Previous: %20s Pos: X:%+7.3f   Y: %+7.3f  Z: %+7.3f\n",volume->GetName().c_str(),pre->GetPosition()[0],pre->GetPosition()[1],pre->GetPosition()[2]);
// printf("Post    : %20s Pos: X:%+7.3f   Y: %+7.3f  Z: %+7.3f\n",PostStepVolume->GetName().c_str(),post->GetPosition()[0],post->GetPosition()[1],post->GetPosition()[2]);
// printf("Length  : %7.3f Edep: %7.3f P[0]: %7.4f P[1]: %7.4f P[2]: %7.4f\n",
//  	 step->GetStepLength(),edep,
// 	 step->GetDeltaMomentum()[0],
//      step->GetDeltaMomentum()[1],
//      step->GetDeltaMomentum()[2]);
   //step length
  G4double stepLength = 0.;
  if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
    {
      stepLength = step->GetStepLength();
    }

	if (PostStepVolume!=0 && PostStepVolume->GetName() == "Blanket" && volume->GetName() != "Blanket")
	{
		G4double X = step->GetPreStepPoint()->GetPosition().getX();
		G4double Y = step->GetPreStepPoint()->GetPosition().getY();
		G4double Z = step->GetPreStepPoint()->GetPosition().getZ();
		G4double theta = step->GetPreStepPoint()->GetMomentumDirection().getTheta();
		G4double phi = step->GetPreStepPoint()->GetMomentumDirection().getPhi();
		theta *= 180. / 3.14;
		phi *= 180. / 3.14;
		fEventAction->AddWin(X,Y,Z,theta,phi);
  }

  //copyNumber for alpide (3 planes)
  G4int alpcopyNumber = 0;
  G4double X, Y, Z;
  //  if(volume->GetName()=="AlpActive1" || volume->GetName()=="AlpActive2")
  if (volume->GetName() == "AlpActive")
  {
	  alpcopyNumber=-1;
	 int depth = step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetDepth();
	  if (step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(depth - 3)->GetName() == "AlStaveCont0")
		  alpcopyNumber = 0;
	  else if (step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(depth - 3)->GetName() == "AlStaveCont1")
		  alpcopyNumber = 1;
	  else if (step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(depth - 3)->GetName() == "AlStaveCont2")
		  alpcopyNumber = 2;

	  X = step->GetPreStepPoint()->GetPosition().getX();
	  Y = step->GetPreStepPoint()->GetPosition().getY();
	  Z = step->GetPreStepPoint()->GetPosition().getZ();
	  fEventAction->AddAlp(edep, stepLength, alpcopyNumber, X, Y, Z);
  }


  //copyNumber for trigger bars
  G4int barcopyNumber;
  if(volume->GetName() == "Bar1")
    {
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T1_1") barcopyNumber = 0;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T1_2") barcopyNumber = 1;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T1_3") barcopyNumber = 2;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T1_4") barcopyNumber = 3;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T1_5") barcopyNumber = 4;
      X = step->GetPreStepPoint()->GetPosition().getX();
	  Y = step->GetPreStepPoint()->GetPosition().getY();
      fEventAction->AddT1Bars(X,Y,edep,stepLength,barcopyNumber);
    }
  if(volume->GetName() == "Bar2")
    {
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T2_1") barcopyNumber = 0;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T2_2") barcopyNumber = 1;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T2_3") barcopyNumber = 2;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T2_4") barcopyNumber = 3;
      X = step->GetPreStepPoint()->GetPosition().getX();
	  Y = step->GetPreStepPoint()->GetPosition().getY();
	  fEventAction->AddT2Bars(X,Y,edep,stepLength,barcopyNumber);
    }
  
  //copyNumber for calo planes
  G4int planecopyNumber;
  if(volume->GetName() == "Planedx")
    {
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxdx1_Block1") planecopyNumber = 0;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxdx3_Block1") planecopyNumber = 2;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxdx1_Block2") planecopyNumber = 3;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxdx3_Block2") planecopyNumber = 5;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxdx2_Block3") planecopyNumber = 8;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxdx4_Block3") planecopyNumber = 10;
      X = step->GetPreStepPoint()->GetPosition().getX();
	  Y = step->GetPreStepPoint()->GetPosition().getY();
      fEventAction->AddPlane(X,Y,edep,stepLength,planecopyNumber);
    }
  if(volume->GetName() == "Planesx")
    {
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx2_Block1") planecopyNumber = 1;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx2_Block2") planecopyNumber = 4;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx4_Block2") planecopyNumber = 6;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx1_Block3") planecopyNumber = 7;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx3_Block3") planecopyNumber = 9;
      X = step->GetPreStepPoint()->GetPosition().getX();
	  Y = step->GetPreStepPoint()->GetPosition().getY();
      fEventAction->AddPlane(X,Y,edep,stepLength,planecopyNumber);
    }
  
  //copyNumber for crystals
  G4int crystalcopyNumber;
  if(volume->GetName() == "Crystal1")
    {
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "BarCont1_1") crystalcopyNumber = 0;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "BarCont2_1") crystalcopyNumber = 1;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "BarCont3_1") crystalcopyNumber = 2;
      
      fEventAction->AddC1Bars(edep,stepLength,crystalcopyNumber);
    }
  if(volume->GetName() == "Crystal2")
    {
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "BarCont1_2") crystalcopyNumber = 0;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "BarCont2_2") crystalcopyNumber = 1;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "BarCont3_2") crystalcopyNumber = 2;
      
      fEventAction->AddC2Bars(edep,stepLength,crystalcopyNumber);
    }
  
  //copyNumber for lateral veto
  G4int VetocopyNumber = 0;
  if(volume->GetName()=="VetoLat")
    {
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(1)->GetName() == "VetoLatContainer1") VetocopyNumber = 0;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(1)->GetName() == "VetoLatContainer2") VetocopyNumber = 1;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(1)->GetName() == "VetoLatContainer3") VetocopyNumber = 2;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(1)->GetName() == "VetoLatContainer4") VetocopyNumber = 3;
      
      fEventAction->AddLatVeto(edep,stepLength, VetocopyNumber);
    }
  
  //Bottom veto
  if(volume->GetName() == "Vetob")
    {
      fEventAction->AddBotVeto(edep,stepLength);
    }
  
  //multiple scattering


  if (PostStepVolume != 0 && (PreStepVolume->GetName() == "AlStaveColdPlatePV") && (PostStepVolume->GetName() != "AlStaveColdPlatePV"))
  {
//g	  printf("POSTPRE  %s %s\n", PreStepVolume->GetName().c_str(), PostStepVolume->GetName().c_str() );
	  int depth = step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetDepth();
	  if (step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(depth-1)->GetName() == "AlStaveCont0")
		  alpcopyNumber = 0;
	  if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(depth-1)->GetName() == "AlStaveCont1")
	   	alpcopyNumber = 1;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(depth-1)->GetName() == "AlStaveCont2") 
	  	alpcopyNumber = 2;
      
      G4double theta = step->GetPostStepPoint()->GetMomentumDirection().getTheta();
      G4double phi = step->GetPostStepPoint()->GetMomentumDirection().getPhi();
      theta *= 180./3.14;
      phi *= 180./3.14;
      fEventAction->AddAlpMSC(alpcopyNumber, theta, phi);
    }

	if (PostStepVolume != 0 && (PreStepVolume->GetName() != "FPCPlastic") && (PostStepVolume->GetName() == "FPCPlastic"))
	{
		int depth = step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetDepth();
		if (step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(depth-2)->GetName() == "AlStaveCont0")
			alpcopyNumber = 0;
		if (step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(depth-2)->GetName() == "AlStaveCont1")
			alpcopyNumber = 1;
		if (step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(depth-2)->GetName() == "AlStaveCont2")
			alpcopyNumber = 2;
		//printf("PREPOST  %s %s  %s %d\n", PreStepVolume->GetName().c_str(), PostStepVolume->GetName().c_str(),
			//    step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(depth-2)->GetName().c_str(),
			// 	   alpcopyNumber);

		G4double theta = step->GetPreStepPoint()->GetMomentumDirection().getTheta();
		G4double phi = step->GetPreStepPoint()->GetMomentumDirection().getPhi();
		theta *= 180. / 3.14;
		phi *= 180. / 3.14;
		fEventAction->AddAlpMSCPre(alpcopyNumber, theta, phi);
	}

	if(PostStepVolume != 0 && PreStepVolume->GetName() != "T1Cont" && PostStepVolume->GetName() == "T1Cont"){
		G4double theta = step->GetPreStepPoint()->GetMomentumDirection().getTheta();
		G4double phi = step->GetPreStepPoint()->GetMomentumDirection().getPhi();
		theta *= 180. / 3.14;
		phi *= 180. / 3.14;
		fEventAction->AddT1Pre( theta, phi);
	}

	if(PostStepVolume != 0 && PreStepVolume->GetName() == "T1Cont" && PostStepVolume->GetName() != "T1Cont"){
		G4double theta = step->GetPreStepPoint()->GetMomentumDirection().getTheta();
		G4double phi = step->GetPreStepPoint()->GetMomentumDirection().getPhi();
		theta *= 180. / 3.14;
		phi *= 180. / 3.14;
		fEventAction->AddT1Post( theta, phi);
	}


	//fraction of energy lost before entering in trigger
	if (PostStepVolume != 0 && PostStepVolume->GetName() == "Bar1" && (volume->GetName() == "T1Cont" || volume->GetName() == "WrappingAfterT1" || volume->GetName() == "WrappingBeforeT1" || volume->GetName() == "T1"))
    {
      fEventAction->AddEBeforeT1(step->GetPreStepPoint()->GetKineticEnergy());
    }
  
  if(PostStepVolume!=0 && PostStepVolume->GetName() == "Bar2" && (volume->GetName()=="T2Cont" || volume->GetName()=="WrappingAfterT2" || volume->GetName()=="WrappingBeforeT2" || volume->GetName()=="T2"))
    {
      fEventAction->AddEBeforeT2(step->GetPreStepPoint()->GetKineticEnergy());
    }
  
  if(PostStepVolume!=0 && PostStepVolume->GetName()=="Planedx" && (volume->GetName() == "PdxWrapping1" || volume->GetName() == "PdxWrapping2"))
    {
      fEventAction->AddEBeforeP1(step->GetPreStepPoint()->GetKineticEnergy());
    }
  
  //Bremsstrahlung gamma generated by e- 
  if(step->GetTrack()->GetParticleDefinition()->GetParticleName() == "gamma" && volume->GetName() == "World" && step->GetTrack()->GetNextVolume() == 0)
    {
      fEventAction->AddGammaKin(step->GetPreStepPoint()->GetKineticEnergy());
    }
  
  //optical photons collection
  G4double phot_energy = step->GetTrack()->GetKineticEnergy();
  
  //NUMBERS from R9880-210 datasheet
  const G4int number = 121;
  G4double ph_energy[number] = {1.692, 1.695, 1.698, 1.701, 1.704,
				1.710, 1.716, 1.725, 1.728, 1.732,
				1.741, 1.744, 1.751, 1.757, 1.764,
				1.767, 1.777, 1.780, 1.784, 1.790,
				1.801, 1.807, 1.811, 1.821, 1.825,
				1.828, 1.835, 1.839, 1.846, 1.850,
				1.860, 1.883, 1.890, 1.901, 1.909,
				1.921, 1.928, 1.936, 1.948, 1.956,
				1.976, 1.993, 2.006, 2.018, 2.036,
				2.053, 2.076, 2.094, 2.113, 2.127,
				2.146, 2.180, 2.211, 2.232, 2.258,
				2.280, 2.302, 2.324, 2.342, 2.359,
				2.365, 2.383, 2.389, 2.401, 2.431,
				2.450, 2.476, 2.508, 2.542, 2.562,
				2.583, 2.612, 2.648, 2.678, 2.708,
				2.740, 2.796, 2.846, 2.890, 2.943,
				2.999, 3.067, 3.138, 3.223, 3.290,
				3.383, 3.470, 3.547, 3.628, 3.743,
				3.818, 3.912, 3.994, 4.045, 4.115,
				4.188, 4.263, 4.321, 4.361, 4.442,
				4.527, 4.571, 4.637, 4.683, 4.730,
				4.801, 4.826, 4.900, 4.951, 4.977,
				5.030, 5.057, 5.111, 5.139, 5.195,
				5.223, 5.252, 5.281, 5.311, 5.371,
				5.402};
  
  G4double pmt_qe[number] ={0.00, 0.00, 0.00, 0.00, 0.00,
			    0.00, 0.00, 0.00, 0.00, 0.00,
			    0.00, 0.00, 0.00, 0.00, 0.00,
			    0.01, 0.01, 0.01, 0.01, 0.01,
			    0.01, 0.01, 0.01, 0.01, 0.01,
			    0.01, 0.02, 0.02, 0.02, 0.02,
			    0.02, 0.02, 0.02, 0.03, 0.03,
			    0.03, 0.04, 0.04, 0.04, 0.04,
			    0.05, 0.05, 0.05, 0.06, 0.06,
			    0.07, 0.07, 0.08, 0.08, 0.09,
			    0.09, 0.10, 0.10, 0.11, 0.12,
			    0.13, 0.13, 0.15, 0.16, 0.17,
			    0.18, 0.19, 0.21, 0.22, 0.24,
			    0.25, 0.26, 0.27, 0.28, 0.29,
			    0.29, 0.30, 0.32, 0.33, 0.34,
			    0.36, 0.37, 0.37, 0.38, 0.39,
			    0.40, 0.40, 0.41, 0.41, 0.41,
			    0.42, 0.42, 0.42, 0.42, 0.41,
			    0.40, 0.39, 0.37, 0.35, 0.34,
			    0.32, 0.30, 0.29, 0.27, 0.26,
			    0.24, 0.22, 0.21, 0.20, 0.18,
			    0.17, 0.16, 0.14, 0.13, 0.12,
			    0.11, 0.10, 0.09, 0.08, 0.07,
			    0.06, 0.06, 0.05, 0.05, 0.04,
			    0.03};
  
  G4int pmtID;
  
  //if the photon is generated in scintillatorEJ200_Opt or LYSO_Opt,
  if(step->GetTrack()->GetParticleDefinition()->GetParticleName() == "opticalphoton" && (step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetMaterial()->GetName() == "ScintillatorEJ200_Opt" || step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetMaterial()->GetName() == "LYSO_Opt"))
    {
      
      //it's expressed in MeV so it must be converted in eV
      phot_energy = phot_energy*1.E6;
      if(step->GetPostStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName() == "Pmt")
	{
	  G4String name = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
	  
	  //PMT trigger T1
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "triggerCont1")
	    {
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T1_1")
		{
		  if(name == "PmtT1_1") pmtID = 0;
		  if(name == "PmtT1_2") pmtID = 1;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T1_2")
		{
		  if(name == "PmtT1_1") pmtID = 2;
		  if(name == "PmtT1_2") pmtID = 3;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T1_3")
		{
		  if(name == "PmtT1_1") pmtID = 4;
		  if(name == "PmtT1_2") pmtID = 5;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T1_4")
		{
		  if(name == "PmtT1_1") pmtID = 6;
		  if(name == "PmtT1_2") pmtID = 7;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T1_5")
		{
		  if(name == "PmtT1_1") pmtID = 8;
		  if(name == "PmtT1_2") pmtID = 9;
		}
	    }
	  
	  //PMT trigger T2
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "triggerCont2")
	    {
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T2_1")
		{
		  if(name == "PmtT2_1") pmtID = 10;
		  if(name == "PmtT2_2") pmtID = 11;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T2_2")
		{
		  if(name == "PmtT2_1") pmtID = 12;
		  if(name == "PmtT2_2") pmtID = 13;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T2_3")
		{
		  if(name == "PmtT2_1") pmtID = 14;
		  if(name == "PmtT2_2") pmtID = 15;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "T2_4")
		{
		  if(name == "PmtT2_1") pmtID = 16;
		  if(name == "PmtT2_2") pmtID = 17;
		}
	    }
	  
	  //PMT calorimeter block1
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "Calorimeter_Block1")
	    {
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxdx1_Block1")
		{
		  if(name == "PmtPdx_1") pmtID = 18;
		  if(name == "PmtPdx_2") pmtID = 19;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx2_Block1")
		{
		  if(name == "PmtPsx_1") pmtID = 20;
		  if(name == "PmtPsx_2") pmtID = 21;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxdx3_Block1")
		{
		  if(name == "PmtPdx_1") pmtID = 22;
		  if(name == "PmtPdx_2") pmtID = 23;
		}
	    }
	  
	  //PMT calorimeter block2
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "Calorimeter_Block2")
	    {
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxdx1_Block2")
		{
		  if(name == "PmtPdx_1") pmtID = 24;
		  if(name == "PmtPdx_2") pmtID = 25;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx2_Block2")
		{
		  if(name == "PmtPsx_1") pmtID = 26;
		  if(name == "PmtPsx_2") pmtID = 27;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxdx3_Block2")
		{
		  if(name == "PmtPdx_1") pmtID = 28;
		  if(name == "PmtPdx_2") pmtID = 29;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx4_Block2")
		{
		  if(name == "PmtPsx_1") pmtID = 30;
		  if(name == "PmtPsx_2") pmtID = 31;
		}
	    }
	  
	  //PMT calorimeter block3
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "Calorimeter_Block3")
	    {
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx1_Block3")
		{
		  if(name == "PmtPsx_1") pmtID = 32;
		  if(name == "PmtPsx_2") pmtID = 33;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxdx2_Block3")
		{
		  if(name == "PmtPdx_1") pmtID = 34;
		  if(name == "PmtPdx_2") pmtID = 35;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx3_Block3")
		{
		  if(name == "PmtPsx_1") pmtID = 36;
		  if(name == "PmtPsx_2") pmtID = 37;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxdx4_Block3")
		{
		  if(name == "PmtPdx_1") pmtID = 38;
		  if(name == "PmtPdx_2") pmtID = 39;
		}
	    }
	  
	  //PMT crystal L1
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(1)->GetName() == "CrystalCont1")
	    {
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "BarCont1_1")
		{
		  if(name == "PmtL1_1") pmtID = 40;
		  if(name == "PmtL1_2") pmtID = 41;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "BarCont2_1")
		{
		  if(name == "PmtL1_1") pmtID = 42;
		  if(name == "PmtL1_2") pmtID = 43;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "BarCont3_1")
		{
		  if(name == "PmtL1_1") pmtID = 44;
		  if(name == "PmtL1_2") pmtID = 45;
		}
	    }
	  
	  //PMT crystal L2
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(1)->GetName() == "CrystalCont2")
	    {
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "BarCont1_2")
		{
		  if(name == "PmtL2_1") pmtID = 46;
		  if(name == "PmtL2_2") pmtID = 47;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "BarCont2_2")
		{
		  if(name == "PmtL2_1") pmtID = 48;
		  if(name == "PmtL2_2") pmtID = 49;
		}
	      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(2)->GetName() == "BarCont3_2")
		{
		  if(name == "PmtL2_1") pmtID = 50;
		  if(name == "PmtL2_2") pmtID = 51;
		}
	    }
	  
	  //PMT Lat Veto
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(1)->GetName() == "VetoLatContainer1")
	    {
	      if(name == "PmtVLat_1") pmtID = 52;
	      if(name == "PmtVLat_2") pmtID = 53;
	    }
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(1)->GetName() == "VetoLatContainer2")
	    {
	      if(name == "PmtVLat_1") pmtID = 54;
	      if(name == "PmtVLat_2") pmtID = 55;
	    }
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(1)->GetName() == "VetoLatContainer3")
	    {
	      if(name == "PmtVLat_1") pmtID = 56;
	      if(name == "PmtVLat_2") pmtID = 57;
	    }
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(1)->GetName() == "VetoLatContainer4")
	    {
	      if(name == "PmtVLat_1") pmtID = 58;
	      if(name == "PmtVLat_2") pmtID = 59;
	    }
	  
	  //PMT Bot Veto
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(1)->GetName() == "VetoBotCont")
	    {
	      if(name == "PmtVBot_1") pmtID = 60;
	      if(name == "PmtVBot_2") pmtID = 61;
	    }
	  
	  G4double prob;
	  for(int i=0; i<number; i++)
	    {
	      prob = rand() % 101;  //random number between 0 and 100
	      prob = prob/100.;
	      
	      if((phot_energy > ph_energy[i] && phot_energy < ph_energy[i+1]) && prob < pmt_qe[i]+(pmt_qe[i+1]-pmt_qe[i])/(ph_energy[i+1]-ph_energy[i])*(phot_energy-ph_energy[i]))
		{
		  fEventAction->AddPhot(pmtID);
		  fEventAction->AddPhotEnergy(pmtID,phot_energy);
		}
	    }
	}
    }
}
