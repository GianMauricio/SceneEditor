#include <d3d11.h>
#include "Text.h"
#include "SimpleMath.h"
Text::Text(const wchar_t output)
{
	std::cout << "Made text object" << std::endl;
	storedText = output;
}

Text::~Text()
{
}

void Text::initialize()
{
	ID3D11DeviceContext* currContext = GraphicsEngine::getInstance()->getD11Context();
	ID3D11Device* currDevice = GraphicsEngine::getInstance()->getDevice();

	spriteBatch = new SpriteBatch(currContext);
	spriteFont = new SpriteFont(currDevice, L"Corbel.spritefont", false);
}

void Text::draw()
{
	//Call to 2D render target
	spriteBatch->Begin();

	//Draw the font
	spriteFont->DrawString(spriteBatch, L"HelloWorld", SimpleMath::Vector2(300, 300));

	spriteBatch->End();
}
