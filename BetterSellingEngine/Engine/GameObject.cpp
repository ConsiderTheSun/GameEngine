#include "GameObject.h"
#include "Systems/GameObjectManager.h"
GameObject::GameObject(std::string name, glm::vec3 position) {
	this->name = name;
	transform = new Transform(this, position);
	transform->gameObject = this;
	componentList.push_back(transform);

}

GameObject::~GameObject() {
	for (Component* c : componentList) {
		free(c);
	}
	componentList.clear();
}

GameObject* GameObject::GetChild(int index) {
	auto gItr = children.begin();
	if (gItr == children.end()) return NULL;
	for (int i = 0; i < index; i++) {
		gItr++;
		if (gItr == children.end()) return NULL;

	}
	return *gItr;
}


bool GameObject::SetParent(GameObject* parent){
	return GameObjectManager::GetInstance()->SetParent(this, parent);
}

std::string GameObject::GetLayerName() {
	LayerMap layerMap = GOM::GetInstance()->layerMap;
	for (std::pair<std::string,int> layerID : layerMap) {
		if (layerID.second == layer) {
			return layerID.first;
		}
	}
	return "default";
}

int GameObject::GetLayer() {
	return layer;
}

void GameObject::SetLayer(std::string layerName) {
	LayerMap layerMap = GOM::GetInstance()->layerMap;
	LayerMap::iterator itr = layerMap.find(layerName);
	if (itr != layerMap.end()) {
		layer = itr->second;
	}
}

void GameObject::HandleEvent(Event* e) {
	for (Component* c : componentList) {
		c->HandleEvent(e);
	}
}

void GameObject::Destroy(GameObject* go) {
	DestroyEvent* e = new DestroyEvent(go);
	EventManager::GetInstance()->AddEvent(e);
}

void GameObject::Destroy() {
	Destroy(this);
}


void GameObject::UpdateTransform() {
	Transform* transform = GetComponent<Transform>();
	transform->SetPosition(transform->GetPosition());
	transform->SetRotation(transform->GetRotation());
	transform->SetScale(transform->GetScale());

	for (GameObject* g : children) {
		g->UpdateTransform();
	}
}