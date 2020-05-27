#pragma once

#include "pch.h"

#include <cas/Track.h>

namespace cas {

	typedef std::shared_ptr <sf::Music> pMusic;
	typedef std::shared_ptr <sf::Sound> pSound;
	typedef std::shared_ptr <sf::SoundBuffer> pSoundBuffer;

	class Core;

	/**
	* @brief Class for managing audio instances
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::Core cas::Track
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API AudioManager final {
		friend class Core;
		Core* core = nullptr; ///< Pointer to Core module

		std::map <std::string, pTrack> mTrack; ///< Storage for all musics that can be used for soundtrack
		std::pair <pMusic, pTrack> mMusic = std::make_pair <pMusic, pTrack>(nullptr, nullptr); ///< Pointers to actually playing music and it's data
		std::vector <pSound> mAudio; ///< Vector of sounds generated on scene

		/**
		* @brief Default private constructor
		* @details Unused. Use constructor with parameter istead.
		* @exception std::runtime_error Throws exception when used (protects from unchecked implementing)
		*/
		AudioManager();

		/**
		* @brief Commonly used constructor
		* @details Creates pointer to Core-mother object. Can be used from Core.
		* @param Pointer to existing Core module
		*/
		AudioManager(Core*) noexcept;

	public:
		/**
		* @brief Add music to track list
		* @details Checks if pTrack data has path info and adds it to track list.
		* @param Name of the track used in development (use easy-to-remember names)
		* @param Pointer to Track structure, where track data are stored
		* @return Pointer to a newly created track
		* @exception std::runtime_error Throws exception when tried to add music without path to file
		*/
		pTrack addMusic(std::string, std::string, std::string, std::string = "null");

		/**
		* @brief Get music by name
		* @details Get pointer to track by name
		* @param Name of the track
		* @return Pointer to track
		*/
		pTrack getMusic(std::string);

		/**
		* @brief Remove track from tracks list
		* @details Removes track from tracks list if exist.
		* @param Name of track to remove. Use code-name not mName from Track struct
		*/
		void removeMusic(std::string);

		/**
		* @brief Remove all tracks from tracks list
		*/
		void clear() noexcept;

		/**
		* @brief Play music selected by name
		* @details Plays music selected by name if exists in track list
		* @param Name of the music (short name not mName from Track struct)
		* @exception std::runtime_error Throws exceptions if cannot open music file
		*/
		void play(std::string);

		/**
		* @brief Play music selected by id
		* @details Plays music selected by id if exists in track list
		* @param ID of music to play
		* @exception std::out_of_range Throws if tried to use track id which is greater than tracks list size
		* @deprecated Please, use play with name argument (string). It is faster and safer than play by id.
		*/
		void play(unsigned int);

		/**
		* @bried Pause currently played music if exists
		*/
		void pause();

		/**
		* @brief Stop currently played music
		* @details Stop currently played music if it's not already stopped or clear music buffor if it's.
		*/
		void stop();

		/**
		* @brief Request playing sound effect
		* @details Creates new sound on scene if sound buffers aren't overflowed or tries to unload them first
		* @param Pointer to Sound Buffer
		* @exception std::length_error Throws if too many (256; this is limit of OpenAL what SFML Documentation says) sounds are played in the same time and noone can be unloaded
		*/
		void requestAudio(pSoundBuffer);

	private:
		/**
		* @brief Runs in every frame
		*/
		void update();
	};

	typedef std::shared_ptr <cas::AudioManager> pAudioManager;
}

