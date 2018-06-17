#pragma once

#ifdef MY_STATIC_LIBRARY // In case of static library
#define API
#else  // In case of dynamic library
#ifdef MY_DYNAMIC_LIBRARY
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif
#endif