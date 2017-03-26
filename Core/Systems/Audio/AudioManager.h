#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include <Common.h>

#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <condition_variable>

#include <Systems/Audio/Audio.h>

#include <gorilla\ga.h>
#include <gorilla\gau.h>

namespace Venus {

class Audio;

class AudioManager 
{
private: 
	static std::vector<Audio*> m_AudioCache;
	static std::vector<std::vector<Audio*>> m_AudioQueueCache;

	static ga_StreamManager* m_StreamManager;
	static gau_Manager* m_SoundManager;
	static ga_Mixer* m_Mixer;

public:
	static void Init();
	static void Clear();

	static Audio* Get(const std::string& name);
	static void Load(Audio* audio);
	static int LoadQueue(std::vector<Audio*> audioQueue);
	static void PlayQueue(int index);
	static std::thread BackgroundAudio(int index);
	static void Delete(Audio* audio);

	static ga_StreamManager* getStreamManager() { return m_StreamManager;  }
	static gau_Manager* getSoundManager() { return m_SoundManager; }
	static ga_Mixer* getMixer() { return m_Mixer; }

	static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);
};

}

#endif