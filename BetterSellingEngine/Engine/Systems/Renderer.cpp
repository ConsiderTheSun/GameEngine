#include "Renderer.h"

#include <iostream>
void Renderer::Init()
{
	defaultShader = new Shader("Engine/default.vert", "Engine/default.frag");
}

Renderer::~Renderer()
{
	free(defaultShader);
}

void Renderer::Draw(const Camera* renderCam, GOM* gom) {
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for (GOM::Iterator gomItr = gom->begin(), end = gom->end(); gomItr != end; ++gomItr) {

		// gets the sprite and skips GOs that don't have one
		Sprite* spriteComponent = gomItr->GetComponent<Sprite>();
		if (!spriteComponent) continue;

		if (!gomItr->Active()) continue;

		// uses the GOs shader, or the default
		Shader* currentShader = spriteComponent->GetCustomShader();
		if (currentShader == NULL) currentShader = defaultShader;
		currentShader->Use();

		// sets uniforms
		currentShader->setVec3("color", glm::value_ptr(spriteComponent->GetColor()));

		//checks if the GO has a texture
		const Material* material = spriteComponent->GetMaterial();
		currentShader->setBool("hasTexture", material != NULL);

		// sets the active texture
		unsigned int mID = spriteComponent->GetMaterialID();
		glActiveTexture(GL_TEXTURE0);
		currentShader->setInt("textureData", 0);
		if (mID != -1) {
			glBindTexture(GL_TEXTURE_2D, mID);
		}

		//light uniforms
		currentShader->setBool("usingLighting", useLight);
		currentShader->setVec3("lightPos", glm::value_ptr(lightPos));

		// sets the mvp matrices
		glm::mat4 model = glm::translate(glm::mat4(1.0f), gomItr->transform->GetWorldPosition());
		model *= gomItr->transform->GetRotationMatrix();
		model = glm::scale(model, gomItr->transform->GetWorldScale());
		currentShader->setMat4("model", model);

		// this needs to be set every time, in case there's a custom shader
		currentShader->setMat4("view", *renderCam->GetView());
		currentShader->setMat4("projection", *renderCam->GetProjection());

		// draws the object
		glBindVertexArray(spriteComponent->GetVAO());
		//glBindBuffer(GL_ARRAY_BUFFER, spriteComponent->GetVBO());
		glDrawElements(GL_TRIANGLES, spriteComponent->PointCount(), GL_UNSIGNED_INT, 0);
	}	
}