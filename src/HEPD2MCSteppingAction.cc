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
  
  G4VPhysicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  
  //energy deposit
  G4double edep = step->GetTotalEnergyDeposit();
  
  //step length
  G4double stepLength = 0.;
  if ( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0.)
    {
      stepLength = step->GetStepLength();
    }
  
  //copyNumber for alpide (3 planes)
  G4int alpcopyNumber = 0;
  G4double X, Y, Z;
  if(volume->GetName()=="AlpActive1" || volume->GetName()=="AlpActive2")
    {
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "AlpPlane1") alpcopyNumber = 0;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "AlpPlane2") alpcopyNumber = 1;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "AlpPlane3") alpcopyNumber = 2;
      
      X = step->GetPreStepPoint()->GetPosition().getX();
      Y = step->GetPreStepPoint()->GetPosition().getY();
      Z = step->GetPreStepPoint()->GetPosition().getZ();
      fEventAction->AddAlp(edep,stepLength,alpcopyNumber, X, Y, Z);
    }
  
  //copyNumber for trigger bars
  G4int barcopyNumber;
  if(volume->GetName() == "Bar1")
    {
      barcopyNumber = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber(1);
      fEventAction->AddT1Bars(edep,stepLength,barcopyNumber);
    }
  if(volume->GetName() == "Bar2")
    {
      barcopyNumber = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber(1);
      fEventAction->AddT2Bars(edep,stepLength,barcopyNumber);
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
      
      fEventAction->AddPlane(edep,stepLength,planecopyNumber);
    }
  if(volume->GetName() == "Planesx")
    {
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx2_Block1") planecopyNumber = 1;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx2_Block2") planecopyNumber = 4;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx4_Block2") planecopyNumber = 6;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx1_Block3") planecopyNumber = 7;
      if(step->GetPreStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "PBoxsx3_Block3") planecopyNumber = 9;
      
      fEventAction->AddPlane(edep,stepLength,planecopyNumber);
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
  G4VPhysicalVolume* PostStepVolume = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
  
  if(PostStepVolume!=0 && (PostStepVolume->GetName() == "AlpActive1" || PostStepVolume->GetName() == "AlpActive2"))
    {
      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "AlpPlane1") alpcopyNumber = 0;
      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "AlpPlane2") alpcopyNumber = 1;
      if(step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetName() == "AlpPlane3") alpcopyNumber = 2;
      
      G4double theta = step->GetPreStepPoint()->GetMomentumDirection().getTheta();
      G4double phi = step->GetPreStepPoint()->GetMomentumDirection().getPhi();
      theta *= 180./3.14;
      phi *= 180./3.14;
      fEventAction->AddAlpMSC(alpcopyNumber, theta, phi);
    }
  
  //fraction of energy lost before entering in trigger
  if(PostStepVolume!=0 && PostStepVolume->GetName() == "Bar1" && (volume->GetName()=="T1Cont" || volume->GetName()=="WrappingAfterT1" || volume->GetName()=="WrappingBeforeT1" || volume->GetName()=="T1"))
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
  
  G4int VolumeCopyNumber;
  G4int pmtID;
  
  //if the photon is generated in scintillatorEJ200_Opt or LYSO_Opt,
  if(step->GetTrack()->GetParticleDefinition()->GetParticleName() == "opticalphoton" && (step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetMaterial()->GetName() == "ScintillatorEJ200_Opt" || step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetMaterial()->GetName() == "LYSO_Opt"))
    {
      //it's expressed in MeV so it must be converted in eV
      phot_energy = phot_energy*1.E6;
      if(step->GetPostStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName() == "Pmt")
	{
	  VolumeCopyNumber = step->GetPostStepPoint()->GetTouchableHandle()->GetHistory()->GetVolume(3)->GetCopyNo();
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "PmtT1_1") pmtID = 2*VolumeCopyNumber;
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "PmtT1_2") pmtID = 2*VolumeCopyNumber+1;
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "PmtT2_1") pmtID = 2*VolumeCopyNumber+10;
	  if(step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "PmtT2_2") pmtID = 2*VolumeCopyNumber+11;
	  
	  //if(name == "PmtP1_1" || name == "PmtP1_2" || name == "PmtP2_1" || name == "PmtP2_2") pmtID = 20+(planecopyNumber/2)*4+pmtCopyNumber;
	  //if(name == "PmtLastP_1" || name == "PmtLastP_2") pmtID = 20+(10/2)*4+pmtCopyNumber;
	  
	  //if(step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "PmtL1_1") pmtID = pmtCopyNumber+44;
	  //if(step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "PmtL1_2") pmtID = pmtCopyNumber+47;
	  //if(step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "PmtL2_1") pmtID = pmtCopyNumber+50;
	  //if(step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "PmtL2_2") pmtID = pmtCopyNumber+53;
	  
	  //... e pmt veto lat
	  //... e pmt veto bot
	  
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
