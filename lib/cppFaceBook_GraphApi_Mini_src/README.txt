//##############################################################################
//                                                                             #
// Copyright 2011 Meir yanovich,	                                           #
//	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com  #
//                                                                             #
//##############################################################################

to compile do this simple steps:
-- on visual studio express 2008 
-------------------------------------------
1. download latest Qt sdk for visual studio i used version 4.7.1 for windows xp. 
2. open cmd ,point it to this directory. 
3. type in the cmd : qmake -tp vc FB_GraphApi.pro 
    it will create the visual studio c++ project files .
4.load the created vc solution file. 
5.open the file "FBApi.cpp" in the top fill your developer id and application id you got from facebook. 
  group id if you like to use the demo example 	
5 hit f5 to compile and run the code.

-- on Qt creator 2.1 
1. download latest Qt sdk for mingw i used version 4.7.2 for windows xp. 
   download the mingw in the same page , and Qt creator 2.1 for windows
2. open the FB_GraphApi_mini.pro into the Qt Creator , it supposed to configure the project.
3. open the file "FBApi.cpp" in the top fill your developer id and application id you got from facebook. 
   group id if you like to use the demo example 
4. hit ctrl+shift+B or the hammer icon to build . 

