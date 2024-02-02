#ifndef HACKTHREADINPUT
#define HACKTHREADINPUT

#include <windows.h>
/* Hack for dragon age inquisition variables */
extern DWORD fromThreadForHack;
extern DWORD toThreadForHack;

DWORD GetFromThreadForHack();
DWORD GetToThreadForHack();

#endif
