#include <stdio.h>
#include <initguid.h>
#include <stdint.h>
#include <ExDisp.h>

#include "rtdConnection.h"

// compilação: gcc rtdConnection.c -I include -L lib -o saida.exe -lole32 -loleaut32 -lcurl
typedef struct _IRTDUpdateVtbl
{
    QueryInterfacePtr *QueryInterface;
    AddRefPtr *AddRef;
    ReleasePtr *Release;
    MyRTDUpdate_UpdateNotifyPtr *UpdateNotify;
    MyRTDUpdate_HeartbeatPtr *Heartbeat;
} IRTDUpdateVtbl;

typedef struct _IRTDServerVtbl
{
    QueryInterfacePtr *QueryInterface;
    AddRefPtr *AddRef;
    ReleasePtr *Release;
    ConnectDataPtr *ConnectData;
    DisconnectDataPtr *DisconnectData;
    HeartbeatPtr *Heartbeat;
    RefreshDataPtr *RefreshData;
    ServerStartPtr *ServerStart;
    ServerTerminatePtr *ServerTerminate;
} IRTDServerVtbl;

typedef struct _IRTDUpdate
{
    IRTDUpdateVtbl *lpVtbl;
    DWORD refCount;
} IRTDUpdate;

typedef struct _IRTDServer
{
    IRTDServerVtbl *lpVtbl;
    DWORD refCount;
} IRTDServer;

// QueryInterface implementation
HRESULT STDMETHODCALLTYPE QueryInterface_Impl(void *This, REFIID riid, void **ppvObject)
{
    printf("QueryInterface called\n");
    if (IsEqualIID(riid, &IID_IUnknown) || IsEqualIID(riid, &IID_IRtdServer))
    {
        *ppvObject = This;
        ((IUnknown *)This)->lpVtbl->AddRef(This);
        return S_OK;
    }
    return E_NOINTERFACE;
}

// AddRef implementation
ULONG STDMETHODCALLTYPE AddRef_Impl(void *This)
{

    return ((IRTDUpdate *)This)->refCount++;
}

// Release implementation
ULONG STDMETHODCALLTYPE Release_Impl(void *This)
{
    ULONG refCount = ((IRTDUpdate *)This)->refCount--;
    if (refCount == 0)
    {
        free(This);
    }
    return refCount;
}

// UpdateNotify: Notify of an update
HRESULT STDMETHODCALLTYPE UpdateNotify_Impl(void *This)
{
    // Custom logic to handle update notification
    return S_OK;
}

// Heartbeat: Check server liveness
HRESULT STDMETHODCALLTYPE Heartbeat_Impl(void *This, int *lHeartbeat)
{
    *lHeartbeat = 1; // 1 indicates active
    return S_OK;
}

// Global Vtable instance
static IRTDUpdateVtbl vtable = {
    QueryInterface_Impl,
    AddRef_Impl,
    Release_Impl,
    UpdateNotify_Impl,
    Heartbeat_Impl};
#include <OleAuto.h>
#include <stdio.h>

void PrintSafeArrayStrings(SAFEARRAY *psa)
{
    if (!psa)
    {
        wprintf(L"NULL SAFEARRAY\n");
        return;
    }

    LONG lBound = 0, uBound = 0, i;
    HRESULT hr = SafeArrayGetLBound(psa, 1, &lBound);
    hr = hr ? hr : SafeArrayGetUBound(psa, 1, &uBound);

    if (FAILED(hr))
    {
        wprintf(L"Failed to get bounds.\n");
        return;
    }

    for (i = lBound; i <= uBound; i++)
    {
        BSTR bstr = NULL;
        hr = SafeArrayGetElement(psa, &i, &bstr);
        if (SUCCEEDED(hr))
        {
            wprintf(L"[%ld]: %s\n", i, bstr);
        }
        else
        {
            wprintf(L"Failed to get element at %ld\n", i);
        }
    }
}

// Helper to create a SAFEARRAY of 2 BSTR strings
SAFEARRAY *CreateStringArray(const wchar_t *str1, const wchar_t *str2)
{
    SAFEARRAY *psa;
    SAFEARRAYBOUND bound;
    BSTR bstr1, bstr2;
    LONG index;

    // Define 1D array with 2 elements
    bound.lLbound = 0;
    bound.cElements = 2;

    psa = SafeArrayCreate(VT_BSTR, 1, &bound);
    if (!psa)
    {
        wprintf(L"Failed to create SafeArray.\n");
        return NULL;
    }

    // Create and insert first string
    bstr1 = SysAllocString(str1);
    index = 0;
    SafeArrayPutElement(psa, &index, bstr1);
    SysFreeString(bstr1); // SafeArray makes a copy

    // Create and insert second string
    bstr2 = SysAllocString(str2);
    index = 1;
    SafeArrayPutElement(psa, &index, bstr2);
    SysFreeString(bstr2);

    return psa;
}

