#!/bin/bash
#
#  install-libs.sh
#  Copyright 2011 Iain Peet
# 
#  Simpleminded script which builds and installs source-only libs distributed
#  with raytrace source.
# 
#  This program is distributed under the of the GNU Lesser Public License. 
# 
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>

# Require all simple statements to succeed
set -e

# Files we need to deal with
JSONCPP_TGZ='jsoncpp-src-0.6.0-rc2.tar.gz'
SCONS_TGZ='scons-local-1.2.0.tar.gz'

# Platform used for jsoncpp build
JSONCPP_PLATFORM='linux-gcc'

# Tests that a given required file exists.  Exit if it doesn't.
function require() {
  if [ ! -e $1 ]; then
    echo "$1 doesn't exist."
    exit 1
  fi
}

# Files we need
require $JSONCPP_TGZ
require $SCONS_TGZ

# Files + dirs we create need to be read / executed by root
umask 0022

# Install libs!

echo "Extracting jsoncpp..."
tar -xzvf $JSONCPP_TGZ
jsoncpp_dir=$(echo $JSONCPP_TGZ | sed s/.tar.gz//)
tar -xzvf $SCONS_TGZ -C $jsoncpp_dir

echo -e "\nBuilding jsoncpp..."
cd $jsoncpp_dir
python scons.py platform=$JSONCPP_PLATFORM 

echo -e "\nInstalling jsoncpp..."
sudo cp -r include/json /usr/local/include
# This assumes only one output platform!  (Clean build, should hold.) 
sudo cp libs/*/*.a /usr/lib/libjsoncpp.a
sudo cp libs/*/*.so /usr/lib/libjsoncpp.so

echo -e "\nCleaning up after jsoncpp install."
cd -
rm -rf $jsoncpp_dir

echo "Done!"

