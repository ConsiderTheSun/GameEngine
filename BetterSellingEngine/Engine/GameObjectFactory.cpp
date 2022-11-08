#include "GameObjectFactory.h"

#include <rapidjson/filereadstream.h>

#define _USE_MATH_DEFINES
#include <math.h>

void GameObjectFactory::CreateAllGameObjects(BetterSellingEngine* bse, std::string dataSource) {
	std::cout << "Creating From File:" << std::endl;

	FILE* fp;
	fopen_s(&fp, dataSource.c_str(), "rb");
	if (!fp) {
		std::cout << "couldn't open file: " << dataSource << std::endl;
		return;
	}

	char readBuffer[8192];
	rapidjson::FileReadStream inputStream(fp, readBuffer, sizeof(readBuffer));

	rapidjson::Document gameObjDoc;
	gameObjDoc.ParseStream(inputStream);

	rapidjson::Value::ConstMemberIterator objectRoot = gameObjDoc.FindMember("objectList");
	if (objectRoot == gameObjDoc.MemberEnd()) {
		std::cout << "json file missing objectList" << std::endl;
		return;
	}
	const rapidjson::Value& gameObject = objectRoot->value;
	for (rapidjson::Value::ConstMemberIterator it = gameObject.MemberBegin(); it != gameObject.MemberEnd(); ++it) {
		GameObjectFactory::CreateGameObject(bse, it);
		
	}
	fclose(fp);
}

#include <glm/glm/gtx/string_cast.hpp>

