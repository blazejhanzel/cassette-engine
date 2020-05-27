#include <cas/pch.h>
#include <cas/Core.h>
#include <cas/Asset.h>
#include <cas/AudioSourceComponent.h>
#include <cas/LogicComponent.h>
#include <cas/RenderObjectComponent.h>

using namespace cas;
using namespace std;

Asset::Asset() noexcept {}

Asset::Asset(string name) noexcept : mName(name) {}

Asset::Asset(string name, const Asset& a) : mName(name) {
	mTag = a.mTag;
	var = a.var;
	for (auto& [k, v] : a.mComponent) {
		addComponent(v->getType(), k, v);
	}
	for (int i = 0; i < a.mChild.size(); i++) {
		pAsset p(new Asset(a.mChild[i]->mName, *a.mChild[i]));
		mChild.push_back(p);
	}
}

pAssetComponent Asset::addComponent(AssetComponent::Type type, string name, pAssetComponent p) {
	if (mComponent.find(name) != mComponent.end())
		throw runtime_error("Component with this name already exists. Possible data loss.");

	switch (type) {
	case AssetComponent::Type::AUDIOSOURCE:
		if (p)
			mComponent[name] = pAssetComponent(new Component::AudioSource(*dynamic_pointer_cast <Component::AudioSource>(p)));
		else
			mComponent[name] = pAssetComponent(new Component::AudioSource);
		break;
	case AssetComponent::Type::RENDEROBJECT:
		if (p)
			mComponent[name] = pAssetComponent(new Component::RenderObject(*dynamic_pointer_cast <Component::RenderObject>(p)));
		else
			mComponent[name] = pAssetComponent(new Component::RenderObject);
		break;
	case AssetComponent::Type::LOGIC:
		if (p)
			addLogic(dynamic_pointer_cast <Component::Logic>(p), name);
		else
			throw invalid_argument("This function cannot handle LOGIC components. Use addLogic() instead.");
		break;
	default:
		throw Exception("022f8a03b2659b8383262bee3a436808");
		return nullptr;
	}

	return mComponent[name];
}

pAssetComponent Asset::getComponent(string name) noexcept {
	if (mComponent.find(name) != mComponent.end())
		return mComponent[name];
	return nullptr;
}

void Asset::removeComponent(string name) noexcept {
	mComponent.erase(name);
}

pAssetComponent Asset::addLogic(std::shared_ptr <Component::Logic> c, string name) {
	if (mComponent.find(name) != mComponent.end())
		throw runtime_error("Component with this name already exists. Possible data loss.");

	if (mComponent.find(name) == mComponent.end()) {
		mComponent[name] = c;
		return mComponent[name];
	}
	return nullptr;
}

void Asset::addChild(std::shared_ptr <Asset> a) noexcept {
	mChild.push_back(a);
}

pAsset Asset::getChild(string name) noexcept {
	for (auto& i : mChild) {
		if (i->mName == name)
			return i;
	}
	return nullptr;
}

void Asset::addTag(string name) noexcept {
	mTag.insert(name);
}

bool Asset::checkTag(string name) noexcept {
	if (mTag.find(name) != mTag.end())
		return true;
	return false;
}

void Asset::removeTag(string name) noexcept {
	mTag.erase(name);
}

bool Asset::isEnabled() noexcept {
	return mEnabled;
}

void Asset::setEnabled(bool b) noexcept {
	mEnabled = b;
}

void Asset::move(sf::Vector3f vec) {
	mPosition += vec;

	for (auto& i : mComponent) {
		i.second->move(vec);
	}
	for (auto& i : mChild) {
		i->move(vec);
	}
}

void Asset::draw(pRenderWindow w) {
	for (auto& c : mComponent) {
		if (c.second->isEnabled() && c.second->getType() == AssetComponent::Type::RENDEROBJECT) {
			pComponentRenderObject p = dynamic_pointer_cast <Component::RenderObject>(c.second);
			w.draw(*(p->mSprite));
		}
	}
	for (auto& c : mChild) {
		if (c->isEnabled()) {
			c->draw(w);
		}
	}
}

void Asset::init(std::shared_ptr <cas::Asset> asset) {
	pGui gui = Core::get()->getDisplayManager()->getDefaultGui();
	for (auto& i : mComponent) {
		if (i.second->isEnabled()) {
			i.second->init(asset, gui);
		}
	}
}

void Asset::eventHandler(std::shared_ptr <cas::Asset> asset, pEvent event) {
	pGui gui = Core::get()->getDisplayManager()->getDefaultGui();
	for (auto& i : mComponent)
		if (i.second->isEnabled())
			i.second->eventHandler(asset, event, gui);
}

void Asset::update(std::shared_ptr <cas::Asset> asset) {
	// call update() for every component of this asset
	pGui gui = Core::get()->getDisplayManager()->getDefaultGui();
	for (auto& i : mComponent) {
		if (i.second->isEnabled()) {
			i.second->update(asset, gui);
		}
	}

	// call update() for every child of this asset
	for (auto& i : mChild)
		i->update(i);
}
