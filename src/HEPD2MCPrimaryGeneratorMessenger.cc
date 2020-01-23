/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCPrimaryGeneratorMessenger.cc file//
//                                         //
/////////////////////////////////////////////

#include "HEPD2MCPrimaryGeneratorMessenger.hh"

#include "HEPD2MCPrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIparameter.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

HEPD2MCPrimaryGeneratorMessenger::HEPD2MCPrimaryGeneratorMessenger(HEPD2MCPrimaryGeneratorAction* Gun):fAction(Gun)
{
  
  fGunDir = new G4UIdirectory("/HEPD02/");
  fGunDir->SetGuidance("primary modes");
  
  fPartCmd = new G4UIcmdWithAString("/HEPD02/primary/particle",this);
  fPartCmd->SetGuidance("Set the particle type");
  fPartCmd->SetParameterName("Particle Type",false);
  fPartCmd->AvailableForStates(G4State_Idle);
  
  fEnerCmd = new G4UIcmdWithADoubleAndUnit("/HEPD02/primary/energy",this);
  fEnerCmd->SetGuidance("Set the particle energy");
  fEnerCmd->SetParameterName("Particle Energy",false);
  fEnerCmd->SetUnitCategory("Energy");
  fEnerCmd->AvailableForStates(G4State_Idle);
  
  G4UIparameter* parameter;
  
  fPointCmd = new G4UIcommand("/HEPD02/primary/point",this);
  fPointCmd->AvailableForStates(G4State_Idle);
  parameter = new G4UIparameter("X",'d',false);
  parameter->SetGuidance("X coordinate of generation point");
  fPointCmd->SetParameter(parameter);
  parameter = new G4UIparameter("Y",'d',false);
  parameter->SetGuidance("Y coordinate of generation point");
  fPointCmd->SetParameter(parameter);
  parameter = new G4UIparameter("Z",'d',false);
  parameter->SetGuidance("Z coordinate of generation point");
  fPointCmd->SetParameter(parameter);
  parameter = new G4UIparameter("unit",'s',false);
  parameter->SetGuidance("length unit");
  fPointCmd->SetParameter(parameter);
  
  fPlanewaveCmd = new G4UIcmdWithoutParameter("/HEPD02/primary/planewave",this);
  fPlanewaveCmd->AvailableForStates(G4State_Idle);
  parameter = new G4UIparameter("Xside",'d',false);
  parameter->SetGuidance("X side dimension");
  fPlanewaveCmd->SetParameter(parameter);
  parameter = new G4UIparameter("Yside",'d',false);
  parameter->SetGuidance("Y side dimension");
  fPlanewaveCmd->SetParameter(parameter);
  parameter = new G4UIparameter("Zplane",'d',false);
  parameter->SetGuidance("Z coordinate of generation plane");
  fPlanewaveCmd->SetParameter(parameter);
  parameter = new G4UIparameter("length_unit",'s',false);
  parameter->SetGuidance("length unit");
  fPlanewaveCmd->SetParameter(parameter);
  parameter = new G4UIparameter("theta",'d',false);
  parameter->SetGuidance("theta");
  fPlanewaveCmd->SetParameter(parameter);
  parameter = new G4UIparameter("phi",'d',false);
  parameter->SetGuidance("phi");
  fPlanewaveCmd->SetParameter(parameter);
  parameter = new G4UIparameter("angle_unit",'s',false);
  parameter->SetGuidance("angle unit");
  fPlanewaveCmd->SetParameter(parameter);
  
  fRandomCmd = new G4UIcmdWithoutParameter("/HEPD02/primary/random",this);
  fRandomCmd->AvailableForStates(G4State_Idle);
  parameter = new G4UIparameter("Xside",'d',false);
  parameter->SetGuidance("X side dimension");
  fRandomCmd->SetParameter(parameter);
  parameter = new G4UIparameter("Yside",'d',false);
  parameter->SetGuidance("Y side dimension");
  fRandomCmd->SetParameter(parameter);
  parameter = new G4UIparameter("Zplane",'d',false);
  parameter->SetGuidance("Z coordinate of generation plane");
  fRandomCmd->SetParameter(parameter);
  parameter = new G4UIparameter("length_unit",'s',false);
  parameter->SetGuidance("length unit");
  fRandomCmd->SetParameter(parameter);
  
  fPowEnergyCmd = new G4UIcmdWithoutParameter("/HEPD02/primary/powenergy",this);
  fPowEnergyCmd->AvailableForStates(G4State_Idle);
  parameter = new G4UIparameter("Emin",'d',false);
  parameter->SetGuidance("Minimum energy value");
  fPowEnergyCmd->SetParameter(parameter);
  parameter = new G4UIparameter("Emax",'d',false);
  parameter->SetGuidance("Maximum energy value");
  fPowEnergyCmd->SetParameter(parameter);
  parameter = new G4UIparameter("energy_unit",'s',false);
  parameter->SetGuidance("energy unit");
  fPowEnergyCmd->SetParameter(parameter);
  parameter = new G4UIparameter("gamma",'i',false);
  parameter->SetGuidance("index of power law");
  fPowEnergyCmd->SetParameter(parameter);  
}

