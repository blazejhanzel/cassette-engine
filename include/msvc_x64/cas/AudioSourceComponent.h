#pragma once

#include "pch.h"

#include "AssetComponent.h"
#include "AudioManager.h"
#include "Resource.h"

namespace cas {
	namespace Component {

		/**
		* @brief Component with audio source class
		* @details Provide functionality to play sounds (sfx) on scene
		* @authors B³a¿ej Hanzel
		* @date 2020
		* @sa cas::AssetComponent cas::Asset cas::Resource cas::AudioManager
		* @copyright B³a¿ej Hanzel
		*/
		class CASENG_API AudioSource final : public AssetComponent {
			friend class Asset;
			pAudioManager mAudioManager; ///< Pointer to AudioManager, because this class use it

			pResource mResource = nullptr; ///< Pointer to used resource

			/**
			* @brief Private constructor
			* @details Does nothing. Don't use it.
			*/
			AudioSource();

			/**
			* @brief Default copy constructor
			* @param Reference to component which will be copied
			*/
			AudioSource(const AudioSource&);

			/**
			* @brief Abstract function to get Type of component
			* @return Type of component
			*/
			AssetComponent::Type getType() noexcept;

			void move(sf::Vector3f) {}

		public:
			/**
			* @brief Connect audio source wih sound buffer resource
			* @param Pointer to resource
			*/
			void connectResource(pResource);

			/**
			* @brief Play sound
			* @details This function requests for creating new sound, request is send to Audio Manager.
			*/
			void play();

		private:
			/**
			* @brief Initialize component
			*/
			void init(pAsset asset, pGui gui);

			/**
			* @brief Runs in every frame
			*/
			void update(pAsset asset, pGui gui);
		};
	}

	typedef std::shared_ptr <cas::Component::AudioSource> pComponentAudioSource;
}
