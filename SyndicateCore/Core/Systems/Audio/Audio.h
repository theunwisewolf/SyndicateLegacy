#ifndef AUDIO_H_
#define AUDIO_H_

#include <Common.h>

#include <string>

#include <Systems/ResourceManager.h>
#include <Systems/Audio/AudioManager.h>

#include <gorilla\ga.h>
#include <gorilla\gau.h>
#include <gorilla\common\gc_common.h>

namespace Syndicate {

class SYNDICATE_API AudioManager;

class SYNDICATE_API Audio 
{
private: 
	SoundData m_AudioData;
	std::string m_AudioFileName;
	std::string m_AudioFileFormat;

	bool m_Loop;
	bool m_Over;
	bool m_Loaded;
	bool m_Playing;
	size_t m_LoopTimes;
	size_t m_Volume;
	
	ga_Sound* m_FileAudio;
	ga_Memory* m_MemoryAudio;
	ga_Handle* m_AudioHandle;

private:
	ga_Handle* createHandleFromFile(void* in_context, gau_SampleSourceLoop** out_loopSrc);
	ga_Handle* createHandleFromPackage(void* in_context, gau_SampleSourceLoop** out_loopSrc);
	void destroyHandle();

public:
	Audio();
	Audio(const std::string& name, bool loop = false);

	void Load(const std::string& filePath);
	void LoadFromPackage(const std::string& identifier, const std::string& package = "");

	const std::string& getName() const { return m_AudioFileName; }
	const std::string& getFormat() const { return m_AudioFileFormat; }
	const size_t& getVolume() const { return m_Volume; }

	void SetData(const SoundData& data) { this->m_AudioData = data; };

	void Update();
	void Play();
	void Pause();
	void Stop();
	void Loop();
	void Loop(unsigned int times);
	bool IsPlaying() const { return m_Playing; }

	// Volume can range from 0-100, we will normalize it to 0.0 to 1.0
	void VolumeUp(int value);
	void VolumeDown(int value);

	~Audio();
};

}

#endif