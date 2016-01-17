#ifndef GRAPHICSCELL_H
#define GRAPHICSCELL_H

#include <SFML/Graphics.hpp>

class GraphicsCell { // TODO: make GraphicsCell a drawable/transformable instead of a cell
public:
	GraphicsCell();
	virtual ~GraphicsCell();

	virtual float graphicalLife() const = 0;
	virtual float graphicalRadius() const = 0;
	virtual sf::Vector2f graphicsPosition() const = 0;

	void drawInnerCell(sf::RenderTarget& target, const sf::RenderStates& states = sf::RenderStates());
	void drawOuterCell(sf::RenderTarget& target, const sf::RenderStates& states = sf::RenderStates());
	void drawBackgroundCell(sf::RenderTarget& target, const sf::RenderStates& states = sf::RenderStates());

private:
	sf::CircleShape mShape;

	sf::Sprite mMetaSprite;
	static sf::Texture msMetaTexture;
};

#endif // GRAPHICSCELL_H
