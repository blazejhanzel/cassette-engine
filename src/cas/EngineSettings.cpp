#include <cas/pch.h>
#include <cas/EngineSettings.h>
#include <cas/Core.h>

using namespace cas;
using namespace std;
using namespace inipp;

#ifndef CAS_CONFIG_FILE
#define CAS_CONFIG_FILE "config.ini"
#endif

EngineSettings::EngineSettings() {
	throw runtime_error("Cannot create EngineSettings class without pointer to Core.");
}

EngineSettings::EngineSettings(Core* c) : core(c) {
	pLogger logger = c->getLogger();

	if (!loadFromFile()) {
		*logger << "Failed loading config file from " CAS_CONFIG_FILE ". New one will be created.";

		if (!saveToFile()) {
			throw runtime_error("Failed on read/write config file.");
		}
	}
}

void EngineSettings::confirmSettings() {
	pDisplayManager d = core->getDisplayManager();
	d->destroyWindow();
	d->newWindow();
}

bool EngineSettings::loadFromFile() {
	Ini<char> ini;
	ifstream vFile(CAS_CONFIG_FILE);
	if (!vFile.is_open())
		return false;
	ini.parse(vFile);

	mWindowWidth = stoi(ini.sections["engineSettings"]["windowWidth"]);
	mWindowHeight = stoi(ini.sections["engineSettings"]["windowHeight"]);
	mFullscreen = stoi(ini.sections["engineSettings"]["fullscreen"]);
	mTicksPerSecond = stoi(ini.sections["engineSettings"]["ticksPerSecond"]);
	mVsync = stoi(ini.sections["engineSettings"]["vSync"]);
	mVolumeMusic = stoi(ini.sections["engineSettings"]["volumeMusic"]);
	mVolumeSfx = stoi(ini.sections["engineSettings"]["volumeSfx"]);
	mBufferResources = stoi(ini.sections["engineSettings"]["bufferResources"]);
	mSystemThreads = stoi(ini.sections["engineSettings"]["systemThreads"]);

	vFile.close();
	return true;
}

bool EngineSettings::saveToFile() {
	Ini<char> ini;

	ifstream vFileIn(CAS_CONFIG_FILE);
	ini.parse(vFileIn);
	vFileIn.close();

	ofstream vFileOut(CAS_CONFIG_FILE);
	if (!vFileOut.is_open())
		return false;

	ini.sections["engineSettings"]["windowWidth"] = to_string(mWindowWidth);
	ini.sections["engineSettings"]["windowHeight"] = to_string(mWindowHeight);
	ini.sections["engineSettings"]["fullscreen"] = to_string(mFullscreen);
	ini.sections["engineSettings"]["ticksPerSecond"] = to_string(mTicksPerSecond);
	ini.sections["engineSettings"]["vSync"] = to_string(mVsync);
	ini.sections["engineSettings"]["volumeMusic"] = to_string(mVolumeMusic);
	ini.sections["engineSettings"]["volumeSfx"] = to_string(mVolumeSfx);
	ini.sections["engineSettings"]["bufferResources"] = to_string(mBufferResources);
	ini.sections["engineSettings"]["systemThreads"] = to_string(mSystemThreads);

	ini.generate(vFileOut);
	vFileOut.close();

	return true; // success
}
