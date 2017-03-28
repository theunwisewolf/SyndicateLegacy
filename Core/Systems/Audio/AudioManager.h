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

#define VENUS_USE_BUFFERED_AUDIO 1
#define VENUS_AUDIO_MAX_VOLUME 100
#define VENUS_AUDIO_MAX_VOLUME_F 100.0f
#define VENUS_AUDIO_MIN_VOLUME 1
#define VENUS_AUDIO_MIN_VOLUME_F 0.1f

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
	static void Update();

	static Audio* Get(const std::string& name);
	static void Load(Audio* audio);
	static int LoadQueue(std::vector<Audio*> audioQueue);
	static void PlayQueue(int index);
	static std::thread BackgroundAudio(int index);
	static void Delete(Audio* audio);

	static ga_StreamManager* getStreamManager() { return m_StreamManager;  }
	static gau_Manager* getSoundManager() { return m_SoundManager; }
	static ga_Mixer* getMixer() { return m_Mixer; }
	static std::vector<Audio*> GetQueue(int index) { if (index >= 0 && index < m_AudioQueueCache.size()) return m_AudioQueueCache[index]; }

	static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);
};

}

#endif