#pragma once

#include "pch.h"

#include "AssetComponent.h"
#include "LogicComponent.h"

namespace cas {
	
	/**
	* @brief Container for asset components which creates one big asset
	* @details Every asset has it own componentns and inherited from sf::Transformable variables and methods for putting it in 2D world
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::AssetManager cas::AssetComponent cas::Scene
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API Asset final {
		friend class AssetManager;
		friend class Scene;

		bool mEnabled = true; ///< Defines if asset is enabled or not, usefull on scenes
		std::string mName; ///< Unique name of asset
		std::set <std::string> mTag; ///< Set of asset tags, used for detecting collision or grouping
		std::map <std::string, pAssetComponent> mComponent; ///< Container for all components gained by this asset, main power of assets
		std::vector <std::shared_ptr <Asset>> mChild; ///< Vector of childs, child objects are managed by their parents and moved where it parents
	
	public:
		sf::Vector3f mPosition = sf::Vector3f(0., 0., 0.);
		sf::Vector3f mRotation = sf::Vector3f(0., 0., 0.);

		std::map <std::string, boost::any> var; ///< Map of dynamically typed variables used in game assets

		/**
		* @brief Public constructor
		* @details Does nothing.
		*/
		Asset() noexcept;

		/**
		* @brief Commonly used public constructor
		* @param Unique name of the asset
		*/
		Asset(std::string) noexcept;

		/**
		* @brief Copy constructor
		* @param Name of instanced asset
		* @param Reference to copied object
		*/
		Asset(std::string, const Asset&);
		
		/**
		* @brief Add new component to asset
		* @details Create new component with specified type (cannot be LOGIC)
		* @param Type of component
		* @param Unique name of component
		* @param Pointer to existing asset component if new component should be a copy
		* @return Pointer to newly created component
		* @exception std::invalid_argument If tried to use with LOGIC component
		* @exception std::runtime_error If component with this name already exist, you can catch and forget about exception but it's not a good practice
		*/
		pAssetComponent addComponent(AssetComponent::Type, std::string, pAssetComponent p = nullptr);

		/**
		* @brief Get component by name
		* @param Name of the component
		* @return Pointer to component or nullptr if doesn't exist
		*/
		pAssetComponent getComponent(std::string) noexcept;

		/**
		* @brief Remove component by name
		* @param Name of the component
		*/
		void removeComponent(std::string) noexcept;

		/**
		* @brief All logic component to asset
		* @param Pointer to logic
		* @param Name of component (must be unique; shared with other components)
		* @return Pointer to newly created component
		* @exception std::runtime_error If component with this name already exist, you can catch and forget about exception but it's not a good practice
		*/
		pAssetComponent addLogic(std::shared_ptr <cas::Component::Logic>, std::string);

		/**
		* @brief Add child asset to this asset
		* @details Child are used to move them relatively for parents and for managind it's update() function from parent
		* @param Pointer to Asset object
		*/
		void addChild(std::shared_ptr <Asset>) noexcept;

		/**
		* @brief Get child by name
		* @param Name of child
		* @warning Complexity of this method is linear. Try not to use it too much for assets with a lot of child or try to not setting to many childs.
		* @return Pointer to asset
		*/
		std::shared_ptr <cas::Asset> getChild(std::string) noexcept;

		/**
		* @brief Add tag to asset
		* @details Tags are used to detect collisions or grouping elements. This method adds a tag.
		* @param Tag - your own tag that you will use later, eg. "bullet" or "weapon"
		*/
		void addTag(std::string) noexcept;

		/**
		* @brief Check if this asset have tag
		* @param Tag to check
		* @retval true Asset have this tag
		* @retval false Asset doesn't have this tag
		*/
		bool checkTag(std::string) noexcept;

		/**
		* @brief Remove tag from asset
		* @param Name of tag to remove
		*/
		void removeTag(std::string) noexcept;

		/**
		* @brief Check if asset is enabled
		* @retval true Asset is enabled
		* @retval false Asset is disabled
		*/
		bool isEnabled() noexcept;

		/**
		* @brief Set asset enabled or not
		* @param True for enable, false for disable
		*/
		void setEnabled(bool) noexcept;

		void move(sf::Vector3f);

	private:
		/**
		* @brief Draw all drawable components
		* @param Target window, where will be drawn
		*/
		void draw(pRenderWindow);

		/**
		* @brief Initialize asset
		* @details Run once, after adding to scene the best
		* @param Pointer to asset where method is called
		*/
		void init(std::shared_ptr <cas::Asset> asset);

		/**
		* @brief Handle event for all components in this asset
		* @param Pointer to asset where method is called
		* @param Reference to sf::Event
		*/
		void eventHandler(std::shared_ptr <cas::Asset> asset, pEvent event);

		/**
		* @brief Runs every frame
		* @param Pointer to asset where method is called
		*/
		void update(std::shared_ptr <cas::Asset> asset);
	};
}
