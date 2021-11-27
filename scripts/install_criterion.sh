#!/bin/bash

readonly deps_install_dir="deps_install"

mkdir ${deps_install_dir}
pushd ${deps_install_dir}

wget https://github.com/Snaipe/Criterion/releases/download/v2.3.3/criterion-v2.3.3-linux-x86_64.tar.bz2
tar -xjvf criterion-v2.3.3-linux-x86_64.tar.bz2
cd criterion-v2.3.3
cd include
sudo cp -rv criterion /usr/include/
cd ../
sudo cp -v lib/libcriterion* /usr/lib64/

popd
rm -r ${deps_install_dir}
