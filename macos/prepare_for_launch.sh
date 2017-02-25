#!/bin/sh
rm bobsgame
cp ../DerivedData/bobsgame/Build/Products/Release/bobsgame ./
for file in *.dylib
do
	name=${file##*/}
	echo $name
	install_name_tool -id @loader_path/libs/$name $name
	install_name_tool -change /usr/local/lib/libPocoFoundation.45.dylib @loader_path/libs/libPocoFoundation.45.dylib $name
	install_name_tool -change /usr/local/lib/libPocoUtil.45.dylib @loader_path/libs/libPocoUtil.45.dylib $name
	install_name_tool -change /usr/local/lib/libPocoNet.45.dylib @loader_path/libs/libPocoNet.45.dylib $name
	install_name_tool -change /usr/local/lib/libPocoZip.45.dylib @loader_path/libs/libPocoZip.45.dylib $name
	install_name_tool -change /usr/local/lib/libPocoXML.45.dylib @loader_path/libs/libPocoXML.45.dylib $name
	install_name_tool -change /usr/local/lib/libPocoJSON.45.dylib @loader_path/libs/libPocoJSON.45.dylib $name
	install_name_tool -change /usr/local/lib/libCppUnit.1.dylib @loader_path/libs/libCppUnit.1.dylib $name
	install_name_tool -change /usr/local/opt/boost/lib/libboost_serialization.dylib @loader_path/libs/ibboost_serialization.dylib $name
	install_name_tool -change /usr/local/lib/$name @loader_path/lib/$name ./bobsgame
	otool -L $name
done

install_name_tool -change @rpath/../../../SDL2.framework/Versions/A/SDL2 @loader_path/../../../../../../../SDL2.framework/Versions/A/SDL2 ./SDL2_mixer.framework/Versions/A/Frameworks/smpeg2.framework/Versions/A/smpeg2
otool -L ./SDL2_mixer.framework/Versions/A/Frameworks/smpeg2.framework/Versions/A/smpeg2


install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image @loader_path/libs/SDL2_image.framework/Versions/A/SDL2_image ./bobsgame
install_name_tool -change @rpath/SDL2_mixer.framework/Versions/A/SDL2_mixer @loader_path/libs/SDL2_mixer.framework/Versions/A/SDL2_mixer ./bobsgame
install_name_tool -change @rpath/SDL2_net.framework/Versions/A/SDL2_net @loader_path/libs/SDL2_net.framework/Versions/A/SDL2_net ./bobsgame
install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf @loader_path/libs/SDL2_ttf.framework/Versions/A/SDL2_ttf ./bobsgame
install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 @loader_path/libs/SDL2.framework/Versions/A/SDL2 ./bobsgame
otool -L ./bobsgame
chmod 755 bobsgame
