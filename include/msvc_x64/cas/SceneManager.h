#pragma once

#include "pch.h"

#include "Scene.h"

namespace cas {

	class Core;

	/**
	* @brief Class for managing scenes
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::Core cas::Scene
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API SceneManager final {
		friend class Core;
		Core* core = nullptr; ///< Pointer to core module

		friend class DisplayManager;

		pScene mActiveScene = nullptr; ///< Pointer to currently rendering scene
		std::map <std::string, pScene> mScene; ///< Map of all scenes used in game

		/**
		* @brief Private constructor
		* @details Doesn nothing, don't use it
		* @exception std::runtime_error Throws when used
		*/
		SceneManager();

		/**
		* @brief Commonly used private constructor
		* @param Pointer to Core
		*/
		SceneManager(Core*);

	public:
		/**
		* @brief Add scene to memory
		* @param Name of the scene (must be unique)
		* @return Pointer to currently added scene
		* @exception std::runtime_error Throws if scene with this name already exists
		* @warning You can catch and forget about exception if you want to overwrite scene, but it's not a good practice.
		*/
		pScene addScene(std::string);

		/**
		* @brief Get scene by name
		* @param Name of the scene
		* @return Pointer to scene
		*/
		pScene getScene(std::string) noexcept;

		/**
		* @brief Remove scene from memory
		* @details Removes scene from memory. You can use this if you don't want to use scene anymore, this will release memory, all instance will be removed.
		* @param Name of the scene to remove
		*/
		void removeScene(std::string) noexcept;

		/**
		* @brief Change active scene
		* @details Changes actually rendered scene to selected
		* @param Pointer to scene which should be active now
		* @warning All will be done in one frame, that means scene is loaded extremally fast but need to be loaded earlier. For loading scene use cas::Task - this provide functionality to do this in the background.
		*/
		void setActiveScene(pScene) noexcept;

		/**
		* @brief Get pointer to active scene
		* @return Pointer to active scene
		*/
		pScene getActiveScene() noexcept;

	private:	
		/**
		* @brief Runs in every frame
		*/
		void update();
	};

	typedef std::shared_ptr <cas::SceneManager> pSceneManager;
}

