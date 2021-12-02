#pragma once
#ifndef _GAME_H__
#define _GAME_H__

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreTrays.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

static Ogre::Real m_Angle = 0.0;
static Ogre::Vector3 translate(0, 0, 0);


class Game
    : public ApplicationContext
    , public InputListener
{
private:
    SceneManager* scnMgr;
    Root* root;
public:
    Game();
    virtual ~Game() {}
    void setup();
    void createSceneLighting();
    void createSceneObjects();
    void createCamera();
    void Update(Ogre::Real timeElapsed);
    bool keyPressed(const KeyboardEvent& evt);
    void createFrameListener();
    void createTrayUI();

    static Game& Instance();
    SceneManager* getSceneManager() { return scnMgr; }

    Ogre::SceneNode* PlayerNodePointer;
    Ogre::SceneNode* PlatformNodePointer;

    OgreBites::TrayListener myTrayListener;
    OgreBites::Label* mInfoLabel;

    OgreBites::Label* mScoreLabel;
    OgreBites::Label* mScore;

    OgreBites::Label* mLivesLabel;
    OgreBites::Label* mLives;

    OgreBites::Label* mTimeLabel;
    OgreBites::Label* mTime;
};

#endif