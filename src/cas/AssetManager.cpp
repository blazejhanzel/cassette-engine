#include <cas/pch.h>
#include <cas/AssetManager.h>
#include <cas/Core.h>

using namespace cas;
using namespace std;

AssetManager::AssetManager() {
	throw runtime_error("Cannot create Asset Manager instance withour pointer to Core.");
}

AssetManager::AssetManager(Core* c) : core(c) {}

pResource AssetManager::newResource(Resource::Type type, std::string name, std::string path) {
	if (mResource.find(name) != mResource.end())
		throw runtime_error("Resource with this name already exists. Potential data loss.");

	mResource[name] = pResource(new Resource(type, path, core->getSettings()->mBufferResources));
	return mResource[name];
}

pResource AssetManager::newResource(Resource::Type type, std::string name, pResource res, int id) {
	if ((type == Resource::Type::TEXTURE || type == Resource::Type::TEXTURESHEET) && res->mType == Resource::Type::TEXTURESHEET) {
		if (mResource.find(name) != mResource.end())
			throw runtime_error("Resource with this name already exists. Potential data loss.");

		mResource[name] = pResource(new Resource(type, res, id));
		return mResource[name];
	}
	else
		throw invalid_argument("This function provide functionality to Texture Resources based on sheets only. Correct params.");
	return nullptr;
}

pResource AssetManager::getResource(std::string name) noexcept {
	if (mResource.find(name) != mResource.end())
		return mResource[name];
	return nullptr;
}

void AssetManager::removeResource(std::string name) noexcept {
	if (mResource.find(name) != mResource.end())
		mResource.erase(name);
}

pAsset AssetManager::newAsset(std::string name) {
	if (mAsset.find(name) != mAsset.end())
		throw runtime_error("Asset with this name already exists. Potential data loss.");

	pAsset asset{ new Asset(name) };
	mAsset[name] = asset;
	return mAsset[name];
}

pAsset AssetManager::getAsset(std::string name) noexcept {
	if (mAsset.find(name) != mAsset.end())
		return mAsset[name];
	return nullptr;
}

void AssetManager::removeAsset(std::string name) noexcept {
	if (mAsset.find(name) != mAsset.end())
		mAsset.erase(name);
}

void AssetManager::update() {
	// TODO: Release memory when resources isn't used anymore
}
