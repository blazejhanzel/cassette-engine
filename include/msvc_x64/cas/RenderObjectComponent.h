#pragma once

#include "pch.h"

#include "AssetComponent.h"
#include "Resource.h"

namespace cas {
	namespace Component {

		/**
		* @brief Component for rendering sprites and animations class
		* @authors B³a¿ej Hanzel
		* @date 2020
		* @sa cas::Asset cas::AssetComponent cas::Resource
		* @copyright B³a¿ej Hanzel
		*/
		class CASENG_API RenderObject : public AssetComponent {
			friend class Asset;

			bool mIsVisible = true; ///< Defines if this render object is rendered, defualt true
			pResource mResource = nullptr; ///< Pointer to texture resource
			pSprite mSprite = nullptr; ///< Pointer to rendered sprite

			/**
			* @brief Private constructor
			* @details does nothing. Don't use it.
			*/
			RenderObject();

			/**
			* @brief Default copy constructor
			* @param Reference to component which will be copied
			*/
			RenderObject(const RenderObject&);

			/**
			* @brief Abstract function to get Type of component
			* @return Type of component
			*/
			AssetComponent::Type getType() noexcept;

		public:
			/**
			* @brief Set if object is rendered or not
			* @param true - render, false- don't render
			*/
			void setVisible(bool) noexcept;

			/**
			* @brief Get object render status
			* @retval true Object is rendered
			* @retval false Object is unvisible, not rendering
			*/
			bool getVisible() noexcept;

			void move(sf::Vector3f);

			/**
			* @brief Connect component with texture resource
			* @param Pointer to texture resource
			* @exception std::invalid_argument Throws if resource isn't texture type
			*/
			void connectResource(pResource);

			/**
			* @brief Get pointer to sprite
			* @return Pointer to current sprite
			*/
			pSprite getSprite() noexcept;

		private:
			/**
			* @brief Initialize this asset
			*/
			void init(pAsset asset, pGui gui);

			/**
			* @brief Runs in every frame
			*/
			void update(pAsset asset, pGui gui);
		};
	}

	typedef std::shared_ptr <cas::Component::RenderObject> pComponentRenderObject;
}
