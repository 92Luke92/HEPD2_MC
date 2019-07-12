/////////////////////////////////////////////
//                                         //
// HEPD2MC software                        //
// HEPD2MCDetConst.hh file                 //
//                                         //
/////////////////////////////////////////////

#ifndef HEPD2MC_CONST
#define HEPD2MC_CONST

//all measurements must be in MILLIMETERS

//AXES
const double AXESBLANKET_DIST = 10.; //distance between origin of axes and blanket

//THERMAL BLANKET
const double BLANKET_SIZEX = 237.; //horizontal width of blanket
const double BLANKET_SIZEY = 218.; //vertical width of blanket
const double BLANKET_SIZEZ = 0.068; //thickness of blanket
const double BLANKETWINDOW_DIST = 13.; //distance between blanket and window

//WINDOW
const double WINDOW_SIZEX = BLANKET_SIZEX; //horizontal width of window
const double WINDOW_SIZEY = BLANKET_SIZEY; //vertical width of window
const double WINDOWOUT_THICKNESS = 0.045; //thickness of window out plane
const double WINDOWIN_THICKNESS = 0.035; //thickness of window in plane
const double WINDOWALPIDE_DIST = 10.; //distance between window and first alpide plane

//WALLHONEYCOMB
const double WALLHONEYCOMB_SIZEX = 345.; //horizontal width of honeycomb wall
const double WALLHONEYCOMB_SIZEY = 490.; //vertical width of honeycomb wall
const double WALLHONEYCOMB_THICKNESS = 5.; //thickness of honeycomb wall
const double WALLEXTERNAL_THICKNESS = 0.5; //thickness of external wall

//ALPIDE
const int NALPIDEX = 10; //number of horizontal alpide sensors
const int NALPIDEY = 5; //number of vertical alpide sensors
const double ALPIDE_SIZEX = 15.; //horizontal width of one alpide sensor
const double ALPIDE_SIZEY = 30.; //vertical width of one alpide sensor
const double ALPIDE_SIZEZ = 0.05; //thickness of one alpide sensor
const double ALPIDE_GAP = 5.; //distance between two alpide planes
const double ALPIDETRIG_DIST = 1.; //distance between last alpide plane and first trigger plane
const double ALPIDE_GAPX = 8.6; //half distance between sensors of two adjacent towers of alpide

//CU SUPPORT ALPIDE
const double CUSUPP_SIZEX = 2*ALPIDE_SIZEX;
const double CUSUPP_SIZEY = NALPIDEY*ALPIDE_SIZEY;
const double CUSUPP_SIZEZ = 0.04;

//FPC PLANE ALPIDE
const double FPC_SIZEX = 2*ALPIDE_SIZEX;
const double FPC_SIZEY = NALPIDEY*ALPIDE_SIZEY;
const double FPC_SIZEZ = 0.14;

//COLDPLATE ALPIDE
const double COLDPLATE_SIZEX = 2*ALPIDE_SIZEX;
const double COLDPLATE_SIZEY = NALPIDEY*ALPIDE_SIZEY;
const double COLDPLATE_SIZEZ = 0.37;

//RIBS
const double RIBS_SIZEX = 1.9;
const double RIBS_SIZEY = NALPIDEY*ALPIDE_SIZEY;
const double RIBS_SIZEZ = 4.6;

//TRIGGER
const int NBARS = 5; //number of bars per trigger plane
const double TRIGGER_THICKNESS = 3.; //thickness of one trigger plane
const double TRIGGER1_SIZEX = 212.; //horizontal width of the 1st trigger plane
const double TRIGGER1_SIZEY = 175.; //vertical width of the 1st trigger plane
const double TRIGGER2_SIZEX = 212.; //horizontal width of the 2nd trigger plane
const double TRIGGER2_SIZEY = 150.; //vertical width of the 2nd trigger plane
const double TRIGGER_GAP = 20.; //distance between the two trigger planes
const double TRIGPLANE_DIST = 20.; //distance between trigger planes and calo tower

//LIGHT GUIDE
const int LGEXIT_X = 8.; //x coordinate of light guide surface coupling with PMT
const int LGEXIT_Y = 8.; //y coordinate of light guide surface coupling with PMT
const int LG_HEIGHT = 20.; //height of light guide

//CFPLANE
const double CFPLANE_THICKNESS = 0.12; //thickness of the carbon fiber plane, positioned before T1

//GREEK STRUCTURE CARBON FIBER
const double GRK_THICKNESS = 0.12; //thickness of the greek structure, and distance between two bars of the same trigger plane (on XY plane)

//ALUMINIUM PLANE
//between last plane and lyso
const double ALUMPLANE_X = 150.;
const double ALUMPLANE_Y = 150.;
const double ALUMPLANE_Z = 1.;

//PLANE
const int NCOUPLEDPLANES = 10; //ATTENTION: this is the number of coupled planes; there is one more plane, so total number of planes is NCOUPLEDPLANES+1
const double PLANE_THICKNESS = 12.; //thickness of one plane
const double PLANE_SIZEXY = 150.; //horizontal and vertical width of a plane not cut (supposing it is a square)
const double PLANE_CUT = 10./1.41421; //horizontal cateto of the cut triangle (supposing it has 45deg angles)
const double PLANE_GAP = 0.12; //distance between two planes

//CRYSTALS
const int NCRYSTALS = 3; //number of bar crystals per plane
const double CRYSTAL_THICKNESS = 25.; //thickness of one crystal
const double CRYSTAL_SIZEX = 50.; //horizontal width of a crystal
const double CRYSTAL_SIZEY = 150.; //vertical width of a crystal
const double CRYSTAL_GAP = 0.5; //distance between two bars of crystal
const double CRYSTALGAP_Z = 2.; //distance between the two planes of crystal
const double CRYSTALVETO_DIST = 2.; //distance between crystal and veto

//VETO
const double VETO_SIZEXY = 180.;
const double VETO_THICKNESS = 10.; //thickness of veto

//PMT
const int NPMTS = 64; //number of PMTs
const double PMT_OUTERR = 4.; //radius of PMTs
const double PMT_HEIGHT = 0.05; //heigth of PMTs

#endif
