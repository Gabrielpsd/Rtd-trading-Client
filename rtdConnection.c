#include <windows.h>
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
    ULONG_PTR dwData2) 
{
    return NULL;
}

int requisitaDadosEmTempoReal() {
    DWORD dwDdeInstance = 0;
    HSZ hszService = 0, hszTopic = 0;
    HCONV hConv = NULL;

    // Initialize DDE
    UINT result = DdeInitialize(&dwDdeInstance, DdeCallback, APPCLASS_STANDARD, 0);
    if (result != DMLERR_NO_ERROR) {
        printf("DDE Initialization failed: 0x%08X\n", result);
        return -1;
    }

    // Create string handles for service and topic
    hszService = DdeCreateStringHandle(dwDdeInstance, "profitchart", CP_WINANSI);
    hszTopic = DdeCreateStringHandle(dwDdeInstance, "cot!'WINZ24.NEG'", CP_WINANSI); // Replace "TopicName" with the server's topic

    // Connect to the DDE server
    hConv = DdeConnect(dwDdeInstance, hszService, hszTopic, NULL);
    if (!hConv) {
        printf("Failed to connect to DDE server. Error: 0x%08X\n", DdeGetLastError(dwDdeInstance));
        DdeFreeStringHandle(dwDdeInstance, hszService);
        DdeFreeStringHandle(dwDdeInstance, hszTopic);
        DdeUninitialize(dwDdeInstance);
        return -1;
    }

    printf("Connected to DDE server.\n");

    // Example: Request data from the server
    HDDEDATA hData = DdeClientTransaction(
        NULL, 0, 
        hConv, 
        DdeCreateStringHandle(dwDdeInstance, "RequestItem", CP_WINANSI), 
        CF_TEXT, 
        XTYP_REQUEST, 
        1000, 
        NULL);

    if (hData) {
        // Retrieve the data
        char *pData = (char *)DdeAccessData(hData, NULL);
        printf("Received data: %s\n", pData);
        DdeUnaccessData(hData);
        DdeFreeDataHandle(hData);
    } else {
        printf("Failed to request data. Error: 0x%08X\n", DdeGetLastError(dwDdeInstance));
    }

    // Disconnect and clean up
    DdeDisconnect(hConv);
    DdeFreeStringHandle(dwDdeInstance, hszService);
    DdeFreeStringHandle(dwDdeInstance, hszTopic);
    DdeUninitialize(dwDdeInstance);

    printf("DDE communication completed.\n");
    return 0;
}