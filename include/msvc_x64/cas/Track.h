#pragma once

#include "pch.h"

namespace cas {
	/**
	* @brief Struct for easier storing track data info
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::AudioManager
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API Track {
		friend class AudioManager;

		std::string mFilePath; ///< Path to file where music is stored
		std::string mName; ///< Name of music, can be used for displaying on GUI
		std::string mArtist; ///< Name of artist, valuable if you want to create something like radio
		bool mLoop = false; ///< Defines if this track should be restarted when ends

	public:
		void setLoop(bool);
	};

	typedef std::shared_ptr <Track> pTrack;
}
