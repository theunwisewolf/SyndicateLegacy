#include "AudioManager.h"

namespace Venus {

std::vector<std::vector<Audio*>> AudioManager::m_AudioQueueCache;
std::vector<Audio*> AudioManager::m_AudioCache;
gau_Manager* AudioManager::m_SoundManager = nullptr;
ga_Mixer* AudioManager::m_Mixer = nullptr;
ga_StreamManager* AudioManager::m_StreamManager = nullptr;

std::mutex m;
std::condition_variable cv;

void AudioManager::Init()
{
	gc_initialize(0);

	//AudioManager::m_SoundManager = gau_manager_create();
	AudioManager::m_SoundManager = gau_manager_create_custom(GA_DEVICE_TYPE_DEFAULT, GAU_THREAD_POLICY_MULTI, 4, 512);
	AudioManager::m_Mixer = gau_manager_mixer(AudioManager::m_SoundManager);
	AudioManager::m_StreamManager = gau_manager_streamManager(AudioManager::m_SoundManager);
}

Audio* AudioManager::Get(const std::string& name)
{
	for (auto audio : m_AudioCache)
	{
		if (audio->getName() == name)
		{
			return audio;
		}
	}

	return nullptr;
}

void AudioManager::Load(Audio* audio)
{
	m_AudioCache.push_back(audio);
}

int AudioManager::LoadQueue(std::vector<Audio*> audioQueue)
{
	m_AudioQueueCache.push_back(audioQueue);

	return m_AudioQueueCache.size() - 1;
}

std::thread AudioManager::BackgroundAudio(int index)
{
	std::thread audioThread(&AudioManager::PlayQueue, index);
	return audioThread;
}

void AudioManager::PlayQueue(int index)
{
	if (index >= 0 && index < m_AudioQueueCache.size())
	{
		std::vector<Audio*> audioQueue = m_AudioQueueCache[index];

		for (auto audio : audioQueue)
		{
			audio->PlayOnThread();
		}
	}
}

void AudioManager::Delete(Audio* audio)
{
	delete audio;
}

void AudioManager::Clear()
{
	for (auto audio : m_AudioCache)
	{
		delete audio;
	}

	m_AudioCache.clear();

	for (int i = 0; i < m_AudioQueueCache.size(); i++)
	{
		for (int j = 0; j < m_AudioQueueCache[i].size(); j++)
		{
			// Shut down the thread so that the audio stops playing
			m_AudioQueueCache[i][j]->ShutDownThread();
			m_AudioQueueCache[i][j]->Stop();

			if (i == 0 && j == 0)
			{
				std::unique_lock<std::mutex> lock(m_AudioQueueCache[i][j]->m_Mutex);
				m_AudioQueueCache[i][j]->m_ConditionVariable.wait(lock);
				lock.unlock();
				delete m_AudioQueueCache[i][j];
			}
		}
		
		m_AudioQueueCache[i].clear();
	}

	m_AudioQueueCache.clear();

	gau_manager_destroy(AudioManager::m_SoundManager);
	gc_shutdown();
}

void AudioManager::setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
{
	gc_int32* flag = (gc_int32*)(in_context);
	*flag = 1;
	ga_handle_destroy(in_handle);
}

}