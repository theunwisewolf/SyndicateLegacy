#ifndef PACKAGE_H_
#define PACKAGE_H_

#include <Common.h>

#include <fstream>
#include <map>

#include <Utilities/Logger.h>
#include <Utilities/File.h>
#include <Utilities/Packaging/ZLib.h>
#include <Utilities/FileSystem/FileSystem.h>

namespace Syndicate {

struct PackageHeader 
{
	U32   signature;
	S8	  version;
	U64   length;
	U32   itemCount;
};

struct Data
{
	U32				id;
	char			format[4]{}; // file format
	U32				length;
	std::string		data;

	Data() :
		id(0),
		length(0),
		data()
	{
		// Default format SYN assumed
		strcpy(format, "syn");
	}

	Data(std::string _data, U32 _length) :
		length(_length),
		data(_data)
	{

	}

	void setData(const std::string& data)
	{
		this->data = data;
	}

	void setFormat(const std::string& fmt)
	{
		std::strncpy(this->format, fmt.c_str(), 3);
	}

	friend std::istream& operator>>(std::istream& stream, Data& data)
	{
		std::vector<char> str;

		stream.read((char*)&data.id, sizeof(id));
		stream.read((char*)&data.length, sizeof(length));

		str.resize(data.length);

		stream.read(&data.format[0], 4);
		stream.read(&str[0], data.length);

		data.data = std::string(str.begin(), str.end());

		return stream;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Data& data)
	{
		stream.write((char*)&data.id, sizeof(id));
		stream.write((char*)&data.length, sizeof(length));
		stream.write(&data.format[0], 4);
		stream.write(&data.data[0], data.length);

		return stream;
	}
};

struct ImageData : public Data
{
	U16				width;
	U16				height;

	ImageData() :
		width(0),
		height(0),
		Data()
	{

	}

	ImageData(std::string data, U32 length, U16 width, U16 height) :
		width(width),
		height(height),
		Data(data, length)
	{

	}

	void setDimensions(const U32& width, const U32& height)
	{
		this->width = width;
		this->height = height;
	}

	friend std::istream& operator>>(std::istream& stream, ImageData& image)
	{
		std::vector<char> str;

		stream.read((char*)&image.id, sizeof(id));
		stream.read((char*)&image.width, sizeof(width));
		stream.read((char*)&image.height, sizeof(height));
		stream.read((char*)&image.length, sizeof(length));
		stream.read(&image.format[0], 4);

		str.resize(image.length);

		stream.read(&str[0], image.length);

		image.data = std::string(str.begin(), str.end());

		return stream;
	}

	friend std::ostream& operator<<(std::ostream& stream, const ImageData& image)
	{
		stream.write((char*)&image.id, sizeof(id));
		stream.write((char*)&image.width, sizeof(width));
		stream.write((char*)&image.height, sizeof(height));
		stream.write((char*)&image.length, sizeof(length));

		stream.write(&image.format[0], 4);
		stream.write(&image.data[0], image.length);

		return stream;
	}
};

struct SoundData : public Data
{
	SoundData() :
		Data()
	{
	
	}

	SoundData(std::string data, U32 length, std::string fmt) :
		Data(data, length)
	{
		if (fmt != "ogg" && fmt != "wav")
		{
			SYNDICATE_ERROR("Using unknown sound format " + fmt + ". Allowed formats are: ogg, wav");
		}

		std::strncpy(this->format, fmt.c_str(), 3);
	}

	void setFormat(const std::string& fmt)
	{
		if (fmt != "ogg" && fmt != "wav")
		{
			SYNDICATE_ERROR( "Using unknown sound format " + fmt + ". Allowed formats are: ogg, wav" );
		}

		std::strncpy(this->format, fmt.c_str(), 3);
	}

	friend std::istream& operator>>(std::istream& stream, SoundData& sound)
	{
		std::vector<char> str;

		stream.read((char*)&sound.id,	 sizeof(id));
		stream.read((char*)&sound.length, sizeof(length));

		str.resize(sound.length);

		stream.read(&sound.format[0], 4);
		stream.read(&str[0], sound.length);

		sound.data = std::string(str.begin(), str.end());

		return stream;
	}

