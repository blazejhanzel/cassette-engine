// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#ifdef CASSETTEENGINE_EXPORTS
#define CASENG_API __declspec(dllexport)
#else
#define CASENG_API __declspec(dllimport)
#endif

#define CAS_VERSION_MAJOR 1
#define CAS_VERSION_MINOR 0
#define CAS_VERSION_PATCH 0
#define CAS_VERSION_TEXT "beta"

#define NOMINMAX

// add headers that you want to pre-compile here
#include "framework.h"

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <sstream>
#include <string>
#include <thread>
#include <typeinfo>
#include <vector>

#include <boost/any.hpp>
#include <inipp.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>

#include "Exception.h"
#include "Logger.h"

namespace cas {
	typedef tgui::Gui& pGui;
	typedef sf::RenderWindow& pRenderWindow;
	typedef std::shared_ptr <sf::Packet> pPacket;
	typedef std::shared_ptr <sf::Socket> pSocket;
	typedef std::shared_ptr <sf::Sprite> pSprite;
	typedef std::shared_ptr <sf::Texture> pTexture;
}

#endif //PCH_H
