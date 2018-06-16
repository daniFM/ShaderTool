#pragma once

#ifdef MY_STATIC_LIBRARY // En caso de usar librería estática
#define API
#else  // En caso de usar librería dinámica
#ifdef MY_DYNAMIC_LIBRARY
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif
#endif