#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

#include "GameWindow.h"
#include "Camera.h"
#include "Systems/Renderer.h"
#include "Systems/GameObjectManager.h"
#include "Systems/Input.h"
#include "Systems/ScriptManager.h"
#include "Systems/Physics.h"
#include "Systems/Events/EventManager.h"

#include "GameObject.h"
#include "GameObject.inl"

#include "Components/Sprite/Sprite.h"
#include "Components/Sprite/Meshes/TriangleMesh.h"
#include "Components/Physics/PhysicsBody.h"

#include "Scene.h"