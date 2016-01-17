#include "clientworld.h"

ClientWorld::ClientWorld() {}

void ClientWorld::addCell(ClientCell* newcell) {
	World::addCell((Cell*)newcell);
	addGraphicsCell((GraphicsCell*)newcell);
}

void ClientWorld::addCellConnectedTo(ClientCell* newcell, Cell* connection) {
	addCell(newcell);
	new Cell::Link((Cell*)newcell, connection);
}

void ClientWorld::removeCell(ClientCell* cell) {
	removeGraphicsCell((GraphicsCell*)cell);
	World::removeCell((Cell*)cell);
}

void ClientWorld::update() {
	World::updatePhysics();
	World::updateLogic();
	World::handleDeadCells();
}

void ClientWorld::onDeadCell(Cell* cell) {
	ClientCell* ccell = dynamic_cast<ClientCell*>(cell);

	if (ccell && !ccell->isClientDead())
		return;

	GraphicsWorld::removeGraphicsCell((GraphicsCell*)ccell);
	World::onDeadCell(cell);
}
