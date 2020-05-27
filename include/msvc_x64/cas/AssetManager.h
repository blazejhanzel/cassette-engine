#pragma once

#include "pch.h"

#include "Asset.h"
#include "Resource.h"

namespace cas {
	class Core;

	/**
	* @brief Class for managing game assets
	* @details Managing assets, resources and it's instances and buffering files
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::Core cas::Asset cas::Resource
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API AssetManager final {
		friend class Core;
		Core* core = nullptr; ///< Pointer to mother Core object

		std::map <std::string, pAsset> mAsset; ///< Map of all assets existing in game
		std::map <std::string, pResource> mResource; ///< Map of all resources used in assets

		/**
		* @brief Private constructor
		* @details Does nothing. Don't use it.
		* @exception std::runtime_error Throws when used
		*/
		AssetManager();

		/**
		* @brief Recently used private constructor
		* @param Pointer to Core object
		*/
		AssetManager(Core*);

	public:
		/**
		* @brief Create new resource
		* @details This function is for resource types: FONT, GUITHEME, SOUND, TEXTURE (single) and TEXTURESHEET, for TEXTURE (from sheet) look function below
		* @param Type of resource
		* @param Name of resource (used in code)
		* @param Resource file path
		* @return Pointer to newly created resource
		* @exception std::runtime_error Throws if resource with this name already exists, you can catch this and forget if you want to overwrite resource, but it's not a good practice
		*/
		pResource newResource(Resource::Type, std::string, std::string);

		/**
		* @brief Create new resource (for TEXTURE based on sheets only)
		* @param Type of resource (TEXTURE only)
		* @param Name of resource (used in code)
		* @param Pointer to TEXTURESHEET resource
		* @param ID of texture to get from sheet
		* @return Pointer to newly created resource
		* @exception std::runtime_error Throws if resource with this name already exists, you can catch this and forget if you want to overwrite resource, but it's not a good practice
		* @exception std::invalid_argument Throws if type isn't TEXTURE or resource from param isn't TEXTURESHEET
		*/
		pResource newResource(Resource::Type, std::string, pResource, int);

		/**
		* @brief Get pointer to resource by name
		* @param Name of resource to get
		* @return Pointer to resource or nullptr if doesn't exist
		*/
		pResource getResource(std::string) noexcept;

		/**
		* @brief Remove resource from resource list to free memory
		* @warning Use this function only if you will not use this resource anymore, otherwise engine automatically free memory - you don't need to remove it all the time
		* @param Name of resource to remove
		*/
		void removeResource(std::string) noexcept;

		/**
		* @brief Create new asset
		* @param Name of newly created asset
		* @return Pointer to newly created asset
		* @exception std::runtime_error Throws if asset with this name already exist, you can catch and forget it if you want to overwrite this asset, but it's not a good practice
		*/
		pAsset newAsset(std::string);

		/**
		* @brief Get asset by name
		* @param Name of asset
		* @return Pointer to Asset or nullptr if doesn't exist
		*/
		pAsset getAsset(std::string) noexcept;

		/**
		* @brief Remove asset by name
		* @param Name of asset to remove
		* @warning Deleting asset which is currently used on scene will probably work, but it's a good practice. Rather use it after closing scene if you will not use it anymore. By deleting you cannot use instances of this asset anymore.
		*/
		void removeAsset(std::string) noexcept;

	private:
		/**
		* @brief Runs in every frame
		*/
		void update();
	};

	typedef std::shared_ptr <cas::AssetManager> pAssetManager;
}
