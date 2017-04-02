#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <Common.h>

#include <Systems/Graphics/Texture.h>
#include <string>
#include <vector>
#include <unordered_map>

namespace Syndicate {

using namespace Graphics;

class SYNDICATE_API ResourceManager {
private:
	unsigned int m_TextureCount;
	static std::unordered_map<std::string, Texture*> textureCache;

private:
	ResourceManager() { m_TextureCount = 0; }
	ResourceManager(const ResourceManager& copy);
	ResourceManager& operator=(const ResourceManager& copy);

public:
	static ResourceManager* i();

	Texture* getTexture(const std::string& filename);

	inline unsigned int getTextureCount() const { return this->m_TextureCount; }

	~ResourceManager();
};

}

#endif