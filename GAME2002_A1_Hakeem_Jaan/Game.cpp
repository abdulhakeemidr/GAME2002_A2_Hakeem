#include "Game.h"
#include "ObjectCreator.h"
#include "GameFrameListener.h"


Game::Game()
    : ApplicationContext("GAME2002 A1 Abdulhakeem Idris")
    
{
}

Game& Game::Instance()
{
    static Game app;
    return app;
}

void Game::Update()
{
}

void Game::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    root = getRoot();
    scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);
    createScene();
    createCamera();
    createTrayUI();
    createFrameListener();
}

void Game::createTrayUI()
{
    OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());
    //you must add this in order to add a tray
    scnMgr->addRenderQueueListener(mOverlaySystem);

    addInputListener(mTrayMgr);

    mInfoLabel = mTrayMgr->createLabel(TL_TOP, "TInfo", "Assignment 1", 250);

    mScoreLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Score", "Score:", 150);
    mScore = mTrayMgr->createLabel(TL_TOPLEFT, "score", "0", 150);

    mLivesLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Lives", "Lives:", 150);
    mLives = mTrayMgr->createLabel(TL_TOPLEFT, "lives", "5", 150);

    mTrayMgr->showFrameStats(TL_TOPRIGHT);
    mTrayMgr->toggleAdvancedFrameStats();

    
}

void Game::createScene()
{

    // -- tutorial section start --
    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));
    //! [turnlights]

    //! [newlight]
    //
    Light* light1 = scnMgr->createLight("Light1");
    light1->setType(Ogre::Light::LT_POINT);
    // Set Light Color
    light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Set Light Reflective Color
    light1->setSpecularColour(1.0f, 0.0f, 0.0f);
    // Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
    light1->setAttenuation(10, 0.5, 0.045, 0.0);

    //
    Entity* lightEnt = scnMgr->createEntity("LightEntity", "sphere.mesh");
    SceneNode* lightNode = scnMgr->createSceneNode("LightNode");
    lightNode->attachObject(lightEnt);
    lightNode->attachObject(light1);
    lightNode->setScale(0.01f, 0.01f, 0.01f);


    scnMgr->getRootSceneNode()->addChild(lightNode);
    //! [newlight]


    //! [lightpos]
    lightNode->setPosition(0, 4, 10);
    //! [lightpos]


    // Ball Object using object creator
    

    ObjectCreator ball("Ball", SceneManager::PrefabType::PT_SPHERE, Ogre::Vector3(0, 0, 0), Ogre::Vector3(0.01f, 0.01f, 0.01f));

    BallNodePointer = ball.getObjectSceneNode();

    ObjectCreator paddle("Player", SceneManager::PrefabType::PT_PLANE, Ogre::Vector3(0, -5, 0), Ogre::Vector3(0.01f, 0.002f, 0.01f));

    PlayerNodePointer = paddle.getObjectSceneNode();
    // -- tutorial section end --
}

void Game::createCamera()
{

    //! [camera]
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 15);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);

    Viewport* viewPort = NULL;

    // and tell it to render into the main window
    viewPort = getRenderWindow()->addViewport(cam);
    // Set the background colour
    viewPort->setBackgroundColour(Ogre::ColourValue(0.0f, 0.5f, 1.0f));

    //! [camera]
}

bool Game::keyPressed(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        break;
    case 'a':
        if (PlayerNodePointer->getPosition().x > -7)
        {
            translate = Ogre::Vector3(-10, 0, 0);
        }
        break;
    case 'd':
        if (PlayerNodePointer->getPosition().x < 7)
        {
            translate = Ogre::Vector3(10, 0, 0);
        }
        
        break;
    default:
        break;
    }
    return true;
}

void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(PlayerNodePointer);

    mRoot->addFrameListener(FrameListener);

    FrameListener = new ExampleFrameListener(BallNodePointer);

    mRoot->addFrameListener(FrameListener);
}