#ifndef GRAPHICSWORLD_H
#define GRAPHICSWORLD_H

#include "graphicscell.h"
#include <list>

class GraphicsWorld {
public:
	GraphicsWorld();
	virtual ~GraphicsWorld();

	void addGraphicsCell(GraphicsCell* cell);
	void removeGraphicsCell(GraphicsCell* cell);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates());

private:
	std::list<GraphicsCell*> mGraphicsCells;

	sf::RenderTexture mMetaRender;
	sf::Sprite mMetaSprite;
	sf::Shader mMetaShader;
};

#endif // GRAPHICSWORLD_H
