cmake_minimum_required(VERSION 3.0)

project(CocosStudio)


set(wxWidgets_CONFIGURATION "mswu")
SET(wxWidgets_USE_STATIC off)
set(OPENGL_LIBRARIES "")
set(GLUT_LIBRARY "")
set(X11_LIBRARIES "")

if(UNIX)
        set(wxWidgets_USE_RELEASE --toolkit=base --prefix=/usr)
        find_package(OpenGL REQUIRED)
        find_package(GLUT REQUIRED)
        #find_package(X11 REQUIRED)
        set(X11_LIBRARIES "")
        message ( STATUS " X11_LIBRARIES: " ${X11_LIBRARIES} )

        message(STATUS "Config for unix")
endif()

if(WIN32)
	set(wxWidgets_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/wxWidgets/")  
	set(wxWidgets_LIB_DIR "${wxWidgets_ROOT_DIR}/lib/vc_dll") 
	
	message(STATUS "Config for win32")
endif()



find_package(wxWidgets COMPONENTS gl core base REQUIRED)


if(UNIX)    
    add_definitions(-std=c++11)
    add_definitions(-lX11)
    set(CMAKE_CXX_FLAGS "${wxWidgets_CXX_FLAGS}")
endif()

if (MSVC)
  set (CMAKE_CXX_FLAGS "/MT /DWIN32 /D_WINDOWS /W3 /GR /Zi /EHsc")
  set (CMAKE_CXX_FLAGS_DEBUG "/EHsc /D_DEBUG /MTd /Ob0 /Od")
  set (CMAKE_CXX_FLAGS_RELEASE "/EHsc /MT /Ox /Ob2 /Oi /Ot /Oy /GL /DNDEBUG")
endif ()

#set(BUILD_SHARED_LIBS ON CACHE BOOL "Set to ON to build DSO libraries" FORCE)
#COCOS

set(COCOS2D_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/external/cocos2d-x)

include_directories(/usr/local/include/GLFW
                    /usr/include/GLFW
                    ${COCOS2D_ROOT}/cocos
                    ${COCOS2D_ROOT}/cocos/platform
                    ${COCOS2D_ROOT}/cocos/audio/include/)

set(COCOS_EXTERNAL_DIR ${COCOS2D_ROOT}/external)

if(UNIX)
    add_definitions(-DLINUX)
    set(COCOS2D_LIB_DIR ${COCOS2D_ROOT}/build/linux-build/lib)
    set(PLATFORM_FOLDER linux)
endif()

if(WIN32)
    add_definitions (-DWIN32)
    set(COCOS2D_LIB_DIR ${COCOS2D_ROOT}/prebuilt/win32)
    set(PLATFORM_FOLDER win32)
endif()
#cocos dependencies includes

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${COCOS2D_ROOT}/cmake/Modules/")
include(CocosUsePrebuiltLibs)

set(COCOS2D_LIBS  ${PNG_LIBRARIES}
                  ${JPEG_LIBRARIES}
                  ${TIFF_LIBRARIES}
                  ${GLFW3_LIBRARIES}
                  ${CHIPMUNK_LIBRARIES}
                  ${ZLIB_LIBRARIES}
                  ${CURL_LIBRARIES}
                  ${FREETYPE_LIBRARIES}
                  ${WEBP_LIBRARIES}
                  ${WEBSOCKETS_LIBRARIES}
                  ${SQLITE3_LIBRARIES}
                  ${GLEW_LIBRARIES}
                  ${ICONV_LIBRARIES}
                  ${MPG123_LIBRARIES}
                  ${VORBIS_LIBRARIES}
                  ${OPENAL_LIBRARIES})


if ( WIN32 )
  
    set(COCOS2D_LIBS  ${COCOS2D_LIBS}
                      ${COCOS2D_LIB_DIR}/lua51-2015.lib
                      ${COCOS2D_LIB_DIR}/libsimulator_2015.lib
                      ${COCOS2D_LIB_DIR}/librecast_2015.lib
                      ${COCOS2D_LIB_DIR}/libluacocos2d_2015.lib
                      ${COCOS2D_LIB_DIR}/libjscocos2d_2015.lib
                      ${COCOS2D_LIB_DIR}/libcocos2d_2015.lib
                      ${COCOS2D_LIB_DIR}/libbox2d_2015.lib
                      ${COCOS2D_LIB_DIR}/libbullet_2015.lib
                      ${COCOS2D_LIB_DIR}/libSpine_2015.lib)
  
  

  
  include_directories(
  ${COCOS_EXTERNAL_DIR}/glfw3/include/win32
  ${COCOS_EXTERNAL_DIR}/win32-specific/gles/include/OGLES

  message(STATUS "${COCOS2D_LIBS}")
)
endif()


if ( UNIX )

    set(COCOS2D_LIBS  ${COCOS2D_LIBS}
                      ${COCOS2D_LIB_DIR}/libbullet.a
                      ${COCOS2D_LIB_DIR}/libcocos2d.a
                      ${COCOS2D_LIB_DIR}/libcocos2dInternal.a
                      ${COCOS2D_LIB_DIR}/libflatbuffers.a
                      ${COCOS2D_LIB_DIR}/libjscocos2d.a
                      ${COCOS2D_LIB_DIR}/libluacocos2d.a
                      ${COCOS2D_LIB_DIR}/librecast.a
                      ${COCOS2D_LIB_DIR}/libtinyxml2.a
                      ${COCOS2D_LIB_DIR}/libunzip.a
                      ${COCOS2D_LIB_DIR}/libxxhash.a)

  message(STATUS "${COCOS2D_LIBS}")

endif()






add_subdirectory(src)

