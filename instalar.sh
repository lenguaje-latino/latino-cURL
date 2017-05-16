rm -CMakeCache.txt
cmake -DENABLE_MANUAL=0 -DBUILDING_LIBCURL=1 -DCMAKE_INSTALL_PREFIX:PATH=/usr . && make all install
