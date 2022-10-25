#pragma once

#include <iterator>
#include <cstddef>
#include <map>
#include "../GameObject.h"
//#include "Events/Event.h"

typedef std::map<std::string, int> LayerMap;

class GameObjectManager {
public:
	struct Iterator {
		using iterator_category = std::input_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = GameObject;
		using pointer = GameObject*;
		using reference = GameObject&;

		Iterator(std::list<GameObject*>& b, bool start) : branches(b) {
			if (start) currentBranch = branches.begin();
			else currentBranch = branches.end();

			if (currentBranch == branches.end()) {
				goPtr = NULL;
			}
			else {
				goPtr = *currentBranch;
			}
			
		}

		reference operator*() const { return *goPtr; }
		pointer operator->() { return goPtr; }

		// Prefix increment
		Iterator& operator++() {
			
			if (!goPtr->children.empty()) {
				goPtr = goPtr->children.front();
			}
			// if there are no children, move back up the tree
			else if (goPtr->parent) {
				GameObject* parent = goPtr->parent;
				GameObject* prevChild = goPtr;

				
				while (parent != NULL) {
					auto itr = parent->children.begin();
					auto end = parent->children.end();

					// finds the previous child in the parent's list
					for (; itr != end; ++itr) {
						if (*itr == prevChild) break;
					}
					
					// this shouldn't happen
					if (itr == end) {
						std::cerr << "Error: GOM Tree malformed" << std::endl;
						goPtr = NULL;
						return *this;
					}
					// if there's a next child, move to that one
					++itr;
					if (itr != end) {
						goPtr = *itr;
						return *this;
					}
					prevChild = parent;
					parent = parent->parent;

				}

				// if there are no more children on this branch, move on
				currentBranch++;
				if (currentBranch == branches.end()) {
					goPtr = NULL;
				}
				else {
					goPtr = *currentBranch;
				}
				return *this;
			}
			// if the end of the branch is reached move onto the next
			else {
				currentBranch++;
				if (currentBranch == branches.end()) {
					goPtr = NULL;
				}
				else {
					goPtr = *currentBranch;
				}
			}
			
			return *this; 
		}

		// Postfix increment
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

		friend bool operator== (const Iterator& a, const Iterator& b) { return a.goPtr == b.goPtr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.goPtr != b.goPtr; };

	private:
		std::list<GameObject*> branches;
		std::list<GameObject*>::iterator currentBranch;
		pointer goPtr;
	};

	Iterator begin() {
		return Iterator(branches, true);
	}
	Iterator end() { 
		return Iterator(branches, false);
	}

	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* GetInstance();

	GameObject* Find(std::string objectName);

	

private:
	int LayerToInt(std::string layerName);
	bool AddLayer(std::string newLayerName);

	void FreeBranch(GameObject* gameObject);

	bool AddGameObject(GameObject* gameObject, GameObject* parent = NULL);
	void RemoveGameObject(GameObject* gameObject);

	bool SetParent(GameObject* gameObject, GameObject* parent);

	bool HasGameObject(const GameObject* gameObject);

	bool HasChild(const GameObject* parent, const GameObject* child);

	static GameObjectManager* gomInstance;
	std::list<GameObject*> branches;


	LayerMap layerMap;
	int layerCount = 1;

	friend class BetterSellingEngine;
	friend class GameObject;
};

typedef GameObjectManager GOM;

