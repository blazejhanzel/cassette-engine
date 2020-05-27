#include <cas/pch.h>
#include <cas/Asset.h>
#include <cas/RenderObjectComponent.h>

using namespace cas;
using namespace cas::Component;
using namespace sf;
using namespace std;

RenderObject::RenderObject() {}

RenderObject::RenderObject(const RenderObject& p) {
	mIsVisible = p.mIsVisible;
	mResource = p.mResource;
	mSprite = make_shared <Sprite>(*p.mSprite);
}

inline AssetComponent::Type RenderObject::getType() noexcept {
	return AssetComponent::Type::RENDEROBJECT;
}

inline void RenderObject::setVisible(bool v) noexcept {
	mIsVisible = v;
}

inline bool RenderObject::getVisible() noexcept {
	return mIsVisible;
}

void RenderObject::move(sf::Vector3f vec) {
	mSprite->move(sf::Vector2f(vec.x, vec.y));
}

void RenderObject::connectResource(pResource res) {
	if (res->getType() == Resource::Type::TEXTURE) {
		mResource = res;

		if (!mSprite)
			mSprite = pSprite(new sf::Sprite);
		mSprite->setTexture(*(res->getTexture()));
	}
	else
		throw invalid_argument("Connectes resource isn't texture type.");
}

inline pSprite RenderObject::getSprite() noexcept {
	return mSprite;
}

void RenderObject::init(pAsset asset, pGui gui) {

}

void RenderObject::update(pAsset asset, pGui gui) {

}
