#include <cas/pch.h>
#include <cas/TaskHandler.h>
#include <cas/Core.h>

using namespace cas;
using namespace std;

TaskHandler::TaskHandler() noexcept {}

void TaskHandler::handleTask(pTask t) {
	if (!mReady) {
		throw logic_error("Someone try to handle task when Task Handler isn't ready. Probability of data loss.");
	}

	mReady = false;
	pLogger logger = Core::get()->getLogger();

	thread thr(&Task::task, t);
	stringstream ss;
	ss << thr.get_id();
	*logger << "New thread with id: " + ss.str() + " just started";
	mThread.push_back(make_pair(move(thr), t));
	mThreadsRunning++;
}

wstring TaskHandler::getDescription() {
	if (mThread.size() > 0)
		return mThread[0].second->mDescription;
	return L"Loading tasks...";
}

void TaskHandler::update() {
	pLogger logger = Core::get()->getLogger();
	const int maxThreads = (Core::get()->getSettings()->mSystemThreads) ? Core::get()->getSettings()->mSystemThreads : 4;

	for (size_t i = mThread.size(); i > 0; i--) {
		if ((mThread[i-1].second)->mDone) {
			if (mThread[i-1].first.joinable()) {
				stringstream ss;
				ss << mThread[i-1].first.get_id();
				*logger << "Thread with id: " + ss.str() + " ends job and is being joined now.";
				mThread[i-1].first.join();
				mThread.erase(mThread.begin() + i - 1);
				mThreadsRunning--;
			}
		}
	}

	if (mThreadsRunning < maxThreads) {
		mReady = true;
	}
}
