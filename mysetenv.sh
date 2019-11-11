opt="$1"

# compilers
export EOS_MGM_URL=root://eosams.cern.ch

#echo "Selecting gcc"
//. /cvmfs/sft.cern.ch/lcg/releases/gcc/4.9.3/x86_64-slc6-gcc49-opt/setup.sh
gcc --version
#export PATH=/cvmfs/sft.cern.ch/lcg/external/Python/2.7.4/x86_64-slc6-gcc48-opt/bin/:$PATH
python --version
#/export PATH=/cvmfs/sft.cern.ch/lcg/releases/CMake/3.11.1-daf3a/x86_64-centos7-gcc48-opt/bin:$PATH
cmake --version

# ROOT
echo "Exporting ROOT vars"
/usr/local/bin/thisroot.sh
#export ROOTSYS=/cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.14.04/x86_64-centos7-gcc48-opt/root
#export PATH=$ROOTSYS/bin:$PATH
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOTSYS/lib
#if [ "$opt" == "exportRIP" ]; then
#  export ROOT_INCLUDE_PATH=/cvmfs/ams.cern.ch/Offline/dbar/public/release_v5/AMS_vdev_190318/include/
#fi
echo "ROOT version" `root-config --version`
export G4SYSTEM=Linux-g++
export G4VIS_USE_OPENGLX=1
export G4VIS_USE_RAYTRACERX=1
export G4VIS_USE_DAWN=1
export G4VIS_USE_VRML=1
export G4UI_USE_TCSH=1
export G4LIB_USE_ZLIB=1
export OGLHOME=/usr
export OGLLIBS="-L/usr/lib64 -lGLU -lGL"

source  ../Geant4-10.01-p03/bin/geant4.sh

