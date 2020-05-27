#pragma once

#include "pch.h"

#include "ResourceContainer.h"

namespace cas {

	class Core;

	/**
	* @brief Class for managing display content and windows
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::Core cas::ResourceContainer cas::EventManager cas::SceneManager cas::AssetComponent
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API DisplayManager final {
		friend class Core;
		Core* core = nullptr; ///< Pointer to Core module

		pResourceContainer mResourceContainer{ new cas::ResourceContainer() }; ///< Pointer to Resource Container

		sf::RenderWindow mWindow; ///< Default and the only window 
		tgui::Gui mSplashScreen{ mWindow }; ///< User interface for splash screen
		tgui::Gui mLoadingScreen{ mWindow }; ///< User interface for loading screen
		tgui::Gui mGui{ mWindow }; ///< Customizable user interface

		/**
		* @brief Default private constructor
		* @details Protects from creating unchecked instances.
		* @exception std::runtime_error Throw exceptions when used
		*/
		DisplayManager();

		/**
		* @brief Private constructor
		* @details Private constructor for creating DisplayManager instance. Can be used only from Core.
		* @param Pointer to existing Core module
		*/
		DisplayManager(cas::Core*);
	
	public:
		/**
		* @brief Create new window
		* @details Method for create new sf::RenderWindow, where all things are displayed.
		* @warning Engine supports only one window at the same time. If you try to create new one exception will be thrown.
		* @exception runtime_error Throws exception if try to create more than one window at the same time.
		* @return Address for sf::RenderWindow used for displaying all stuff.
		*/
		pRenderWindow newWindow();

		/**
		* @brief Get address of existing window
		* @return Address for sf::RenderWindow used for displaying all stuff.
		*/
		pRenderWindow getWindow() noexcept;

		/**
		* @brief Destroy existing window
		* @details Destroys existing window if exist.
		*/
		void destroyWindow();

		/**
		* @brief Get active GUI
		* @return Address of used tgui::Gui container
		*/
		pGui getGui() noexcept;

		/**
		* @brief Get default GUI for drawing in assets logic
		* @return Address of used tgui::Gui container
		*/
		pGui getDefaultGui() noexcept;
		
	private:
		/**
		* @brief Runs in every frame
		*/
		void update();
	};

	typedef std::shared_ptr <cas::DisplayManager> pDisplayManager;
}
