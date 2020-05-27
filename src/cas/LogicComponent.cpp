#include <cas/pch.h>
#include <cas/LogicComponent.h>

using namespace cas;
using namespace cas::Component;
using namespace std;

Logic::Logic() {}

Logic::Logic(const Logic& l) {}

inline AssetComponent::Type Logic::getType() noexcept {
	return AssetComponent::Type::LOGIC;
}
