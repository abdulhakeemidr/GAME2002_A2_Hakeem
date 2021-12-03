#pragma once

#ifndef _OBJECTCREATOR_H__
#define _OBJECTCREATOR_H__

#include "Ogre.h"
#include "Game.h"
#include <vector>

//using namespace Ogre;
//class Game;

class ObjectCreator
{
private:
	Ogre::Entity* ObjectEntity = nullptr;
	Ogre::SceneNode* ObjSceneNode = nullptr;
	Ogre::String childSceneNodeName;
	// Dynamic array of Vector3
	//Ogre::Vector3 vertex[VertexNum];
	std::vector<Ogre::Vector3> vertices;
	SceneManager::PrefabType pType;
	Ogre::Vector3 Position;
	Ogre::Vector3 Scale;

	void CreatePrimitiveObject(Ogre::String SceneName);

	void CreateMeshObject(const Ogre::String& mesh);

public:
	ObjectCreator(Ogre::SceneManager::PrefabType type, Ogre::String objectName, const Vector3& position, const Vector3& scale);

	ObjectCreator(const Ogre::String& meshFileName, const Vector3& position, const Ogre::String& objectName = "");

	SceneNode* getObjectSceneNode();

	Entity* getObjEntity();

	void SetPosition(const Ogre::Vector3& position);

	void SetOrientation(Ogre::Real pitchAngle = 0.0f, Ogre::Real yawAngle = 0.0f, Ogre::Real rollAngle = 0.0f);

	void SetScale(const Ogre::Vector3& scale);
};



#endif