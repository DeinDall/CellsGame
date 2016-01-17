#include "cellupdateevent.h"

CellUpdateEvent::CellUpdateEvent(NetworkCell* cell) : GameEvent(GameEvent::TypeCellUpdate), mCell(cell) {}

void CellUpdateEvent::pack(sf::Packet& packet) {
	packet << mCell->cellId();
	mCell->fillPacket(packet);
}

void CellUpdateEvent::unpack(sf::Packet& packet) {
	mCell->updateFromPacket(packet);
}
