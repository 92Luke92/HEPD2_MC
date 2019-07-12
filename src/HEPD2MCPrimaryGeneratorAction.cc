/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCPrimaryGeneratorAction.cc file   //
//                                         //
/////////////////////////////////////////////

#include "HEPD2MCPrimaryGeneratorAction.hh"
#include "HEPD2MCPrimaryGeneratorMessenger.hh"
#include "HEPD2MCDetConst.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

HEPD2MCPrimaryGeneratorAction::HEPD2MCPrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction(),
    fParticleGun(0)
{
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);
  
  point = false;
  planewave = false;
  random = false;
  powenergy = false;
  
  // default particle kinematic
  G4ParticleDefinition* particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(50.*MeV);
  
  fGunMessenger = new HEPD2MCPrimaryGeneratorMessenger(this);
}

HEPD2MCPrimaryGeneratorAction::~HEPD2MCPrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fGunMessenger;
}

void HEPD2MCPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //energy
  if(powenergy)
    {
      G4double energy;
      if(fgamma==0.) energy = G4RandFlat::shoot(fEmin, fEmax);
      G4double alpha = 1. + fgamma;
      if(alpha==0.) {energy = exp(log(fEmin)+G4RandFlat::shoot(0., 1.)*(log(fEmax)-log(fEmin)));}
      else
	{
	  if(fEmin==0.) fEmin = 1.E-10;
	  energy = pow((G4RandFlat::shoot(0., 1.)*(pow(fEmax, alpha)-pow(fEmin, alpha))+pow(fEmin, alpha)),1./alpha);
	}
      fParticleGun->SetParticleEnergy(energy);
    }
  
  
  //position & direction
  //point generates primary in fixed point with fixed direction
  //you can set the point in mac
  if(point)
    {
      fParticleGun->SetParticlePosition(G4ThreeVector(fX, fY, fZ));
      G4ThreeVector direction = G4ThreeVector(0.,0.,1.);
      fParticleGun->SetParticleMomentumDirection(direction.unit());
    }
  
  //planewave generates primary in random point with fixed direction
  //you can set X side, Y side, Z coordinate of plane, theta and phi in mac
  if(planewave)
    {
      fParticleGun->SetParticlePosition(G4ThreeVector(-fXside/2.+fXside*G4RandFlat::shoot(), -fYside/2.+fYside*G4RandFlat::shoot(),fZplane));
      
      G4ThreeVector direction = G4ThreeVector(cos(fPhi)*sin(fTheta),sin(fPhi)*sin(fTheta),cos(fTheta));
      fParticleGun->SetParticleMomentumDirection(direction.unit());
    }
  
  //random generates primary in random point with random direction
  //you can set X side, Y side, Z coordinate of plane
  if(random)
    {
      fParticleGun->SetParticlePosition(G4ThreeVector(-fXside/2.+fXside*G4RandFlat::shoot(), -fYside/2.+fYside*G4RandFlat::shoot(),fZplane));
      
      G4double costheta, theta, phi;
      phi = 2*CLHEP::pi*G4RandFlat::shoot();
      costheta = std::sqrt(G4RandFlat::shoot());
      theta = std::acos(costheta);
      G4ThreeVector direction = G4ThreeVector(cos(phi)*sin(theta),sin(phi)*sin(theta),cos(theta));
      fParticleGun->SetParticleMomentumDirection(direction.unit());
    }
  
  fParticleGun->GeneratePrimaryVertex(anEvent);
  
}

void HEPD2MCPrimaryGeneratorAction::SetParticle(G4String part)
{
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = part;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);
}

void HEPD2MCPrimaryGeneratorAction::SetEnergy(G4double energy)
{
  fParticleGun->SetParticleEnergy(energy);
}

void HEPD2MCPrimaryGeneratorAction::SetPoint(G4double X, G4double Y, G4double Z)
{
  point = true;
  fX = X;
  fY = Y;
  fZ = Z;
}

void HEPD2MCPrimaryGeneratorAction::SetPlanewave(G4double Xside, G4double Yside, G4double Zplane, G4double theta, G4double phi)
{
  planewave = true;
  fXside = Xside;
  fYside = Yside;
  fZplane = Zplane;
  fTheta = theta;
  fPhi = phi;
}

void HEPD2MCPrimaryGeneratorAction::SetRandom(G4double Xside, G4double Yside, G4double Zplane)
{
  random = true;
  fXside = Xside;
  fYside = Yside;
  fZplane = Zplane;
}

void HEPD2MCPrimaryGeneratorAction::SetPowEnergy(G4double Emin, G4double Emax, G4double gamma)
{
  powenergy = true;
  fEmin = Emin;
  fEmax = Emax;
  fgamma = gamma;
}
