#include <cas/pch.h>
#include <cas/SceneManager.h>
#include <cas/Core.h>

using namespace cas;
using namespace std;

SceneManager::SceneManager() {
	throw runtime_error("Cannot create scene manager without poiner to Core.");
}

SceneManager::SceneManager(Core* c) : core(c) {}

pScene SceneManager::addScene(string name) {
	if (mScene.find(name) != mScene.end())
		throw runtime_error("Scene with this name already exist. Possible data loss.");

	mScene[name] = pScene(new Scene);
	if (!mActiveScene)
		mActiveScene = mScene[name];

	return mScene[name];
}

pScene SceneManager::getScene(string name) noexcept {
	if (mScene.find(name) != mScene.end())
		return mScene[name];
	return nullptr;
}

inline void SceneManager::removeScene(string name) noexcept {
	mScene.erase(name);
}

void SceneManager::setActiveScene(pScene p) noexcept {
	core->getStateManager()->setState(StateManager::State::LOADING);
	mActiveScene = p;
	p->init(); // NOTE: Idk, but this probably should be runned after all, maybe in state manager?
}

inline pScene SceneManager::getActiveScene() noexcept {
	return mActiveScene;
}

void SceneManager::update() {
	if (mActiveScene)
		mActiveScene->update();
	else {
		*(core->getLogger()) << "SCENE MGR: There are no scenes in memory. Ending app.";
		core->getStateManager()->setState(StateManager::State::END);
	}
}
