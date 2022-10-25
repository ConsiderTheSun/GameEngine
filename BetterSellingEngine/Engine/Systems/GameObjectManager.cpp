#include "GameObjectManager.h"





GOM* GOM::gomInstance = nullptr;
GOM* GOM::GetInstance() {
	if (!gomInstance)
		gomInstance = new GOM();
	return gomInstance;
};

GOM::GameObjectManager() {
	layerMap.insert({ "default", 0 });
}

GOM::~GameObjectManager() {
	gomInstance = NULL;

	while (!branches.empty()) {
		RemoveGameObject(branches.front());
	}
}

GameObject* GOM::Find(std::string objectName) {
	for (GOM::Iterator gomItr = this->begin(), end = this->end(); gomItr != end; ++gomItr) {
		if (gomItr->GetName() == objectName) {
			return &*gomItr;
		}
	}
	return NULL;
}


bool GOM::AddGameObject(GameObject* gameObject, GameObject* parent) {
	// checks if go has been added before
	if (HasGameObject(gameObject)) {
		std::cerr << "Warning: gameObject already added, changing parent\n";
		return this->SetParent(gameObject, parent);
	}

	if (!parent) {
		branches.push_front(gameObject);
		return true;
	}
	else {
		// adds the gameObject to the GOM
		return this->SetParent(gameObject, parent);
	}
}

int GOM::LayerToInt(std::string layerName) {
	LayerMap::iterator layerItr = layerMap.find(layerName);
	if (layerItr != layerMap.end()) {
		return layerItr->second;
	}
	return 0;
}


bool GOM::AddLayer(std::string newLayerName) {
	LayerMap::iterator alreadyExistingLayer = layerMap.find(newLayerName);
	if (alreadyExistingLayer == layerMap.end()) {
		layerMap.insert({ newLayerName, layerCount++ });
		return true;
	}
	return false;
}

void GOM::FreeBranch(GameObject* gameObject){
	for (GameObject* g : gameObject->children) {
		FreeBranch(g);
	}
	delete(gameObject);
}

void GOM::RemoveGameObject(GameObject* gameObject) {
	// checks if object is in GOM
	if (!HasGameObject(gameObject)) {
		std::cerr << "Warning can't delete object not in scene\n";
	}

	// removes the GameObject from the GOM
	if (!gameObject->parent) {
		branches.remove(gameObject);
	}
	else {
		gameObject->parent->children.remove(gameObject);
	}

	//frees the memory of gameObject, and its children
	FreeBranch(gameObject);
}

bool GOM::SetParent(GameObject* gameObject, GameObject* parent) {
	GameObject* oldParent = gameObject->parent;
	if (oldParent == parent) return true;

	// removes child from old parent
	if (oldParent) {
		oldParent->children.remove(gameObject);
	}
	else {
		branches.remove(gameObject);
	}
	// sets the parent
	gameObject->parent = parent;
	if (parent) {
		parent->children.push_front(gameObject);
	}
	else {
		branches.push_front(gameObject);
	}

	// updates the world coords of the game object (and its children)
	gameObject->UpdateTransform();

	return true;
}

bool GOM::HasGameObject(const GameObject* gameObject) {
	if (!gameObject) return false;

	// climbs tree to the top of the branch
	while (gameObject->parent) {
		gameObject = gameObject->parent;
	}

	// checks if top of the branch is part of the GOM
	return std::find(branches.begin(), 
		branches.end(), 
		gameObject) != branches.end();
}

bool GOM::HasChild(const GameObject* parent, const GameObject* child) {

	const std::list<GameObject*> childrenList = parent->getChildrenList();
	//checks for immediate children
	for (const GameObject* c : childrenList) {
		if (c == child) {
			return true;
		}
	}

	//moves down the tree
	for (const GameObject* c : childrenList) {
		if (HasChild(c,child)) {
			return true;
		}
	}
	return false;
}
