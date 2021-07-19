#include "Text.h"
#include <iostream>
Text::Text()
{
    //Make everything NULL so that if something explodes it explodes very loudly
    hwnd = NULL;
    wszText = NULL;
    cTextLength = 0;
    D2DFactory = NULL;
    pRT = NULL;
    pBlackBrush = NULL;
    DWriteFactory = NULL;
    pTextFormat = NULL;
}

Text::~Text()
{
    SafeRelease(&D2DFactory);
    SafeRelease(&pRT);
    SafeRelease(&pBlackBrush);
    SafeRelease(&DWriteFactory);
    SafeRelease(&pTextFormat);
}

//Initialize
HRESULT Text::Initialize(HWND hwndParent)
{
    WNDCLASSEX wcex;

    //Get the dpi information
    HDC screen = GetDC(0);
    dpiScaleX = GetDeviceCaps(screen, LOGPIXELSX) / 96.0f;
    dpiScaleY = GetDeviceCaps(screen, LOGPIXELSY) / 96.0f;
    ReleaseDC(0, screen);

    HRESULT hr = S_OK;

    if (SUCCEEDED(hr))
    {
        std::cout << "Creating Independent resources" << std::endl;
        //If the DeviceResponds correctly, then get independent resources
        hr = CreateDeviceIndependentResources();
    }

    if (SUCCEEDED(hr))
    {
        std::cout << "Creating Dependent resources" << std::endl;
        //If the DeviceResponds correctly, then get independent resources
        hr = CreateDeviceResources();
    }

    return hr;
}

HWND Text::getHwnd()
{
    return hwnd;
}

HRESULT Text::CreateDeviceIndependentResources()
{
    HRESULT hr;

    // Create Direct2D factory.
    //Multithreading O wO???
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2DFactory);


    // Create a shared DirectWrite factory.
    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&DWriteFactory));
    }


    // The string to display.
    wszText = L"WorldSpace Text!";
    cTextLength = (UINT32)wcslen(wszText);


    // Create a text format using Gabriola with a font size of 72.
    // This sets the default font, weight, stretch, style, and locale.

    //NEVER TOUCH THIS OR BAD THINGS HAPPEN
    if (SUCCEEDED(hr))
    {
        hr = DWriteFactory->CreateTextFormat(
            L"Gabriola",                // Font family name.
            NULL,                       // Font collection (NULL sets it to use the system font collection).
            DWRITE_FONT_WEIGHT_REGULAR,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            72.0f,
            L"en-us",
            &pTextFormat
        );
    }

    // Center align (horizontally) the text.
    if (SUCCEEDED(hr))
    {
        hr = pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    }

    if (SUCCEEDED(hr))
    {
        hr = pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }
    return hr;
}

void Text::DiscardDeviceIndependentResources()
{

}

HRESULT Text::CreateDeviceResources()
{
    HRESULT hr = S_OK;
    RECT rc;
    GetClientRect(hwnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

    // Create a Direct2D render target.
    hr = D2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hwnd, size), &pRT);

    // Create a black brush.
    if (SUCCEEDED(hr))
    {
        hr = pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black),&pBlackBrush);
    }

    return hr;
}

void Text::DiscardDeviceResources()
{
    SafeRelease(&pRT);
    SafeRelease(&pBlackBrush);
}

HRESULT Text::DrawD2DContent()
{
    HRESULT hr;

    hr = CreateDeviceResources();

    if (!(pRT->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
    {
        pRT->BeginDraw();

        pRT->SetTransform(D2D1::IdentityMatrix());

        pRT->Clear(D2D1::ColorF(D2D1::ColorF::White));

        // Call the DrawText method of this class.
        hr = DrawText();

        if (SUCCEEDED(hr))
        {
            hr = pRT->EndDraw();
        }
    }

    if (FAILED(hr))
    {
        DiscardDeviceResources();
    }
    return hr;
}

HRESULT Text::DrawText()
{
    RECT rc;

    GetClientRect(hwnd,&rc);

    // Create a D2D rect that is the same size as the window.

    D2D1_RECT_F layoutRect = D2D1::RectF(
        static_cast<FLOAT>(rc.top) / dpiScaleY,
        static_cast<FLOAT>(rc.left) / dpiScaleX,
        static_cast<FLOAT>(rc.right - rc.left) / dpiScaleX,
        static_cast<FLOAT>(rc.bottom - rc.top) / dpiScaleY);


    // Use the DrawText method of the D2D render target interface to draw.
    pRT->DrawText(
        wszText,        // The string to render.
        cTextLength,    // The string's length.
        pTextFormat,    // The text format.
        layoutRect,       // The region of the window where the text will be rendered.
        pBlackBrush     // The brush used to draw the text.
    );

    return S_OK;
}

//If the window gets resized
void Text::OnResize(UINT width, UINT height)
{
    if (pRT)
    {
        D2D1_SIZE_U size;
        size.width = width;
        size.height = height;
        pRT->Resize(size);
    }
}
