/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCPrimaryGeneratorAction.hh file   //
//                                         //
/////////////////////////////////////////////

#ifndef HEPD2MCPrimaryGeneratorAction_h
#define HEPD2MCPrimaryGeneratorAction_h 1

#include "HEPD2MCPrimaryGeneratorMessenger.hh"
#include "HEPD2MCDetectorConstruction.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class HEPD2MCPrimaryGeneratorMessenger;

class HEPD2MCPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  HEPD2MCPrimaryGeneratorAction();
  virtual ~HEPD2MCPrimaryGeneratorAction();
  
  virtual void GeneratePrimaries(G4Event* event);
  virtual void SetParticle(G4String part);
  virtual void SetEnergy(G4double energy);
  virtual void SetPoint(G4double X, G4double Y, G4double Z);
  virtual void SetPlanewave(G4double Xside, G4double Yside, G4double Zplane, G4double theta, G4double phi);
  virtual void SetRandom(G4double Xside, G4double Yside, G4double Zplane);
  virtual void SetPowEnergy(G4double Emin, G4double Emax, G4double gamma);
  
  // set methods
  void SetRandomFlag(G4bool value);
  
private:
  G4ParticleGun*  fParticleGun;
  HEPD2MCPrimaryGeneratorMessenger* fGunMessenger;
  
  G4bool point;
  G4bool planewave;
  G4bool random;
  G4bool powenergy;
  
  G4double fX, fY, fZ;
  G4double fXside, fYside, fZplane, fTheta, fPhi;
  G4double fEmin, fEmax, fgamma;
};

#endif
