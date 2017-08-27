ADD_EXECUTABLE(07_c_cond_variables main.cpp)

IF (UNIX)
	TARGET_LINK_LIBRARIES(07_c_cond_variables pthread)
ENDIF()