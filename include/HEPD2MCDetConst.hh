////////////////////////////////////////////
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
const double BLANKET_SIZEX = 236.; //horizontal width of blanket
const double BLANKET_SIZEY = 258.; //vertical width of blanket
const double BLANKET_SIZEZ = 0.068; //thickness of blanket
const double BLANKETWINDOW_DIST = 13.; //distance between blanket and window

//WINDOW
const double WINDOW_SIZEX = BLANKET_SIZEX; //horizontal width of window
const double WINDOW_SIZEY = BLANKET_SIZEY; //vertical width of window
const double WINDOWOUT_THICKNESS = 0.045; //thickness of window out plane
const double WINDOWIN_THICKNESS = 0.035; //thickness of window in plane
const double WINDOWALPIDE_DIST = 7.; //distance between window and first alpide plane

//WALLHONEYCOMB
const double WALLHONEYCOMB_SIZEX = 486.; //horizontal width of honeycomb wall
const double WALLHONEYCOMB_SIZEY = 348.; //vertical width of honeycomb wall
const double WALLHONEYCOMB_THICKNESS = 2.; //thickness of honeycomb wall
const double WALLEXTERNAL_THICKNESS = 0.5; //thickness of external wall

//ALPIDE
const int NALPIDEX = 10; //number of horizontal alpide sensors
const int NALPIDEY = 5; //number of vertical alpide sensors
const double ALPIDE_SIZEX = 15.; //horizontal width of one alpide sensor
const double ALPIDE_SIZEY = 30.; //vertical width of one alpide sensor
const double ALPIDE_SIZEZ = 0.05; //thickness of one alpide sensor
const double ALPIDEACTIVE_SIZEX = 13.76; //horizontal width of one alpide active sensor
const double ALPIDEACTIVE_SIZEY = 29.94; //vertical width of one alpide active sensor
const double ALPIDEACTIVE_SIZEZ = 0.05; //thickness of one alpide active sensor
const double ALPIDE_GAP = 8.38; //distance between two alpide sensors
const double ALPIDETRIG_DIST = 18.; //distance between last alpide sensor and first trigger plane
const double ALPIDE_GAPX = 0.63; //half distance between ribs of two adjacent towers of alpide
const double ALPCHIP_GAP = 0.15; //distance between two chips of the same stave

//ALPIDE RIBS
const double ALPRIBS_SIZEX = 1.9;
const double ALPRIBS_SIZEY = 196.;
const double ALPRIBS_SIZEZ = 7.;

//CU SUPPORT ALPIDE
const double CUSUPP_SIZEX = 2*ALPIDE_SIZEX+2.*ALPRIBS_SIZEX+ALPCHIP_GAP;
const double CUSUPP_SIZEY = 190.;
const double CUSUPP_SIZEZ = 0.04;

//FPC PLANE ALPIDE
const double FPC_SIZEX = 2*ALPIDE_SIZEX+2.*ALPRIBS_SIZEX+ALPCHIP_GAP;
const double FPC_SIZEY = 190.;
const double FPC_SIZEZ = 0.14;
const double FPCSHIFT_Y = 11.5;

//COLDPLATE ALPIDE
const double COLDPLATE_SIZEX = 2*ALPIDE_SIZEX+ALPCHIP_GAP;
const double COLDPLATE_SIZEY = ALPRIBS_SIZEY;
const double COLDPLATE_SIZEZ = 0.4;
const double COLDPLATESHIFT_Y = FPCSHIFT_Y+1.;

//ALPIDE INTERFACE PLATE
const double ALPINTERFACE_SIZEX = 222.;
const double ALPINTERFACE_SIZEY = 265.;
const double ALPINTERFACE_THICKNESS = 4.;

//TRIGGER
const int NBARS = 5; //number of bars per trigger plane
const double TRIGGER_GAP = 11.; //distance between the two trigger planes
const double TRIGPLANE_DIST = 14.; //distance between trigger planes and calo tower
const double BARS_GAP = 4.86; //distance between two bars of the same trigger plane

//T1
const double TRIGGER1_THICKNESS = 2.; //thickness of first trigger plane
const double TRIGGER1_SIZEX = 175.; //horizontal width of the 1st trigger plane
const double TRIGGER1_SIZEY = 152.; //vertical width of the 1st trigger plane

//T1 PORON
const double T1PORON_THICKNESS = 2.2; //thickness of poron before and after T1 bars

//T2 PORON
const double T2PORON_THICKNESS = 0.7; //thickness of poron before and after T1 bars

//T1 WRAPPING
const double T1WRAPPING_THICKNESS = 1.5; //thickness of wrapping per side for T1 bars

//T2 WRAPPING
const double T2WRAPPING_THICKNESS = 1.5; //thickness of wrapping per side for T2 bars

//T1 FRAME SUPPORT
const double FRAMET1_SIZEX = 4.; //X dimension of T1 frame 
const double FRAMET1_SIZEY = 4.; //Y dimension of T1 frame
const double FRAMET1_THICKNESS = 24.; //T1 frame thickness
const double PMTFRAMET1_DIST = 8.; //distance between pmt and T1 fram

//LIGHT GUIDE
const int LGEXIT_X = 8.; //x coordinate of light guide surface coupling with PMT
const int LGEXIT_Y = 8.; //y coordinate of light guide surface coupling with PMT
const int LG_HEIGHT = 20.; //height of light guide

