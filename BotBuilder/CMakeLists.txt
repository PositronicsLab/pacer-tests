cmake_minimum_required(VERSION 2.8.3)

project(BotBuilder)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMakeModules)


SET(CMAKE_C_FLAGS_DEBUG "-g")
SET(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")


set (LIBS "")


find_package( X11 REQUIRED )
set (LIBS ${LIBS} ${X11_LIBRARIES})


find_package( DL REQUIRED )
set (LIBS ${LIBS} ${DL_LIBRARIES})


find_package( Xext REQUIRED )
set (LIBS ${LIBS} ${Xext_LIBRARIES})


find_package( Xinerama REQUIRED )
set (LIBS ${LIBS} ${Xinerama_LIBRARIES})

find_package( Xft REQUIRED )
set (LIBS ${LIBS} ${Xft_LIBRARIES})

find_package( Xcursor REQUIRED )
set (LIBS ${LIBS} ${Xcursor_LIBRARIES})

find_package( fontconfig REQUIRED )
set (LIBS ${LIBS} ${fontconfig_LIBRARIES})

find_package( Xfixes REQUIRED )
set (LIBS ${LIBS} ${_LIBRARIES})
