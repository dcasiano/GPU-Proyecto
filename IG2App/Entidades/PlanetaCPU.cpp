#include "PlanetaCPU.h"

#include "Defines.h"

#include <random>
#include <Ogre.h>

PlanetaCPU::PlanetaCPU(Ogre::SceneNode* node, int n) : EntidadIG(node)
{
	// Creamos el generador de números aleatorios
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> rnd;

	Ogre::SceneNode* esfera = mNode->createChildSceneNode();
	Ogre::Entity* ent = mSM->createEntity("triangle.mesh");

	radius_ = ((n % MAX_RADIUS * CPU_) + OFFSET) * CPU_;
	rnd = std::uniform_real_distribution<float>(MIN_MASS, MAX_MASS);
	mass_ = rnd(gen);

	rnd = std::uniform_real_distribution<float>(MIN_SPEED, MAX_SPEED);
	speed_= rnd(gen);

	rnd = std::uniform_real_distribution<float>(MIN_SIZE, MAX_SIZE);
	float size = rnd(gen);
	esfera->setScale(size, size, size);

	time_ = 0;

	Ogre::MaterialPtr baseMaterial = Ogre::MaterialManager::getSingleton().getByName("GPUs/body");
	std::string s = "planeta" + std::to_string(n);
	Ogre::MaterialPtr material = baseMaterial->clone(s);
	Ogre::GpuProgramParametersSharedPtr params = material->getTechnique(0)->getPass(0)->getFragmentProgramParameters();
	rnd = std::uniform_real_distribution<float>(0.0f, 1.0f);
	params->setNamedConstant("r", rnd(gen));
	params->setNamedConstant("g", rnd(gen));
	params->setNamedConstant("b", rnd(gen));

	esfera->attachObject(ent);
	ent->setMaterial(material);
	
}

PlanetaCPU::~PlanetaCPU()
{
}

void PlanetaCPU::frameRendered(const Ogre::FrameEvent& evt)
{
	time_ += evt.timeSinceLastFrame;

	//Posición calculada correctamente
	//const float G = 6.6743e-11; 
	//const float M = 1.9891e30; 

	//float E_cin = 0.5 * mass_ * pow(radius_, 2);
	//float v0 = sqrt(2 * E_cin / mass_);

	//float F = (G * mass_ * M) / pow(radius_, 2); 
	//float a = F / mass_; 

	//float x = radius_ * cos(v0 / radius_ * time_); 
	//float y = radius_ * sin(v0 / radius_ * time_); 

	//Simulación bonita
	float x = radius_ * cos(time_ * speed_);
	float y = radius_ * sin(time_ * speed_);

	mNode->setPosition(x, y, 0);
}
