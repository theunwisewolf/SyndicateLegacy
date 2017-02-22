#include "ResourceManager.h"

namespace Venus {

std::map<std::string, Texture*> ResourceManager::textureCache;

ResourceManager* ResourceManager::i()
{
	static ResourceManager instance;
	return &instance;
}

Texture* ResourceManager::getTexture(const std::string& filename)
{
	// We only load the texture if it's not found in the cache
	auto it = ResourceManager::textureCache.find(filename);

	// Not found
	if (it == textureCache.end())
	{
		m_TextureCount++;

		Texture* texture = new Texture(filename);
		texture->loadTexture();

		ResourceManager::textureCache.emplace(filename, texture);
		return texture;
	}

	return it->second;
}

ResourceManager::~ResourceManager()
{
	for (auto texture : ResourceManager::textureCache)
	{
		if (texture.second)
		{
			delete texture.second;
			ResourceManager::textureCache.erase(texture.first);
		}
	}
}

}