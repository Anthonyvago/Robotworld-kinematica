mkdir build -p &&
cd build &&
cmake .. &&
make -j4 2>&1 | tee build.log &&
./kinematica
