#include "PlanetaGPU.h"

#include "Defines.h"

#include <Ogre.h>
#include <random>



PlanetaGPU::PlanetaGPU(Ogre::SceneNode* node, int n) : EntidadIG(node)
{
	// Creamos el generador de números aleatorios
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> rnd;


	Ogre::SceneNode* esfera = mNode->createChildSceneNode();
	Ogre::Entity* ent = mSM->createEntity("triangle.mesh");


	Ogre::MaterialPtr baseMaterial = Ogre::MaterialManager::getSingleton().getByName("GPUs/nBody");
	std::string s = "planeta" + std::to_string(n);
	Ogre::MaterialPtr material = baseMaterial->clone(s);

	Ogre::GpuProgramParametersSharedPtr params = material->getTechnique(0)->getPass(0)->getVertexProgramParameters();
	float radius = (n % MAX_RADIUS) + OFFSET;
	params->setNamedConstant("radius", radius);
	rnd = std::uniform_real_distribution<float>(MIN_MASS, MAX_MASS);
	params->setNamedConstant("mass", rnd(gen));
	rnd = std::uniform_real_distribution<float>(MIN_SPEED, MAX_SPEED);
	params->setNamedConstant("speed", rnd(gen));

	ent->setMaterial(material);
	esfera->attachObject(ent);

	rnd = std::uniform_real_distribution<float>(MIN_SIZE, MAX_SIZE);
	float size = rnd(gen);
	esfera->setScale(size, size, size);	

	params = material->getTechnique(0)->getPass(0)->getFragmentProgramParameters();
	rnd = std::uniform_real_distribution<float>(0.0f, 1.0f);
	params->setNamedConstant("r", rnd(gen));
	params->setNamedConstant("g", rnd(gen));
	params->setNamedConstant("b", rnd(gen));
}

PlanetaGPU::~PlanetaGPU()
{

}


