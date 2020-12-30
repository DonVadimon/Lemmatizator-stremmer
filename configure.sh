mkdir build
cd build
cmake ..
make
./Lemmatizator
cp -rf ../postfixes/ .
ctest