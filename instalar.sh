apt-get install libssl-dev
rm CMakeCache.txt
cmake -DBUILD_CURL_EXE=0 -DENABLE_MANUAL=0 -DBUILDING_LIBCURL=1 -DCURL_STATICLIB=1 -DCMAKE_INSTALL_PREFIX:PATH=/usr . && make all install
