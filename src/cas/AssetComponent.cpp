#include <cas/pch.h>
#include <cas/AssetComponent.h>
#include <cas/Core.h>
#include <cas/Asset.h>

using namespace cas;
using namespace std;

void AssetComponent::setEnabled(bool b) {
	mEnabled = b;
}

bool AssetComponent::isEnabled() {
	return mEnabled;
}
