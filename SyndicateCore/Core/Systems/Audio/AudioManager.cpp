#include "AudioManager.h"

namespace Syndicate {

AudioManager::AudioManager() :
	m_AudioThread(),
	m_StopThread(false),
	m_SoundManager(nullptr),
	m_Mixer(nullptr),
	m_StreamManager(nullptr),
	m_InsertingAudio(false),
	m_Finished(false)
{
}

void AudioManager::ShutDown()
{
	if (!m_ShutDown)
	{
		m_StopThread = true;

		this->Clear();

		if (m_AudioThread.joinable())
		{
			m_AudioThread.join();
		}

		SYNDICATE_SUCCESS("Audio Manager Terminated...");
		m_ShutDown = true;
	}
}

AudioManager::~AudioManager()
{
	this->ShutDown();
}

void AudioManager::Initialize()
{
	gc_initialize(0);

	AudioManager::m_SoundManager = gau_manager_create_custom(GA_DEVICE_TYPE_DEFAULT, GAU_THREAD_POLICY_MULTI, 4, 512);
	AudioManager::m_Mixer = gau_manager_mixer(AudioManager::m_SoundManager);
	AudioManager::m_StreamManager = gau_manager_streamManager(AudioManager::m_SoundManager);

	m_AudioThread = std::thread(&AudioManager::Start, this);
}

void AudioManager::Start()
{
	while (!m_StopThread)
	{
		this->Update();
	}

	// Finished...
	this->m_Finished = true;

	// Notify waiting threads
	this->m_ConditionVariable.notify_all();
}

void AudioManager::Stop()
{
	m_StopThread = true;
}

void AudioManager::Update()
{
	// A synnew file is to be insert in the cache
	if (m_InsertingAudio)
	{
		// Notify waiting threads to do their work
		//this->m_ConditionVariable.notify_all();

		// Halt this thread and let it insert
		std::unique_lock<std::mutex> lock(this->m_Mutex);

		bool &var = (bool&)std::ref(m_InsertingAudio);
		this->m_ConditionVariable.wait(lock, [&] {
			return var;
		});

		lock.unlock();
	}

	std::vector<Audio*> copy(m_AudioCache);

	for (auto audioIt = copy.begin(); audioIt != copy.end(); audioIt++)
	{
		(*audioIt)->Update();
	}
}

void AudioManager::StopAll()
{
	std::vector<Audio*> copy(m_AudioCache);
	for (auto audioIt = copy.begin(); audioIt != copy.end(); audioIt++)
	{
		(*audioIt)->Stop();
	}
}

Audio* AudioManager::Get(const std::string& name)
{
	for (auto audioIt = m_AudioCache.begin(); audioIt != m_AudioCache.end(); audioIt++)
	{
		if ((*audioIt)->getName() == name)
		{
			return (*audioIt);
		}
	}

	return nullptr;
}

void AudioManager::VolumeUp(size_t volume)
{
	for (auto audioIt = m_AudioCache.begin(); audioIt != m_AudioCache.end(); audioIt++)
	{
		(*audioIt)->VolumeUp(volume);
	}
}

void AudioManager::VolumeDown(size_t volume)
{
	for (auto audioIt = m_AudioCache.begin(); audioIt != m_AudioCache.end(); audioIt++)
	{
		(*audioIt)->VolumeDown(volume);
	}
}

void AudioManager::Load(Audio* audio)
{
	if (!Utilities::File::Exists(audio->getPath()))
	{
		SYNDICATE_WARNING("Audio File " + audio->getName() + " does not exist at " + audio->getPath());
		delete audio;
		return;
	}

	// We will only insert if the audio does not already exist
	for (auto _audio : m_AudioCache)
	{
		if (_audio->getName() == audio->getName())
		{
			//SYNDICATE_WARNING("Audio File " + audio->getName() + " already in cache, returning");
			delete audio;
			return;
		}
	}

	m_InsertingAudio = true;
	m_AudioCache.push_back(audio);

	// Done inserting
	m_InsertingAudio = false;

	// Resume audio Playing
	this->m_ConditionVariable.notify_one();
}

void AudioManager::Delete(Audio* audio)
{
	delete audio;
}

void AudioManager::Clear()
{
	// Thread is still playing, wait for it to finish
	std::unique_lock<std::mutex> lock(this->m_Mutex);
	this->m_ConditionVariable.wait(lock, [this]() {
		bool status = this->getStatus();
		return status;
	});
	lock.unlock();

	for (auto audio : m_AudioCache)
	{
		delete audio;
	}

	m_AudioCache.clear();

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