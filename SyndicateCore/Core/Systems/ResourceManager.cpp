#include "ResourceManager.h"

#include <unordered_map>

namespace Syndicate {

std::unordered_map<std::string, Texture*> ResourceManager::textureCache;

ResourceManager* ResourceManager::i()
{
	static ResourceManager instance;
	return &instance;
}

ResourceManager::ResourceManager()
{
	this->m_AudioCount = 0;
	this->m_ShaderCount = 0;
	this->m_PackageCount = 0;
	this->m_TextureCount = 0;
	this->m_MiscDataCount = 0;
}

bool ResourceManager::Initialize()
{
	return true;
}

Texture* ResourceManager::getTexture(const std::string& identifier)
{
	// We only load the texture if it's not found in the cache
	auto it = ResourceManager::textureCache.find(identifier);

	// Not found
	if (it == textureCache.end())
	{
		m_TextureCount++;

		// Load the texture from package
		ImageData* image = this->LoadTexture(identifier);
		Texture* texture = synnew Texture(image);

		ResourceManager::textureCache.emplace(identifier, texture);
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
			m_TextureCount--;

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

void ResourceManager::LoadPackage(std::string packageName)
{
	Package package;
	package.Unpack(packageName);

	this->m_Packages.push_back(package);
}

SoundData* ResourceManager::LoadAudio(const std::string& name)
{
	int index = -1;

	for (int i = 0; i < m_Packages.size(); ++i)
	{
		// Found...
		if (this->LoadAudio(name, m_Packages[i]) != nullptr)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		SYNDICATE_ERROR("Audio not found (Access Identifier: " + name + ")");
		return nullptr;
	}

	return this->m_Packages[index].GetSound(name);
}

SoundData* ResourceManager::LoadAudio(const std::string& name, Package package)
{
	return package.GetSound(name);
}

SoundData* ResourceManager::LoadAudio(const int& id)
{
	int index = -1;

	for (int i = 0; i < m_Packages.size(); ++i)
	{
		// Found...
		if (this->LoadAudio(id, m_Packages[i]) != nullptr)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		SYNDICATE_ERROR("Audio not found (Access Identifier: " + std::to_string(id) + ")");
		return nullptr;
	}

	return this->m_Packages[index].GetSound(id);
}

SoundData* ResourceManager::LoadAudio(const int& id, Package package)
{
	return package.GetSound(id);
}

ImageData* ResourceManager::LoadTexture(const std::string& name)
{
	int index = -1;

	for (int i = 0; i < m_Packages.size(); ++i)
	{
		// Found...
		if (this->LoadTexture(name, m_Packages[i]) != nullptr)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		SYNDICATE_ERROR("Texture/Image not found (Access Identifier: " + name + ")");
		return nullptr;
	}

	return this->m_Packages[index].GetImage(name);
}

ImageData* ResourceManager::LoadTexture(const std::string& name, Package package)
{
	return package.GetImage(name);
}

ImageData* ResourceManager::LoadTexture(const int& id)
{
	int index = -1;

	for (int i = 0; i < m_Packages.size(); ++i)
	{
		// Found...
		if (this->LoadTexture(id, m_Packages[i]) != nullptr)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		SYNDICATE_ERROR("Texture/Image not found (Access Identifier: " + std::to_string(id) + ")");
		return nullptr;
	}

	return this->m_Packages[index].GetImage(id);
}

ImageData* ResourceManager::LoadTexture(const int& id, Package package)
{
	return package.GetImage(id);
}

FontData* ResourceManager::LoadFont(const std::string& name)
{
	int index = -1;

	for (int i = 0; i < m_Packages.size(); ++i)
	{
		// Found...
		if (this->LoadFont(name, m_Packages[i]) != nullptr)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		SYNDICATE_ERROR("Font not found (Access Identifier: " + name + ")");
		return nullptr;
	}

	return this->m_Packages[index].GetFont(name);
}

FontData* ResourceManager::LoadFont(const std::string& name, Package package)
{
	return package.GetFont(name);
}

FontData* ResourceManager::LoadFont(const int& id)
{
	int index = -1;

	for (int i = 0; i < m_Packages.size(); ++i)
	{
		// Found...
		if (this->LoadFont(id, m_Packages[i]) != nullptr)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		SYNDICATE_ERROR("Font not found (Access Identifier: " + std::to_string(id) + ")");
		return nullptr;
	}

	return this->m_Packages[index].GetFont(id);
}

FontData* ResourceManager::LoadFont(const int& id, Package package)
{
	return package.GetFont(id);
}

ShaderData* ResourceManager::LoadShader(const std::string& name)
{
	int index = -1;

	for (int i = 0; i < m_Packages.size(); ++i)
	{
		// Found...
		if (this->LoadShader(name, m_Packages[i]) != nullptr)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		SYNDICATE_ERROR("Shader not found (Access Identifier: " + name + ")");
		return nullptr;
	}

	return this->m_Packages[index].GetShader(name);
}

ShaderData* ResourceManager::LoadShader(const std::string& name, Package package)
{
	return package.GetShader(name);
}

ShaderData* ResourceManager::LoadShader(const int& id)
{
	int index = -1;

	for (int i = 0; i < m_Packages.size(); ++i)
	{
		// Found...
		if (this->LoadShader(id, m_Packages[i]) != nullptr)
		{
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		SYNDICATE_ERROR("Shader not found (Access Identifier: " + std::to_string(id) + ")");
		return nullptr;
	}

	return this->m_Packages[index].GetShader(id);
}

ShaderData* ResourceManager::LoadShader(const int& id, Package package)
{
	return package.GetShader(id);
}

Data* ResourceManager::LoadData(const std::string& name)
{
	int index = -1;

	for (int i = 0; i < m_Packages.size(); ++i)
	{
		// Found...
		if (this->LoadData(name, m_Packages[i]) != nullptr)
		{
			SYNDICATE_ERROR("Data item not found (Access Identifier: " + name + ")");
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		return nullptr;
	}

	return this->m_Packages[index].GetData(name);
}

Data* ResourceManager::LoadData(const std::string& name, Package package)
{
	return package.GetData(name);
}

Data* ResourceManager::LoadData(const int& id)
{
	int index = -1;

	for (int i = 0; i < m_Packages.size(); ++i)
	{
		// Found...
		if (this->LoadData(id, m_Packages[i]) != nullptr)
		{
			SYNDICATE_ERROR("Data item not found (Access Identifier: " + std::to_string(id) + ")");
			index = i;
			break;
		}
	}

	if (index == -1)
	{
		return nullptr;
	}

	return this->m_Packages[index].GetData(id);
}

Data* ResourceManager::LoadData(const int& id, Package package)
{
	return package.GetData(id);
}

ResourceManager::~ResourceManager()
{
	if (m_TextureCount)
	{
		this->Shutdown();
	}
}

}