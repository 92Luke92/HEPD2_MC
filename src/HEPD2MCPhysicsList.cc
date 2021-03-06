/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCPhysicsList.cc file              //
//                                         //
/////////////////////////////////////////////

#include "globals.hh"
#include "HEPD2MCPhysicsList.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4IonElasticPhysics.hh"
#include "G4HadronPhysicsShielding.hh"
#include "G4IonQMDPhysics.hh"

#include "G4ProcessManager.hh"

#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpMieHG.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"

HEPD2MCPhysicsList::HEPD2MCPhysicsList() 
 : G4VUserPhysicsList(),
   fVerboseLebel(0), fMaxNumPhotonStep(100)
{
  SetVerboseLevel(1);
}

HEPD2MCPhysicsList::~HEPD2MCPhysicsList()
{
}

void HEPD2MCPhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program.
  
  G4BosonConstructor bConstructor;
  bConstructor.ConstructParticle();
  
  G4LeptonConstructor lConstructor;
  lConstructor.ConstructParticle();
  
  G4MesonConstructor mConstructor;
  mConstructor.ConstructParticle();
  
  G4BaryonConstructor rConstructor;
  rConstructor.ConstructParticle();
  
  G4IonConstructor iConstructor;
  iConstructor.ConstructParticle();
  
}

void HEPD2MCPhysicsList::ConstructProcess()
{
   
  AddTransportation();
  ConstructDecay();
  ConstructOp();
  
  //ELECTROMAGNETIC model
  ConstructEM();
  //ELASTIC HADRONIC models
  hadronPhys.push_back(new G4HadronElasticPhysics());
  hadronPhys.push_back(new G4IonElasticPhysics());
  //INELASTIC HADRONIC models
  hadronPhys.push_back(new G4HadronPhysicsShielding());
  hadronPhys.push_back(new G4IonQMDPhysics());
  
  for(size_t i=0; i<hadronPhys.size(); i++)
    hadronPhys[i]->ConstructProcess();
  
  
}

#include "G4Decay.hh"

void HEPD2MCPhysicsList::ConstructDecay()
{
  // Add Decay Process
  G4Decay* theDecayProcess = new G4Decay();
  theParticleIterator->reset();
  while( (*theParticleIterator)() )
    {
      G4ParticleDefinition* particle = theParticleIterator->value();
      G4ProcessManager* pmanager = particle->GetProcessManager();
      if (theDecayProcess->IsApplicable(*particle))
	{
	  pmanager ->AddProcess(theDecayProcess);
	  // set ordering for PostStepDoIt and AtRestDoIt
	  pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
	  pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
	}
    }
}


#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"
#include "G4hMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"

void HEPD2MCPhysicsList::ConstructEM()
{
  theParticleIterator->reset();
  while( (*theParticleIterator)() )
    {
      G4ParticleDefinition* particle = theParticleIterator->value();
      G4ProcessManager* pmanager = particle->GetProcessManager();
      G4String particleName = particle->GetParticleName();
      
      if (particleName == "gamma")
	{
	  pmanager->AddDiscreteProcess(new G4GammaConversion());
	  pmanager->AddDiscreteProcess(new G4ComptonScattering());
	  pmanager->AddDiscreteProcess(new G4PhotoElectricEffect());
	  
	}
      else if (particleName == "e-")
	{
	  pmanager->AddProcess(new G4eMultipleScattering(),-1, 1, 1);
	  pmanager->AddProcess(new G4eIonisation(),       -1, 2, 2);
	  pmanager->AddProcess(new G4eBremsstrahlung(),   -1, 3, 3);
	  
	}
      else if (particleName == "e+")
	{
	  pmanager->AddProcess(new G4eMultipleScattering(),-1, 1, 1);
	  pmanager->AddProcess(new G4eIonisation(),       -1, 2, 2);
	  pmanager->AddProcess(new G4eBremsstrahlung(),   -1, 3, 3);
	  pmanager->AddProcess(new G4eplusAnnihilation(),  0,-1, 4);
	  
	}
      else if( particleName == "mu+" ||
	       particleName == "mu-" )
	{
	  pmanager->AddProcess(new G4MuMultipleScattering(),-1, 1, 1);
	  pmanager->AddProcess(new G4MuIonisation(),      -1, 2, 2);
	  pmanager->AddProcess(new G4MuBremsstrahlung(),  -1, 3, 3);
	  pmanager->AddProcess(new G4MuPairProduction(),  -1, 4, 4);
	  
	}
      else
	{
	  if ((particle->GetPDGCharge() != 0.0) &&
	      (particle->GetParticleName() != "chargedgeantino") &&
	      !particle->IsShortLived())
	    {
	      pmanager->AddProcess(new G4hMultipleScattering(),-1,1,1);
	      pmanager->AddProcess(new G4hIonisation(),       -1,2,2);
	    }
	}
    }
}

