#include "cellcreateevent.h"

CellCreateEvent::CellCreateEvent(NetworkCell* cell) : CellUpdateEvent(cell) {
	mType = GameEvent::TypeCreateCell;
}
