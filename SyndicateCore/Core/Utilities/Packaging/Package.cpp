#include "Package.h"

namespace Syndicate {

Package::Package(const std::string& signature) :
	m_ImageCount(0),
	m_ShaderCount(0),
	m_SoundCount(0),
	m_FontCount(0),
	m_DataCount(0)
{
	const char *sig = signature.c_str();

	this->m_Header.signature = 0;

	this->m_Header.signature = sig[2];
	this->m_Header.signature = (this->m_Header.signature << 8) | sig[1];
	this->m_Header.signature = (this->m_Header.signature << 8) | sig[0];

	this->m_Header.length = 0;
	this->m_Header.version = SYNDICATE_VERSION;
	this->m_Header.itemCount = 0;
}

int Package::AddImage(const std::string& identifier, ImageData image)
{
	image.id = this->m_ImageCount + 1;

	this->m_Images.push_back(image);
	this->m_ImageCount++;
	this->m_Header.itemCount++;

	this->m_Header.length += image.length;

	this->m_DataMap.emplace(identifier, image.id);

	return image.id;
} 

int Package::AddShader(const std::string& identifier, ShaderData shader)
{
	shader.id = this->m_ShaderCount + 1;

	this->m_Shaders.push_back(shader);
	this->m_ShaderCount++;
	this->m_Header.itemCount++;

	this->m_Header.length += shader.length;

	this->m_DataMap.emplace(identifier, shader.id);

	return shader.id;
}

int Package::AddSound(const std::string& identifier, SoundData sound)
{
	sound.id = this->m_SoundCount + 1;

	this->m_Sounds.push_back(sound);
	this->m_SoundCount++;
	this->m_Header.itemCount++;

	this->m_Header.length += sound.length;

	this->m_DataMap.emplace(identifier, sound.id);

	return sound.id;
}

int Package::AddFont(const std::string& identifier, FontData font)
{
	font.id = this->m_FontCount + 1;

	this->m_Fonts.push_back(font);
	this->m_FontCount++;
	this->m_Header.itemCount++;

	this->m_Header.length += font.length;

	this->m_DataMap.emplace(identifier, font.id);

	return font.id;
}

int Package::AddData(const std::string& identifier, Data data)
{
	data.id = this->m_DataCount + 1;

	this->m_Data.push_back(data);
	this->m_DataCount++;
	this->m_Header.itemCount++;

	this->m_Header.length += data.length;

	this->m_DataMap.emplace(identifier, data.id);

	return data.id;
}

void Package::Pack(std::string package)
{
	ZLib zlib;

	if (FileSystem::i()->GetExtension(package) != "spkg")
	{
		package = package + ".spkg";
	}

#ifndef SYNDICATE_DEBUG
	package = SyndicateRoot + "/" + package;
#endif

	// Create a temp file
	std::string tempFile = FileSystem::i()->CreateTempFile();

	// Write the data temporarily to some file
	std::ofstream stream(tempFile, std::ios::binary);

	// Write the header
	stream.write((char*)&m_Header, sizeof(PackageHeader));

	// Write the required counters
	stream.write((char*)&m_ImageCount, sizeof(U32));
	stream.write((char*)&m_SoundCount, sizeof(U32));
	stream.write((char*)&m_FontCount, sizeof(U32));
	stream.write((char*)&m_ShaderCount, sizeof(U32));
	stream.write((char*)&m_DataCount, sizeof(U32));

	int dataLength;

	// The data map is going to help us retrieve data back from the Package
	for (auto pair : this->m_DataMap)
	{
		dataLength = pair.first.length();

		stream.write((char*)&pair.second, sizeof(U32));
		stream.write((char*)&dataLength, sizeof(U32));
		stream.write((char*)&pair.first[0], pair.first.length());
	}

	// Write images, if any
	for (auto image : this->m_Images)
	{
		stream << image;
	}

	// Write sounds, if any
	for (auto sound : this->m_Sounds)
	{
		stream << sound;
	}

	// Write Fonts, if any
	for (auto font : this->m_Fonts)
	{
		stream << font;
	}

	// Write shaders, if any
	for (auto shader : this->m_Shaders)
	{
		stream << shader;
	}

	// Write other data, if any
	for (auto data : this->m_Data)
	{
		stream << data;
	}

	stream.close();

	if (!zlib.Compress(tempFile, package))
	{
		SYNDICATE_ERROR(zlib.getError());
		SYNDICATE_ERROR("Failed to pack resources");
	}

	if (!FileSystem::i()->RemoveFile(tempFile))
	{
		SYNDICATE_ERROR("Failed to remove file temporary created while packing resources");
	}

	// Clear out all data
	this->m_Data.clear();
	this->m_Images.clear();
	this->m_Shaders.clear();
	this->m_Sounds.clear();
	this->m_DataMap.clear();
}

void Package::Unpack(std::string package)
{
	ZLib zlib;

	if (FileSystem::i()->GetExtension(package) != "spkg")
	{
		this->m_PackageName = package;
		this->m_PackageFullName = package + ".spkg";
	}
	else
	{
		this->m_PackageFullName = package;
		this->m_PackageName = package.replace(package.find_last_of("."), 5, "");
	}

#ifndef SYNDICATE_DEBUG
	this->m_PackageFullName = SyndicateRoot + "/" + this->m_PackageFullName;
#endif

	if (!Utilities::File::Exists(this->m_PackageFullName))
	{
		SYNDICATE_ERROR("Package: " + this->m_PackageFullName + " does not exist");
		return;
	}

	// Create a temp file
	std::string tempFile = FileSystem::i()->CreateTempFile();

	// Unpack the resources
	if (!zlib.Decompress(this->m_PackageFullName, tempFile))
	{
		SYNDICATE_ERROR(zlib.getError());
		SYNDICATE_ERROR("Failed to unpack resources");

		return;
	}

	std::ifstream stream(tempFile, std::ios::binary);
	stream.read((char*)&m_Header, sizeof(PackageHeader));

	stream.read((char*)&m_ImageCount, sizeof(U32));
	stream.read((char*)&m_SoundCount, sizeof(U32));
	stream.read((char*)&m_FontCount, sizeof(U32));
	stream.read((char*)&m_ShaderCount, sizeof(U32));
	stream.read((char*)&m_DataCount, sizeof(U32));

	int id;
	int dataLength;
	std::vector<char> dataIdentifier;

	// The data map is going to help us retrieve data back from the Package
	for (int i = 0; i < this->m_Header.itemCount; ++i)
	{
		stream.read((char*)&id, sizeof(U32));
		stream.read((char*)&dataLength, sizeof(U32));

		dataIdentifier.resize(dataLength);

		stream.read((char*)&dataIdentifier[0], dataLength);

		// Place it in the map
		this->m_DataMap.emplace(std::string(dataIdentifier.begin(), dataIdentifier.end()), id);

		// We don't want to resuse the old data now, do we?
		dataIdentifier.clear();
	}

	ImageData image;

	// Read images, if any
	for (int i = 0; i < m_ImageCount; ++i)
	{
		stream >> image;
		this->m_Images.push_back(image);
	}

	SoundData sound;

	// Read sounds, if any
	for (int i = 0; i < m_SoundCount; ++i)
	{
		stream >> sound;
		this->m_Sounds.push_back(sound);
	}

	FontData font;

	// Read fonts, if any
	for (int i = 0; i < m_FontCount; ++i)
	{
		stream >> font;
		this->m_Fonts.push_back(font);
	}

	ShaderData shader;

	// Read shaders, if any
	for (int i = 0; i < m_ShaderCount; ++i)
	{
		stream >> shader;
		this->m_Shaders.push_back(shader);
	}

	Data data;

	// Read shaders, if any
	for (int i = 0; i < m_DataCount; ++i)
	{
		stream >> data;
		this->m_Data.push_back(data);
	}

	stream.close();

	if (!FileSystem::i()->RemoveFile(tempFile))
	{
		SYNDICATE_ERROR( "Failed to remove file temporary file created while unpacking resources" );
	}

	this->m_ImageCount = this->m_Images.size();
	this->m_SoundCount = this->m_Sounds.size();
	this->m_FontCount = this->m_Fonts.size();
	this->m_ShaderCount = this->m_Shaders.size();
	this->m_DataCount = this->m_Data.size();
}

ImageData* Package::GetImage(const int& id)
{
	if (id > this->m_ImageCount || id <= 0)
	{
		return nullptr;
	}

	return &this->m_Images[id - 1];
}

SoundData* Package::GetSound(const int& id)
{
	if (id > this->m_SoundCount || id <= 0)
	{
		return nullptr;
	}

	return &this->m_Sounds[id - 1];
}

ShaderData* Package::GetShader(const int& id)
{
	if (id > this->m_ShaderCount || id <= 0)
	{
		return nullptr;
	}

	return &this->m_Shaders[id - 1];
}

FontData* Package::GetFont(const int& id)
{
	if (id > this->m_DataCount || id <= 0)
	{
		return nullptr;
	}

	return &this->m_Fonts[id - 1];
}

Data* Package::GetData(const int& id)
{
	if (id > this->m_DataCount || id <= 0)
	{
		return nullptr;
	}

	return &this->m_Data[id - 1];
}

FontData* Package::GetFont(const std::string& identifier)
{
	auto it = this->m_DataMap.find(identifier);

	if (it == this->m_DataMap.end())
	{
		return nullptr;
	}

	return &this->m_Fonts[it->second - 1];
}

ImageData* Package::GetImage(const std::string& identifier)
{
	auto it = this->m_DataMap.find(identifier);

	if (it == this->m_DataMap.end())
	{
		return nullptr;
	}

	return &this->m_Images[it->second - 1];
}

SoundData* Package::GetSound(const std::string& identifier)
{
	auto it = this->m_DataMap.find(identifier);

	if (it == this->m_DataMap.end())
	{
		return nullptr;
	}

	return &this->m_Sounds[it->second - 1];
}

ShaderData* Package::GetShader(const std::string& identifier)
{
	auto it = this->m_DataMap.find(identifier);

	if (it == this->m_DataMap.end())
	{
		return nullptr;
	}

	return &this->m_Shaders[it->second - 1];
}

Data* Package::GetData(const std::string& identifier)
{
	auto it = this->m_DataMap.find(identifier);

	if (it == this->m_DataMap.end())
	{
		return nullptr;
	}

	return &this->m_Data[it->second - 1];
}

Package::~Package()
{
	this->m_Data.clear();
	this->m_Images.clear();
	this->m_Shaders.clear();
	this->m_Sounds.clear();
	this->m_DataMap.clear();
}

}