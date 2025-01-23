#include "rtdConnection.h"


HRESULT CreateRtdInstance(_IRtd_ **ppRtd)
{
    CLSID clsid;
    HRESULT hr = CLSIDFromProgID(L"RTDTrading.RTDServer", &clsid);
HRESULT hr = CoCreateInstance(L"{1B611A56-6802-11D0-A097-00C05BF9F6C6}", NULL, CLSCTX_INPROC_SERVER, L"{272D2E65-05FB-4500-BD7B-5905D5B0A1B8}", (void**)ppRtd);
    if (FAILED(hr))
    {
        printf("Failed to create RTD instance. Error: 0x%08lx\n", hr);
    }
    return hr;
}


int executeConnection()
{
    HRESULT hr;
    _IRtd_ *pRtd = NULL;
    LONG lCookie = 0;

    // Initialize COM
    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("Failed to initialize COM. Error: 0x%08lx\n", hr);
        return 1;
    }

    // Create an RTD instance
    hr = CreateRtdInstance(&pRtd);
    if (FAILED(hr))
    {
        goto cleanup;
    }

    // Connect to the RTD server
    hr = pRtd->lpVtbl->Connect(L"{272D2E65-05FB-4500-BD7B-5905D5B0A1B8}", 1, 0);
    if (FAILED(hr))
    {
        printf("Failed to connect to RTD server. Error: 0x%08lx\n", hr);
        goto cleanup;
    }

    // Set up event handling
    pRtd->lpVtbl->AddRef();
    lCookie = GetCurrentThreadId();
    SetLastError(0);


    // Request an update
    hr = pRtd->lpVtbl->RequestUpdate(0.0);

    if (FAILED(hr))
    {
        printf("Failed to request RTD update. Error: 0x%08lx\n", hr);
        goto cleanup;
    }

    // Keep the main thread running
    Sleep(INFINITE);
cleanup:
    if (pRtd)
    {
        pRtd->lpVtbl->Disconnect();
        pRtd->lpVtbl->Release();
    }

    CoUninitialize();

    return 0;
}