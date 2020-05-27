#pragma once

#include "pch.h"

namespace cas {

	/**
	* @brief Simple class for engine exceptions
	* @details Main difference between this and std exceptions is that this automatically log itself in file and terminal (uses cas::Logger) so you don't need to call what()
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::Logger cas::Core
	* @copyright B³a¿ej Hanzel
	*/
	class Exception : public std::exception {
		const char* mArg; ///< Contains error text (default, this is md5 sum of something that provide functionality to recognise problem)

	public:
		/**
		* @brief Public constructor
		* @param Error text to display
		*/
		Exception(const std::string& what_arg);

		/**
		* @brief Public constructor
		* @param Error text to display
		*/
		Exception(const char* what_arg);

		/**
		* @brief Display error text
		* @return Text of error
		*/
		const char* what() const noexcept;
	};
}
