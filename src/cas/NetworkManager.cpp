#include <cas/pch.h>
#include <cas/NetworkManager.h>
#include <cas/Core.h>

using namespace cas;
using namespace std;

NetworkManager::NetworkManager() {
	throw runtime_error("Cannot create Asset Manager instance withour pointer to Core.");
}

NetworkManager::NetworkManager(Core* c) : core(c) {}

pSocket NetworkManager::newConnection(std::string name, Type type, std::string ip, int port) {
	while (!mSocketLock.test_and_set(memory_order_acquire));

	mSocket[name].first = type;
	mSocket[name].second = (type == Type::TCP) ? pSocket(new sf::TcpSocket) : pSocket(new sf::UdpSocket);
	if (type == Type::TCP) {
		if (dynamic_pointer_cast<sf::TcpSocket>(mSocket[name].second)->connect(ip, port) != sf::Socket::Done)
			return nullptr;
	}
	else {
		// TODO: Implenet this
		throw runtime_error("UDP is currently not supported by engine.");
	}
	mSocket[name].second->setBlocking(false);

	mSocketLock.clear(memory_order_release);
	return mSocket[name].second;
}

pSocket NetworkManager::getConnection(std::string name) {
	if (mSocket.find(name) != mSocket.end())
		return mSocket[name].second;
	return nullptr;
}

void NetworkManager::removeConnection(std::string name) {
	mSocket.erase(name);
}

void NetworkManager::send(std::string name, pPacket p) {
	mSendQueue[name].push_back(p);
}

pPacket NetworkManager::receive(std::string name) {
	if (mReceiveQueue.find(name) != mReceiveQueue.end() && mReceiveQueue[name].size() > 0) {
		pPacket ret;
		ret = mReceiveQueue[name][0];
		mReceiveQueue[name].erase(mReceiveQueue[name].begin());
		return ret;
	}
	return nullptr;
}

void NetworkManager::update() {
	while (core->getStateManager()->getState() != StateManager::State::END) {
		if (!mSocketLock.test_and_set(memory_order_acquire)) {
			for (auto& [k, v] : mSendQueue) {
				if (mSocket[k].first == Type::TCP) {
					auto socket = dynamic_pointer_cast<sf::TcpSocket>(mSocket[k].second);
					for (auto& i : v) {
						sf::Socket::Status status = sf::Socket::Status::NotReady;
						do {
							status = socket->send(*i);
						} while (status == sf::Socket::Status::Partial);

					}
					mSendQueue[k].clear();
				}
				else {
					// TODO: Implenet this
					throw runtime_error("UDP is currently not supported by engine.");
				}
			}

			for (auto& [k, v] : mSocket) {
				if (mSocket[k].first == Type::TCP) {
					auto socket = dynamic_pointer_cast<sf::TcpSocket>(mSocket[k].second);
					pPacket packet{ new sf::Packet };
					socket->receive(*packet);
					sf::Packet check = *packet;
					int type = 0;
					check >> type;
					if (type == 1) { // it's a ping message!
						pPacket ping = pPacket(new sf::Packet);
						*ping << 1;
						send("server", ping);
					}
					else if (type != 0) { // not a empty packet
						mReceiveQueue[k].push_back(packet);
					}
				}
				else {
					// TODO: Implenet this
					throw runtime_error("UDP is currently not supported by engine.");
				}
			}

			mSocketLock.clear(memory_order_release);
		}
		this_thread::sleep_for(chrono::microseconds(1000)); // NOTE: it's for cpu lower usage, limits ping to about 5 ms in localhost; if lag occures remove this line or set lower time
	}
}
