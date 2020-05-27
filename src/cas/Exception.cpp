#include <cas/pch.h>
#include <cas/Exception.h>
#include <cas/Core.h>

using namespace cas;
using namespace std;

Exception::Exception(const string& what_arg) : mArg(what_arg.c_str()) {
	*(Core::get()->getLogger()) << "Internal engine exception: " + what_arg;
}

Exception::Exception(const char* what_arg) : mArg(what_arg) {
	*(Core::get()->getLogger()) << "Internal engine exception: " + (string)what_arg;
}

const char* Exception::what() const noexcept {
	string str = "Internal engine exception: " + (string)mArg;
	return str.c_str();
}
