#!/bin/bash

__exists() {
    which $1 1>/dev/null 2>&1
}

get="fetch";
! __exists fetch && get="curl -OL";

if [ ! -f gmp-6.1.2.tar.bz2 ];
then
    $get ftp://ftp.gmplib.org/pub/gmp-6.1.2/gmp-6.1.2.tar.bz2
fi


sum=`openssl sha1 gmp-6.1.2.tar.bz2 | awk -F' ' '{print $2}'`

if [[ $sum != "366ded6a44cd108ba6b3f5b9a252eab3f3a95cdf" ]];
then
    echo ''
    echo '=========================================='
    echo 'ERROR: could not verify gmp-5.0.5.tar.bz2;'
    echo 'Downloaded over untrusted channel (non-https)'
    echo '=========================================='
    exit;
fi

echo 'gmp-6.1.2.tar.bz2 downloaded and verified sha1 signature'

tar xf gmp-6.1.2.tar.bz2

cd gmp-6.1.2
patch -p 1 < ../gmp-6.1.2.patch
mkdir ../gmp-patched
./configure --prefix=$PWD/../gmp-patched/
make
make install
cd ..
# make
#
#
