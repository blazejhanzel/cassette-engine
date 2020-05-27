#pragma once

#include "pch.h"

#include "TaskHandler.h"
#include "Task.h"

namespace cas {

	class Core;

	/**
	* @brief Class for managing game state and do tasks in background threads
	* @details Class is required for engine proper working. This class can be created only in Core.
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::Core cas::TaskHandler cas::Task
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API StateManager final {
		friend class Core;
		Core* core = nullptr; ///< Pointer to Core module

	public:
		/**
		* @brief Enum class with defined possible engine states
		*/
		enum class State {
			SPLASHSCREEN, ///< Default value when engine starts, it is only moment when it can be used
			LOADING, ///< State for loading, when it's active, TaskHandler does his tasks
			SCENEACTIVE, ///< When this is active, user (programmer) have control of what is doing
			END ///< Used only when exiting, this provide a message for all managers to end their job
		};
		
	private:
		State mState = State::SPLASHSCREEN; ///< Defines current engine state
		State mStateSet = State::SPLASHSCREEN; ///< Defines state which will be set in next frame
		pTaskHandler mTaskHandler{ new cas::TaskHandler }; ///< Pointer to TaskHandler class used for create threads
		std::vector <pTask> mTask; ///< Vector of task that need to be done in next LOADING state

		/**
		* @brief Default private constructor
		* @details Does nothing. Protects from creating unchecked instances.
		* @except std::runtime_error Throws exceptions when runs.
		*/
		StateManager();

		/**
		* @brief Private constructor
		* @details Creates instance of StateManager with pointer to Core. Can be used only in Core.
		*/
		StateManager(Core*);

	public:
		/**
		* @brief Set actual engine state
		* @exception std::runtime_error Throws exception if tried to set to SPLASHSCREEN value.
		*/
		void setState(State);

		/**
		* @brief Get actual engine state
		* @return Returns current state in StateManager::State (enum) type.
		*/
		State getState() noexcept;

		/**
		* @brief Get pointer to Task Handler
		* @return Pointer to Task Handler
		*/
		pTaskHandler getTaskHandler() noexcept;

		/**
		* @brief Add Task object to do when loading
		* @details All tasks added to StateManager will be done in background thread when state is set to LOADING.
		*/
		void addTask(pTask) noexcept;

	private:
		/**
		* @brief Runs in every frame
		*/
		void update();
	};

	typedef std::shared_ptr <cas::StateManager> pStateManager;
}
