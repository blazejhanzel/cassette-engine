#pragma once

#include "pch.h"

namespace cas {

	class Core;

	/**
	* @brief Class for managing basic engine configurations
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::Core
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API EngineSettings final {
		friend class Core;
		Core* core = nullptr; ///< Pointer to Core module

	public:
		int mWindowWidth = 1280; ///< Width of window that will be created
		int mWindowHeight = 720; ///< Height of window that will be created
		bool mFullscreen = false; ///< Information about running in windowed/fullscreen mode
		int mTicksPerSecond = 60; ///< Max fps that will be generated
		bool mVsync = true; ///< Try to always use monitors refreshrate as fps
		int mVolumeMusic = 100; ///< Users volume for music
		int mVolumeSfx = 100; ///< Users volume for sound effects
		bool mBufferResources = true; ///< Buffer all resources at init or when needed
		int mSystemThreads = std::thread::hardware_concurrency(); ///< Number of threads that can be used by the engine paralelly

	private:
		/**
		* @brief Default private constructor
		* @details Protects from creating unchecked instances
		* @exception std::runtime_error Throws exception when used (protect from unchecked implementing)
		*/
		EngineSettings();

		/**
		* @brief Private constructor
		* @details Private constructor accessible from Core, load default values on start
		* @param Pointer to existing Core module
		* @exception std::runtime_error Throws exception if don't have permission to read/write config file
		*/
		EngineSettings(Core*);

	public:
		/**
		* @brief Apply settings to windows and managers
		* @details Applies values to managers, e.g. resize a window
		*/
		void confirmSettings();

		/**
		* @brief Load settings from config file
		* @retval true If file was opened and configuration loaded succesfully
		* @retval false If file doesn't exist or cannot open it
		*/
		bool loadFromFile();

		/**
		* @brief Save settings to config file
		* @details Don't remove values existing in file (but change order) and save current.
		* @retval true If file was opened add configuraion saved succesfully
		* @retval false If file cannot be created
		*/
		bool saveToFile();
	};

	typedef std::shared_ptr <cas::EngineSettings> pEngineSettings;
}

