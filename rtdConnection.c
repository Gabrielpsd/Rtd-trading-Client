#include <stdio.h>
#include <initguid.h>
#include <stdint.h>
#include <ExDisp.h>

#include "rtdConnection.h"

// compilação: gcc rtdConnection.c -I include -L lib -o saida.exe -lole32 -loleaut32 -lcurl

// callback object for IRTDUpdateEvent
static volatile LONG g_update_flag = 0;

static WCHAR currentSymbol[SYMBOLSIZE] = L"";
static WCHAR currentTopic[TOPICSIZE] = L"";
static CRITICAL_SECTION symbolLock;
static BOOL shouldReconnect = FALSE;
static BOOL shouldExit = FALSE;  // Flag for application exit
static BOOL shouldPause = FALSE; // Add this line for pause control

static HRESULT STDMETHODCALLTYPE QueryInterface_impl(IRTDUpdateEvent *This, REFIID riid, void **ppvObject);
static ULONG STDMETHODCALLTYPE AddRef_impl(IRTDUpdateEvent *This);
static ULONG STDMETHODCALLTYPE Release_impl(IRTDUpdateEvent *);
static HRESULT STDMETHODCALLTYPE UpdateNotify_impl(IRTDUpdateEvent *This);

/* Idispatch Stub */
static HRESULT STDMETHODCALLTYPE GetTypeInfoCount_impl(IRTDUpdateEvent *, UINT *);
static HRESULT STDMETHODCALLTYPE GetTypeInfo_impl(IRTDUpdateEvent *, UINT, LCID, ITypeInfo **);
static HRESULT STDMETHODCALLTYPE GetIDsOfNames_impl(IRTDUpdateEvent *, REFIID, LPOLESTR *, UINT, LCID, DISPID *);
static HRESULT STDMETHODCALLTYPE Invoke_impl(IRTDUpdateEvent *, DISPID, REFIID, LCID, WORD, DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);
static HRESULT STDMETHODCALLTYPE get_HeartbeatInterval_impl(IRTDUpdateEvent *, long *);
static HRESULT STDMETHODCALLTYPE put_HeartbeatInterval_impl(IRTDUpdateEvent *, long);
static HRESULT STDMETHODCALLTYPE Disconnect_impl(IRTDUpdateEvent *);

// Global Vtable instance
static IRTDUpdateEventVtbl vtable = {

    // IUnknown
    QueryInterface_impl,
    AddRef_impl,
    Release_impl,

    // Idispatch
    GetTypeInfoCount_impl,
    GetTypeInfo_impl,
    GetIDsOfNames_impl,
    Invoke_impl,

    // IRTDUpdateEvent
    UpdateNotify_impl,
    get_HeartbeatInterval_impl,
    put_HeartbeatInterval_impl,
    Disconnect_impl};

/**
 * Creates a COM callback object
 */
MyCallBack *CreateCallback(void)
{
    MyCallBack *cb = (MyCallBack *)CoTaskMemAlloc(sizeof *cb);
    cb->lpVtbl = &vtable;
    cb->refCount = 1;
    return cb;
}

// QueryInterface implementation
HRESULT STDMETHODCALLTYPE QueryInterface_impl(IRTDUpdateEvent *This, REFIID riid, void **ppvObject)
{
    printf("QueryInterface called\n");
    if (IsEqualIID(riid, &IID_IUnknown) || IsEqualIID(riid, &IID_IDispatch) || IsEqualIID(riid, &IID_IRTDUpdateEvent))
    {
        *ppvObject = This;
        This->lpVtbl->AddRef(This);
        return S_OK;
    }

    *ppvObject = NULL;
    return E_NOINTERFACE;
}

// AddRef implementation
ULONG STDMETHODCALLTYPE AddRef_impl(IRTDUpdateEvent *This)
{
    MyCallBack *cb = (MyCallBack *)This;
    return InterlockedIncrement(&cb->refCount);
}

// Release implementation
ULONG STDMETHODCALLTYPE Release_impl(IRTDUpdateEvent *This)
{
    MyCallBack *cb = (MyCallBack *)This;
    LONG refCount = InterlockedDecrement(&cb->refCount);
    if (refCount == 0)
    {
        CoTaskMemFree(This);
    }
    return refCount;
}

// UpdateNotify: Notify of an update
/* This method is called by RTD server when data have any change */
HRESULT STDMETHODCALLTYPE UpdateNotify_impl(IRTDUpdateEvent *This)
{
    InterlockedExchange(&g_update_flag, 1);
    return S_OK;
}

