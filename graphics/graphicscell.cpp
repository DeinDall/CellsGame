#include "graphicscell.h"
#include "stk/vec2.h"

sf::Texture GraphicsCell::msMetaTexture;

GraphicsCell::GraphicsCell() : mShape(1) {
	if (msMetaTexture.getSize().x==0) { // TODO: move textures elsewhere
		sf::Image img;
		img.create(256, 256);

		stk::vec2 center(128, 128);

		for (unsigned int ix=0; ix<256; ++ix) {
			for (unsigned int iy=0; iy<256; ++iy) {
				float r = stk::vec2::len(center-stk::vec2(ix, iy))*(1/128.f);
				float v = 0.f;

				if (r>=0 && r<=(1/3.f))
					v = 1-3.f*r*r;
				else if (r<=1)
					v = (3/2.f)*(1-r)*(1-r);
				img.setPixel(ix, iy, sf::Color(255*sqrtf(v), 255*sqrtf(v), 255*sqrtf(v), 255*v));
			}
		}

		msMetaTexture.loadFromImage(img);
		msMetaTexture.setSmooth(true);
		//msMetaTexture.loadFromFile("ball.png");
	}

	mShape.setOrigin(1, 1);
	mShape.setFillColor(sf::Color(255, 255, 255, 128));

	mMetaSprite.setTexture(msMetaTexture);
	mMetaSprite.setOrigin(128, 128);
}

GraphicsCell::~GraphicsCell() {}

void GraphicsCell::drawInnerCell(sf::RenderTarget& target, const sf::RenderStates& states) {
	// TODO: draw inner cell contents
}

void GraphicsCell::drawOuterCell(sf::RenderTarget& target, const sf::RenderStates& states) {
	mShape.setScale(graphicalRadius(), graphicalRadius());
	mShape.setPosition(graphicsPosition());

	target.draw(mShape, states);
}

void GraphicsCell::drawBackgroundCell(sf::RenderTarget& target, const sf::RenderStates& states) {
	mMetaSprite.setScale(graphicalRadius()/48.f, graphicalRadius()/48.f);
	mMetaSprite.setPosition(graphicsPosition());
	mMetaSprite.setColor(sf::Color(204, 128, 204, graphicalLife()*255));

	target.draw(mMetaSprite, states);
}
