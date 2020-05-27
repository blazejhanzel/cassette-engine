#include <cas/pch.h>
#include <cas/DisplayManager.h>
#include <cas/Core.h>

using namespace cas;
using namespace std;
using namespace sf;
using namespace tgui;

sf::Clock vSplashClock, vLoadingClock;

DisplayManager::DisplayManager() {
	throw runtime_error("Cannot create DisplayManager instance without pointer to Core.");
}

DisplayManager::DisplayManager(cas::Core* c) : core(c) {
    pEngineSettings sets = core->getSettings();
    mSplashScreen.setFont("res/fonts/Overlock-Regular.ttf"); // TODO: This should be moved to ResourceManager when it will be possible
    mLoadingScreen.setFont("res/fonts/BalooChettan2-Bold.ttf"); // TODO: This should be moved to ResourceManager when it will be possible
    
    // SPLASHSCREEN
    auto canvas = Canvas::create({ 512, 256 });
    canvas->setPosition(sets->mWindowWidth / 2 - 256, sets->mWindowHeight / 2 - 128);
    canvas->clear();
    canvas->draw(mResourceContainer->mLogoSpr);
    canvas->draw(mResourceContainer->mEngineNameText);
    canvas->draw(mResourceContainer->mCompanyNameText);
    canvas->draw(mResourceContainer->mVersionText);
    canvas->display();
    mSplashScreen.add(canvas);
    canvas->setWidgetName("canvas");

    auto label = Label::create();
    label->setRenderer(mResourceContainer->mTheme.getRenderer("Label"));
    label->setText("Cassette logo and Cassette names are private property. All rights reserved. This screen is regulation of this license.\nCassette Engine use external libraries such like: SFML, TGUI, Box2d, IniPP\nFonts deployed with engine: Baloo Chettan 2, FiraCode, Overlock.\nAll license files are included in engine directory.");
    label->setHorizontalAlignment(Label::HorizontalAlignment::Center);
    label->setPosition(sets->mWindowWidth / 2 - label->getFullSize().x / 2, sets->mWindowHeight / 2 + 128);
    label->setTextSize(18);
    mSplashScreen.add(label);
    label->setWidgetName("label");


    // LOADING SCREEN
    label = Label::create("Loading");
    label->getRenderer()->setTextColor(tgui::Color(255, 255, 255, 255));
    label->setTextSize(28);
    label->setHorizontalAlignment(Label::HorizontalAlignment::Left);
    label->setPosition(32, sets->mWindowHeight - 16 - label->getFullSize().y);
    mLoadingScreen.add(label);
    label->setWidgetName("loading-text");
}

pRenderWindow DisplayManager::newWindow() {
    if (mWindow.isOpen())
        throw runtime_error("Cannot create new window. Another one is still alive.");

	pEngineSettings vSettings = core->getSettings();
    Uint32 style = ((vSettings->mFullscreen) ? Style::Fullscreen : Style::Default);
	mWindow.create(sf::VideoMode(vSettings->mWindowWidth, vSettings->mWindowHeight), "Cassette Engine", style);
	mWindow.setFramerateLimit(vSettings->mTicksPerSecond);
	mWindow.setVerticalSyncEnabled(vSettings->mVsync);
	mWindow.setIcon(64, 64, mResourceContainer->mEngineIcon.data());
    vSplashClock.restart();

    mGui.setView(mWindow.getView());
    mLoadingScreen.setView(mWindow.getView());
    mSplashScreen.setView(mWindow.getView());

    return mWindow;
}

pRenderWindow DisplayManager::getWindow() noexcept {
    return mWindow;
}

void DisplayManager::destroyWindow() {
    if (mWindow.isOpen())
        mWindow.close();
}

pGui DisplayManager::getDefaultGui() noexcept {
    return mGui;
}

pGui DisplayManager::getGui() noexcept {
    switch (core->getStateManager()->getState()) {
        case StateManager::State::SPLASHSCREEN:
            return mSplashScreen;
        case StateManager::State::LOADING:
            return mLoadingScreen;
        default:
            return mGui;
    }
}

void DisplayManager::update() {
    if (mWindow.isOpen())
        mWindow.clear(sf::Color::Black);

    switch (core->getStateManager()->getState()) {
        case StateManager::State::SPLASHSCREEN: {
            pEngineSettings sets = core->getSettings();
            mSplashScreen.get("canvas")->setPosition(sets->mWindowWidth / 2 - 256, sets->mWindowHeight / 2 - 128);
            mSplashScreen.get("label")->setPosition(sets->mWindowWidth / 2 - mSplashScreen.get("label")->getFullSize().x / 2, sets->mWindowHeight / 2 + 128);

            if (vSplashClock.getElapsedTime() >= sf::milliseconds(5000)) {
                core->getStateManager()->setState(StateManager::State::LOADING);
                vLoadingClock.restart();
            }
            mSplashScreen.draw();
            break;
        }
        case StateManager::State::LOADING: {
            mLoadingScreen.get("loading-text")->setPosition(32, core->getSettings()->mWindowHeight - 16 - mLoadingScreen.get("loading-text")->getFullSize().y);

            if (vLoadingClock.getElapsedTime() >= sf::milliseconds(1000)) {
                Label::Ptr l = mLoadingScreen.get<Label>("loading-text");
                if (l) {
                    wstring loadingText = core->getStateManager()->getTaskHandler()->getDescription();
                    if (loadingText == L"") {
                        l->setText("Loading...");
                    }
                    else if (loadingText == l->getText()) {
                        string str = l->getText();
                        str += ".";
                        l->setText(str);
                    }
                    else {
                        l->setText(loadingText);
                    }
                    vLoadingClock.restart();
                }
            }
            mLoadingScreen.draw();
            break;
        }
        case StateManager::State::SCENEACTIVE: {
            pScene scene = core->getSceneManager()->getActiveScene();
            if (scene)
                scene->draw(mWindow);
            mGui.draw();
            break;
        }
        case StateManager::State::END: {
            mWindow.close();
            break;
        }
    }
    
    if (mWindow.isOpen())
        mWindow.display();
}
