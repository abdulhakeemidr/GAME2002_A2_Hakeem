#include "ObjectCreator.h"


void ObjectCreator::CreatePrimitiveObject(Ogre::String SceneName)
{
	ObjectEntity = Game::Instance().getSceneManager()->createEntity(pType);
	ObjSceneNode = Game::Instance().getSceneManager()->getRootSceneNode()->createChildSceneNode(SceneName);
	ObjSceneNode->setPosition(0, -5, 0);
	ObjSceneNode->setScale(Scale);
	ObjSceneNode->attachObject(ObjectEntity);
}

void ObjectCreator::CreateMeshObject(const Ogre::String& mesh)
{
	ObjectEntity = Game::Instance().getSceneManager()->createEntity(mesh);
	ObjectEntity->setCastShadows(true);
	if (childSceneNodeName != "")
	{
		ObjSceneNode = Game::Instance().getSceneManager()->getRootSceneNode()->createChildSceneNode(childSceneNodeName);
	}
	else
	{
		ObjSceneNode = Game::Instance().getSceneManager()->getRootSceneNode()->createChildSceneNode();
	}

	ObjSceneNode->setPosition(0, -5, 0);
	ObjSceneNode->attachObject(ObjectEntity);
}

ObjectCreator::ObjectCreator(Ogre::SceneManager::PrefabType type, Ogre::String objectName, const Vector3& position, const Vector3& scale)
	: childSceneNodeName(objectName), pType(type), Position(position)
{
	Scale = scale;
	childSceneNodeName = objectName;
	CreatePrimitiveObject(objectName);
}

ObjectCreator::ObjectCreator(const Ogre::String& meshFileName, const Vector3& position, const Ogre::String& objectName)
	: Position(position)
{
	childSceneNodeName = objectName;
	CreateMeshObject(meshFileName);
}

SceneNode* ObjectCreator::getObjectSceneNode()
{
	return ObjSceneNode;
}

Entity* ObjectCreator::getObjEntity()
{
	return ObjectEntity;
}

void ObjectCreator::SetPosition(const Ogre::Vector3& position)
{
	ObjSceneNode->setPosition(position);
}

void ObjectCreator::SetOrientation(Ogre::Real pitchAngle, Ogre::Real yawAngle, Ogre::Real rollAngle)
{
	ObjSceneNode->pitch(Degree(pitchAngle)); // X-axis
	ObjSceneNode->yaw(Degree(yawAngle)); // Y-axis
	ObjSceneNode->roll(Degree(rollAngle)); // Z-axis
}

void ObjectCreator::SetScale(const Ogre::Vector3& scale)
{
	ObjSceneNode->setScale(scale);
}