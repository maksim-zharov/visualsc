#!/bin/sh
clear

cd bin/release

install_name_tool -id "$PWD/libscdatamodel.1.dylib" $PWD/libscdatamodel.1.dylib
install_name_tool -change "libscdatamodel.1.dylib" "$PWD/libscdatamodel.1.dylib" $PWD/libscdatamodel.1.dylib

install_name_tool -id "$PWD/libscgraphicsview.1.dylib" $PWD/libscgraphicsview.1.dylib
install_name_tool -change "libscgraphicsview.1.dylib" "$PWD/libscgraphicsview.1.dylib" $PWD/libscgraphicsview.1.dylib

install_name_tool -id "$PWD/libscformview.1.dylib" $PWD/libscformview.1.dylib
install_name_tool -change "libscformview.1.dylib" "$PWD/libscformview.1.dylib" $PWD/libscformview.1.dylib

/Users/maksimzharov/Qt/5.5/clang_64/bin/macdeployqt visualsc.app

cp -r ../../reference.app/Contents/Frameworks visualsc.app/Contents
cp -r ../../reference.app/Contents/PlugIns visualsc.app/Contents/PlugIns
cp ../../reference.app/Contents/Resources/qt.conf visualsc.app/Contents/Resources/qt.conf
