#include <cas/pch.h>
#include <cas/EventManager.h>
#include <cas/Core.h>

using namespace cas;
using namespace std;
using namespace sf;

EventManager::EventManager() {
	throw runtime_error("Cannot create Event Manager without pointer to Core");
}

EventManager::EventManager(Core* c) noexcept : core(c) {}

pEvent EventManager::getEvent() noexcept {
	return mEvent;
}

void EventManager::update() {
	pRenderWindow window = core->getDisplayManager()->getWindow();
	if (window.isOpen()) {
		while (window.pollEvent(mEvent)) {
			pGui gui = core->getDisplayManager()->getGui();

			if (mEvent.type == sf::Event::Closed) {
				core->getStateManager()->setState(StateManager::State::END);
			}
			else if (mEvent.type == sf::Event::Resized) {
				core->getSettings()->mWindowWidth = mEvent.size.width;
				core->getSettings()->mWindowHeight = mEvent.size.height;

				window.setView(sf::View(sf::FloatRect(0.f, 0.f, mEvent.size.width, mEvent.size.height)));

				gui.setView(window.getView());
			}

			if (core->getStateManager()->getState() == StateManager::State::SCENEACTIVE)
				core->getSceneManager()->getActiveScene()->eventHandler(mEvent);

			gui.handleEvent(mEvent);
		}
	}
}
