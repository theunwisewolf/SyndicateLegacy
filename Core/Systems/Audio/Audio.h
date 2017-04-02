#ifndef AUDIO_H_
#define AUDIO_H_

#include <Common.h>

#include <string>

#include <Systems/Audio/AudioManager.h>

#include <gorilla\ga.h>
#include <gorilla\gau.h>

namespace Syndicate {

class SYNDICATE_API AudioManager;

class SYNDICATE_API Audio 
{
private: 
	std::string m_AudioFileName;
	std::string m_AudioFilePath;
	std::string m_AudioFileFormat;

	bool m_Loop;
	bool m_Over;
	bool m_Playing;
	size_t m_LoopTimes;
	size_t m_Volume;

	ga_Sound* m_Audio;
	ga_Handle* m_AudioHandle;

private:
	ga_Handle* createHandle(void* in_context, gau_SampleSourceLoop** out_loopSrc);
	void destroyHandle();

public:
	Audio(const std::string& name, const std::string& path, bool loop = false);
	Audio(const std::string& path);

	const std::string& getName() const { return m_AudioFileName; }
	const std::string& getPath() const { return m_AudioFilePath; }
	const std::string& getFormat() const { return m_AudioFileFormat; }
	const size_t& getVolume() const { return m_Volume; }

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