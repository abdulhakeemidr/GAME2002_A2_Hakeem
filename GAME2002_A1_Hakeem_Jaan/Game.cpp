#include "Game.h"
#include "ObjectCreator.h"
#include "GameFrameListener.h"


Game::Game()
    : ApplicationContext("GAME2002 A2 Abdulhakeem Idris")
    
{
}

Game& Game::Instance()
{
    static Game app;
    return app;
}

void Game::Update(Ogre::Real timeElapsed)
{
    PlatformNodePointer->translate(Ogre::Vector3(0, -0.1, 0));
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

    createCamera();
    createSceneObjects();
    createSceneLighting();
    createTrayUI();
    createFrameListener();

    // -- tutorial section end --
}

void Game::createTrayUI()
{
    OgreBites::TrayManager* mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());
    //you must add this in order to add a tray
    scnMgr->addRenderQueueListener(mOverlaySystem);

    addInputListener(mTrayMgr);

    mInfoLabel = mTrayMgr->createLabel(TL_TOP, "TInfo", "Assignment 2", 250);

    mScoreLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Score", "Score:", 150);
    mScore = mTrayMgr->createLabel(TL_TOPLEFT, "score", "0", 150);

    mLivesLabel = mTrayMgr->createLabel(TL_TOPLEFT, "Lives", "Lives:", 150);
    mLives = mTrayMgr->createLabel(TL_TOPLEFT, "lives", "5", 150);

    mTrayMgr->showFrameStats(TL_TOPRIGHT);
    mTrayMgr->toggleAdvancedFrameStats();

    
}

void Game::createCamera()
{
    /*
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
    viewPort->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f));

    //! [camera]
    */

    //! [cameracreate]
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    Camera* cam = scnMgr->createCamera("myCam");
    //! [cameracreate]

    //! [cameraposition]
    camNode->setPosition(0, 300, 1000);
    camNode->lookAt(Vector3(0, 0, 0), Node::TransformSpace::TS_WORLD);
    //! [cameraposition]

    //! [cameralaststep]
    cam->setNearClipDistance(5);
    camNode->attachObject(cam);
    //! [cameralaststep]

    //! [addviewport]
    Viewport* vp = getRenderWindow()->addViewport(cam);
    //! [addviewport]

    //! [viewportback]
    vp->setBackgroundColour(ColourValue(0, 1, 1));
    //! [viewportback]

    //! [cameraratio]
    cam->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
    //! [cameraratio]

    //! [lightingsset]
    scnMgr->setAmbientLight(ColourValue(0.1, 0.1, 0.1));
    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
    //! [lightingsset]

}

void Game::createSceneLighting()
{
    /*
    // -- tutorial section start --
    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));
    //! [turnlights]

    //! [newlight]
    //
    Light* directionalLight = scnMgr->createLight("DirectionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    // Set Light Color
    directionalLight->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Set Light Reflective Color
    directionalLight->setSpecularColour(1.0f, 0.0f, 0.0f);
    // Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
    directionalLight->setAttenuation(10, 0.5, 0.045, 0.0);

    //
    //Entity* lightEnt = scnMgr->createEntity("LightEntity", "sphere.mesh");
    SceneNode* lightNode = scnMgr->createSceneNode("LightNode");
    //lightNode->attachObject(lightEnt);
    lightNode->attachObject(directionalLight);
    lightNode->setDirection(0, -1, -1);

    scnMgr->getRootSceneNode()->addChild(lightNode);
    //! [newlight]

    //! [lightpos]
    lightNode->setPosition(0, 4, 10);
    //! [lightpos]
    */

    //! [spotlight]
    Light* spotLight = scnMgr->createLight("SpotLight");
    //! [spotlight]

    //! [spotlightcolor]
    spotLight->setDiffuseColour(0, 1.0, 0);
    spotLight->setSpecularColour(0, 1.0, 0);
    //! [spotlightcolor]

    //! [spotlighttype]
    spotLight->setType(Light::LT_SPOTLIGHT);
    //! [spotlighttype]

    //! [spotlightposrot]
    SceneNode* spotLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    spotLightNode->attachObject(spotLight);
    spotLightNode->setDirection(-1, -1, 0);
    spotLightNode->setPosition(Vector3(200, 200, 0));
    //! [spotlightposrot]

    //! [spotlightrange]
    spotLight->setSpotlightRange(Degree(35), Degree(50));
    //! [spotlightrange]

    //! [directlight]
    Light* directionalLight = scnMgr->createLight("DirectionalLight");
    directionalLight->setType(Light::LT_DIRECTIONAL);
    //! [directlight]

    //! [directlightcolor]
    directionalLight->setDiffuseColour(ColourValue(1.0, 1.0, 1.0));
    directionalLight->setSpecularColour(ColourValue(1.0, 1.0, 1.0));
    //! [directlightcolor]

    //! [directlightdir]
    SceneNode* directionalLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    directionalLightNode->attachObject(directionalLight);
    directionalLightNode->setDirection(Vector3(0, -1, -1));
    //! [directlightdir]

}

