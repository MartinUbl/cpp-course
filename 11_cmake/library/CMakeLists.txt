# Toto je konfigurace sestaveni staticke knihovny

# najdeme vsechny .cpp a .h soubory a ulozime je do library_sources
FILE(GLOB_RECURSE library_sources library/ *.cpp *.h)

# pridame staticky linkovanou (STATIC) knihovnu do projektu
ADD_LIBRARY(my-library STATIC ${library_sources})
