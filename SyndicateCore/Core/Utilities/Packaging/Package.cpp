#include "Package.h"

namespace Syndicate {

Package::Package(std::string signature) :
	m_ImageCount(0),
	m_ShaderCount(0),
	m_SoundCount(0),
	m_DataCount(0)
{
	const char *sig = signature.c_str();

	this->m_Header.signature = 0;

	this->m_Header.signature = sig[2];
	this->m_Header.signature = (this->m_Header.signature << 8) | sig[1];
	this->m_Header.signature = (this->m_Header.signature << 8) | sig[0];

	this->m_Header.length = 0;
	this->m_Header.version = SYNDICATE_VERSION;
}

int Package::AddImage(std::string identifier, ImageData image)
{
	image.id = this->m_ImageCount + 1;

	this->m_Images.push_back(image);
	this->m_ImageCount++;

	this->m_Header.length += image.length;

	this->m_DataMap.emplace(identifier, image.id);

	return image.id;
}

int Package::AddShader(std::string identifier, ShaderData shader)
{
	shader.id = this->m_ShaderCount + 1;

	this->m_Shaders.push_back(shader);
	this->m_ShaderCount++;

	this->m_Header.length += shader.length;

	this->m_DataMap.emplace(identifier, shader.id);

	return shader.id;
}

int Package::AddSound(std::string identifier, SoundData sound)
{
	sound.id = this->m_SoundCount + 1;

	this->m_Sounds.push_back(sound);
	this->m_SoundCount++;

	this->m_Header.length += sound.length;

	this->m_DataMap.emplace(identifier, sound.id);

	return sound.id;
}

int Package::AddData(std::string identifier, Data data)
{
	data.id = this->m_DataCount + 1;

	this->m_Data.push_back(data);
	this->m_DataCount++;

	this->m_Header.length += data.length;

	this->m_DataMap.emplace(identifier, data.id);

	return data.id;
}

void Package::Pack(std::string package)
{
	ZLib zlib;

	// Create a temp file
	std::string tempFile = FileSystem::i()->CreateTempFile();

	// Write the data temporarily to some file
	std::ofstream stream(tempFile, std::ios::binary);

	// Write the header
	stream.write((char*)&m_Header, sizeof(PackageHeader));

	// Write the required counters
	stream.write((char*)&m_ImageCount, sizeof(U32));
	stream.write((char*)&m_SoundCount, sizeof(U32));
	stream.write((char*)&m_ShaderCount, sizeof(U32));
	stream.write((char*)&m_DataCount, sizeof(U32));

	for (auto pair : this->m_DataMap)
	{

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

	if (!zlib.Compress(tempFile, package + ".spkg"))
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
}

void Package::Unpack(std::string package)
{
	ZLib zlib;

	package += ".spkg";

	if (!Utilities::File::Exists(package))
	{
		SYNDICATE_ERROR("Package: " + package + " does not exist");
		return;
	}

	// Create a temp file
	std::string tempFile = FileSystem::i()->CreateTempFile();

	// Unpack the resources
	if (!zlib.Decompress(package, tempFile))
	{
		SYNDICATE_ERROR(zlib.getError());
		SYNDICATE_ERROR("Failed to unpack resources");

		return;
	}

	std::ifstream stream(tempFile, std::ios::binary);
	stream.read((char*)&m_Header, sizeof(PackageHeader));

	stream.read((char*)&m_ImageCount, sizeof(U32));
	stream.read((char*)&m_SoundCount, sizeof(U32));
	stream.read((char*)&m_ShaderCount, sizeof(U32));
	stream.read((char*)&m_DataCount, sizeof(U32));

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
		stream >> shader;
		this->m_Data.push_back(data);
	}

	stream.close();

	if (!FileSystem::i()->RemoveFile(tempFile))
	{
		SYNDICATE_ERROR( "Failed to remove file temporary file created while unpacking resources" );
	}

	this->m_ImageCount = this->m_Images.size();
	this->m_SoundCount = this->m_Sounds.size();
	this->m_DataCount = this->m_Data.size();
	this->m_ShaderCount = this->m_Shaders.size();
}

ImageData* Package::GetImage(int id)
{
	if (id > this->m_ImageCount || id <= 0)
	{
		return nullptr;
	}

	return &this->m_Images[id - 1];
}

SoundData* Package::GetSound(int id)
{
	if (id > this->m_SoundCount || id <= 0)
	{
		return nullptr;
	}

	return &this->m_Sounds[id - 1];
}

ShaderData* Package::GetShader(int id)
{
	if (id > this->m_ShaderCount || id <= 0)
	{
		return nullptr;
	}

	return &this->m_Shaders[id - 1];
}

Data* Package::GetData(int id)
{
	if (id > this->m_DataCount || id <= 0)
	{
		return nullptr;
	}

	return &this->m_Data[id - 1];
}

Package::~Package()
{
	this->m_Data.clear();
	this->m_Images.clear();
	this->m_Shaders.clear();
	this->m_Sounds.clear();
}

}