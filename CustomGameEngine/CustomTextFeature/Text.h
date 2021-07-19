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

class Text
{
public:
	Text();
	~Text();

    //Initialize
	HRESULT Initialize(HWND hwndParent);
	HWND getHwnd();

    //Edit
    HRESULT CreateDeviceIndependentResources();
    void DiscardDeviceIndependentResources();
    HRESULT CreateDeviceResources();
    void DiscardDeviceResources();

    //Draw
    HRESULT DrawD2DContent();
    HRESULT DrawText();

    //Change text size
    void OnResize(UINT width,UINT height);

    //Status check
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    HWND hwnd;

    //Scale relative to 96DPI
    float dpiScaleX;
    float dpiScaleY;

    // Direct2D
    ID2D1Factory* D2DFactory;
    ID2D1HwndRenderTarget* pRT;
    ID2D1SolidColorBrush* pBlackBrush;

    // DirectWrite
    IDWriteFactory* DWriteFactory;
    IDWriteTextFormat* pTextFormat;

    const wchar_t* wszText; /*The actual string element but not really*/
    UINT32 cTextLength;
};

