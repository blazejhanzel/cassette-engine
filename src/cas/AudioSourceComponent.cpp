#include <cas/pch.h>
#include <cas/AudioSourceComponent.h>
#include <cas/Core.h>

// TODO: Add positions too sounds and listender component class so sound could be 3D

using namespace cas;
using namespace cas::Component;
using namespace std;

AudioSource::AudioSource() : mAudioManager(Core::get()->getAudioManager()) {}

AudioSource::AudioSource(const AudioSource& p) {
	mResource = p.mResource;
}

inline AssetComponent::Type AudioSource::getType() noexcept {
	return AssetComponent::Type::AUDIOSOURCE;
}

void AudioSource::connectResource(pResource res) {
	if (res->getType() == Resource::Type::SOUND)
		mResource = res;
	else
		throw invalid_argument("Connected resource isn't sound type.");
}

void AudioSource::play() {
	mAudioManager->requestAudio(mResource->getSound());
}

void AudioSource::init(pAsset asset, pGui gui) {

}

void AudioSource::update(pAsset asset, pGui gui) {

}
