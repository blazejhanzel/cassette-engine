#pragma once

#include "pch.h"

namespace cas {

	class Core;

	class CASENG_API NetworkManager final {
		friend class Core;
		Core* core = nullptr;

	public:
		enum class Type {
			TCP,
			UDP
		};

	private:
		std::map <std::string, std::pair <Type, pSocket>> mSocket;
		std::map <std::string, std::vector <pPacket>> mSendQueue;
		std::map <std::string, std::vector <pPacket>> mReceiveQueue;
		std::atomic_flag mSocketLock = ATOMIC_FLAG_INIT;

	public:
		NetworkManager();
		NetworkManager(Core* c);

		pSocket newConnection(std::string, Type, std::string, int);
		pSocket getConnection(std::string);
		void removeConnection(std::string);
		void send(std::string, pPacket);
		pPacket receive(std::string);

	private:
		void update();
	};

	typedef std::shared_ptr <cas::NetworkManager> pNetworkManager;
}

