#include "EventManager.h"


EventManager* EventManager::eventMInstance = nullptr;
EventManager* EventManager::GetInstance() {
	if (!eventMInstance)
		eventMInstance = new EventManager();
	return eventMInstance;
}

void EventManager::AddEvent(Event* e) {
	if (registeredEvents.find(e->typeName) != registeredEvents.end()) {
		DestroyEvent* DestroyE = dynamic_cast<DestroyEvent*>(e);
		if (DestroyE) {
			destroyEventList.push_back(DestroyE);
		}
		else {
			eventList.push_back(e);
		}

	}
}

void EventManager::HandleEvents() {
	for (Event* e : eventList) {
		e->eventObject->HandleEvent(e);
		delete(e);
	}
	eventList.clear();
}