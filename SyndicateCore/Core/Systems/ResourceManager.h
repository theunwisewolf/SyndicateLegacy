#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <Common.h>

#include <Utilities/Packaging/Package.h>

#include <Systems/Graphics/Texture.h>
#include <string>
#include <vector>
#include <unordered_map>

namespace Syndicate {

using namespace Graphics;

class SYNDICATE_API ResourceManager {
private:
	std::vector<Package> m_Packages;

	unsigned int m_TextureCount;
	static std::unordered_map<std::string, Texture*> textureCache;

private:
	ResourceManager() { m_TextureCount = 0; }
	ResourceManager(const ResourceManager& copy) = delete;
	ResourceManager& operator=(const ResourceManager& copy) = delete;

public:
	static ResourceManager* i();

	bool Initialize();

	Texture* getTexture(const std::string& filename);

	SoundData LoadAudio(std::string name);

	inline unsigned int getTextureCount() const { return this->m_TextureCount; }

	void Shutdown();

	~ResourceManager();
};

}

#endif