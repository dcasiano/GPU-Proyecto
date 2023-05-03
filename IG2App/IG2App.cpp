#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreKeyFrame.h>
#include <OgreMeshManager.h>

#include "EntidadIG.h"

#include "Entidades/PlanetaGPU.h"
#include "Entidades/PlanetaCPU.h"
#include "Entidades/Sol.h"

#include <iostream>
#include  <cstdlib>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
	  exit(0);
    getRoot()->queueEndRendering();
  }
  
  return true;
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt)
{
	
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
  // do not forget to call the base first
  IG2ApplicationContext::setup();

  mSM = mRoot->createSceneManager();  

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(mSM);

  mSM->addRenderQueueListener(mOverlaySystem);

  mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);

  addInputListener(this);  



  setupScene();
}

void IG2App::setupScene(void)
{
  // create the camera
  Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(100000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);

  //mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  //mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  
  
  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);

  vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(1.0, 1.0, 1.0);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();
  //mLightNode->setPosition(0, 0, 2000);
 
  //------------------------------------------------------------------------

  mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -75),
	  "GPUs/space"
	  , 1, 1, true, 1.0, 100, 100);

  //Info de la gráfica utilizada
  Ogre::RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
  const Ogre::RenderSystemCapabilities* capabilities = rs->getCapabilities();
  std::cout << capabilities->getDeviceName() << "\n";

  //initGPU(32768);
  //initCPU(32768);

  //initGPU(16384);
  //initCPU(16384);

  initGPU(8192);
  //initCPU(8192);

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

  
}

void IG2App::initGPU(int n)
{
	auto sn = mSM->getRootSceneNode();
	new Sol(sn->createChildSceneNode());
	for (int i = 0; i < n; i++) {
		new PlanetaGPU(sn->createChildSceneNode(), i);
	}
}

void IG2App::initCPU(int n)
{
	auto sn = mSM->getRootSceneNode();
	new Sol(sn->createChildSceneNode());
	for (int i = 0; i < n; i++) {
		addInputListener(new PlanetaCPU(sn->createChildSceneNode(), i));
	}
}

