#pragma once
#include "GameObject.h"


template <typename T,
	typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
inline T* GameObject::AddComponent() {
	// checks if gameObject already has the component
	if (this->GetComponent<T>()) {
		return NULL;
	}

	// creates the component and adds it to the gameObject
	T* newComponent = new T(this);
	componentList.push_back((Component*)newComponent);

	return newComponent;
}


template <typename T,
	typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
inline T* GameObject::GetComponent() {

	for (Component* c : componentList){
		T* componentT = dynamic_cast<T*>(c);
		if (componentT) {
			return componentT;
		}
	}
	return NULL;
}

template <typename T,
	typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
inline std::vector<T*> GameObject::GetAllComponents() {
	std::vector<T*> cVector;
	for (Component* c : componentList) {
		T* componentT = dynamic_cast<T*>(c);
		if (componentT) {
			cVector.push_back(componentT);
			//return componentT;
		}
	}
	return cVector;
}