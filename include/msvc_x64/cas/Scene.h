#pragma once

#include "pch.h"

#include "Asset.h"

namespace cas {

	/**
	* @brief Container class for all assets
	* @details This container is a world that will be rendered
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::SceneManager cas::DisplayManager cas::Asset
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API Scene final {
		friend class DisplayManager;
		friend class SceneManager;
		friend class EventManager;

		std::map <std::string, pAsset> mAsset; ///< Map of all asset in this world

		/**
		* @brief Default private constructor
		*/
		Scene();

	public:
		/**
		* @brief Add Asset by pointer
		* @details Creates copy of predefined asset in world
		* @param Pointer to asset that will be instancated
		* @param Name of instance
		* @return Pointer to newly created asset
		* @warning If asset with this name already exists new one will be created with suffix -X, where X is unique number. This provide functionality to copy asset which names doesn't matter.
		*/
		pAsset addAsset(pAsset, std::string);

		/**
		* @brief Get asset by name
		* @param Name of asset to get
		* @return Pointer to asset or nullptr if doesn't exist
		* @warning Note, that names can be changed by engine, see above (addAsset).
		*/
		pAsset getAsset(std::string) noexcept;

		/**
		* @brief Remove asset by name
		* @param Name of asset to remove
		*/
		void removeAsset(std::string) noexcept;

		/**
		* @brief Remove all assets from scene
		*/
		void clear() noexcept;

	private:
		/**
		* @brief Draw all assets on scene
		* @details This function call draw() functions in every Asset
		* @param Pointer to draw target window
		*/
		void draw(pRenderWindow);

		/**
		* @brief Initialize all assets on scene
		* @details This method runs init() and intGui() in all assets on scene
		* @warning You should initialize asset only once since scene runned, this function is used by engine and better not use it if you are not sure what you are doing.
		*/
		void init();

		/**
		* @brief Handle event for all assets on scene
		* @param Reference to sf::Event
		*/
		void eventHandler(pEvent event);

		/**
		* @brief Runs every frame
		*/
		void update();
	};

	typedef std::shared_ptr <cas::Scene> pScene;
}
