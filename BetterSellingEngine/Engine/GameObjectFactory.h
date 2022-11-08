#pragma once

#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "engineIncludes.h"
#include "BetterSellingEngine.h"
class GameObjectFactory{

public:

	static void CreateAllGameObjects(BetterSellingEngine* bse, std::string dataSource);
	static void CreateGameObject(BetterSellingEngine* bse, rapidjson::Value::ConstMemberIterator it);
private:

};