IRTDUpdate *CreateRTDUpdate()
{
    IRTDUpdate *obj = (IRTDUpdate *)malloc(sizeof(IRTDUpdate));
    if (obj)
    {
        obj->lpVtbl = &vtable;
        obj->refCount = 1; // Initial reference count
    }
    return obj;
}

int requestRTD();

int main(char argc, char **argv)
{

    requestRTD();

    return 0;
}

int requestRTD()
{

    LPOLESTR clsidstr = NULL;
    IRTDServer *pRTDServer = NULL;
    IRTDUpdate *pRTDUpdate = CreateRTDUpdate();

    StringFromCLSID(&CLSID_MyRTDServer, &clsidstr);
    printf("Our targeted CLSID is %ls\n", clsidstr);

    HRESULT hr;
    hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
                                  COINIT_DISABLE_OLE1DDE);

    if (FAILED(hr))
    {
        wprintf(L"COM initialization failed: 0x%08X\n", hr);
        return 1;
    }

    hr = CoCreateInstance(
        &CLSID_MyRTDServer,
        NULL,
        CLSCTX_LOCAL_SERVER,
        &IID_IRtdServer,
        (LPVOID *)&pRTDServer);

    if (FAILED(hr))
    {
        wprintf(L"Failed to create RTD object: 0x%08X\n", hr);
        CoUninitialize();
        return 1;
    }

    if (pRTDServer == NULL)
    {
        printf("pRTDServer é NULL!\n");
        return E_FAIL;
    }

    if (pRTDServer->lpVtbl == NULL)
    {
        printf("pRTDServer->lpVtbl é NULL!\n");
        return E_FAIL;
    }

    printf("Server create RefCount: %d\n", pRTDServer->refCount);
    printf("Server : %d\n", pRTDServer);

    /* hr = pRTDServer->lpVtbl->QueryInterface((IUnknown *)pRTDServer, &IID_IRtdServer, (void **)&pRTDUpdate);

    printf("After a release: %d\n", pRTDServer->refCount);

    if (FAILED(hr)) {
        wprintf(L"QueryInterface failed: 0x%08X\n", hr);
        pRTDServer->lpVtbl->Release(pRTDServer);
        CoUninitialize();
        return 1;
    } */

    SAFEARRAY *string = CreateStringArray(L"PETR4_B_0", L"ULT");
    SAFEARRAY *response;
    VARIANT_BOOL getNewValues = VARIANT_TRUE;
    int topicID = 0, i; // Example TopicID, should be set according to your needs

    hr = pRTDServer->lpVtbl->ConnectData(pRTDServer, &topicID, string, &getNewValues);

    if (FAILED(hr))
    {
        wprintf(L"ConnectData failed: 0x%08X\n", hr);
    }
    else
    {
        printf("Printing psa");
        PrintSafeArrayStrings(string);
        wprintf(L"ConnectData succeeded for TopicID: %ld\n", topicID);
        printf("Imprimindo SAFE ARRAY\n");
        i = 0;
        while (i < 10)
        {
            /* code */

            wprintf(L"RefreshData before request: %f\n", response);
            hr = pRTDServer->lpVtbl->RefreshData(pRTDServer, &topicID, &response);
            wprintf(L"RefreshData: 0x%08X\n", hr);
            wprintf(L"RefreshData returned: %f\n", response);
            printf("Topic ID: %ld\n", topicID);

            if (topicID == 0)
            {
                printf("No update on TOPIC. \n");
            }
            else if (response != NULL)
            {
                LONG linhaUm, linhaDois, colunaUm, colunaDois;
                LONG i, j;

                printf("Cheguei aqui (0)\n");
                SafeArrayGetLBound(response, 1, &linhaUm);
                SafeArrayGetUBound(response, 1, &linhaDois);
                SafeArrayGetLBound(response, 2, &colunaUm);
                SafeArrayGetUBound(response, 2, &colunaDois);

                printf("Cheguei aqui (1)\n");
                printf("Response dimensions: %ld x %ld\n", linhaDois - linhaUm + 1, colunaDois - colunaUm + 1);
                printf("Cheguei aqui (2)\n");
                for (i = linhaUm; i <= linhaDois; i++)
                {
                    for (j = colunaUm; j <= colunaDois; j++)
                    {
                        BSTR bstr;
                        hr = SafeArrayGetElement(response, (LONG[]){i, j}, &bstr);
                        if (SUCCEEDED(hr))
                        {
                            wprintf(L"[%ld, %ld]: %s\n", i, j, bstr);
                        }
                        else
                        {
                            wprintf(L"Failed to get element at [%ld, %ld]\n", i, j);
                        }
                    }
                }
            }
            Sleep(1000);
            i++;
        }
    }

    printf("ServerStart RefCount: %0x%08X\n", hr);

    if (FAILED(hr))
    {
        wprintf(L"ServerStart failed: 0x%08X\n", hr);
        pRTDServer->lpVtbl->Release(pRTDServer);
        CoUninitialize();
        return 1;
    }

    pRTDServer->lpVtbl->Release(pRTDServer);
    pRTDUpdate->lpVtbl->Release(pRTDUpdate);

    CoUninitialize();
    return 0;
}