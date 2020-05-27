#pragma once

#include "pch.h"

namespace cas {

	/**
	* @brief Class for logging engine behaviours to console and file
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::Core
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API Logger final {
		friend class Core;
		
		std::fstream mFile; ///< Output log file

		/**
		* @brief Get formatted system time
		* @details Function getting system time and returning as formatted text.
		* @return Time format HH:MM:SS as std::string
		*/
		std::string getSystemTime() noexcept;

	public:
		/**
		* @brief Default public constructor
		*/
		Logger();

		/**
		* @brief Default destructor
		* @details Close file stream.
		*/
		~Logger();

		/**
		* @brief Stream out operator
		* @details Save content of stream to log file and display in console. 
		* @retrun Address of this class
		*/
		template < typename T > Logger& operator << (const T& os) {
			mFile << getSystemTime() << " " << os << std::endl;
			std::cout << getSystemTime() << " " << os << std::endl;
			return *this;
		}
	};

	typedef std::shared_ptr <cas::Logger> pLogger;
}