// Heartbeat: return the heartbeat interval in milliseconds
HRESULT STDMETHODCALLTYPE get_HeartbeatInterval_impl(IRTDUpdateEvent *This, long *lHeartbeat)
{
    *lHeartbeat = 100; // 100ms for more frequent updates
    return S_OK;
}

// Sets the heartbeat interval
HRESULT STDMETHODCALLTYPE put_HeartbeatInterval_impl(IRTDUpdateEvent *This, long lHeartbeat)
{
    return S_OK;
}

// Called when the servers disconnects
HRESULT STDMETHODCALLTYPE Disconnect_impl(IRTDUpdateEvent *This)
{
    return S_OK;
}

/**
 * IDispatch stub implementations
 */
static HRESULT STDMETHODCALLTYPE GetTypeInfoCount_impl(IRTDUpdateEvent *this, UINT *pctinfo)
{
    *pctinfo = 0;
    return S_OK;
}

static HRESULT STDMETHODCALLTYPE GetTypeInfo_impl(IRTDUpdateEvent *this, UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
    *ppTInfo = NULL;
    return E_NOTIMPL;
}

static HRESULT STDMETHODCALLTYPE GetIDsOfNames_impl(IRTDUpdateEvent *this, REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
    return E_NOTIMPL;
}

static HRESULT STDMETHODCALLTYPE Invoke_impl(IRTDUpdateEvent *this, DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pvarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    return E_NOTIMPL;
}

static BOOL WINAPI ConsoleHandler(DWORD signal)
{
    if (signal == CTRL_C_EVENT || signal == CTRL_BREAK_EVENT)
    {
        wprintf(L"\nCtrl+C received, exiting...\n");
        shouldExit = TRUE;
        return TRUE; // Handled the signal
    }
    return FALSE; // Pass other signals to the next handler
}

/**
 * Input thread to handle symbol changes
 */
static DWORD WINAPI InputThreadProc(LPVOID lpParam)
{
    char input[256];
    WCHAR wideInput[256];

    while (!shouldExit)
    {
        // Only print the prompt if the stream is paused (waiting for user input)
        if (shouldPause)
        {
            printf("Enter new symbol (or 'quit' to exit): ");
            fflush(stdout);
        }
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        // Remove newline
        input[strcspn(input, "\r\n")] = 0;

        if (strcmp(input, "quit") == 0)
        {
            wprintf(L"\nShutting down...\n");
            shouldExit = TRUE; // Set global exit flag
            break;
        }

        // If input is empty, pause the stream and show prompt again
        if (input[0] == '\0')
        {
            shouldPause = TRUE;
            continue;
        }
        else
        {
            shouldPause = FALSE;
        }

        // Convert to wide string
        MultiByteToWideChar(CP_UTF8, 0, input, -1, wideInput, sizeof(wideInput) / sizeof(WCHAR));

        // Update symbol with lock protection
        EnterCriticalSection(&symbolLock);
        wcscpy_s(currentSymbol, 32, wideInput);
        shouldReconnect = TRUE;
        LeaveCriticalSection(&symbolLock);
        // Do not print the prompt here; let the main loop handle the next pause
    }

    return 0;
}

BOOL ConnectToSymbol(IRtdServer *pSrv, WCHAR *symbol, SAFEARRAY **ppArgs, int *pTopicID)
{
    // disconnect existing if needed
    if (*ppArgs)
    {
        pSrv->lpVtbl->DisconnectData(pSrv, *pTopicID);
        SafeArrayDestroy(*ppArgs);
        *ppArgs = NULL;
    }

    wchar_t topicStr[] = L"PETR4_B_0";
    wchar_t symbolStr[] = L"ULT";
    SAFEARRAYBOUND bound;
    BSTR bstr1, bstr2;
    LONG index;
    VARIANT_BOOL newVal = VARIANT_TRUE;

    bound.lLbound = 0;
    bound.cElements = 2;
    *ppArgs = SafeArrayCreate(VT_VARIANT, 1, &bound);

    if (!*ppArgs)
    {
        wprintf(L"Failed to create SafeArray.\n");
        return FALSE;
    }

    bstr2 = SysAllocString(topicStr);
    printf("bstr2: %ls\n", bstr2);
    printf("currentSymbol: %ls\n", currentSymbol);
    index = 1;
    SafeArrayPutElement(*ppArgs, &index, bstr2);
    SysFreeString(bstr2);

    bstr1 = SysAllocString(symbolStr);
    printf("bstr1: %ls\n", bstr1);
    printf("currentTopic: %ls\n", currentTopic);
    index = 0;
    SafeArrayPutElement(*ppArgs, &index, bstr1);
    SysFreeString(bstr1);
    
    // conect to data
    
    printf("topicID before ConnectData: %ld\n", *pTopicID);
    printf("About to call ConnectData with ppArgs = %p\n", ppArgs);
    HRESULT hr = pSrv->lpVtbl->ConnectData(pSrv, pTopicID, ppArgs, &newVal);

    printf("ConnectData returned: 0x%08X\n", hr);

    if (FAILED(hr))
    {
        wprintf(L"ConnectData failed: 0x%08X on connect to simbol: %ls\n", hr, symbol);
        return FALSE;
    }

    wprintf(L"ConnectData to simbol: %ls\n", symbol);
    return TRUE;
}

