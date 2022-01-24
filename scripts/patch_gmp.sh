#!/bin/bash

# This is a modified version of the patch script of factorable.net.

__exists() {
    which $1 1>/dev/null 2>&1
}

cd gmp

gmptar=gmp-6.1.2.tar.xz
get="fetch";
! __exists fetch && get="curl -o $gmptar -L";

if [ ! -f $gmptar ];
then
    $get https://gmplib.org/download/gmp/$gmptar
fi


sum=`openssl sha1 $gmptar | awk -F' ' '{print $2}'`

if [[ $sum != "9dc6981197a7d92f339192eea974f5eca48fcffe" ]];
then
    echo ""
    echo "=========================================="
    echo "ERROR: could not verify $gmptar;"
    echo "=========================================="
    exit;
fi

echo "$gmptar downloaded and verified sha1 signature"

tar xf $gmptar

cd gmp-6.1.2
patch -p 1 < ../gmp-6.1.2.patch
mkdir ../patched
./configure --prefix=$PWD/../patched/
make
make install
cd ..
