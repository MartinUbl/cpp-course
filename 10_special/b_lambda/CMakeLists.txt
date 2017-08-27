ADD_EXECUTABLE(10_b_lambda main.cpp)

IF (UNIX)
	TARGET_LINK_LIBRARIES(10_b_lambda pthread)
ENDIF()