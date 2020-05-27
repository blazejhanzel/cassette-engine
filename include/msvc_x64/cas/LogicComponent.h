#pragma once

#include "pch.h"

#include "AssetComponent.h"

namespace cas {
	namespace Component {
		class CASENG_API Logic : public AssetComponent {
			friend class Asset;

		public:
			std::map <std::string, boost::any> var; // TODO: This should be in Asset class

			/**
			* @brief Default public constructor
			* @details Does nothing.
			*/
			Logic();

			/**
			* @brief Copy constructor
			* @param Reference to component which will be copied
			*/
			Logic(const Logic&);

			/**
			* @brief Abstract function to get Type of component
			* @return Type of component
			*/
			AssetComponent::Type getType() noexcept final;

			void move(sf::Vector3f) {}

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
	}

	typedef std::shared_ptr <cas::Component::Logic> pComponentLogic;
}
