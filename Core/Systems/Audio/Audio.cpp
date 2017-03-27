#include "Audio.h"

namespace Venus {

Audio::Audio(const std::string& path) :
	m_AudioFilePath(path),
	m_Close(false),
	m_Playing(false)
{
	m_AudioFileFormat = m_AudioFilePath.substr(m_AudioFilePath.size() - 3, 3);
	//m_Audio = gau_load_sound_file(m_AudioFilePath.c_str(), m_AudioFileFormat.c_str());
}

Audio::Audio(const std::string& name, const std::string& path, bool loop) : 
	m_AudioFileName(name),
	m_AudioFilePath(path),
	m_Loop(loop),
	m_Close(false),
	m_Playing(false)
{
	m_AudioFileFormat = m_AudioFilePath.substr(m_AudioFilePath.size() - 3, 3);
	//m_Audio = gau_load_sound_file(m_AudioFilePath.c_str(), m_AudioFileFormat.c_str());
}

ga_Handle* Audio::createHandle(void* in_context, gau_SampleSourceLoop** out_loopSrc)
{
	//m_AudioHandle = gau_create_handle_sound(AudioManager::getMixer(), m_Audio, &AudioManager::setFlagAndDestroyOnFinish, in_context, out_loopSrc);
	m_AudioHandle = gau_create_handle_buffered_file(AudioManager::getMixer(), AudioManager::getStreamManager(), m_AudioFilePath.c_str(), m_AudioFileFormat.c_str(), &AudioManager::setFlagAndDestroyOnFinish, in_context, out_loopSrc);

	return m_AudioHandle;
}

void Audio::destroyHandle()
{
	ga_handle_destroy(m_AudioHandle);
}

void Audio::PlayOnThread()
{
	m_Over = false;
	m_Playing = true;

	// NULL means no looping
	this->createHandle(&m_Over, NULL);
	ga_handle_play(m_AudioHandle);

	while (!m_Over && !m_Close)
	{
		gau_manager_update(AudioManager::getSoundManager());
		gc_thread_sleep(1);
	}

	// Notify any waiting threads
	if (m_Close)
	{
		m_ConditionVariable.notify_all();
	}

	m_Playing = false;
}

void Audio::Play()
{
	m_Over = false;
	m_Playing = true;

	// NULL means no looping
	this->createHandle(&m_Over, NULL);
	ga_handle_play(m_AudioHandle);

	while(!m_Over)
	{
		gau_manager_update(AudioManager::getSoundManager());

#ifdef AUDIODEBUG
		printf("%d / %d\n", ga_handle_tell(m_AudioHandle, GA_TELL_PARAM_CURRENT), ga_handle_tell(m_AudioHandle, GA_TELL_PARAM_TOTAL));
#endif

		gc_thread_sleep(1);
	}

	m_Playing = false;
}

void Audio::Pause()
{
	this->Stop();
}

void Audio::Stop()
{
	if (m_Playing && m_AudioHandle != nullptr)
	{
		ga_handle_stop(m_AudioHandle);
		m_Playing = false;
	}
}

void Audio::Loop()
{
	gau_SampleSourceLoop* loopSrc = 0;
	gau_SampleSourceLoop** pLoopSrc = &loopSrc;
	m_Over = false;

	this->createHandle(&m_Over, pLoopSrc);
	ga_handle_play(m_AudioHandle);

	while (!m_Over)
	{
		gau_manager_update(AudioManager::getSoundManager());
		gc_thread_sleep(1);
	}

	m_Playing = false;
}

void Audio::Loop(unsigned int times)
{
	m_Over = false;
	m_Playing = true;

	this->createHandle(&m_Over, NULL);
	ga_handle_play(m_AudioHandle);

	while (times)
	{
		gau_manager_update(AudioManager::getSoundManager());
		int current = ga_handle_tell(m_AudioHandle, GA_TELL_PARAM_CURRENT);
		int end		= ga_handle_tell(m_AudioHandle, GA_TELL_PARAM_TOTAL);

		gc_thread_sleep(1);

		if (current == end)
		{
			times--;

			this->destroyHandle();
			this->createHandle(&m_Over, NULL);
			ga_handle_play(m_AudioHandle);
		}
	}

	m_Playing = false;
}

Audio::~Audio()
{
	//ga_sound_release(m_Audio);
	//this->destroyHandle();
}

}