#ifndef _OUTLOOK_H
#define _OUTLOOK_H

#if defined(WIN32) && !defined(MAC)

#ifndef __IOutlookExtCallback_FWD_DEFINED__
#define __IOutlookExtCallback_FWD_DEFINED__
typedef interface IOutlookExtCallback IOutlookExtCallback;
#endif    /* __IOutlookExtCallback_FWD_DEFINED__ */

// Outlook defines this interface as an alternate to IExchExtCallback.
#ifndef __IOutlookExtCallback_INTERFACE_DEFINED__
#define __IOutlookExtCallback_INTERFACE_DEFINED__

EXTERN_C const IID IID_IOutlookExtCallback;

    interface DECLSPEC_UUID("0006720D-0000-0000-C000-000000000046")
    IOutlookExtCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetObject( 
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOfficeCharacter( 
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppmsotfc) = 0;
    };

DEFINE_GUID(IID_IOutlookExtCallback,
    0x0006720d,
    0x0000,
    0x0000,
    0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

#endif    /* __IOutlookExtCallback_INTERFACE_DEFINED__ */

#endif // defined(WIN32) && !defined(MAC)

#endif // _OUTLOOK_H