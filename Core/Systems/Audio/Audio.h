#ifndef AUDIO_H_
#define AUDIO_H_

#include <Common.h>

#include <string>

#include <Systems/Audio/AudioManager.h>

#include <gorilla\ga.h>
#include <gorilla\gau.h>

namespace Venus {

class AudioManager;

class Audio 
{
private: 
	std::string m_AudioFileName;
	std::string m_AudioFilePath;
	std::string m_AudioFileFormat;

	bool m_Loop;
	bool m_Over;
	unsigned int m_LoopTimes;

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

	void Play();
	void Pause();
	void Stop();
	void Loop();
	void Loop(unsigned int times);

	~Audio();
};

}

#endif