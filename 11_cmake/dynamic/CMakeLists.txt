# Toto je konfigurace sestaveni dynamicke knihovny

# nalezneme vsechny .cpp a .h soubory a pridame je do promenne dynlibrary_sources
FILE(GLOB_RECURSE dynlibrary_sources dynamic/ *.cpp *.h)

# pridame dynamicky linkovanou (SHARED) knihovnu
ADD_LIBRARY(my-dynamic SHARED ${dynlibrary_sources})

# jelikoz pouzivame jeden z pristupu, jak docilit pohodlneho exportu/importu, potrebujeme
# v teto knihovne nastavit priznak kompilatoru, abychom zvolili spravny "smer" exportu/importu
# toto detekuje, ze chceme nastavit definici IS_DYNAMIC_SOURCE a nastavi ji do projektu
# dale viz dyninclude.h (je includovan jak z dynmain.cpp, tak z main.cpp (aplikace))
TARGET_COMPILE_DEFINITIONS(my-dynamic PUBLIC -DIS_DYNAMIC_SOURCE)
