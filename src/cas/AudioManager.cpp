#include <cas/pch.h>
#include <cas/AudioManager.h>
#include <cas/Core.h>

using namespace cas;
using namespace std;
using namespace sf;

AudioManager::AudioManager() {
	throw runtime_error("Cannot create AudioManager instance without pointer to Core.");
}

AudioManager::AudioManager(Core* c) noexcept : core(c) {}

pTrack AudioManager::addMusic(string id, string path, string name, string artist) {
	pTrack track{ new Track };
	track->mFilePath = path;
	track->mName = name;
	track->mArtist = artist;
	mTrack[id] = track;
	return mTrack[id];
}

pTrack AudioManager::getMusic(string id) {
	return (mTrack.find(id) != mTrack.end()) ? mTrack[id] : nullptr;
}

void AudioManager::removeMusic(string s) {
	if (mTrack.find(s) != mTrack.end()) {
		mTrack.erase(s);
	}
}

void AudioManager::clear() noexcept {
	mTrack.clear();
}

void AudioManager::play(string id) {
	if (mTrack.find(id) != mTrack.end()) {
		if (mMusic.first != nullptr) {
			mMusic.first->stop();
			mMusic = make_pair <pMusic, pTrack>(nullptr, nullptr);
		}

		pMusic music{ new Music };
		if (!music->openFromFile(mTrack[id]->mFilePath)) {
			throw runtime_error("Cannot open file " + mTrack[id]->mFilePath);
		}

		mMusic = make_pair (music, mTrack[id]);
		mMusic.first->play();
		mMusic.first->setLoop(mTrack[id]->mLoop);
	}
}

[[deprecated("Please, use play with name argument (string). It is faster and safer than play by id.")]]
void AudioManager::play(unsigned int id) {
	if (id < mTrack.size()) {
		map <string, pTrack>::iterator it = mTrack.begin();
		for (unsigned int i = 0; i < id; i++) {
			++it;
		}
		play(it->first);
	}
	else {
		throw out_of_range("Tried to use track id which is greater than tracks list size.");
	}
}

void AudioManager::pause() {
	if (mMusic.first != nullptr)
		mMusic.first->pause();
}

void AudioManager::stop() {
	if (mMusic.first->getStatus() == SoundSource::Status::Stopped)
		mMusic = make_pair <pMusic, pTrack>(nullptr, nullptr);
	else
		mMusic.first->stop();
}

void AudioManager::requestAudio(pSoundBuffer p) {
	if (mAudio.size() < 255) {
		pSound sfx;
		sfx->setBuffer(*p);
		mAudio.push_back(sfx);
		sfx->play();
	}
	else {
		if (mAudio.size() > 0) {
			mAudio.erase(mAudio.begin());
			requestAudio(p);
		}
		else {
			throw length_error("Cannot handle too many (256) sounds and buffers in the same time but nothing can be automatically freed.");
		}
	}
}

void AudioManager::update() {
	// Release memory where Audio stopped playing
	for (unsigned int i = 0; i < mAudio.size(); i++) {
		if (mAudio[i]->getStatus() == SoundSource::Status::Stopped) {
			mAudio.erase(mAudio.begin() + i);
			i--;
		}
	}


	// Update music volume
	if (mMusic.first)
		mMusic.first->setVolume(core->getSettings()->mVolumeMusic);
}
