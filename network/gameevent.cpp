#include "gameevent.h"

GameEvent::GameEvent(EventType evType) {
	mType = evType;
}

GameEvent::~GameEvent() {}

GameEvent::EventType GameEvent::type() const {
	return mType;
}
