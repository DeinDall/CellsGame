#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <SFML/Network.hpp>

class GameEvent {
public:
	enum EventType : unsigned char {
		TypeCreateCell,
		TypeDeadCell,

		TypeCellUpdate/*,

		TypeCellLink,
		TypeCellUnlink,
		TypeCellRelink //*/
	};

public:
	virtual ~GameEvent();

	EventType type() const;

	virtual void pack(sf::Packet& packet) = 0;
	virtual void unpack(sf::Packet& packet) = 0;

protected:
	GameEvent(EventType evType);
	EventType mType;
};

#endif // GAMEEVENT_H
