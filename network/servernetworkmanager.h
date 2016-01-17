#ifndef SERVERNETWORKMANAGER_H
#define SERVERNETWORKMANAGER_H

#include "gameevent.h"
#include <list>

class ServerNetworkManager {
public:
	ServerNetworkManager();

	void send(GameEvent* ev);

private:
	unsigned int mCurrentDate;
	std::list<GameEvent*> mPreviousEvents;

	sf::TcpListener mListener;
	sf::TcpSocket mClientConnection;
};

#endif // SERVERNETWORKMANAGER_H
