#include <cas/pch.h>
#include <cas/Logger.h>

#pragma warning(disable:4996)

using namespace cas;
using namespace std;

Logger::Logger() {
	mFile.open("log.txt", std::ios::out | std::ios::trunc);
}

Logger::~Logger() {
	if (mFile.is_open())
		mFile.close();
}

string Logger::getSystemTime() noexcept {
	auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
	string str;
	try {
		str = [](string str) {
			return str.substr(str.find(":") - 2, 8);
		} ((string)ctime(&timenow));
	}
	catch (...) {
		str = "UNKNOWN:";
	}
	return str;
}
