# Toto je organizacni soubor pro konfiguraci projektu
# Nenachazi se zde pridani konkretnich veci, pouze delegujeme praci do podslozek, kde je vse dodefinovano

# Minimalne chceme verzi 2.4 (v podstate pro nase jednoduche ucely cokoliv 2.0+)
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

# nas projekt (workspace, solution, ...) se bude jmenovat takto
PROJECT(cpp-course-example-project)

# nasledujici tri radky reknou CMake, aby slo hledat CMakeLists.txt v danych podslozkach a provedlo ho

ADD_SUBDIRECTORY(program)
ADD_SUBDIRECTORY(library)
ADD_SUBDIRECTORY(dynamic)
