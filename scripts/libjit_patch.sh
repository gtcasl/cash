#!/bin/bash

# fix autoconf scripts
pushd third_party/libjit
git apply ../../scripts/libjit.patch  
popd
