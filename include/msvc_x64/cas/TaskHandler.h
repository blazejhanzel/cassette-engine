#pragma once

#include "pch.h"

#include "Task.h"

namespace cas {

	/**
	* @brief Helper class for handle task in separated threads
	* @details This class is protected from creating instances and inherit by end-user
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::StateManager cas::Task
	* @copyright B³a¿ej Hanzel
	*/
	class TaskHandler final {
		friend class StateManager;

		bool mReady = true; ///< Define if TaskHandler can receive new tasks
		int mThreadsRunning = 0; ///< Define how many threads are running now
		std::vector <std::pair <std::thread, pTask>> mThread; ///< Vector of all running threads with pointer to theirs Tasks

		/**
		* @brief Default private constructor
		* @details Do nothing. Can be used only from StateManager.
		*/
		TaskHandler() noexcept;

		/**
		* @brief Create new thread for new task
		* @details Creates new thread for predefined Task object. Can handle as many threads as detected in system (or infinity if system doesn't provide info).
		* @param std::shared_ptr <pTask> Task for which thread will be created
		* @exception std::logic_error Throws exception if someone call this function when TaskHandler isn't ready (probability of data loss).
		*/
		void handleTask(pTask);

	public:
		/**
		* @brief Get description from running task
		* @return Description of task
		* @retval Empty string if there is no description or no threads are running
		* @warning If there are more than one task running at the same time, desctiption is taken from first one.
		*/
		std::wstring getDescription();

	private:
		/**
		* @brief Run in every frame if StateManager calls it
		* @details Checks for done threads, joins them and release memory for Tasks
		*/
		void update();
	};

	typedef std::shared_ptr <TaskHandler> pTaskHandler;
}
