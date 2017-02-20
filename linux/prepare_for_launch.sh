#!/bin/sh
for file in *.so*
do
	name=${file##*/}
	echo $name
done

sudo ldd ./bobsgame | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -v '{}' ./
sudo ldd ./libPocoFoundation.so.45 | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -v '{}' ./
sudo ldd ./libPocoNet.so.45 | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -v '{}' ./
sudo ldd ./libPocoJSON.so.45 | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -v '{}' ./
sudo ldd ./libPocoXML.so.45 | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -v '{}' ./
sudo ldd ./libPocoUtil.so.45 | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -v '{}' ./
sudo ldd ./libPocoZip.so.45 | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -v '{}' ./
sudo ldd ./libCppUnit.so.1 | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -v '{}' ./
sudo ldd ./libboost_serialization.so.1.62.0 | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -v '{}' ./
sudo ldd ./bobsgame | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -v '{}' ./
strip bobsgame
chmod 755 bobsgame
rm VBoxOGLcrutil.so
rm libGL.so.1
rm libc.so.6
rm libdl.so.2
rm libm.so.6
rm libpthread.so.0
rm libresolv.so.2

rm libasyncns* #libasyncns is a C library for Linux/Unix for executing name service queries asynchronously
rm libdbus* #D-Bus supplies both a system daemon (for events such as "new hardware device added" or "printer queue changed") and a per-user-login-session daemon (for general IPC needs among user applications).
rm libffi* #The libffi library provides a portable, high level programming interface to various calling conventions
rm libgcc_s* #GCC provides a low-level runtime library, libgcc.a or libgcc_s.so.1 on some platforms
rm libglib* #GTK General purpose utility library
rm libnsl* #libnsl - This library contains the public client interface for NIS(YP) and NIS+ in a IPv6 ready version
rm libreadline* #The GNU Readline library provides a set of functions for use by applications that allow users to edit command lines as they are typed in
rm librt* #librt, libposix4 - POSIX.1b Realtime Extensions library 
rm libstdc++* #libc++ is a new implementation of the C++ standard library, targeting C++11
rm libtinfo* #symlink to ncurses for use in cuda and other packages
rm libway*
rm libwrap* #TCP Wrapper is a host-based networking ACL system
rm libX*
rm libxcb* # The libxcb package provides an interface to the X Window System protocol
rm libxkbcommon*
rm libxshm*

rm libasound.so.2
rm libpulse*




echo ok
