#!/bin/sh

#TO DEPLOY MACOS APP, CLEAN RELEASE FOLDER, MAKE REBUILD ALL AND EXECUTE THIS SCRIPT
clear

cd bin/release

install_name_tool -change "libscdatamodel.1.dylib" "$PWD/libscdatamodel.1.dylib" $PWD/visualsc.app/Contents/MacOS/visualsc
install_name_tool -change "libscgraphicsview.1.dylib" "$PWD/libscgraphicsview.1.dylib" $PWD/visualsc.app/Contents/MacOS/visualsc
install_name_tool -change "libscformview.1.dylib" "$PWD/libscformview.1.dylib" $PWD/visualsc.app/Contents/MacOS/visualsc

install_name_tool -change "libscdatamodel.1.dylib" "@executable_path/../Frameworks/libscdatamodel.1.dylib" libscgraphicsview.1.dylib
install_name_tool -change "libscdatamodel.1.dylib" "@executable_path/../Frameworks/libscdatamodel.1.dylib" libscformview.1.dylib

/Users/maksimzharov/Qt/5.7/5.7/clang_64/bin/macdeployqt visualsc.app