#pragma once

// CMake nastavi do projektu dynamicke knihovny IS_DYNAMIC_SOURCE, do ostatnich ale ne
// dynamicka knihovna tedy bude sestavovana s dllexport, vse ostatni s dllimport
#ifdef IS_DYNAMIC_SOURCE
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif

// vytiskne radku s prefixem
DLL_DECLSPEC void printPrefixedLine(std::string& str);
