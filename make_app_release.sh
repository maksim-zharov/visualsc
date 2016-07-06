#!/bin/sh

#TO DEPLOY MACOS APP, CLEAN RELEASE FOLDER, MAKE REBUILD ALL AND EXECUTE THIS SCRIPT
clear

cd bin/release

#I just wanna say to Qt and MacOS ... FFUUUUCKKKK YOOOUUUUU BIIITTTCHHHH

install_name_tool -change "libscdatamodel.1.dylib" "$PWD/libscdatamodel.1.dylib" $PWD/visualsc.app/Contents/MacOS/visualsc
install_name_tool -change "libscgraphicsview.1.dylib" "$PWD/libscgraphicsview.1.dylib" $PWD/visualsc.app/Contents/MacOS/visualsc
install_name_tool -change "libscformview.1.dylib" "$PWD/libscformview.1.dylib" $PWD/visualsc.app/Contents/MacOS/visualsc

install_name_tool -change "libscdatamodel.1.dylib" "@rpath/libscdatamodel.1.dylib" libscgraphicsview.1.dylib
install_name_tool -change "libscdatamodel.1.dylib" "@rpath/libscdatamodel.1.dylib" libscformview.1.dylib

/Users/maksimzharov/Qt/5.7/5.7/clang_64/bin/macdeployqt visualsc.app

install_name_tool -change "$PWD/libscdatamodel.1.dylib" "@executable_path/../Frameworks/libscdatamodel.1.dylib" $PWD/visualsc.app/Contents/MacOS/visualsc
install_name_tool -change "$PWD/libscgraphicsview.1.dylib" "@executable_path/../Frameworks/libscgraphicsview.1.dylib" $PWD/visualsc.app/Contents/MacOS/visualsc
install_name_tool -change "$PWD/libscformview.1.dylib" "@executable_path/../Frameworks/libscformview.1.dylib" $PWD/visualsc.app/Contents/MacOS/visualsc