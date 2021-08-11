#pragma once
#include <Windows.h>
#include "EngineTime.h"

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
	virtual void onFocus();
	virtual void onKillFocus();

	HWND getWindowHandle();

	~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;
};