/*
    Format variant value as string (ALTERNATIVE VERSION, NOT USED IN THIS CODE, BUT CAN BE HELPFUL FOR DEBUGGING PURPOSES)


void FormatVariant(VARIANT *var, WCHAR *buffer, size_t bufferSize)
{
    if (var->vt == VT_BSTR)
    {
        wcsncpy_s(buffer, bufferSize, var->bstrVal, _TRUNCATE);
    }
    else if (var->vt == VT_R8)
    {
        swprintf_s(buffer, bufferSize, L"%f", var->dblVal);
    }
    else if (var->vt == VT_I4)
    {
        swprintf_s(buffer, bufferSize, L"%d", var->lVal);
    }
    else
    {
        wcsncpy_s(buffer, bufferSize, L"Unsupported type", _TRUNCATE);
    }
} */

/*
    Format variant value as string

*/
void FormatVariant(VARIANT *var, WCHAR *buffer, size_t bufferSize)
{
    switch (var->vt)
    {
    case VT_BSTR:
        swprintf(buffer, bufferSize, L"%s", var->bstrVal);
        break;
    case VT_R8:
        swprintf(buffer, bufferSize, L"%f", var->dblVal);
        break;
    case VT_I4:
        swprintf(buffer, bufferSize, L"%d", var->lVal);
        break;
    default:
        swprintf(buffer, bufferSize, L"Unsupported type (VT=%d)", var->vt);
        break;
    }
}

