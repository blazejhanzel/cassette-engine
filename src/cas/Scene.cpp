#include <cas/pch.h>
#include <cas/Scene.h>

using namespace cas;
using namespace std;

Scene::Scene() {}

pAsset Scene::addAsset(pAsset a, string name) {
	if (mAsset.find(name) != mAsset.end()) {
		int nameNumber = 0;
		string newName;
		do {
			newName = name + "-" + to_string(nameNumber);
			nameNumber++;
		} while (mAsset.find(newName) != mAsset.end());
		name = newName;
	}

	mAsset[name] = pAsset(new Asset(name, *dynamic_pointer_cast <Asset>(a)));
	mAsset[name]->init(mAsset[name]);
	return mAsset[name];
}

pAsset Scene::getAsset(std::string name) noexcept {
	if (mAsset.find(name) != mAsset.end())
		return mAsset[name];
	return nullptr;
}

inline void Scene::removeAsset(std::string name) noexcept {
	mAsset.erase(name);
}

inline void Scene::clear() noexcept {
	mAsset.clear();
}

void Scene::draw(pRenderWindow w) {
	for (auto& i : mAsset)
		if (i.second->isEnabled())
			i.second->draw(w);
}

void Scene::init() {
	for (auto& i : mAsset)
		i.second->init(i.second);
}

void Scene::eventHandler(pEvent event) {
	for (auto& i : mAsset)
		if (i.second->isEnabled())
			i.second->eventHandler(i.second, event);
}

void Scene::update() {
	for (auto& i : mAsset)
		if (i.second->isEnabled())
			i.second->update(i.second);
}
