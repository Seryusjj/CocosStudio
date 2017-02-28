
file(GLOB SRCS *.cpp *.h *.xmp)
set(PROJECT_NAME CocosStudioUI)

if(wxWidgets_FOUND)
     include(${wxWidgets_USE_FILE})
     add_executable(${PROJECT_NAME} ${SRCS})
         if(WIN32)
                set_target_properties (${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:windows")

                add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                                                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                                                   ${wxWidgets_LIB_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
		target_link_libraries(${PROJECT_NAME} ${COCOS2D_LIBS} ${wxWidgets_LIBRARIES})
	 else()
	         target_link_libraries(${PROJECT_NAME} ${COCOS2D_LIBS} 
						       ${wxWidgets_LIBRARIES}
						       ${GLEW_LIBRARIES}
						       ${GLUT_LIBRARY}
						       ${OPENGL_LIBRARIES}
						       ${X11_X11_LIB} 
						       ${X11_Xrandr_LIB}
						       ${X11_Xinerama_LIB}
						       ${X11_Xxf86vm_LIB}
						       ${X11_Xcursor_LIB}					      
						       ${PNG_LIBRARIES}
						       -lfontconfig)
         endif()



endif()
