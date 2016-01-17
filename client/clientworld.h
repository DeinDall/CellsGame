#ifndef CLIENTWORLD_H
#define CLIENTWORLD_H

#include "clientcell.h"
//#include "physics/physics.h"
#include "game/world.h"
#include "graphics/graphicsworld.h"

class ClientWorld : public World, public GraphicsWorld {
public:
	ClientWorld();

	void addCell(ClientCell* newcell);
	void addCellConnectedTo(ClientCell* newcell, Cell* connection);

	void removeCell(ClientCell* cell);

	void update();

protected:
	void onDeadCell(Cell* cell);
};

#endif // CLIENTWORLD_H
