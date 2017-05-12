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
	unsigned int m_AudioCount;
	unsigned int m_PackageCount;
	unsigned int m_ShaderCount;
	unsigned int m_MiscDataCount;

	static std::unordered_map<std::string, Texture*> textureCache;

private:
	ResourceManager();
	ResourceManager(const ResourceManager& copy) = delete;
	ResourceManager& operator=(const ResourceManager& copy) = delete;

public:
	static ResourceManager* i();

	bool Initialize();

	void LoadPackage(std::string packageName);

	Texture* getTexture(const std::string& identifier);

	SoundData* LoadAudio(const std::string& name);
	SoundData* LoadAudio(const std::string& name, Package package);
	SoundData* LoadAudio(const int& id);
	SoundData* LoadAudio(const int& id, Package package);
		
	ImageData* LoadTexture(const std::string& name);
	ImageData* LoadTexture(const std::string& name, Package package);
	ImageData* LoadTexture(const int& id);
	ImageData* LoadTexture(const int& id, Package package);

	FontData* LoadFont(const std::string& name);
	FontData* LoadFont(const std::string& name, Package package);
	FontData* LoadFont(const int& id);
	FontData* LoadFont(const int& id, Package package);

	ShaderData* LoadShader(const std::string& name);
	ShaderData* LoadShader(const std::string& name, Package package);
	ShaderData* LoadShader(const int& id);
	ShaderData* LoadShader(const int& id, Package package);

	Data* LoadData(const std::string& name);
	Data* LoadData(const std::string& name, Package package);
	Data* LoadData(const int& id);
	Data* LoadData(const int& id, Package package);

	inline unsigned int getTextureCount() const { return this->m_TextureCount; }

	void Shutdown();

	~ResourceManager();
};

}

#endif