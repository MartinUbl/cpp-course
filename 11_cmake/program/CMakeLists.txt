# Toto je soubor, kde budeme konfigurovat nas hlavni program

# najdeme vsechny .cpp a .h soubory a vlozime je do promenne program_sources
FILE(GLOB_RECURSE program_sources . *.cpp *.h)

# pridame cil typu "executable" a rekneme, ze ma sestavat z program_sources zdrojaku
ADD_EXECUTABLE(my-program ${program_sources})

# treba budeme potrebovat OpenSSL knihovnu - najdeme ji, REQUIRED znaci, ze bez ni to fakt nepude
FIND_PACKAGE(OpenSSL REQUIRED)
# pokud byla knihovna nalezena, prostredi nastavi promennou OpenSSL_FOUND (mimo jine)
IF(OpenSSL_FOUND)
	# povedlo se, pridame OpenSSL include slozky (find skript nam nasel i je a nastavil promennou)
	INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${OPENSSL_INCLUDE_DIR})
ELSE()
	# vypiseme nejakou hlasku, znamenajici prusvih, pokud jsme OpenSSL nenasli
	MESSAGE(FATAL_ERROR "OpenSSL not found! Make sure you have OpenSSL installed!")
ENDIF()

# prilinkujeme k nasi aplikaci (my-program, prvni argument) knihovny co potrebujeme
# staticka knihovna je jasna - budeme linkovat staticky celou
# u dynamicke knihovny prilinkujeme minimalni statickou knihovnu s exporty (CMake zaridi)
# a take by bylo dobre prilinkovat vyse nalezene OpenSSL knihovny
TARGET_LINK_LIBRARIES(my-program my-library my-dynamic ${OPENSSL_LIBRARIES})
