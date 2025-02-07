/*
 * Copyright 2017 Piotr Caban for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "vbscript.h"

#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(vbscript);

typedef struct {
    IEnumVARIANT IEnumVARIANT_iface;

    LONG ref;

    SAFEARRAY *sa;
    ULONG i, size;
} safearray_iter;

static inline safearray_iter *impl_from_IEnumVARIANT(IEnumVARIANT *iface)
{
    return CONTAINING_RECORD(iface, safearray_iter, IEnumVARIANT_iface);
}

static HRESULT WINAPI safearray_iter_IEnumVARIANT_QueryInterface(
        IEnumVARIANT *iface, REFIID riid, void **ppv)
{
    safearray_iter *This = impl_from_IEnumVARIANT(iface);

    if(IsEqualGUID(riid, &IID_IUnknown)) {
        TRACE("(%p)->(IID_IUnknown %p)\n", This, ppv);
        *ppv = &This->IEnumVARIANT_iface;
    }else if(IsEqualGUID(riid, &IID_IEnumVARIANT)) {
        TRACE("(%p)->(IID_IEnumVARIANT %p)\n", This, ppv);
        *ppv = &This->IEnumVARIANT_iface;
    }else {
        FIXME("(%p)->(%s %p)\n", This, debugstr_guid(riid), ppv);
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    IUnknown_AddRef((IUnknown*)*ppv);
    return S_OK;
}

static ULONG WINAPI safearray_iter_IEnumVARIANT_AddRef(IEnumVARIANT *iface)
{
    safearray_iter *This = impl_from_IEnumVARIANT(iface);
    LONG ref = InterlockedIncrement(&This->ref);

    TRACE("(%p) ref=%ld\n", This, ref);

    return ref;
}

static ULONG WINAPI safearray_iter_IEnumVARIANT_Release(IEnumVARIANT *iface)
{
    safearray_iter *This = impl_from_IEnumVARIANT(iface);
    LONG ref = InterlockedDecrement(&This->ref);

    TRACE("(%p) ref=%ld\n", iface, ref);

    if(!ref) {
        if(This->sa)
            SafeArrayUnlock(This->sa);
        free(This);
    }

    return ref;
}

static HRESULT WINAPI safearray_iter_IEnumVARIANT_Next(IEnumVARIANT *iface,
        ULONG celt, VARIANT *rgVar, ULONG *pCeltFetched)
{
    safearray_iter *This = impl_from_IEnumVARIANT(iface);
    HRESULT hres;
    VARIANT *v;

    TRACE("(%p)->(%lu %p %p)\n", This, celt, rgVar, pCeltFetched);

    if(celt != 1) {
        FIXME("celt != 1\n");
        return E_NOTIMPL;
    }

    if(This->i >= This->size) {
        if(pCeltFetched)
            *pCeltFetched = 0;
        return S_FALSE;
    }

    if(!This->sa->cLocks)
        ERR("SAFEARRAY not locked\n");

    if (This->sa->fFeatures & FADF_VARIANT)
    {
        v = (VARIANT*)(((BYTE*)This->sa->pvData) + This->i * This->sa->cbElements);
        V_VT(rgVar) = VT_EMPTY;
        hres = VariantCopy(rgVar, v);
        if(FAILED(hres))
            return hres;
    }
    else if (This->sa->fFeatures & FADF_BSTR)
    {
        BSTR bstr  = *(BSTR*)(((BYTE*)This->sa->pvData) + This->i * This->sa->cbElements);
        V_VT(rgVar) = VT_BSTR;
        V_BSTR(rgVar) = SysAllocString(bstr);
    }

    This->i++;
    if(pCeltFetched)
        *pCeltFetched = 1;
    return S_OK;
}

static HRESULT WINAPI safearray_iter_IEnumVARIANT_Skip(IEnumVARIANT *iface, ULONG celt)
{
    FIXME("\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI safearray_iter_IEnumVARIANT_Reset(IEnumVARIANT *iface)
{
    FIXME("\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI safearray_iter_IEnumVARIANT_Clone(
        IEnumVARIANT *iface, IEnumVARIANT **ppEnum)
{
    FIXME("\n");
    return E_NOTIMPL;
}

static const IEnumVARIANTVtbl safearray_iter_EnumVARIANTVtbl = {
    safearray_iter_IEnumVARIANT_QueryInterface,
    safearray_iter_IEnumVARIANT_AddRef,
    safearray_iter_IEnumVARIANT_Release,
    safearray_iter_IEnumVARIANT_Next,
    safearray_iter_IEnumVARIANT_Skip,
    safearray_iter_IEnumVARIANT_Reset,
    safearray_iter_IEnumVARIANT_Clone
};

static ULONG get_safearray_size(SAFEARRAY *sa)
{
    ULONG ret = 1;
    USHORT i;

    if(!sa)
        return 0;

    for(i=0; i<sa->cDims && ret; i++)
        ret *= sa->rgsabound[i].cElements;
    return ret;
}

HRESULT create_safearray_iter(SAFEARRAY *sa, IEnumVARIANT **ev)
{
    safearray_iter *iter;
    HRESULT hres;

    iter = malloc(sizeof(*iter));
    if(!iter)
        return E_OUTOFMEMORY;

    if(sa) {
        hres = SafeArrayLock(sa);
        if(FAILED(hres)) {
            free(iter);
            return hres;
        }
    }

    iter->IEnumVARIANT_iface.lpVtbl = &safearray_iter_EnumVARIANTVtbl;
    iter->ref = 1;
    iter->sa = sa;
    iter->i = 0;
    iter->size = get_safearray_size(sa);

    *ev = &iter->IEnumVARIANT_iface;
    return S_OK;
}
