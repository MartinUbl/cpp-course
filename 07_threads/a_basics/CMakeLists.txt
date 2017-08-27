ADD_EXECUTABLE(07_a_basics main.cpp)

IF (UNIX)
	TARGET_LINK_LIBRARIES(07_a_basics pthread)
ENDIF()