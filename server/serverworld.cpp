#include "serverworld.h"

#include "network/events/cellcreateevent.h"
#include "network/events/celldestroyevent.h"

ServerWorld::ServerWorld() {
	mCurrentUpdatingCellId = -1;
}

void ServerWorld::update() {
	World::updatePhysics();
	World::updateLogic();
	World::handleDeadCells();

	updateNetworks();
}

void ServerWorld::updateNetworks() {
	Cell* cellToUpdate = nullptr;
	for (Cell* cell : mCells)
		if (cell->cellId()>mCurrentUpdatingCellId) {
			cellToUpdate = cell;
			break;
		}

	if (cellToUpdate==nullptr)
		cellToUpdate = mCells.front();
	mCurrentUpdatingCellId = cellToUpdate->cellId();

	NetworkCell* ncell = dynamic_cast<NetworkCell*>(cellToUpdate);

	if (ncell)
		mNetworkManager.send(new CellUpdateEvent(ncell));
}

void ServerWorld::onNewCell(Cell* cell) {
	NetworkCell* ncell = dynamic_cast<NetworkCell*>(cell);

	if (ncell)
		mNetworkManager.send(new CellCreateEvent(ncell));

	World::onNewCell(cell);
}

void ServerWorld::onDeadCell(Cell* cell) {
	NetworkCell* ncell = dynamic_cast<NetworkCell*>(cell);

	if (ncell)
		mNetworkManager.send(new CellDestroyEvent(ncell));

	World::onDeadCell(cell);
}
