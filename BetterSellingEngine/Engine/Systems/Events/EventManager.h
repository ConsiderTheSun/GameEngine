#pragma once

#include <vector>
#include <set>
#include "../../GameObject.h"
#include "Event.h"

class EventManager {
public:
	static EventManager* GetInstance();

	template <typename T,
		typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
	inline void RegisterEvent() {
		registeredEvents.insert(typeid(T).name());
	}

	template <typename T,
		typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
	inline void UnregisterEvent() {
		std::set<std::string>::iterator itr = registeredEvents.find(typeid(T).name());
		if (itr != registeredEvents.end()) {
			registeredEvents.erase(itr);
		}
	}

	void AddEvent(Event* e);

	void HandleEvents();
	std::vector<DestroyEvent*>& GetDestroyEvents() { return destroyEventList; }
private:
	static EventManager* eventMInstance;

	std::set<std::string> registeredEvents;

	std::vector<Event*> eventList;
	std::vector<DestroyEvent*> destroyEventList;

};