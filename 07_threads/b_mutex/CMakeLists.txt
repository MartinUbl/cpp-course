ADD_EXECUTABLE(07_b_mutex main.cpp)

IF (UNIX)
	TARGET_LINK_LIBRARIES(07_b_mutex pthread)
ENDIF()