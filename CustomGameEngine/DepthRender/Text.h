#pragma once
#include "GraphicsEngine.h"
#include "SpriteFont.h"
#include "SpriteBatch.h"
#include <iostream>

using namespace DirectX;

class Text
{
public:
	Text();
	~Text();

	//Make stuff work
	void initialize();

	//Make sure stuff still works
	void update();

	//Draw stuff
	void draw();

private:
	//Not sure if this is needed to be unique
	SpriteFont* spriteFont;
	SpriteBatch* spriteBatch;

	wchar_t storedText;
};

