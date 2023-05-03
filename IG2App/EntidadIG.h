#pragma once

#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

enum MessageType { _m_GENERAL,
				_m_SIMBAD_MUERE,
				_m_BOMBA_EXPLOTA,
				_m_RIO_SE_SECA };

class EntidadIG : public OgreBites::InputListener {
public:
	//Constructora y destructora
	EntidadIG(Ogre::SceneNode* node);
	~EntidadIG();
	//Vector estático de listeners
	static std::vector<EntidadIG*> appListeners;
	//Añadir entidad como listener al vector con push_back()
	static void addListener(EntidadIG* entidad) {
		appListeners.push_back(entidad);
	};	

protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) {
		return false;
	};
	virtual void frameRendered(const Ogre::FrameEvent& evt) {};

	void sendEvent(EntidadIG* entidad, MessageType message = _m_GENERAL) {
		for (EntidadIG* e : appListeners)
			e->receiveEvent(entidad, message);
	}

	virtual void receiveEvent(EntidadIG* entidad, MessageType message) {};
};

