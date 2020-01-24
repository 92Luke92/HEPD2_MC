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
const double BLANKET_SIZEX = 258.; //horizontal width of blanket
const double BLANKET_SIZEY = 236.; //vertical width of blanket
const double BLANKET_SIZEZ = 0.068; //thickness of blanket
const double BLANKETWINDOW_DIST = 13.; //distance between blanket and window

//WINDOW
const double WINDOW_SIZEX = BLANKET_SIZEX; //horizontal width of window
const double WINDOW_SIZEY = BLANKET_SIZEY; //vertical width of window
const double WINDOWOUT_THICKNESS = 0.045; //thickness of window out plane
const double WINDOWIN_THICKNESS = 0.035; //thickness of window in plane

//WALLHONEYCOMB
const double WALLHONEYCOMB_SIZEX = 348.; //horizontal width of honeycomb wall
const double WALLHONEYCOMB_SIZEY = 486.; //vertical width of honeycomb wall
const double WALLHONEYCOMB_THICKNESS = 2.; //thickness of honeycomb wall
const double WALLEXTERNAL_THICKNESS = 0.5; //thickness of external wall

//TRIGGER
const int NBARST1 = 5; //number of bars per trigger plane T1
const int NBARST2 = 4; //number of bars per trigger plane T2
const double TRIGPLANE_DIST = 16.; //distance between 2nd trigger plane and 1st calo plane
const double BARS_GAP = 1.9; //distance between two bars of the same trigger plane
const double TRIGWIND_DIST = 11.25; //distance between box window and 1st trigger plane

//T1
const double TRIGGER1_THICKNESS = 2.; //thickness of first trigger plane
const double TRIGGER1_SIZEX = 154.; //horizontal width of the 1st trigger plane
const double TRIGGER1_SIZEY = 176.3; //vertical width of the 1st trigger plane

//T1 WRAPPING
const double T1WRAPPING_THICKNESS = 0.25; //thickness of wrapping per side for T1 bars

//T1 FRAME SUPPORT
const double FRAMET1_SIZEX = 4.; //X dimension of T1 frame 
const double FRAMET1_SIZEY = 4.; //Y dimension of T1 frame
const double FRAMET1_THICKNESS = 24.; //T1 frame thickness
const double PMTFRAMET1_DIST = 8.; //distance between pmt and T1 frame

//LIGHT GUIDE
const int LGEXIT_X = 8.; //x coordinate of light guide surface coupling with PMT
const int LGEXIT_Y = 8.; //y coordinate of light guide surface coupling with PMT
const int LG_HEIGHTUP = 45.; //height of light guide
const int LG_HEIGHTDOWN = 24.; //height of light guide

//TRIGGER COMP PLANE T1
const double T1COMP_THICKNESS = 0.8; //thickness of the carbon fiber plane, positioned before T1 and after T1
const double T1COMP_DIST = 3.; //distance between the comp plane and the bar

//T1 RIBS
const double T1RIBS_SIZEX = TRIGGER1_SIZEX+LG_HEIGHTUP+LG_HEIGHTDOWN; //X dimension of T1 support ribs
const double T1RIBS_SIZEY = 1.; //Y dimension of T1 support ribs
const double T1RIBS_SIZEZ = 2.*T1WRAPPING_THICKNESS + TRIGGER1_THICKNESS + 2.*T1COMP_DIST; //Z dimension of T1 support ribs

//PLATE KAPTON
const double KPLATE_SIZEZ = 0.15; //thickness of plate in kapton before and after alpide
const double KPLATECOMPT1_GAP = 7.3; //distance between kapton plate and comp plane of T1
const double KFPC_DIST = 5.8;
const double KPLATECOLD_DIST = 13.; //distance between kapton plate and cold plate of Alpide
const double KPLATET2_DIST = 6.3; //distance between kapton plate and 2nd trigger plane


//ALPIDE INTERFACE PLATE
const double ALPINTERFACE_SIZEX = 265.;
const double ALPINTERFACE_SIZEY = 222.;
const double ALPINTERFACE_THICKNESS = 5.;

//ALPIDE
const int NALPIDEX = 5; //number of horizontal alpide sensors
const int NALPIDEY = 10; //number of vertical alpide sensors
const double ALPIDE_SIZEX = 30.; //horizontal width of one alpide sensor
const double ALPIDE_SIZEY = 15.; //vertical width of one alpide sensor
const double ALPIDE_SIZEZ = 0.05; //thickness of one alpide sensor
const double ALPIDEACTIVE_SIZEX = 29.94; //horizontal width of one alpide active sensor
const double ALPIDEACTIVE_SIZEY = 13.76; //vertical width of one alpide active sensor
const double ALPIDEACTIVE_SIZEZ = 0.05; //thickness of one alpide active sensor
const double ALPIDE_GAP = 8.5; //distance between two alpide sensors
const double ALPIDE_GAPY = 0.63; //half distance between ribs of two adjacent towers of alpide
const double ALPCHIP_GAP = 0.15; //distance between two chips of the same stave

//ALPIDE RIBS
const double ALPRIBS_SIZEX = 196.;
const double ALPRIBS_SIZEY = 2.;
const double ALPRIBS_SIZEZ = 7.;

