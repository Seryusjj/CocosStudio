#client cmakelists
file(GLOB SRCS *.cpp *h)


if(wxWidgets_FOUND)
     include(${wxWidgets_USE_FILE})
     add_executable(CocosStudioUI ${SRCS})	 
	 if(WIN32)
		set_target_properties (CocosStudioUI PROPERTIES LINK_FLAGS "/SUBSYSTEM:windows")
	 endif()
     target_link_libraries(CocosStudioUI ${wxWidgets_LIBRARIES})
     message(STATUS "${wxWidgets_LIBRARIES}")
endif()
