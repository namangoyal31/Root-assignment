#!/bin/bash
set -e

rootcling -f Question4/MyParticleDict.cxx \
  -rml Question4/libMyParticles.so \
  -rmf Question4/libMyParticles.rootmap \
  Question4/MyGenParticle.h \
  Question4/MyElectron.h \
  Question4/MyMuon.h \
  Question4/LinkDef.h

g++ -fPIC -shared \
  $(root-config --cflags) \
  -I. \
  Question4/MyParticleDict.cxx \
  Question4/MyParticleClasses.C \
  -o Question4/libMyParticles.so \
  $(root-config --libs)

echo "ROOT dictionary built successfully."
