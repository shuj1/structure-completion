echo "[cuboid-prediction]"
echo "Minhyuk Sung"
echo "Mar. 2015"
echo "Install libraries..."
echo ""

echo "Please make sure that followings are installed on your machine:"
echo " - g++"
echo " - gfortran"
echo " - cmake"
echo " - wget"
echo " - git"
echo " - svn"
echo " - pkgconfig"
echo " - glew"

read -p "Press any key to continue... " -n1 -s

mkdir lib && cd lib

# ANN
wget http://www.cs.umd.edu/~mount/ANN/Files/1.1.2/ann_1.1.2.tar.gz
tar xvf ann_1.1.2.tar.gz
rm -rf ann_1.1.2.tar.gz
mv ann_1.1.2 ann-1.1.2
cd ann-1.1.2
make macosx-g++
cd ../

# Eigen
wget https://bitbucket.org/eigen/eigen/get/3.2.2.tar.gz
tar xvf 3.2.2.tar.gz
rm -rf 3.2.2.tar.gz
mv eigen-eigen-* eigen-3.2.2

# gflags
git clone https://github.com/gflags/gflags.git
cd gflags
mkdir build && cd build
cmake ..
make
make test
cd ../../

# glew
wget https://sourceforge.net/projects/glew/files/glew/1.12.0/glew-1.12.0.tgz
tar xvf glew-1.12.0.tgz
rm -rf glew-1.12.0.tgz
cd glew-1.12.0
cd build
cmake ..
make
make test
cd ../../

# glog
git clone https://github.com/google/glog.git
cd glog
mkdir build
./configure --prefix=$(pwd)/build
make
make install
cd ../

# IPOPT
wget http://www.coin-or.org/download/source/Ipopt/Ipopt-3.12.1.tgz
tar xvf Ipopt-3.12.1.tgz
rm -rf Ipopt-3.12.1.tgz
cd Ipopt-3.12.1
mkdir build
cd ThirdParty
cd Metis
./get.Metis
./configure --prefix=$(pwd)/../../build
make
make test
cd ../Mumps
./get.Mumps
./configure --prefix=$(pwd)/../../build
make
make test
cd ../../
./configure --prefix=$(pwd)/build
make
make test
make install
cd ../

# OpenMesh
svn co http://openmesh.org/svnrepo/OpenMesh/trunk/ OpenMesh
cd OpenMesh
mkdir build && cd build
cmake ..
make
make test
cd ../../

# TRW_S
wget http://ftp.research.microsoft.com/downloads/dad6c31e-2c04-471f-b724-ded18bf70fe3/TRW_S-v1.3.zip
unzip TRW_S-v1.3.zip
rm -rf TRW_S-v1.3.zip
cd TRW_S-v1.3
mkdir temp
mv example.cpp temp/
cd ../

# wingsit_QP
git clone https://github.com/wingsit/QP.git wingsit_QP
cd wingsit_QP
mkdir temp
mv umain.cc uQuadProg++.hh uQuadProg++.cc temp/
cd ../

