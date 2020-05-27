#pragma once

#include "pch.h"

namespace cas {

	/**
	* @brief Helper class for storing resources used by engine
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::DisplayManager
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API ResourceContainer final {
		friend class DisplayManager;

		std::array <sf::Uint8, 64*64*4> mEngineIcon; ///< 64x64 engine icon raw data
		std::array <sf::Uint8, 256*256*4> mEngineLogo; ///< 256x256 engine logo raw data

		tgui::Theme mTheme; // TODO: This should be moved to ResourcesManager when it will be possible
		sf::Font mFontBlack, mFontRegular; // TODO: This should be moved to ResourcesManager when it will be possible

		sf::Texture mLogoTex; ///< Texture variable for logo on splash screen
		sf::Sprite mLogoSpr; ///< Sprite variable for logo on splash screen
		sf::Text mEngineNameText; ///< Title text on splash screen
		sf::Text mCompanyNameText; ///< Company or author name on splash screen (displayed above title)
		sf::Text mVersionText; ///< Current version info text, displayed below title

		/**
		* @brief Default private constructor
		* @details Constructor accessible only be DisplayManager. Define entire splash screen gui
		*/
		ResourceContainer();
	};

	typedef std::unique_ptr <ResourceContainer> pResourceContainer;
}