#include "G4Threading.hh"

void HEPD2MCPhysicsList::ConstructOp()
{
  G4Cerenkov* cerenkovProcess = new G4Cerenkov("Cerenkov");
  cerenkovProcess->SetMaxNumPhotonsPerStep(fMaxNumPhotonStep);
  cerenkovProcess->SetMaxBetaChangePerStep(10.0);
  cerenkovProcess->SetTrackSecondariesFirst(true);
  
  G4Scintillation* scintillationProcess = new G4Scintillation("Scintillation");
  scintillationProcess->SetScintillationYieldFactor(1.);
  scintillationProcess->SetScintillationExcitationRatio(0.0);
  scintillationProcess->SetTrackSecondariesFirst(true);
  
  G4OpAbsorption* absorptionProcess = new G4OpAbsorption();
  
  G4OpRayleigh* rayleighScatteringProcess = new G4OpRayleigh();
  
  G4OpMieHG* mieHGScatteringProcess = new G4OpMieHG();
  
  G4OpBoundaryProcess* boundaryProcess = new G4OpBoundaryProcess();
  
  cerenkovProcess->SetVerboseLevel(fVerboseLebel);
  scintillationProcess->SetVerboseLevel(fVerboseLebel);
  absorptionProcess->SetVerboseLevel(fVerboseLebel);
  rayleighScatteringProcess->SetVerboseLevel(fVerboseLebel);
  mieHGScatteringProcess->SetVerboseLevel(fVerboseLebel);
  boundaryProcess->SetVerboseLevel(fVerboseLebel);
  
  // Use Birks correction in the scintillation process
  if(!G4Threading::IsWorkerThread())
  {
    G4EmSaturation* emSaturation =
      G4LossTableManager::Instance()->EmSaturation();
    scintillationProcess->AddSaturation(emSaturation);
  }
  
  theParticleIterator->reset();
  while( (*theParticleIterator)() )
    {
      G4ParticleDefinition* particle = theParticleIterator->value();
      G4ProcessManager* pmanager = particle->GetProcessManager();
      G4String particleName = particle->GetParticleName();
      if (cerenkovProcess->IsApplicable(*particle))
	{
	  pmanager->AddProcess(cerenkovProcess);
	  pmanager->SetProcessOrdering(cerenkovProcess,idxPostStep);
	}
      if (scintillationProcess->IsApplicable(*particle))
	{
	  pmanager->AddProcess(scintillationProcess);
	  pmanager->SetProcessOrderingToLast(scintillationProcess, idxAtRest);
	  pmanager->SetProcessOrderingToLast(scintillationProcess, idxPostStep);
	}
      if (particleName == "opticalphoton")
	{
	  G4cout << " AddDiscreteProcess to OpticalPhoton " << G4endl;
	  pmanager->AddDiscreteProcess(absorptionProcess);
	  pmanager->AddDiscreteProcess(rayleighScatteringProcess);
	  pmanager->AddDiscreteProcess(mieHGScatteringProcess);
	  pmanager->AddDiscreteProcess(boundaryProcess);
	}
    }
}

void HEPD2MCPhysicsList::SetCuts()
{
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets the default cut value for all particle types
  SetCutsWithDefault();
  
  if (verboseLevel>0) DumpCutValuesTable();
}
