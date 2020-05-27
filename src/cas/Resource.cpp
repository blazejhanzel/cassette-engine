#include <cas/pch.h>
#include <cas/Resource.h>
#include <cas/Core.h>

using namespace cas;
using namespace sf;
using namespace std;
using namespace tgui;

Resource::Resource() {
	throw runtime_error("Don't create resource using it's constructor. Look for Asset Manager function instead.");
}

Resource::Resource(Resource::Type type, string path, bool buffer) : mType(type), mFilePath(path) {
	mSource = Source::FILE;

	if (buffer)
		this->buffer();
}

Resource::Resource(Resource::Type type, pResource res, int id) {
	if (res->mType == Type::TEXTURESHEET) {
		mType = type;
		mRes = res;
		mSource = Source::MEMORY;

		mTexture = res->getTexture(id);
		mIsBuffered = true;
	}
	else {
		throw invalid_argument("Pointered resource need to be TEXTURESHEET type.");
	}
}

void Resource::buffer() {
	if (!mIsBuffered) {
		switch (mType) {
		case Type::FONT:
			mFont = pFont(new sf::Font);
			if (!mFont->loadFromFile(mFilePath))
				throw runtime_error("Cannot load " + mFilePath + " to buffer.");
			break;
		case Type::GUITHEME:
			mGuiTheme = pGuiTheme(new tgui::Theme);
			try {
				mGuiTheme->load(mFilePath);
			}
			catch (const tgui::Exception& e) {
				*(Core::get()->getLogger()) << e.what();
			}
			break;
		case Type::SOUND:
			mSoundBuffer = pSoundBuffer(new sf::SoundBuffer);
			if (!mSoundBuffer->loadFromFile(mFilePath))
				throw runtime_error("Cannot load " + mFilePath + " to buffer.");
			break;
		case Type::TEXTURE:
			mTexture = pTexture(new sf::Texture);
			if (mSource == Source::FILE) {
				if (!mTexture->loadFromFile(mFilePath)) {
					throw runtime_error("Cannot load " + mFilePath + " to buffer.");
				}
			}
			else {
				mRes->buffer();
			}
			break;
		case Type::TEXTURESHEET:
			mImage = pImage(new sf::Image);
			if (mSource == Source::FILE) {
				if (!mImage->loadFromFile(mFilePath)) {
					throw runtime_error("Cannot load " + mFilePath + " to buffer.");
				}
			}
			else {
				mRes->buffer();
			}
			break;
		}

		mIsBuffered = true;
	}
}

void Resource::unbuffer() noexcept {
	if (mIsBuffered) {
		switch (mType) {
		case Type::FONT:
			mFont.reset();
			break;
		case Type::GUITHEME:
			mGuiTheme.reset();
			break;
		case Type::SOUND:
			mSoundBuffer.reset();
			break;
		case Type::TEXTURE:
			if (mSource == Source::FILE)
				mTexture.reset();
			break;
		case Type::TEXTURESHEET:
			if (mSource == Source::FILE)
				mImage.reset();
			break;
		}

		mIsBuffered = false;
	}
}

void Resource::setRectSize(IntRect rect) {
	if (mType == Type::TEXTURESHEET) // FIXME: Exception thrown (sometimes): read access violation; this was nullptr
		mRect.push_back(rect);
	else
		throw logic_error("Cannot create texture coordinate rects in resource that isn't texture sheet.");
}

pFont Resource::getFont() {
	if (mType == Type::FONT) {
		if (!mIsBuffered)
			buffer();
		return mFont;
	}
	else
		throw runtime_error("Resource is other type than user specfied to get.");
	return nullptr;
}

pGuiTheme Resource::getGuiTheme() {
	if (mType == Type::GUITHEME) {
		if (!mIsBuffered)
			buffer();
		return mGuiTheme;
	}
	else
		throw runtime_error("Resource is other type than user specfied to get.");
	return nullptr;
}

inline size_t Resource::getSheetSize() noexcept {
	return mRect.size();
}

pSoundBuffer Resource::getSound() {
	if (mType == Type::SOUND) {
		if (!mIsBuffered)
			buffer();
		return mSoundBuffer;
	}
	else
		throw runtime_error("Resource is other type than user specfied to get.");
	return nullptr;
}

pTexture Resource::getTexture(int id) {
	if (mType == Type::TEXTURE) {
		if (!mIsBuffered)
			buffer();
		return mTexture;
	}
	else if (mType == Type::TEXTURESHEET) {
		if (!mIsBuffered)
			buffer();
		pTexture tex = pTexture(new sf::Texture);
		tex->loadFromImage(*mImage, mRect[id]);
		return tex;
	}
	else
		throw runtime_error("Resource is other type than user specfied to get.");
	return nullptr;
}

Resource::Type Resource::getType() noexcept {
	return mType;
}