	friend std::ostream& operator<<(std::ostream& stream, const SoundData& sound)
	{
		stream.write((char*)&sound.id,	   sizeof(id));
		stream.write((char*)&sound.length, sizeof(length));
		stream.write(&sound.format[0],	  4);
		stream.write(&sound.data[0],   sound.length);

		return stream;
	}
};

struct ShaderData : public Data
{
	ShaderData():
		Data()
	{
	}

	ShaderData(std::string data, U32 length) :
		Data(data, length)
	{

	}

	friend std::istream& operator>>(std::istream& stream, ShaderData& data)
	{
		std::vector<char> str;

		stream.read((char*)&data.id, sizeof(id));
		stream.read((char*)&data.length, sizeof(length));

		str.resize(data.length);

		stream.read(&data.format[0], 4);
		stream.read(&str[0], data.length);

		data.data = std::string(str.begin(), str.end());

		return stream;
	}

	friend std::ostream& operator<<(std::ostream& stream, const ShaderData& data)
	{
		stream.write((char*)&data.id, sizeof(id));
		stream.write((char*)&data.length, sizeof(length));
		stream.write(&data.format[0], 4);
		stream.write(&data.data[0], data.length);

		return stream;
	}
};

struct FontData : public Data
{
	FontData() :
		Data()
	{

	}

	FontData(std::string data, U32 length) :
		Data(data, length)
	{

	}

	friend std::istream& operator>>(std::istream& stream, FontData& font)
	{
		std::vector<char> str;

		stream.read((char*)&font.id, sizeof(id));
		stream.read((char*)&font.length, sizeof(length));

		str.resize(font.length);

		stream.read(&str[0], font.length);

		font.data = std::string(str.begin(), str.end());

		return stream;
	}

	friend std::ostream& operator<<(std::ostream& stream, const FontData& font)
	{
		stream.write((char*)&font.id, sizeof(id));
		stream.write((char*)&font.length, sizeof(length));
		stream.write(&font.data[0], font.length);

		return stream;
	}
};

class SYNDICATE_API Package
{
private:
	PackageHeader m_Header;

	U32		m_ImageCount;
	U32		m_SoundCount;
	U32		m_FontCount;
	U32		m_ShaderCount;
	U32		m_DataCount;

	std::vector<ImageData>	m_Images;
	std::vector<ShaderData> m_Shaders;
	std::vector<SoundData>	m_Sounds;
	std::vector<FontData>	m_Fonts;
	std::vector<Data>		m_Data;

	std::map<std::string, int> m_DataMap;

	// Internal details
	std::string m_PackageName;
	std::string m_PackageFullName;

public:
	Package(const std::string& signature = "RES");
	~Package();

	int AddImage(const std::string& identifier, ImageData image);
	int AddSound(const std::string& identifier, SoundData sound);
	int AddFont(const std::string& identifier, FontData font);
	int AddShader(const std::string& identifier, ShaderData shader);
	int AddData(const std::string& identifier, Data data);

	ImageData*		GetImage(const int& id);
	SoundData*		GetSound(const int& id);
	ShaderData*		GetShader(const int& id);
	FontData*		GetFont(const int& id);
	Data*			GetData(const int& id);

	ImageData*		GetImage(const std::string& identifier);
	SoundData*		GetSound(const std::string& identifier);
	ShaderData*		GetShader(const std::string& identifier);
	FontData*		GetFont(const std::string& identifier);
	Data*			GetData(const std::string& identifier);

	std::string getSignature()
	{
		std::string signature;

		signature += (char)(this->m_Header.signature & 0xff);
		signature += (char)(this->m_Header.signature >> 8 & 0xff);
		signature += (char)(this->m_Header.signature >> 16 & 0xff);
		
		return signature;
	}

	void Pack(std::string package);
	void Unpack(std::string package);
};

}

#endif