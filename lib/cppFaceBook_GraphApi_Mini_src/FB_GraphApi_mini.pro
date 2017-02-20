##############################################################################
#                                                                              
# Copyright 2011 Meir yanovich,								 
#	   Questions just email me to meiry242@gmail.com / meiryanovich@gmail.com   
#                                                                              
###############################################################################
QT      +=  webkit network script
HEADERS =   MainWindowContainer.h \
	    FBApi.h \	    
	    HttpClient.h \
	    UT.h  \
	    lib_json/json_batchallocator.h  \
	    lib_json/json_internalarray.inl \
	    lib_json/json_internalmap.inl \
	    lib_json/json_valueiterator.inl
	    
	    
SOURCES =   main.cpp \
            MainWindowContainer.cpp \
	    FBApi.cpp \	    
	    HttpClient.cpp \
	    UT.cpp \
	    lib_json/json_reader.cpp \
	    lib_json/json_value.cpp \
	    lib_json/json_writer.cpp

INCLUDEPATH += . lib_json/include lib_json/include/json

FORMS += fbapi_gui.ui 
	     
  

 
 