void Game::createSceneObjects()
{
    // Ball Object using object creator

    //ObjectCreator ball("Ball", SceneManager::PrefabType::PT_SPHERE, Ogre::Vector3(0, 0, 0), Ogre::Vector3(0.01f, 0.01f, 0.01f));

    /*
    ObjectCreator ball("ninja.mesh", Ogre::Vector3(0, 0, 0), Ogre::Vector3(0.01f, 0.01f, 0.01f));

    BallNodePointer = ball.getObjectSceneNode();

    ObjectCreator paddle("Player", SceneManager::PrefabType::PT_PLANE, Ogre::Vector3(0, -5, 0), Ogre::Vector3(0.01f, 0.002f, 0.01f));

    PlayerNodePointer = paddle.getObjectSceneNode();
    // -- tutorial section end --
    */

    //! [ninja]
    Entity* ninjaEntity = scnMgr->createEntity("ninja.mesh");
    ninjaEntity->setCastShadows(true);

    PlayerNodePointer = scnMgr->getRootSceneNode()->createChildSceneNode("Player");
    PlayerNodePointer->attachObject(ninjaEntity);
    PlayerNodePointer->setPosition(Ogre::Vector3(0.0f, 4.0f, 0.0f));
    PlayerNodePointer->yaw(Degree(180));
    //PlayerNodePointer->setScale(3.0f, 3.0f, 3.0f);
    //! [ninja]
    
    Entity* cubeEntity = scnMgr->createEntity("WoodPallet.mesh");
    PlatformNodePointer = scnMgr->getRootSceneNode()->createChildSceneNode("Ball");
    PlatformNodePointer->attachObject(cubeEntity);
    PlatformNodePointer->setPosition(0.0f, -1.0f, 0.0f);
    PlatformNodePointer->setScale(20.0f, 15.0f, 10.0f);

    /*
    //! [plane]
    Plane plane(Vector3::UNIT_Y, 0);
    //! [plane]

    //! [planedefine]
    MeshManager::getSingleton().createPlane(
        "ground", RGN_DEFAULT,
        plane,
        1500, 1500, 20, 20,
        true,
        1, 5, 5,
        Vector3::UNIT_Z);
    //! [planedefine]

    //! [planecreate]
    Entity* groundEntity = scnMgr->createEntity("ground");
    scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    //! [planecreate]

    //! [planenoshadow]
    groundEntity->setCastShadows(false);
    //! [planenoshadow]

    //! [planesetmat]
    groundEntity->setMaterialName("Examples/Rockwall");
    //! [planesetmat]
    */
}


bool Game::keyPressed(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        break;
    case 'w':
        translate = Ogre::Vector3(0, 10, 0);
        break;
    case 's':
        translate = Ogre::Vector3(0, -10, 0);
        break;
    case 'a':
        break;
    case 'd':
        break;
    default:
        break;
    }
    return true;
}

void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener();
    mRoot->addFrameListener(FrameListener);

    /*FrameListener = new ExampleFrameListener(PlatformNodePointer);
    mRoot->addFrameListener(FrameListener);*/
}