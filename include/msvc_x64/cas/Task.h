#pragma once

#include "pch.h"

namespace cas {

	/**
	* @brief Class with instructions to do
	* @details Inherit from it and write own task() function to use it for loading instructions.
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::StateManager cas::TaskHandler
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API Task {
		friend class StateManager;
		friend class TaskHandler;

	protected:
		std::wstring mDescription = L""; ///< Variable for storing text displayed on loading screen, can be change while task() is running

	private:
		bool mDone = false; ///< TaskHandler use this for check if Thread is done

	protected:
		/**
		* @brief Make Task done
		* @details Use this at the end of your Task object to tell that this thread can be released
		* @warning If you forget to use this, you will be able to create only few threads and then engine will fall in loading loop forever (actually, not exactly forever, it depends on your hardware; nevertheless don't forget!).
		*/
		virtual void done() final;

		/**
		* @brief Pure virtual function for instructions to do on load
		* @details Override this function and write what you need to load, eg. for creating assets in background thread.
		*/
		virtual void task() = 0;
	};

	typedef std::shared_ptr <cas::Task> pTask;
}
