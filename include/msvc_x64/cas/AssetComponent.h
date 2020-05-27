#pragma once

#include "pch.h"

#include "DisplayManager.h"
#include "EventManager.h"

namespace cas {

	class Asset;
	typedef std::shared_ptr <cas::Asset> pAsset;
	
	/**
	* @brief Abstract class, being base to other components
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::Asset cas::DisplayManager cas::EventManager cas::Component::AudioSource cas::Component::Logic cas::Component::RenderObject
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API AssetComponent {
		friend class Asset;

	public:
		/**
		* @brief Enum class for define asset component type
		*/
		enum class Type {
			AUDIOSOURCE,
			LOGIC,
			RENDEROBJECT
		};

	protected:
		std::shared_ptr <Asset> asset; ///< Pointer to asset connected with this component
		bool mEnabled = true; ///< Defines if this component is currently enabled

		/**
		* @brief Abstract function to get Type of component
		* @return Type of component
		*/
		virtual Type getType() noexcept = 0;

	public:
		/**
		* @brief Set status of component
		* @details If component is deactivated, it won't be updated and rendered.
		* @param true for enable or false to disable
		*/
		virtual void setEnabled(bool) final;

		/**
		* @brief Check if this component is currently enabled
		* @retval true If component is enabled
		* @retval false If component is disabled
		*/
		virtual bool isEnabled() final;

		virtual void move(sf::Vector3f) {};

	protected:
		/**
		* @brief Virtual abstact function for initialization
		* @details Initialization runs after component creates
		*/
		virtual void init(pAsset asset, pGui gui) {};

		/**
		* @brief Virtual function for handling events
		* @details Event handling runs every second when it's time to handle events
		*/
		virtual void eventHandler(pAsset asset, pEvent event, pGui gui) {};

		/**
		* @brief Virtual abstract function for updating
		* @details Update runs every frame
		*/
		virtual void update(pAsset asset, pGui gui) {};
	};

	typedef std::shared_ptr <cas::AssetComponent> pAssetComponent;
}