//CU SUPPORT ALPIDE
const double CUSUPP_SIZEX = 190.;
const double CUSUPP_SIZEY = 2*ALPIDE_SIZEY+2.*ALPRIBS_SIZEY+ALPCHIP_GAP;
const double CUSUPP_SIZEZ = 0.04;

//FPC PLANE ALPIDE
const double FPC_SIZEX = 190.;
const double FPC_SIZEY = 2*ALPIDE_SIZEY+2.*ALPRIBS_SIZEY+ALPCHIP_GAP;
const double FPC_SIZEZ = 0.14;
const double FPCSHIFT_X = -11.5;

//GLUE ALPIDE
const double GLUE_SIZEX = NALPIDEX*ALPIDE_SIZEX + (NALPIDEY-1)*ALPCHIP_GAP;
const double GLUE_SIZEY = 2*ALPIDE_SIZEY+ALPCHIP_GAP;
const double GLUE_FPC_SIZEZ = 0.05;
const double GLUE_COLDPLATE_SIZEZ = 0.1;

//COLDPLATE ALPIDE
const double COLDPLATE_SIZEX = ALPRIBS_SIZEX;
const double COLDPLATE_SIZEY = 2*ALPIDE_SIZEY+ALPCHIP_GAP;
const double COLDPLATE_SIZEZ = 0.4;
const double COLDPLATESHIFT_X = FPCSHIFT_X+1.;

//T2
const double TRIGGER2_THICKNESS = 8.; //thickness of second trigger plane
const double TRIGGER2_SIZEX = 150.; //horizontal width of the 2nd trigger plane
const double TRIGGER2_SIZEY = 150.; //vertical width of the 2nd trigger plane

//T2 PORON
const double T2PORON_THICKNESS = 0.7; //thickness of poron before and after T1 bars

//T2 WRAPPING
const double T2WRAPPING_THICKNESS = 0.25; //thickness of wrapping per side for T2 bars

//TRIGGER COMP PLANE T2
const double T2COMP_THICKNESS = 0.8; //thickness of the carbon fiber plane, positioned before T2 and after T2

//T2 RIBS
const double T2RIBS_SIZEX = 1.; //X dimension of T2 support ribs
const double T2RIBS_SIZEY = TRIGGER2_SIZEY; //Y dimension of T2 support ribs
const double T2RIBS_SIZEZ = TRIGGER2_THICKNESS+2.*T2WRAPPING_THICKNESS + 2.*T2PORON_THICKNESS; //Z dimension of T2 support ribs

//CALORIMETER
const int NCALOPLANES_BLOCK1 = 4;
const int NCALOPLANES_BLOCK2 = 4;
const int NCALOPLANES_BLOCK3 = 4;
const int NCALOPLANES = NCALOPLANES_BLOCK1+NCALOPLANES_BLOCK2+NCALOPLANES_BLOCK3;
const double PLANE_THICKNESS = 12.7; //thickness of one plane
const double PLANE_SIZEXY = 150.; //horizontal and vertical width of a plane not cut (supposing it is a square)
const double PLANE_CUT = 18./1.41421; //horizontal cateto of the cut triangle (supposing it has 45deg angles)
const double DIST_CALOBLOCKS = 9.5; //distance between two calo blocks

const double PCOMPPLANE_THICKNESS = 1.;
const double PPORON_THICKNESS = 0.7;
const double PWRAPPING_THICKNESS = 0.25;

//CRYSTALS
const int NCRYSTALS = 3; //number of bar crystals per plane
const double CRYSTAL_THICKNESS = 25.; //thickness of one crystal
const double CRYSTAL_SIZEX = 50.; //horizontal width of a crystal
const double CRYSTAL_SIZEY = 150.; //vertical width of a crystal
const double CWRAPPING_THICKNESS = 0.25; //thickness of a lyso wrapping
const double SCOTCHTAPE_THICKNESS = 0.8; //thickness of a scotch tape
const double SCOTCHTAPE_SIZEY = 20.; //horizontal width of a scotch tape
const double SCOTCHTAPE_DIST = 6.; //distance between 2 scotch tapes on the same crystal

const double CRYSTALGAP_Z = 3.; //distance between the two planes of crystal
const double CRYSTALVETO_DIST = 2.6; //distance between crystal and veto

//LYSO COVER
//between last tower plane and lyso
const double LYSOCOVER_X = 150.;
const double LYSOCOVER_Y = 150. + 6.*CWRAPPING_THICKNESS + 2.*SCOTCHTAPE_THICKNESS;
const double LYSOCOVER_Z = 2.;
const double DIST_LASTPLANE_LYSOCOVER = 4.;

//VETO LATERAL
const double VETOLATCONT_X = 222.;
const double VETOLATCONT_Y = 300.;
const double VETO_THICKNESS = 8.; //thickness of veto
const double VETO_HOLEUPX = 25.1;
const double VETO_HOLEUPY = 62.1;
const double VETO_HOLEDOWNX = 34.1;
const double VETO_HOLEDOWNY = 62.1;
const double VETOLAT_X = 217.;
const double VETOLAT_Y = 296.;
const double VPORON_THICKNESS = 3.;
const double VWRAPPING_THICKNESS = 0.25;
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
