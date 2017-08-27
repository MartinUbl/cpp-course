ADD_EXECUTABLE(07_d_atomic main.cpp)

IF (UNIX)
	TARGET_LINK_LIBRARIES(07_d_atomic pthread)
ENDIF()