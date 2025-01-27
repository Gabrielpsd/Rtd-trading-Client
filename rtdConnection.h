
#include <windows.h>
#include <objbase.h>
#include <oleauto.h>
#include <stdio.h>

// Callback function for DDE
HDDEDATA CALLBACK DdeCallback(
    UINT uType, 
    UINT uFmt, 
    HCONV hConv, 
    HSZ hsz1, 
    HSZ hsz2, 
    HDDEDATA hData, 
    ULONG_PTR dwData1, 
    ULONG_PTR dwData2);

int requisitaDadosEmTempoReal();