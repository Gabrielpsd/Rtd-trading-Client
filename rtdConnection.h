
#ifndef RTDCONNECTION_H
#define RTDCONNECTION_H
#include <oaidl.h>
#include <ocidl.h>
#include <initguid.h>

#define SYMBOLSIZE 64
#define TOPICSIZE 32

// Forward declarations
typedef struct IRtdServer IRtdServer;
typedef struct IRTDUpdateEvent IRTDUpdateEvent;
typedef struct IRtdServerVtbl IRtdServerVtbl;
typedef struct IRTDUpdateEventVtbl IRTDUpdateEventVtbl;

// Define the CLSID of the RTD server (replace with your RTD server's CLSID)
DEFINE_GUID(CLSID_MyRTDServer,
            0x272D2E65, 0x05FB, 0x4500, 0xBD, 0x7B, 0x59, 0x05, 0xD5, 0xB0, 0xA1, 0xB8);

// Define the IID for IRtdServer
DEFINE_GUID(IID_IRtdServer,
            0xEC0E6191, 0xDB51, 0x11D3, 0x8F, 0x3E, 0x00, 0xC0, 0x4F, 0x36, 0x51, 0xB8);

// Define IRTDUpdateEvent interface GUID
DEFINE_GUID(IID_IRTDUpdateEvent,
            0xA43788C1, 0xD91B, 0x11D3, 0x8F, 0x39, 0x00, 0xC0, 0x4F, 0x36, 0x51, 0xB8);

// Callback structure definition (forward declaration of vtable)
typedef struct MyCallback {
    IRTDUpdateEventVtbl *lpVtbl;
    LONG                refCount;
} MyCallBack;

// Topic subscription structure
typedef struct {
    SAFEARRAY* pArgs;
    long topicID;
    WCHAR symbol[64];
    WCHAR topic[32];
} TopicSubscription;

// Function declarations
MyCallBack* CreateCallback(void);
BOOL ConnectToSymbol(IRtdServer *pSrv, WCHAR *symbol, SAFEARRAY **ppArgs, int *pTopicID);
void FormatVariantValue(VARIANT *value, WCHAR *buffer, size_t bufferSize);

// IRtdServer vtable definition
typedef struct IRtdServerVtbl
{
    // IUnknown methods
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IRtdServer *This,
        REFIID riid,
        void **ppvObject);
    
    ULONG (STDMETHODCALLTYPE *AddRef)(
        IRtdServer *This);
    
    ULONG (STDMETHODCALLTYPE *Release)(
        IRtdServer *This);
    
    // IDispatch methods
    HRESULT (STDMETHODCALLTYPE *GetTypeInfoCount)(
        IRtdServer *This,
        UINT *pctinfo);
    
    HRESULT (STDMETHODCALLTYPE *GetTypeInfo)(
        IRtdServer *This,
        UINT iTInfo,
        LCID lcid,
        ITypeInfo **ppTInfo);
    
    HRESULT (STDMETHODCALLTYPE *GetIDsOfNames)(
        IRtdServer *This,
        REFIID riid,
        LPOLESTR *rgszNames,
        UINT cNames,
        LCID lcid,
        DISPID *rgDispId);
    
    HRESULT (STDMETHODCALLTYPE *Invoke)(
        IRtdServer *This,
        DISPID dispIdMember,
        REFIID riid,
        LCID lcid,
        WORD wFlags,
        DISPPARAMS *pDispParams,
        VARIANT *pVarResult,
        EXCEPINFO *pExcepInfo,
        UINT *puArgErr);
    
    // IRtdServer specific methods
    HRESULT (STDMETHODCALLTYPE *ServerStart)(
        IRtdServer *This,
        IRTDUpdateEvent *CallbackObject,
        long *pfRes);
    
    HRESULT (STDMETHODCALLTYPE *ConnectData)(
        IRtdServer *This,
        int* TopicID,
        SAFEARRAY **Strings,
        VARIANT_BOOL *GetNewValues);
    
    HRESULT (STDMETHODCALLTYPE *RefreshData)(
        IRtdServer *This,
        int *TopicCount,
        SAFEARRAY **parrayOut);
    
    HRESULT (STDMETHODCALLTYPE *DisconnectData)(
        IRtdServer *This,
        int TopicID);
    
    HRESULT (STDMETHODCALLTYPE *Heartbeat)(
        IRtdServer *This,
        int *pfRes);
    
    HRESULT (STDMETHODCALLTYPE *ServerTerminate)(
        IRtdServer *This);
} IRtdServerVtbl;

// IRtdServer interface
typedef struct IRtdServer
{
    const IRtdServerVtbl *lpVtbl;
} IRtdServer;

// IRTDUpdateEvent vtable definition
typedef struct IRTDUpdateEventVtbl
{
    // IUnknown methods
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IRTDUpdateEvent *This,
        REFIID riid,
        void **ppvObject);
    
    ULONG (STDMETHODCALLTYPE *AddRef)(
        IRTDUpdateEvent *This);
    
    ULONG (STDMETHODCALLTYPE *Release)(
        IRTDUpdateEvent *This);
    
    // IDispatch methods
    HRESULT (STDMETHODCALLTYPE *GetTypeInfoCount)(
        IRTDUpdateEvent *This,
        UINT *pctinfo);
    
    HRESULT (STDMETHODCALLTYPE *GetTypeInfo)(
        IRTDUpdateEvent *This,
        UINT iTInfo,
        LCID lcid,
        ITypeInfo **ppTInfo);
    
    HRESULT (STDMETHODCALLTYPE *GetIDsOfNames)(
        IRTDUpdateEvent *This,
        REFIID riid,
        LPOLESTR *rgszNames,
        UINT cNames,
        LCID lcid,
        DISPID *rgDispId);
    
    HRESULT (STDMETHODCALLTYPE *Invoke)(
        IRTDUpdateEvent *This,
        DISPID dispIdMember,
        REFIID riid,
        LCID lcid,
        WORD wFlags,
        DISPPARAMS *pDispParams,
        VARIANT *pVarResult,
        EXCEPINFO *pExcepInfo,
        UINT *puArgErr);
    
    // IRTDUpdateEvent specific methods
    HRESULT (STDMETHODCALLTYPE *UpdateNotify)(
        IRTDUpdateEvent *This);
    
    HRESULT (STDMETHODCALLTYPE *get_HeartbeatInterval)(
        IRTDUpdateEvent *This,
        long *plRetVal);
    
    HRESULT (STDMETHODCALLTYPE *put_HeartbeatInterval)(
        IRTDUpdateEvent *This,
        long plRetVal);
    
    HRESULT (STDMETHODCALLTYPE *Disconnect)(
        IRTDUpdateEvent *This);
} IRTDUpdateEventVtbl;

// IRTDUpdateEvent interface
typedef struct IRTDUpdateEvent
{
    const IRTDUpdateEventVtbl *lpVtbl;
} IRTDUpdateEvent;


#endif // RTDCONNECTION