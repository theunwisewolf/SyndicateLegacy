#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include <Common.h>

#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <condition_variable>

#include <Systems/Audio/Audio.h>
#include <Utilities/Logger.h>
#include <Utilities/File.h>

#include <gorilla/ga.h>
#include <gorilla/gau.h>

#define SYNDICATE_USE_BUFFERED_AUDIO 1
#define SYNDICATE_AUDIO_MAX_VOLUME 100
#define SYNDICATE_AUDIO_MAX_VOLUME_F 100.0f
#define SYNDICATE_AUDIO_MIN_VOLUME 1
#define SYNDICATE_AUDIO_MIN_VOLUME_F 0.1f

namespace Syndicate {

class SYNDICATE_API Audio;

SYNDICATE_TEMPLATE template class SYNDICATE_API std::allocator<Audio*>;
SYNDICATE_TEMPLATE template class SYNDICATE_API std::vector<Audio*>;

class SYNDICATE_API AudioManager 
{
public:
	static AudioManager* i()
	{
		static AudioManager instance;
		return &instance;
	}

private: 
	// Thread Related Stuff
	std::thread m_AudioThread;
	std::condition_variable m_ConditionVariable;
	std::atomic<bool> m_StopThread;
	std::atomic<bool> m_Finished;
	std::atomic<bool> m_InsertingAudio;
	std::mutex m_Mutex;

	std::vector<Audio*> m_AudioCache;

	ga_StreamManager* m_StreamManager;
	gau_Manager* m_SoundManager;
	ga_Mixer* m_Mixer;

	bool m_ShutDown = false;

private:
	AudioManager();
	AudioManager(AudioManager const& copy) = delete;
	AudioManager& operator=(AudioManager const& copy) = delete;

public:
	~AudioManager();

	// Initializes the class
	bool Initialize();
	// The thread handler
	void Start();
	// Stops a thread
	void Stop();
	// Clears the members
	void Clear();
	// Updates Audio
	void Update();

	void ShutDown();

	// Audio Related Functions
	// Stops all playing audio files
	void StopAll();
	void VolumeUp(size_t volume);
	void VolumeDown(size_t volume);

	Audio* Get(const std::string& name);
	void Load(Audio* audio);
	void Delete(Audio* audio);

	ga_Mixer* getMixer() { return m_Mixer; }
	gau_Manager* getSoundManager() { return m_SoundManager; }
	ga_StreamManager* getStreamManager() { return m_StreamManager; }

	std::atomic<bool>& getThreadStatus() { return std::ref(m_StopThread); }
	std::atomic<bool>& getStatus() { return std::ref(m_Finished); }

	static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);
};

}

#endif