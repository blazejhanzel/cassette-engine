#include <cas/pch.h>
#include <cas/Core.h>

using namespace cas;
using namespace std;

Core::Core() {
	string ver = to_string(CAS_VERSION_MAJOR) + "." + to_string(CAS_VERSION_MINOR) + "." + to_string(CAS_VERSION_PATCH);
#ifdef CAS_VERSION_TEXT
	ver += "-" CAS_VERSION_TEXT;
#endif
	*mLogger << "Hello! Cassette Engine just started. Your version is " + ver;
}

Core::Core(const Core& c) noexcept : Core() {}

Core::~Core() noexcept {}

pAssetManager Core::getAssetManager() noexcept {
	return mAssetManager;
}

pAudioManager Core::getAudioManager() noexcept {
	return mAudioManager;
}

pDisplayManager Core::getDisplayManager() noexcept {
	return mDisplayManager;
}

pEventManager Core::getEventManager() noexcept {
	return mEventManager;
}

pNetworkManager Core::getNetworkManager() noexcept {
	return mNetworkManager;
}

pSceneManager Core::getSceneManager() noexcept {
	return mSceneManager;
}

pStateManager Core::getStateManager() noexcept {
	return mStateManager;
}

pEngineSettings Core::getSettings() noexcept {
	return mEngineSettings;
}

pLogger Core::getLogger() noexcept {
	return mLogger;
}

Core* Core::get() noexcept {
	static Core core;
	return &core;
}

void Core::processArgs(int argc, char** argv) {
	if (argc > 1) {
		string msg = "Processed args: ";

		for (int i = 1; i < argc; i++) {
			if (!strcmp(argv[i], "-width")) {
				mEngineSettings->mWindowWidth = atoi(argv[i + 1]);
				i++;
			}
			else if (!strcmp(argv[i], "-height")) {
				mEngineSettings->mWindowHeight = atoi(argv[i + 1]);
				i++;
			}
			else if (!strcmp(argv[i], "-fullscreen")) {
				mEngineSettings->mFullscreen = true;
			}
			else if (!strcmp(argv[i], "-windowed")) {
				mEngineSettings->mFullscreen = false;
			}
			else if (!strcmp(argv[i], "-ticks")) {
				mEngineSettings->mTicksPerSecond = atoi(argv[i + 1]);
				i++;
			}
			else if (!strcmp(argv[i], "-vsync")) {
				if (!strcmp(argv[i + 1], "disable")) {
					mEngineSettings->mVsync = false;
					i++;
				}
				else {
					mEngineSettings->mVsync = true;
				}
			}
			else if (!strcmp(argv[i], "-volumeMusic")) {
				mEngineSettings->mVolumeMusic = atoi(argv[i + 1]);
				i++;
			}
			else if (!strcmp(argv[i], "-volumeSfx")) {
				mEngineSettings->mVolumeSfx = atoi(argv[i + 1]);
				i++;
			}
			else if (!strcmp(argv[i], "-buffer")) {
				if (!strcmp(argv[i + 1], "disable")) {
					mEngineSettings->mBufferResources = false;
					i++;
				}
				else {
					mEngineSettings->mBufferResources = true;
				}
			}
			else if (!strcmp(argv[i], "-nosplash")) {
				mStateManager->setState(StateManager::State::LOADING);
			}
			else {
				msg += argv[i];
			}
		}

		if (msg != "Processed args: ") {
			*mLogger << msg;
		}

		mEngineSettings->saveToFile();
	}
}

int Core::run() {
	mEngineSettings->loadFromFile();
	mDisplayManager->newWindow();
	
	// TODO: This need some cleaning when all managers will work properly
	thread networkThr([&]() { mNetworkManager->update(); });
	while (mStateManager->getState() != StateManager::State::END) {
		mStateManager->update();
		mEventManager->update();
		mAssetManager->update();
		mAudioManager->update();
		if (mStateManager->getState() == StateManager::State::SCENEACTIVE)
			mSceneManager->update();
		mDisplayManager->update();
	}
	networkThr.join();

	return 0;
}
