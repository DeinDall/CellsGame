#ifndef SERVERWORLD_H
#define SERVERWORLD_H

#include "game/world.h"
#include "network/servernetworkmanager.h"

class ServerWorld : public World {
public:
	ServerWorld();

	void update();

protected:
	void updateNetworks();

	void onNewCell(Cell* cell);
	void onDeadCell(Cell* cell);
//	void onDestroyCell(Cell* cell);

private:
	ServerNetworkManager mNetworkManager;
	unsigned int mCurrentUpdatingCellId;
};

#endif // SERVERWORLD_H
