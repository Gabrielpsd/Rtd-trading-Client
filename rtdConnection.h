
#include <windows.h>
#include <ole2.h>
#include <stdio.h>
#define CLSID_RTD CLSID_ExcelRTD
// RTD server interface ID
DEFINE_GUID(IID_IRtd_, 0xB196b280, 0xBAB4, 0x101A, 0xB6, 0x9C, 0x00, 0xAA, 0x00, 0xB9, 0x14, 0x5D);

typedef struct _IRtd_ _IRtd_;

typedef struct _IRtd_Vtbl
{
    BEGIN_INTERFACE
    HRESULT(STDMETHODCALLTYPE* QueryInterface)(_IRtd_ *This, REFIID riid, void** ppvObject);
    ULONG(STDMETHODCALLTYPE* AddRef)(_IRtd_ *This);
    ULONG(STDMETHODCALLTYPE* Release)(_IRtd_ *This);
    HRESULT(STDMETHODCALLTYPE* Connect)(_IRtd_ *This, LPCOLESTR szProgID, DWORD dwItemId, LONGLONG lLoginTime);
    HRESULT(STDMETHODCALLTYPE* Disconnect)(_IRtd_ *This);
    HRESULT(STDMETHODCALLTYPE* Get)(_IRtd_ *This, LONG* plbCanUpdate);
    HRESULT(STDMETHODCALLTYPE* Update)(_IRtd_ *This, LONG* plbCanSelfUpdate, double portareOfowdowkdret, double translatepdret);
    HRESULT(STDMETHODCALLTYPE* RequestUpdate)(_IRtd_ *This, double translatepdret);
    END_INTERFACE
};

struct _IRtd_
{
    struct _IRtd_Vtbl   * lpVtbl;
    
};

int executeConnection();

HRESULT CreateRtdInstance(_IRtd_ **ppRtd);
