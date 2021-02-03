#pragma once

#ifdef ECACONTROLLER_EXPORTS
#define ECACONTROLLER_DLL __declspec(dllexport)
#else
#define ECACONTROLLER_DLL __declspec(dllimport)
#endif