ADD_EXECUTABLE(13_c_deadlock main.cpp)

IF (UNIX)
	TARGET_LINK_LIBRARIES(13_c_deadlock pthread)
ENDIF()