#include <oaidl.h>
#include <ocidl.h>
#include <initguid.h>

// Define the CLSID of the RTD server (replace with your RTD server's CLSID)
DEFINE_GUID(CLSID_MyRTDServer, 
    0x272D2E65, 0x05FB, 0x4500, 0xBD, 0x7B, 0x59, 0x05, 0xD5, 0xB0, 0xA1, 0xB8);

// Define the IID for IRtdServer
DEFINE_GUID(IID_IRtdServer, 
    0xEC0E6191, 0xDB51, 0x11D3, 0x8F, 0x3E, 0x00, 0xC0, 0x4F, 0x36, 0x51, 0xB8);

typedef HRESULT STDMETHODCALLTYPE QueryInterfacePtr(void* This, REFIID riid, void** ppvObject);
typedef ULONG STDMETHODCALLTYPE AddRefPtr(void* This);
typedef ULONG STDMETHODCALLTYPE ReleasePtr(void* This);
typedef HRESULT STDMETHODCALLTYPE MyRTDUpdate_UpdateNotifyPtr(void* This);
typedef HRESULT STDMETHODCALLTYPE MyRTDUpdate_HeartbeatPtr(void* This, int* pResponse);
typedef HRESULT  STDMETHODCALLTYPE ServerStartPtr(IUnknown* Callback);
typedef HRESULT  STDMETHODCALLTYPE ServerTerminatePtr(void* this);
typedef HRESULT  STDMETHODCALLTYPE ConnectDataPtr(void* this, int* TopicID, SAFEARRAY* Strings, VARIANT_BOOL* NewValue);
typedef HRESULT  STDMETHODCALLTYPE RefreshDataPtr(void* this, int* TopicCount,SAFEARRAY** Strings);
typedef HRESULT  STDMETHODCALLTYPE DisconnectDataPtr(void* this, LONG TopicID);
typedef HRESULT  STDMETHODCALLTYPE HeartbeatPtr(void* this, int* Result);
