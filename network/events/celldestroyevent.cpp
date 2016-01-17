#include "celldestroyevent.h"

CellDestroyEvent::CellDestroyEvent(NetworkCell* cell) : CellUpdateEvent(cell) {
	mType = GameEvent::TypeDeadCell;
}

