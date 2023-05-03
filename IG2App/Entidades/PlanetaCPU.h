#pragma once

#include "../EntidadIG.h"

class PlanetaCPU : public EntidadIG
{
public:
	PlanetaCPU(Ogre::SceneNode* node, int n); // #include <OgreSceneNode.h>
	~PlanetaCPU();

protected:

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

private:

	float mass_;
	float radius_;
	float time_;
	float speed_;
};

