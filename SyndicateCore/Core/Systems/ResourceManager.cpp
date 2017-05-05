#include "ResourceManager.h"

#include <unordered_map>

namespace Syndicate {

std::unordered_map<std::string, Texture*> ResourceManager::textureCache;

ResourceManager* ResourceManager::i()
{
	static ResourceManager instance;
	return &instance;
}

bool ResourceManager::Initialize()
{


	return true;
}

Texture* ResourceManager::getTexture(const std::string& filename)
{
	// We only load the texture if it's not found in the cache
	auto it = ResourceManager::textureCache.find(filename);

	// Not found
	if (it == textureCache.end())
	{
		m_TextureCount++;

		Texture* texture = synnew Texture(filename);

		ResourceManager::textureCache.emplace(filename, texture);
		return texture;
	}

	return it->second;
}

void ResourceManager::Shutdown()
{
	for (auto it = ResourceManager::textureCache.begin(); it != ResourceManager::textureCache.end();)
	{
		if (it->second)
		{
			delete it->second;
			ResourceManager::textureCache.erase(it->first);
			it = ResourceManager::textureCache.begin();
		}
		else
		{
			++it;
		}
	}

	m_TextureCount = 0;
}

SoundData ResourceManager::LoadAudio(std::string name)
{
	Package cpkg;
	cpkg.Unpack("res/amn");

	SoundData *storedSound = cpkg.GetSound(1);

	return *storedSound;
}

ResourceManager::~ResourceManager()
{
	if(m_TextureCount)
		this->Shutdown();
}

}