//T1 RIBS
const double T1RIBS_SIZEX = 1.; //X dimension of T1 support ribs
const double T1RIBS_SIZEY = TRIGGER1_SIZEY+2*LG_HEIGHT; //Y dimension of T1 support ribs
const double T1RIBS_SIZEZ = 2.*T1PORON_THICKNESS + 2.*T1WRAPPING_THICKNESS + TRIGGER1_THICKNESS; //Z dimension of T1 support ribs

//T2
const double TRIGGER2_THICKNESS = 8.; //thickness of second trigger plane
const double TRIGGER2_SIZEX = 150.; //horizontal width of the 2nd trigger plane
const double TRIGGER2_SIZEY = 170.; //vertical width of the 2nd trigger plane

//TRIGGER COMP PLANE T1
const double T1COMP_THICKNESS = 0.8; //thickness of the carbon fiber plane, positioned before T1, after T1, before T2 and after T2

//TRIGGER COMP PLANE T2
const double T2COMP_THICKNESS = 0.8; //thickness of the carbon fiber plane, positioned before T1, after T1, before T2 and after T2

//T2 RIBS
const double T2RIBS_SIZEX = TRIGGER2_SIZEX; //X dimension of T1 support ribs
const double T2RIBS_SIZEY = 1.; //Y dimension of T1 support ribs
const double T2RIBS_SIZEZ = 12.; //Z dimension of T1 support ribs

//CALORIMETER
const int NCALOPLANES_BLOCK1 = 3;
const int NCALOPLANES_BLOCK2 = 4;
const int NCALOPLANES_BLOCK3 = 4;
const int NCALOPLANES = NCALOPLANES_BLOCK1+NCALOPLANES_BLOCK2+NCALOPLANES_BLOCK3;
const double PLANE_THICKNESS = 12.; //thickness of one plane
const double PLANE_SIZEXY = 150.; //horizontal and vertical width of a plane not cut (supposing it is a square)
const double PLANE_CUT = 18./1.41421; //horizontal cateto of the cut triangle (supposing it has 45deg angles)
const double DIST_CALOBLOCKS = 8.; //distance between two calo blocks

const double PCOMPPLANE_THICKNESS = 1.;
const double PPORON_THICKNESS = 0.7;
const double PWRAPPING_THICKNESS = 1.5;

/*
//PLANE OLD
const int NCOUPLEDPLANES = 10; //ATTENTION: this is the number of coupled planes; there is one more plane, so total number of planes is NCOUPLEDPLANES+1
const double PLANE_THICKNESS = 12.; //thickness of one plane
const double PLANE_SIZEXY = 150.; //horizontal and vertical width of a plane not cut (supposing it is a square)
const double PLANE_CUT = 18./1.41421; //horizontal cateto of the cut triangle (supposing it has 45deg angles)
const double PLANE_GAP = 0.12; //distance between two planes
*/

//CRYSTALS
const int NCRYSTALS = 3; //number of bar crystals per plane
const double CRYSTAL_THICKNESS = 25.; //thickness of one crystal
const double CRYSTAL_SIZEX = 150.; //horizontal width of a crystal
const double CRYSTAL_SIZEY = 50.; //vertical width of a crystal
const double CWRAPPING_THICKNESS = 1.5; //thickness of a lyso wrapping
const double SCOTCHTAPE_THICKNESS = 0.8; //thickness of a scotch tape
const double SCOTCHTAPE_SIZEX = 20.; //horizontal width of a scotch tape
const double SCOTCHTAPE_DIST = 6.; //distance between 2 scotch tapes on the same crystal

const double CRYSTALGAP_Z = 3.; //distance between the two planes of crystal
const double CRYSTALVETO_DIST = 2.6; //distance between crystal and veto

//LYSO COVER
//between last tower plane and lyso
const double LYSOCOVER_X = 150. + 6.*CWRAPPING_THICKNESS + 2.*SCOTCHTAPE_THICKNESS;
const double LYSOCOVER_Y = 150.;
const double LYSOCOVER_Z = 2.;
const double DIST_LASTPLANE_LYSOCOVER = 4.;

//VETO LATERAL
const double VETOLATCONT_X = 222.;
const double VETOLATCONT_Y = 305.;
const double VETO_THICKNESS = 8.; //thickness of veto
const double VETO_HOLEX = 15.1;
const double VETO_HOLEY = 46.1;
const double VETOLAT_X = 198.;
const double VETOLAT_Y = 283.;
const double VPORON_THICKNESS = 3.;
const double VWRAPPING_THICKNESS = 1.5;
const double VETOLATCOVER_THICKNESS = 1.;

//VETO BOTTOM
const double VETO_SIZEXY = 166.;
const double VETOBOT_Z = 8.;
const double VETO_CUT = 11.3/1.41421;
const double VETOBOTCOVER_Z = 1.;
const double VETOBOTPORON_Z = 0.7;
const double REARVETOBOT_Z = 3.;
const double REARCOVER_DIST = 5.;

//PMT
const int NPMTS = 64; //number of PMTs
const double PMT_OUTERR = 4.; //radius of PMTs
const double PMT_HEIGHT = 0.05; //heigth of PMTs

#endif
