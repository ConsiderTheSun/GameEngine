#include "Material.h"
#ifndef DEBUG
#define DEBUG
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#endif
Material::Material(const char* texPath, bool noAlpha) {

	initializationError = false;

    glGenTextures(1, &texID); 
    glBindTexture(GL_TEXTURE_2D, texID);

    // texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // creates texture and mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texPath, &width, &height, &nrChannels, 0);
    if (data) {
        if (noAlpha) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cerr << "Error: couldn't load texture from: " << texPath << std::endl;
        initializationError = true;
    } 
    stbi_image_free(data);
}