/*
    main
*/
int main(void)
{
    HRESULT hr;
    CLSID clsid;
    IRtdServer *pSrv = NULL;
    IRTDUpdateEvent *pCallback = NULL;
    SAFEARRAY *pArgs = NULL;
    SAFEARRAY *pOutArr = NULL;
    int topicCount = 0;
    int topicID = 0;
    BOOL running = TRUE;

    // Set up Ctrl+C handler
    SetConsoleCtrlHandler(ConsoleHandler, TRUE);
    wprintf(L"\n");
    wprintf(L"+--------------------------------------------------+\n");
    wprintf(L"| RTD Client - Real-time Market Data Viewer        |\n");
    wprintf(L"+--------------------------------------------------+\n\n");

    wprintf(L"\nPress \"Enter\" at any time to change symbols or to exit\n\n");

    // Initialize COM
    hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr))
    {
        wprintf(L"COM initialization failed: 0x%08X\n", hr);
        return 1;
    }

    // Initialize thread safety for symbol changes
    InitializeCriticalSection(&symbolLock);

    // Prompt for initial symbol
    char symbolInput[SYMBOLSIZE];
    wprintf(L"Enter stock symbol: ");
    if (fgets(symbolInput, sizeof(symbolInput), stdin) == NULL)
    {
        wprintf(L"Error reading input. Exiting.\n");
        return 1;
    }

    symbolInput[strcspn(symbolInput, "\r\n")] = 0; // Remove newline
    MultiByteToWideChar(CP_UTF8, 0, symbolInput, -1, currentSymbol, sizeof(currentSymbol) / sizeof(WCHAR));

    // Prompt for initial topic
    char topicInput[TOPICSIZE];
    wprintf(L"Enter data topic (LAST, BID, ASK, etc): ");
    if (fgets(topicInput, sizeof(topicInput), stdin) == NULL)
    {
        wprintf(L"Error reading input. Exiting.\n");
        return 1;
    }
    topicInput[strcspn(topicInput, "\r\n")] = 0; // Remove newline
    MultiByteToWideChar(CP_UTF8, 0, topicInput, -1, currentTopic, sizeof(currentTopic) / sizeof(WCHAR));

    // Create and start the input thread for symbol changes
    HANDLE inputThread = CreateThread(NULL, 0, InputThreadProc, NULL, 0, NULL);
    if (!inputThread)
    {
        wprintf(L"Failed to create input thread: %d\n", GetLastError());
        return 1;
    }

    // Create an instance of the RTD server
    hr = CoCreateInstance(&CLSID_MyRTDServer, NULL, CLSCTX_LOCAL_SERVER,
                          &IID_IRtdServer, (void **)&pSrv);
    printf("Here(1)");
    if (FAILED(hr))
    {
        wprintf(L"Failed to create RTD server instance: 0x%08X\n", hr);
        goto cleanup;
    }

    printf("Here(2)");
    // Create our callback and start the server
    pCallback = (IRTDUpdateEvent *)CreateCallback();
    printf("Here(3)");
    /*     hr = pSrv->lpVtbl->ServerStart(pSrv, pCallback, &(long){1000});
        printf("Here(4)");
        if (FAILED(hr))
        {
            wprintf(L"RTD server failed to start: 0x%08X\n", hr);
            goto cleanup;
        } */

    wprintf(L"\nRTD server connection established successfully\n");

    // Connect to initial symbol
    if (!ConnectToSymbol(pSrv, currentSymbol, &pArgs, &topicID))
    {
        wprintf(L"Initial connection failed\n");
        goto cleanup;
    }
    // Main event loop
    while (running && !shouldExit)
    {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                running = FALSE;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Check if we need to reconnect with a different symbol
        EnterCriticalSection(&symbolLock);
        if (shouldReconnect)
        {
            if (wcslen(currentSymbol) > 0)
            {
                wprintf(L"\nReconnecting with new symbol: %ls\n", currentSymbol);
                if (ConnectToSymbol(pSrv, currentSymbol, &pArgs, &topicID))
                {
                    wprintf(L"Connected to symbol: %ls\n", currentSymbol);
                }
                else
                {
                    wprintf(L"Failed to connect to symbol: %ls\n", currentSymbol);
                }
            }
            shouldReconnect = FALSE;
        }
        LeaveCriticalSection(&symbolLock);

        // Pause the stream if shouldPause is set
        if (shouldPause)
        {
            Sleep(100); // Wait until user enters a new symbol
            continue;
        }

        // Process RTD updates
        if (InterlockedCompareExchange(&g_update_flag, 0, 1))
        {
            topicCount = 0;
            hr = pSrv->lpVtbl->RefreshData(pSrv, &topicCount, &pOutArr);

            if (SUCCEEDED(hr) && pOutArr && topicCount > 0)
            {
                // Process the data
                if (pOutArr->cDims == 2)
                {
                    LONG rowCount = pOutArr->rgsabound[0].cElements;
                    LONG colCount = pOutArr->rgsabound[1].cElements;

                    VARIANT *pData = NULL;
                    hr = SafeArrayAccessData(pOutArr, (void **)&pData);

                    if (SUCCEEDED(hr))
                    {
                        // Get current timestamp for display
                        SYSTEMTIME st;
                        GetLocalTime(&st);

                        int i;

                        // Process all elements that were updated
                        for (i = 0; i < min(rowCount, topicCount); i++)
                        {
                            // Get the topic ID from the first column
                            if (pData[i * colCount].vt == VT_I4)
                            {
                                long rcvTopicID = pData[i * colCount].lVal;

                                // If this is our topic ID, print the value
                                if (rcvTopicID == topicID)
                                {
                                    // Get the value from the second column
                                    VARIANT *value = &pData[i * colCount + 1];
                                    WCHAR valueStr[128] = L"";

                                    // Format the value
                                    FormatVariant(value, valueStr, ARRAYSIZE(valueStr));

                                    // Print update with timestamp
                                    wprintf(L"[%02d:%02d:%02d.%03d] %ls = %ls\n",
                                            st.wHour, st.wMinute, st.wSecond, st.wMilliseconds,
                                            currentSymbol, valueStr);
                                }
                            }
                        }

                        SafeArrayUnaccessData(pOutArr);
                    }
                }

                SafeArrayDestroy(pOutArr);
                pOutArr = NULL;
            }
        }

        Sleep(100); // Small sleep to avoid excessive CPU usage
    }

cleanup:
    wprintf(L"Cleaning up and exiting\n");

    // Disconnect data if connected
    if (pArgs)
    {
        pSrv->lpVtbl->DisconnectData(pSrv, topicID);
        SafeArrayDestroy(pArgs);
        pArgs = NULL;
    }

    // Terminate RTD server
    if (pSrv)
    {
        pSrv->lpVtbl->ServerTerminate(pSrv);
        pSrv->lpVtbl->Release(pSrv);
    }

    // Release callback
    if (pCallback)
        pCallback->lpVtbl->Release(pCallback);

    // Clean up thread resources
    DeleteCriticalSection(&symbolLock);

    CoUninitialize();
    return 0;
}
