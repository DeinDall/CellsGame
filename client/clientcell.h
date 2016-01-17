#ifndef CLIENTCELL_H
#define CLIENTCELL_H

#include "game/cell.h"
#include "graphics/graphicscell.h"

class ClientCell : public Cell, public GraphicsCell {
public:
	ClientCell();

	float graphicalLife() const;
	float graphicalRadius() const;
	sf::Vector2f graphicsPosition() const;

	void update();

	void kill();

	bool isClientDead() const;

private:
	float mGraphicalLife;
	float mGraphicalRadius;

	bool mClientDeath;
};

#endif // CLIENTCELL_H