void GameObjectFactory::CreateGameObject(BetterSellingEngine* bse, rapidjson::Value::ConstMemberIterator object) {

	std::cout << "Object: " << object->name.GetString() << std::endl;

	GameObject* newGO = new GameObject(object->name.GetString());

	std::cout << "Spawning " << newGO->GetName() << std::endl;

	rapidjson::Value::ConstMemberIterator layer = object->value.FindMember("layer");
	if (layer != object->value.MemberEnd() && layer->value.IsString()) {
		newGO->SetLayer(layer->value.GetString());
	}
	

	rapidjson::Value::ConstMemberIterator components = object->value.FindMember("componentList");

	rapidjson::Value::ConstMemberIterator componentMember;
	rapidjson::Value::ConstMemberIterator subMember;

	const rapidjson::Value* memberValue;
	for (rapidjson::Value::ConstMemberIterator componentItr = components->value.MemberBegin(); componentItr != components->value.MemberEnd(); ++componentItr) {
		std::cout << "Component: " << componentItr->name.GetString() << std::endl;

		std::string componentName = componentItr->name.GetString();
		if (componentName == "transform") {
			const int memberCount = 3;
			glm::vec3 position = glm::vec3(0, 0, 0);
			glm::vec3 rotation = glm::vec3(0, 0, 0);
			glm::vec3 scale = glm::vec3(1, 1, 1);

			std::string memberName[memberCount] = { "position" ,"rotation" , "scale" };
			glm::vec3* memberData[memberCount] = { &position, &rotation, &scale };

			for (int i = 0; i < memberCount; ++i) {
				componentMember = componentItr->value.FindMember(memberName[i].c_str());
				if (componentMember != componentItr->value.MemberEnd() && componentMember->value.IsArray()) {
					memberValue = &componentMember->value;
					*memberData[i] = glm::vec3((*memberValue)[0].GetFloat(),
						(*memberValue)[1].GetFloat(),
						(*memberValue)[2].GetFloat());
				}
			}

			std::cout << "position is: " << glm::to_string(position) << std::endl;
			std::cout << "rotation is: " << glm::to_string(rotation) << std::endl;
			std::cout << "scale is: " << glm::to_string(scale) << std::endl;

			Transform* transformComponent = newGO->GetComponent<Transform>();
			transformComponent->SetPosition(position);
			transformComponent->SetRotation((float)(M_PI / 180) * rotation);
			transformComponent->SetScale(scale);
		}

		else if (componentName == "sprite") {
			Sprite::Mesh mesh = Sprite::Mesh::Triangle;

			bool customMeshData = false;
			const rapidjson::Value* meshData = NULL;

			glm::vec3 color = glm::vec3(1, 1, 1);

			bool hasMaterial = false;
			std::string material = "";
			
			bool customShader = false;
			std::pair<std::string, std::string> shaderFiles;


			componentMember = componentItr->value.FindMember("geometry");
			if (componentMember != componentItr->value.MemberEnd()) {
				subMember = componentMember->value.FindMember("mesh");
				if (subMember != componentMember->value.MemberEnd() && subMember->value.IsString()) {
					//mesh = subMember->value.GetString();
					mesh = Sprite::StringToMesh(subMember->value.GetString());
				}


				subMember = componentMember->value.FindMember("data");
				if (subMember != componentMember->value.MemberEnd() && subMember->value.IsArray() && !subMember->value.Empty()) {
					customMeshData = true;
					meshData = &subMember->value;
				}
					
			}

			componentMember = componentItr->value.FindMember("color");
			if (componentMember != componentItr->value.MemberEnd() && componentMember->value.IsArray()) {
				memberValue = &componentMember->value;
				color = glm::vec3((*memberValue)[0].GetFloat(),
					(*memberValue)[1].GetFloat(),
					(*memberValue)[2].GetFloat());
			}

			componentMember = componentItr->value.FindMember("material");
			if (componentMember != componentItr->value.MemberEnd() && componentMember->value.IsString()) {
				hasMaterial = true;
				material = componentMember->value.GetString();

			}

			componentMember = componentItr->value.FindMember("shader");
			if (componentMember != componentItr->value.MemberEnd() && componentMember->value.IsArray()) {
				customShader = true;
				shaderFiles.first = componentMember->value[0].GetString();
				shaderFiles.second = componentMember->value[1].GetString();
			}

			Sprite* spriteComponent = newGO->AddComponent<Sprite>();

			switch (mesh)
			{
			case Sprite::Triangle:
				if (customMeshData && meshData->Capacity() == 15) {
					glm::vec3 p1 = glm::vec3((*meshData)[0].GetFloat(),
						(*meshData)[1].GetFloat(),
						(*meshData)[2].GetFloat());
					glm::vec3 p2 = glm::vec3((*meshData)[3].GetFloat(),
						(*meshData)[4].GetFloat(),
						(*meshData)[5].GetFloat());
					glm::vec3 p3 = glm::vec3((*meshData)[6].GetFloat(),
						(*meshData)[7].GetFloat(),
						(*meshData)[8].GetFloat());
					glm::vec2 t1 = glm::vec2((*meshData)[9].GetFloat(),
						(*meshData)[10].GetFloat());
					glm::vec2 t2 = glm::vec2((*meshData)[11].GetFloat(),
						(*meshData)[12].GetFloat());
					glm::vec2 t3 = glm::vec2((*meshData)[13].GetFloat(),
						(*meshData)[14].GetFloat());
					spriteComponent->SetTriangleGeometry(p1, p2, p3, t1, t2, t3);
				}
				else {
					spriteComponent->SetTriangleGeometry();
				}
				break;
			case Sprite::Quad:
				if (customMeshData && meshData->Capacity() == 20) {
					glm::vec3 p1 = glm::vec3((*meshData)[0].GetFloat(),
						(*meshData)[1].GetFloat(),
						(*meshData)[2].GetFloat());
					glm::vec3 p2 = glm::vec3((*meshData)[3].GetFloat(),
						(*meshData)[4].GetFloat(),
						(*meshData)[5].GetFloat());
					glm::vec3 p3 = glm::vec3((*meshData)[6].GetFloat(),
						(*meshData)[7].GetFloat(),
						(*meshData)[8].GetFloat());
					glm::vec3 p4 = glm::vec3((*meshData)[9].GetFloat(),
						(*meshData)[10].GetFloat(),
						(*meshData)[11].GetFloat());

					glm::vec2 t1 = glm::vec2((*meshData)[12].GetFloat(),
						(*meshData)[13].GetFloat());
					glm::vec2 t2 = glm::vec2((*meshData)[14].GetFloat(),
						(*meshData)[15].GetFloat());
					glm::vec2 t3 = glm::vec2((*meshData)[16].GetFloat(),
						(*meshData)[17].GetFloat());
					glm::vec2 t4 = glm::vec2((*meshData)[18].GetFloat(),
						(*meshData)[19].GetFloat());
					spriteComponent->SetQuadGeometry(p1,p2,p3,p4,t1,t2,t3,t4);
				}
				else {
					spriteComponent->SetQuadGeometry();
				}
				break;
			case Sprite::Cube:
				if (customMeshData && meshData->Capacity() == 1) {
					spriteComponent->SetCubeGeometry((*meshData)[0].GetFloat());
				}
				else {
					spriteComponent->SetCubeGeometry();
				}
				break;
			case Sprite::Circle:
				if (customMeshData && meshData->Capacity() == 1) {
					spriteComponent->SetCircleGeometry((*meshData)[0].GetInt());
				}
				else {
					spriteComponent->SetCircleGeometry();
				}
				
				break;
			case Sprite::Cylinder:
				if (customMeshData && meshData->Capacity() == 1) {
					spriteComponent->SetCylinderGeometry((*meshData)[0].GetInt());
				}
				else {
					spriteComponent->SetCylinderGeometry();
				}
				break;
			default:
				spriteComponent->SetTriangleGeometry();
				break;
			}


			spriteComponent->SetColor(color);
			if (hasMaterial) {
				spriteComponent->SetMaterial(material.c_str());
			}

			if (customShader) {
				spriteComponent->SetCustomShader(shaderFiles.first.c_str(), shaderFiles.second.c_str());
			}
		}
		else if (componentName == "physicsBody") {
			Shape::ShapeType shape = Shape::ShapeType::Default;
			componentMember = componentItr->value.FindMember("shape");
			if (componentMember != componentItr->value.MemberEnd() && componentMember->value.IsString()) {
				std::string shapeStr = componentMember->value.GetString();
				if (shapeStr == "OBB")			shape = Shape::ShapeType::OBB;
				else if (shapeStr == "OBC2AA")	shape = Shape::ShapeType::OBC2AA;
				else if (shapeStr == "OBC")		shape = Shape::ShapeType::OBC;
				else if (shapeStr == "Circle")	shape = Shape::ShapeType::Circle;
			}

			float mass = 1;
			componentMember = componentItr->value.FindMember("mass");
			if (componentMember != componentItr->value.MemberEnd() && componentMember->value.IsFloat()) {
				mass = componentMember->value.GetFloat();
			}

			bool hasGravity = true;
			componentMember = componentItr->value.FindMember("gravity");
			if (componentMember != componentItr->value.MemberEnd() && componentMember->value.IsBool()) {
				hasGravity = componentMember->value.GetBool();
			}

			PhysicsBody* bodyComponent = newGO->AddComponent<PhysicsBody>();

			switch (shape)
			{
			case Shape::OBB:
				bodyComponent->SetOBB();
				break;
			case Shape::OBC:
				bodyComponent->SetOBC();
				break;
			case Shape::OBC2AA:
				bodyComponent->SetOBC2AA();
				break;
			case Shape::Circle:
				bodyComponent->SetCircle();
				break;
			default:
				break;
			}
			bodyComponent->SetMass(mass);
			bodyComponent->SetHasGravity(hasGravity);
		}
	}

	
	
	rapidjson::Value::ConstMemberIterator children = object->value.FindMember("children");
	if (children != object->value.MemberEnd() && children->value.IsArray()) {
		
		for (int i = 0; i < children->value.Capacity(); ++i) {
			children->value[i];
			GameObject* childGO = GOM::GetInstance()->Find(children->value[i].GetString());
			if (childGO) {
				childGO->SetParent(newGO);
			}
		}
	}

	rapidjson::Value::ConstMemberIterator parent = object->value.FindMember("parent");
	if (parent != object->value.MemberEnd() && parent->value.IsString()) {
		std::cout << "find parent" << std::endl;
		GameObject* parentGO = GOM::GetInstance()->Find(parent->value.GetString());
		bse->AddGameObject(newGO, parentGO);
	}
	else {
		bse->AddGameObject(newGO);
	}
	

	std::cout << std::endl;
}
