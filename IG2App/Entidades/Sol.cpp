#include "Sol.h"

#include <Ogre.h>

Sol::Sol(Ogre::SceneNode* node) : EntidadIG(node)
{
	// Creamos el generador de números aleatorios
	Ogre::SceneNode* esfera = mNode->createChildSceneNode();
	Ogre::Entity* ent = mSM->createEntity("uv_sphere.mesh");

	ent->setMaterialName("GPUs/sun");
	esfera->attachObject(ent);

	float size = 1;
	esfera->setScale(size, size, size);
}

Sol::~Sol()
{
}
