#pragma once

#include "pch.h"

namespace cas {

	typedef sf::Event& pEvent;

	class Core;

	/**
	* @brief Class for managing events
	* @details Basic implementation handle window resize, window close and gui events
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::Core cas::DisplayManager cas::AssetComponent
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API EventManager final {
		friend class Core;
		Core* core = nullptr; ///< Pointer to mother Core object

		sf::Event mEvent; ///< SFML Event variable for handling events

		/**
		* @brief Default private constructor
		* @details Do nothing. Protects from unchecked instances.
		* @exception runtime_error Throws exception when used.
		*/
		EventManager();

		/**
		* @brief Commonly used private constructor
		* @details Create EventManager instance with pointer to Core. Can be used only from Core.
		* @param Pointer to existing Core module
		*/
		EventManager(Core*) noexcept;

	public:
		/**
		* @brief Get address to currently used gui
		* @return Address to currently used gui
		*/
		pEvent getEvent() noexcept;

	private:
		/**
		* @brief Runs in every frame
		*/
		void update();
	};

	typedef std::shared_ptr <cas::EventManager> pEventManager;
}
