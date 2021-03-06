/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2_MC.cc file                        //
//                                         //
/////////////////////////////////////////////

#include "HEPD2MCDetectorConstruction.hh"
#include "HEPD2MCActionInitialization.hh"
#include "HEPD2MCPhysicsList.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "FTFP_BERT.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalPhysics.hh"

#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

namespace {
  void PrintUsage() {
    G4cerr << " Usage: " << G4endl;
    G4cerr << " ./HEPD2_MC [-m macro ] [-u UIsession] [-t nThreads]" << G4endl;
    G4cerr << "   note: -t option is available only for multi-threaded mode."
           << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Evaluate arguments
  //
  if ( argc > 7 ) {
    PrintUsage();
    return 1;
  }
  
  G4String macro;
  G4String session;
#ifdef G4MULTITHREADED
  G4int nThreads = 0;
#endif
  for ( G4int i=1; i<argc; i=i+2 )
    {
      if      ( G4String(argv[i]) == "-m" ) macro = argv[i+1];
      else if ( G4String(argv[i]) == "-u" ) session = argv[i+1];
#ifdef G4MULTITHREADED
      else if ( G4String(argv[i]) == "-t" )
	{
	  nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
	}
#endif
      else
	{
	  PrintUsage();
	  return 1;
	}
    }
  
  // Choose the Random engine
  //
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
  // Construct the default run manager
  //
#ifdef G4MULTITHREADED
  G4MTRunManager * runManager = new G4MTRunManager;
  if ( nThreads > 0 )
    {
      runManager->SetNumberOfThreads(nThreads);
    }
#else
  G4RunManager * runManager = new G4RunManager;
#endif
  
  // Set mandatory initialization classes
  //
  HEPD2MCDetectorConstruction* detConstruction = new HEPD2MCDetectorConstruction();
  runManager->SetUserInitialization(detConstruction);
  
  HEPD2MCPhysicsList* physicsList = new HEPD2MCPhysicsList();
  runManager->SetUserInitialization(physicsList);
  
  HEPD2MCActionInitialization* actionInitialization
     = new HEPD2MCActionInitialization(detConstruction);
  runManager->SetUserInitialization(actionInitialization);
  
  
  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  
  // Process macro or start UI session
  //
  if (macro.size()) //batch mode
    {
      G4String command = "/control/execute ";
      UImanager->ApplyCommand(command+macro);
    }
  else //define visualization and UI terminal for interactive mode
    {
#ifdef G4VIS_USE
      // Initialize visualization
      G4VisManager* visManager = new G4VisExecutive;
      // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
      // G4VisManager* visManager = new G4VisExecutive("Quiet");
      visManager->Initialize();
#endif
      
#ifdef G4UI_USE
      // Detect interactive mode (if no macro provided) and define UI session
      G4UIExecutive * ui = new G4UIExecutive(argc, argv, session);
#ifdef G4VIS_USE
      // interactive mode : define UI session
      UImanager->ApplyCommand("/control/execute init_vis.mac");
      if(ui->IsGUI())
	{
	  UImanager->ApplyCommand("/control/execute gui.mac");
	}
      
#endif
      ui->SessionStart();
      delete ui;
#endif
      
#ifdef G4VIS_USE
      delete visManager;
#endif
    }
  
  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete runManager;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
