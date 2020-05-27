#include <cas/pch.h>
#include <cas/StateManager.h>
#include <cas/Core.h>

using namespace cas;
using namespace std;

StateManager::StateManager() {
	throw runtime_error("Cannot create StateManager without pointer to Core.");
}

StateManager::StateManager(Core* c) : core(c) {}

void StateManager::setState(StateManager::State state) {
	if (state == State::SPLASHSCREEN) {
		throw runtime_error("Cannot change state to Splashscreen while application is running. This is default stratup state.");
	}
	else {
#ifdef _DEBUG
		*(core->getLogger()) << "Engine state has been changed to " + [](StateManager::State s)->string {
			switch (s) {
				case StateManager::State::LOADING:
					return "LOADING";
				case StateManager::State::SCENEACTIVE:
					return "SCENEACTIVE";
				case StateManager::State::END:
					return "END";
			}
			return "UNKNOWN";
		} (state);
#endif
		mStateSet = state;
	}
}

StateManager::State StateManager::getState() noexcept {
	return mState;
}

pTaskHandler StateManager::getTaskHandler() noexcept {
	return mTaskHandler;
}

void StateManager::addTask(pTask vTask) noexcept {
	mTask.push_back(vTask);
}

void StateManager::update() {
	mState = mStateSet;

	if (mState == State::LOADING) {
		mTaskHandler->update();

		if (mTaskHandler->mReady) {
			if (mTask.size() > 0) {
				mTaskHandler->handleTask(mTask[0]);
				mTask.erase(mTask.begin());
			}
			else {
				if (mTaskHandler->mThreadsRunning == 0) {
					setState(State::SCENEACTIVE);
				}
			}
		}
	}
}