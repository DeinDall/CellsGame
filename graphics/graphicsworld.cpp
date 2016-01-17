#include "graphicsworld.h"

GraphicsWorld::GraphicsWorld() {
	mMetaRender.create(854, 480);
	mMetaSprite.setTexture(mMetaRender.getTexture());

	mMetaShader.loadFromFile("effect.frag", sf::Shader::Fragment);
	mMetaShader.setParameter("tex", mMetaRender.getTexture());
}

GraphicsWorld::~GraphicsWorld() {}

void GraphicsWorld::addGraphicsCell(GraphicsCell* cell) {
	mGraphicsCells.push_back(cell);
}

void GraphicsWorld::removeGraphicsCell(GraphicsCell* cell) {
	mGraphicsCells.remove(cell);
}

void GraphicsWorld::draw(sf::RenderTarget& target, sf::RenderStates states) {
	mMetaRender.clear(sf::Color::Transparent);
	mMetaRender.setView(target.getView());

	for (GraphicsCell* cell : mGraphicsCells)
		cell->drawBackgroundCell(mMetaRender, sf::BlendAdd);

	mMetaRender.display();

	target.setView(target.getDefaultView());

	target.draw(mMetaSprite, &mMetaShader);

	target.setView(mMetaRender.getView());

	for (GraphicsCell* cell : mGraphicsCells)
		cell->drawInnerCell(target, states);
	for (GraphicsCell* cell : mGraphicsCells)
		cell->drawOuterCell(target, states);
}
