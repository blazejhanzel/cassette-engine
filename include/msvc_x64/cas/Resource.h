#pragma once

#include "pch.h"

namespace cas {
	typedef std::shared_ptr <sf::Font> pFont;
	typedef std::shared_ptr <tgui::Theme> pGuiTheme;
	typedef std::shared_ptr <sf::SoundBuffer> pSoundBuffer;
	typedef std::shared_ptr <sf::Texture> pTexture;
	typedef std::shared_ptr <sf::Image> pImage;

	/**
	* @brief Class representing resources used in game
	* @details Using resources could make game using less memory, because every resource need to be loaded only once and can be used in different assets.
	* @authors B³a¿ej Hanzel
	* @date 2020
	* @sa cas::AssetManager cas::AssetComponent::RenderObject cas::AssetComponent::AudioSource
	* @copyright B³a¿ej Hanzel
	*/
	class CASENG_API Resource final {
		friend class AssetManager;

		/**
		* @brief Enum class to represent resource type
		*/
	public:
		enum class Type {
			FONT, ///< Used for font files
			GUITHEME, ///< Used for tgui theme files
			SOUND, ///< Used for sound buffers
			TEXTURE, ///< Used for textures
			TEXTURESHEET ///< Used for few textures in one sheet or animations
		};

	private:
		Type mType; ///< Defines type of this resource

		/**
		* @brief Union of possible resource buffer
		* @details Like union, only one can be used in current time.
		*/
		union {
			pFont mFont; ///< Used for fonts
			pGuiTheme mGuiTheme; ///< Used for tgui themes
			pSoundBuffer mSoundBuffer; ///< Used for sfx
			pTexture mTexture; ///< Used for textures
			pImage mImage; ///< Used for texture sheets
		};

		/**
		* @brief Enum for defining source of used resource
		* @details File source can be buffered/unbuffered depending of using. Memory sources define using other resources to work properly.
		* @warning Using memory sources increases spped of buffering resources and decreases used RAM but they cannot be unbuffered automatically. If you want Engine to do this for you, use file-based resources.
		*/
		enum class Source { // TODO: Memory source types cannot be unbuffered, need to fix that
			FILE, ///< Resource loaded from file
			MEMORY ///< Resource loaded using other resource
		} mSource; ///< Defines what is source (type) of this resource

		/**
		* @brief Union for defines resources source location
		*/
		union {
			std::string mFilePath; ///< Used for file resources
			std::shared_ptr <cas::Resource> mRes; ///< Used for resources used in this resource
		};

		bool mIsBuffered = false; ///< Defines if this resource is currently buffered or not, engine use this info to auto load/unload resources
		std::vector <sf::IntRect> mRect; ///< Vector of rectangles used in texture sheets, every rectangle defines every possible texture from source file

		/**
		* @brief Private constructor
		* @details Does nothing. Don't use it.
		* @exception std::runtime_error Throws when used, protects from unchecked instances
		*/
		Resource();

		/**
		* @brief Private, commonly used, constructor
		* @param Type of new created resource
		* @param Path to file, this resource use
		* @param Load on create
		*/
		Resource(Resource::Type, std::string, bool);

		/**
		* @brief Private constructor used for texture sheet based textures
		* @param Type of new created resource
		* @param Pointer to resource containing sheet of textures (must be properly type)
		* @param ID of texture (rectangle) to get from sheet
		* @exception std::invalid_argument Throws exception if tried to use inproper type in pointered resource
		*/
		Resource(Resource::Type, std::shared_ptr <cas::Resource>, int);

	public:
		~Resource() {}

	private:
		/**
		* @brief Load file to memory
		* @details Engine use this function to automatically load resource file to memory when it's needed.
		*/
		void buffer();

		/**
		* @brief Unload file from memory
		* @details Engine use this function to automatically unload resource file from memory when it's no more needed.
		*/
		void unbuffer() noexcept;

	public:
		/**
		* @brief Set coordinates of texture in this texture sheet
		* @details Sets vector of rectangle coordinated used in texture sheets
		* @param sf::IntRect rectangle of texture coordinates
		* @warning Note that rectangle are added to vector, so you need to remember order of used textures. You do it on your own.
		* @exception std::logic_error Throws exception if resource isn't texture sheet type
		*/
		void setRectSize(sf::IntRect);

		/**
		* @brief Get font from resource
		* @exception std::runtime_error Throws exception if resource type isn't requested get type
		* @return Pointer to sf::Font
		*/
		pFont getFont();

		/**
		* @brief Get tgui theme from resource
		* @exception std::runtime_error Throws exception if resource type isn't requested get type
		* @return Pointer to tgui::Theme
		*/
		pGuiTheme getGuiTheme();

		/**
		* @brief Get number of textures defined in sheet
		* @return Number of defined textures
		*/
		size_t getSheetSize() noexcept;

		/**
		* @brief Get sound buffer from resource
		* @exception std::runtime_error Throws exception if resource type isn't requested get type
		* @return Pointer to sf::SoundBuffer
		*/
		pSoundBuffer getSound();

		/**
		* @brief Get texture from resource
		* @details Get pointer to single texture or pointer to texture loaded from texture sheet (with ID specified in param)
		* @param ID of texture to get (used in texture sheet resources only)
		* @exception std::runtime_error Throws exception if resource type isn't requested get type
		* @return Pointer to sf::Texture
		*/
		pTexture getTexture(int id = 0);

		/**
		* @brief Get type of this resource
		* @return Type of this resource
		*/
		Resource::Type getType() noexcept;
	};

	typedef std::shared_ptr <cas::Resource> pResource;
}
