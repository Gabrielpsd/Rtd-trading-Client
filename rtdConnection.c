#include <windows.h>
#include <stdio.h>
#include <initguid.h>
#include <stdint.h>
#include <ExDisp.h>

#include "rtdConnection.h"


typedef struct _IRTDUpdateVtbl{
    QueryInterfacePtr *QueryInterface;
    AddRefPtr *AddRef;
    ReleasePtr *Release;
    MyRTDUpdate_UpdateNotifyPtr *UpdateNotify;
    MyRTDUpdate_HeartbeatPtr *Heartbeat;
} IRTDUpdateVtbl;

typedef struct _IRTDServerVtbl{
    QueryInterfacePtr *QueryInterface;
    AddRefPtr *AddRef;
    ReleasePtr *Release;
    ServerStartPtr *ServerStart;
    ServerTerminatePtr *ServerTerminate;
    ConnectDataPtr *ConnectData;
    RefreshDataPtr *RefreshData;
    DisconnectDataPtr *DisconnectData;
    HeartbeatPtr *Heartbeat;
} IRTDServerVtbl;

typedef struct _IRTDUpdate{
    IRTDUpdateVtbl *lpVtbl;
    DWORD refCount;
} IRTDUpdate;


typedef struct _IRTDServer{
    IRTDServerVtbl *lpVtbl;
    DWORD refCount;
} IRTDServer;

HRESULT STDMETHODCALLTYPE QueryInterface(void* This, REFIID riid, void** ppvObject){
    FILE *logFile = fopen("rtdConnection.log", "a+");
    if (logFile == NULL) {
        printf("Failed to open log file\n");
        return E_FAIL;
    }
    fprintf(logFile, "QueryInterface called\n");
    fclose(logFile);
    IRTDServer *pRTDServer = (IRTDServer *)This;
    if (IsEqualIID(riid, &IID_IRtdServer)) {
        *ppvObject = pRTDServer;
        pRTDServer->lpVtbl->AddRef(pRTDServer);
        return S_OK;
    } else if (IsEqualIID(riid, &IID_IUnknown)) {
        *ppvObject = (IUnknown *)pRTDServer;
        pRTDServer->lpVtbl->AddRef(pRTDServer);
        return S_OK;
    } else {
        *ppvObject = NULL;
        return E_NOINTERFACE;
    }
}
ULONG STDMETHODCALLTYPE AddRef(void* This){
    FILE *logFile = fopen("rtdConnection.log", "a+");
    if (logFile == NULL) {
        printf("Failed to open log file\n");
        return E_FAIL;
    }
    fprintf(logFile, "AddRef called\n");
    fclose(logFile);
    IRTDServer *pRTDServer = (IRTDServer *)This;
    pRTDServer->refCount++;
    return pRTDServer->refCount;
}
ULONG STDMETHODCALLTYPE Release(void* This)
{
    FILE *logFile = fopen("rtdConnection.log", "a+");
    if (logFile == NULL) {
        printf("Failed to open log file\n");
        return E_FAIL;
    }
    fprintf(logFile, "Release called\n");
    fclose(logFile);
    IRTDServer *pRTDServer = (IRTDServer *)This;
    pRTDServer->refCount--;
    if (pRTDServer->refCount == 0) {
        free(pRTDServer);
        return 0;
    }
    return pRTDServer->refCount;
}
HRESULT STDMETHODCALLTYPE MyRTDUpdate_UpdateNotify(void* This)
{
    FILE *logFile = fopen("rtdConnection.log", "a+");
    if (logFile == NULL) {
        printf("Failed to open log file\n");
        return E_FAIL;
    }
    fprintf(logFile, "UpdateNotify called\n");
    fclose(logFile);
    // This function is called when the RTD server needs to notify Excel of a data change.
    // Implement your logic here.
    printf("UpdateNotify called\n");
    return S_OK;
}
HRESULT STDMETHODCALLTYPE MyRTDUpdate_Heartbeat(void* This, int* pResponse){
    // This function is called to check if the RTD server is still alive.
    // Implement your logic here.
    FILE *logFile = fopen("rtdConnection.log", "a+");
    if (logFile == NULL) {
        printf("Failed to open log file\n");
        return E_FAIL;
    }
    fprintf(logFile, "HeartBeat called\n");
    fclose(logFile);
    *pResponse = 1; // Indicate that the server is alive
    return S_OK;
}

int requestRTD();


 int main(char argc, char **argv){
    
    requestRTD();

    return 0;
 }

int requestRTD(){

    LPOLESTR clsidstr = NULL;
    IRTDServer *pRTDServer = NULL;
    IRTDUpdate *pRTDUpdate = NULL;

    StringFromCLSID(&CLSID_MyRTDServer, &clsidstr);
    printf("Our targeted CLSID is %ls\n", clsidstr);
    
    HRESULT hr;
    hr = CoInitialize(NULL);

    if (FAILED(hr)) {
        wprintf(L"COM initialization failed: 0x%08X\n", hr);
        return 1;
    }
    
     hr = CoCreateInstance(
        &CLSID_MyRTDServer,     
        NULL,
        CLSCTX_LOCAL_SERVER,       
        &IID_IRtdServer,   
        (LPVOID*)&pRTDServer
    );

    if (FAILED(hr)) {
        wprintf(L"Failed to create RTD object: 0x%08X\n", hr);
        CoUninitialize();
        return 1;
    }

    printf("Server create RefCount: %d\n", pRTDServer->refCount);
    printf("Server : %d\n", pRTDServer);

    hr = pRTDServer->lpVtbl->QueryInterface((IUnknown *)pRTDServer, &IID_IRtdServer, (void **)&pRTDUpdate);

    if (FAILED(hr)) {
        wprintf(L"QueryInterface failed: 0x%08X\n", hr);
        pRTDServer->lpVtbl->Release(pRTDServer);
        CoUninitialize();
        return 1;
    }
    printf("QueryInterface RefCount: %d\n", pRTDUpdate->refCount);
    hr = pRTDServer->lpVtbl->ServerStart((IUnknown *)pRTDUpdate);

    if (FAILED(hr)) {
        wprintf(L"ServerStart failed: 0x%08X\n", hr);
        pRTDServer->lpVtbl->Release(pRTDServer);
        CoUninitialize();
        return 1;
    }

    printf("Iniciado conexão\n");
    pRTDServer->lpVtbl->Release(pRTDServer);
    CoUninitialize();
    return 0;
}