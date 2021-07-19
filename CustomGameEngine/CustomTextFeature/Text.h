#pragma once
#include "dwrite.h"
#include "d2d1.h"
#include "GraphicsEngine.h"

//Bomb defuser
/*
* TL;DR: this function takes a pointer to ANY type of allocated memory and safely removes it from the place it has been allocated
* This ONLY works if the thing it's trying to safely release is no longer being used anywhere, hence the term "Safely"
* After this function works, the pointer is effectively NULL
* 
* NEVER USE THIS ON SINGLETONS OR ELSE BIG BOOM HAPPENS
*/
template <class T> void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif
class Text
{
public:
    Text();
    ~Text();

    HRESULT Initialize(HWND hwndParent);

    HWND GetHwnd() { return hwnd_; }

private:
    HRESULT CreateDeviceIndependentResources(
    );

    void DiscardDeviceIndependentResources(
    );

    HRESULT CreateDeviceResources(
    );

    void DiscardDeviceResources(
    );

    HRESULT DrawD2DContent(
    );

    HRESULT DrawText(
    );

    void OnResize(
        UINT width,
        UINT height
    );

    static LRESULT CALLBACK WndProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    );

private:
    HWND hwnd_;

    // how much to scale a design that assumes 96-DPI pixels
    float dpiScaleX_;
    float dpiScaleY_;

    // Direct2D

    ID2D1Factory* pD2DFactory_;
    ID2D1HwndRenderTarget* pRT_;
    ID2D1SolidColorBrush* pBlackBrush_;


    // DirectWrite

    IDWriteFactory* pDWriteFactory_;
    IDWriteTextFormat* pTextFormat_;



    const wchar_t* wszText_;
    UINT32 cTextLength_;


};

