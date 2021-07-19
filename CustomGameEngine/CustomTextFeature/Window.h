#pragma once
#include <Windows.h>
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif



class Window
{
public:
	Window();
	//Initialize the window
	bool init();
	bool broadcast();
	//Release the window
	bool release();
	bool isRunning();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);


	//EVENTS
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	HWND getWindowHandle();

	~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;
};

