#pragma once

#include "pch.h"

#include "AssetManager.h"
#include "AudioManager.h"
#include "DisplayManager.h"
#include "EventManager.h"
#include "NetworkManager.h"
#include "SceneManager.h"
#include "StateManager.h"
#include "EngineSettings.h"

namespace cas {

	class CASENG_API Core final {
		pLogger mLogger{ new cas::Logger() };
		pEngineSettings mEngineSettings{ new cas::EngineSettings(this) };

		pAssetManager mAssetManager{ new cas::AssetManager(this) };
		pAudioManager mAudioManager{ new cas::AudioManager(this) };
		pDisplayManager mDisplayManager{ new cas::DisplayManager(this) };
		pEventManager mEventManager{ new cas::EventManager(this) };
		pNetworkManager mNetworkManager{ new cas::NetworkManager(this) };
		pSceneManager mSceneManager{ new cas::SceneManager(this) };
		pStateManager mStateManager{ new cas::StateManager(this) };

		Core();
		Core(const Core&) noexcept;
		~Core() noexcept;

	public:
		pAssetManager getAssetManager() noexcept;
		pAudioManager getAudioManager() noexcept;
		pDisplayManager getDisplayManager() noexcept;
		pEventManager getEventManager() noexcept;
		pNetworkManager getNetworkManager() noexcept;
		pSceneManager getSceneManager() noexcept;
		pStateManager getStateManager() noexcept;
		pEngineSettings getSettings() noexcept;
		pLogger getLogger() noexcept;
		static Core* get() noexcept;

		/**
		* @brief Process arguments to angine
		* @details Sets EngineSettings values to processed in args list and save configuration to file. Possible values are listed below.
		* @li @c -width Set window width to value next to it
		* @li @c -height Set height of window to value next to it
		* @li @c -fullscreen Display content in fullscreen mode
		* @li @c -windowed Display content in windowed mode (it's stronger than @c -fullscreen arg
		* @li @c -ticks Set maximum ticks per second to value next to it
		* @li @c -vsync Set vsync enable, add @c disable next to it to disable
		* @li @c -volumeMusic Set volume of music to value next to it (percentage, eg. @c 70 )
		* @li @c -volumeSfx Set volume of sound effects to value next to it (percentage)
		* @li @c -buffer Try to load resources on application load nor in background when running. Add @c disable to disable this functionality.
		* @param argc Count of arguments
		* @param argv Pointer to char* witch contains args texts
		*/
		void processArgs(int argc, char** argv);
		int run();
	};

	typedef Core* pCore;
}
