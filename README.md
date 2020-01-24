# HEPD2_MC
Last changes on 24/01/2020

Monte Carlo Geant4 software of experiment HEPD-02

This software is a Monte Carlo Geant4 simulation of experiment HEPD-02. Geant version is Geant4.10.01 (patch-03)

To compile and install HEPD2_MC:

create a build directory

cmake ../

make

To execute HEPD2_MC in visualization mode:

./HEPD2_MC

> /control/execute <mac file>

To execute HEPD2_MC in batch mode from macro files (without visualization)

./HEPD2_MC -m <mac file>

*******************
*  GEOMETRY       *
*******************

The detector is composed of

(1) 1 plastic scintillator plane, segmented in 5 bars;

(2) 3 planes of ALPIDE tracker (with mechanical supports);

(3) 1 plastic scintillator plane, segmented in 4 bars perpendicularly allineated to the previous one;

(4) a calorimeter of 12 plastic scintillator planes;

(5) 2 planes of LYSO crystal, each segmented in 3 bars perpendicularly allineated;

(6) a veto system composed by plastic scintillator planes surrounds the calorimeter and the crystals.

The simulation includes also the satellite thermal blanket and the box window in front of the tracker.

The geometry is instantiated in HEPD2MCDetectorConstruction class; there is the possibility of modify geometry via the G4 build-in commands (HEPD2MCDetectorMessenger class); the geometry parameters are listed in include/HEPD2MCDetConst.hh.


*******************
*  PHYSICS LIST   *
*******************

The physics lists used in the simulation are instantiated in HEPD2MCPhysicsList class.
They are:

(1)  Electromagnetic processes: gamma conversion, Compton scattering and photoelectric effect for gammas; multiple scattering, ionisation and Bremsstrahlung for electrons, positrons and muons; annihilation for positrons; pair production for muons;

(2)  Elastic hadronic model: G4HadronElasticPhysics and G4IonElasticPhysics;

(3)  Inelastic hadronic model: G4HadronPhysicsShielding and G4IonQMDPhysics;

(4)  Optical physics: Cerenkov, scintillation, absorption, Rayleigh and Mie scattering, optical buondary processes, Birks saturation.


************************
*  PRIMARY GENERATOR   *
************************

It is possible to set the particle features of the primary generator in HEPD2MCPrimaryGeneratorAction class or via the G4 build-in commands (HEPD2MCPrimaryGeneratorMessenger class).
The following commands are available:

(1) /HEPD02/ActivateOptics <bool> enables or disables the scintillating materials in the detector (it only works in vis mode);

(2) /HEPD02/primary/particle <string> sets the particle type to be generated;

(3) /HEPD02/primary/energy <double> <string> sets the value and unit of measure of the particle fixed energy to be generated;

(4) /HEPD02/primary/powenergy <double> <double> <string> <int> sets the minimum and maximum value, the unit of measure and the spetral index of the particle energy spectrum to be generated;

(5) /HEPD02/primary/point <double> <double> <double> <string> (fixed point with fixed direction) sets the X, Y and Z coordinates and unit of measure of the particle point to be generated;

(6) /HEPD02/primary/planewave <double> <double> <double> <string> <double> <double> <string> (random point from a plane rectangle with fixed direction) sets the X and Y maximum coordinates, Z coordinate and unit of measure of the plane, the theta and phi angle and unit of measure of the particle position and direction to be generated;

(7) /HEPD02/primary/random <double> <double> <double> <string> (random point from a plane rectangle with random direction) sets the X and Y coordinates, Z coordinate and unit of measure of the plane of the particle to be generated;

************************
*  DETECTOR RESPONSE   *
************************

The energy deposit, track length and other informations of particles are recorded on an event and stored in a ROOT file. Energies are expressed in MeV, distances and coordinates are expressed in mm.
At the end of the simulation, the ROOT file includes a TTree "HEPD2", which is composed by several branches:

"particleid"	  Int_t       	       stores the particle ID classified using Geant4 particle numbering scheme;

"energy"	  Double_t	       stores the primary particle energy;

"gen[3]"	  vector<double>       stores the primary particle position;

"theta"	  	  Double_t	       stores the primary particle theta angle;

"phi"		  Double_t	       stores the primary particle phi angle;

"p[3]"		  vector<double>       stores the primary particle momentum;

"Alp1Edep"	  Double_t	       stores the energy deposit in the 1st ALPIDE plane;

"Alp2Edep"	  Double_t	       stores the energy deposit in the 2nd ALPIDE plane;

"Alp3Edep"	  Double_t	       stores the energy deposit in the 3rd ALPIDE plane;

"Alp1Pos[3]"	  vector<double>       stores the particle incident position on the 1st ALPIDE plane;

"Alp2Pos[3]"	  vector<double>       stores the particle incident position on the 2nd ALPIDE plane;

"Alp3Pos[3]"	  vector<double>       stores the particle incident position on the 3rd ALPIDE plane;

"Alp1Dir[3]"	  vector<double>       stores the particle incident direction on the 1st ALPIDE plane;

"Alp2Dir[3]"	  vector<double>       stores the particle incident direction on the 2nd ALPIDE plane;

"Alp3Dir[3]"	  vector<double>       stores the particle incident direction on the 3rd ALPIDE plane;

"T1Edep[5]"	  vector<double>       stores the energy deposit in the 1st trigger plane (5 bars);

"T2Edep[5]"	  vector<double>       stores the energy deposit in the 2nd trigger plane (5 bars);

"TRIGEdep"	  Double_t	       stores the energy deposit in the 2 trigger planes overall;

"PEdep[12]"	  vector<double>       stores the energy deposit in the calorimeter planes (12 planes);

"TOWEREdep"	  Double_t	       stores the energy deposit in the calorimeter planes overall;

"L1Edep[3]"	  vector<double>       stores the energy deposit in the 1st crystal plane (3 bars);

"L2Edep[3]"	  vector<double>       stores the energy deposit in the 2nd crystal plane (3 bars);

"LYSOEdep"	  Double_t	       stores the energy deposit in the 2 crystal planes overall;

"CALOEdep"	  Double_t	       stores the energy deposit in the 2 trigger planes, in the calorimeter planes and in the 2 crystal planes overall;

"VEdep[5]"	  vector<double>       stores the energy deposit in the veto planes (5 planes);

"phot[64]"	  vector<int>	       stores the number of optical photons registered (that is, entered and passed quantum efficiency) by the 64 PMTs;

"Alp1Leng"	  Double_t	       stores the track length in the 1st ALPIDE plane;

"Alp2Leng"	  Double_t	       stores the track length in the 2nd ALPIDE plane;

"Alp3Leng"	  Double_t	       stores the track length in the 3rd ALPIDE plane;

"T1Leng[5]"	  vector<double>       stores the track length in the 1st trigger plane (5 bars);

"T2Leng[5]"	  vector<double>       stores the track length in the 2nd trigger plane (5 bars);

"PLeng[12]"	  vector<double>       stores the track length in the calorimeter planes (12 planes);

"L1Leng[3]"	  vector<double>       stores the track length in the 1st crystal plane (3 bars);

"L2Leng[3]"	  vector<double>       stores the track length in the 2nd crystal plane (3 bars);

"VLeng[5]"	  vetor<double>	       stores the track length in the veto planes (5 planes);

"EGammaKin"	  Double_t	       stores the kinetic energy of a gamma exiting world

"EBeforeT1"	  Double_t	       stores the kinetic energy before entering T1;

"EBeforeT2"	  Double_t	       stores the kinetic energy before entering T2;

"EBeforeP1"	  Double_t	       stores the kinetic energy before entering P1.