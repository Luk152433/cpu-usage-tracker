# cpu-usage-tracker
project has reader, analyzer, pinter and unit test for reader.

-run mode

 cd main/
 
 cmake . -DCMAKE_C_COMPILER=gcc     or    -DCMAKE_C_COMPILER=clang
 
 cmake --build .
 ./Project
 
 
-test mode

cmake . -DTestOption=ON

cmake --build .

./TestProject
