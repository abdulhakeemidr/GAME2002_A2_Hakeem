#pragma once
#include "Ogre.h"
#include "Game.h"
#include <OgreApplicationContextBase.h>

class ExampleFrameListener : public Ogre::FrameListener
{
private:
    Ogre::SceneNode* _node;
    Ogre::Vector3 ballTranslate = Ogre::Vector3(1, 0.5, 0);
public:
    ExampleFrameListener(){}

    ExampleFrameListener(Ogre::SceneNode* node)
    {
        _node = node;
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {
        Game::Instance().Update(evt.timeSinceLastFrame);

        /*
        if (_node->getName() == "Player")
        {
            _node->translate(translate * evt.timeSinceLastFrame * 200.0f);
            translate = Ogre::Vector3(0, 0, 0);
            std::cout << _node->getPosition().x << std::endl;
        }

        if (_node->getName() == "Ball")
        {
            //_node->translate(Ogre::Vector3(0, -0.1, 0));
        }
        */
        return true;
    }
};