HEPD2MCPrimaryGeneratorMessenger::~HEPD2MCPrimaryGeneratorMessenger()
{
  delete fPartCmd;
  delete fEnerCmd;
  delete fPointCmd;
  delete fPlanewaveCmd;
  delete fRandomCmd;
  delete fPowEnergyCmd;
}

void HEPD2MCPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if(command == fPartCmd)
    {
      fAction->SetParticle(newValue);
    }
  
  if(command == fEnerCmd)
    {
      fAction->SetEnergy(fEnerCmd->GetNewDoubleValue(newValue));
    }
  
  if(command == fPointCmd)
    {
      G4double X = 0.;
      G4double Y = 0.;
      G4double Z = 0.;
      G4String unit;
      std::istringstream is(newValue);
      is >> X >> Y >> Z >> unit;
      X*= G4UIcommand::ValueOf(unit);
      Y*= G4UIcommand::ValueOf(unit);
      Z*= G4UIcommand::ValueOf(unit);
      
      fAction->SetPoint(X, Y, Z);
    }
  
  if(command == fPlanewaveCmd)
    {
      G4double Xside = 0.;
      G4double Yside = 0.;
      G4double Zplane = 0.;
      G4String length_unit;
      G4double theta = 0.;
      G4double phi = 0.;
      G4String angle_unit;
      std::istringstream is(newValue);
      is >> Xside >> Yside >> Zplane >> length_unit >> theta >> phi >> angle_unit;
      Xside*= G4UIcommand::ValueOf(length_unit);
      Yside*= G4UIcommand::ValueOf(length_unit);
      Zplane*= G4UIcommand::ValueOf(length_unit);
      theta*= G4UIcommand::ValueOf(angle_unit);
      phi*= G4UIcommand::ValueOf(angle_unit);
      
      fAction->SetPlanewave(Xside, Yside, Zplane, theta, phi);
    }
  
  if(command == fRandomCmd)
    {
      G4double Xside = 0.;
      G4double Yside = 0.;
      G4double Zplane = 0.;
      G4String length_unit;
      std::istringstream is(newValue);
      is >> Xside >> Yside >> Zplane >> length_unit;
      Xside*= G4UIcommand::ValueOf(length_unit);
      Yside*= G4UIcommand::ValueOf(length_unit);
      Zplane*= G4UIcommand::ValueOf(length_unit);
      
      fAction->SetRandom(Xside, Yside, Zplane);
    }
  
  if(command == fPowEnergyCmd)
    {
      G4double Emin = 0.;
      G4double Emax = 0.;
      G4String energy_unit;
      G4int gamma = 0;
      std::istringstream is(newValue);
      is >> Emin >> Emax >> energy_unit >> gamma;
      Emin*= G4UIcommand::ValueOf(energy_unit);
      Emax*= G4UIcommand::ValueOf(energy_unit);
      
      fAction->SetPowEnergy(Emin, Emax, gamma);
    }
  
}
