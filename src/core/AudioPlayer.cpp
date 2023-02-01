#include <ewa/core/AudioPlayer.hpp>
#include <Windows.h>
#include <mmsystem.h>
#include <stdexcept>
#include <thread>

std::vector<std::string> AudioPlayer::_loaded = {};

std::string rndStr()
{
	std::string str;
	str.resize(rand() % 32 + 32);

	for (size_t i = 0; i < str.size(); ++i)
	{
		*const_cast<char*>(str.data()) = rand() % 27 + 91;
	}

	return str;
}
std::string getFileExt(const std::string& filename)
{
	const auto dp = filename.find_last_of('.') + 1;
	if (dp >= filename.size())
		return "";

	return filename.substr(dp);
}

unsigned AudioPlayer::play(const std::string& file)
{
	return sendCommand("play " + file);
}

void AudioPlayer::playAsync(const std::string& file, unsigned* ret)
{
	std::thread([ret, file](){
		if (ret)
			*ret = play(file);
		else
			play(file);
	}).detach();
}

unsigned AudioPlayer::load(const std::string &file)
{
	if (isLoaded(file))
		return 0;

	const auto ret = sendCommand("open " + file + " type " + getModeByExt(file));
	if (ret != 0)
		return ret;

	_loaded.emplace_back(file);
	return 0;
}

unsigned AudioPlayer::load(const std::string& file, const std::string& alias)
{
	const auto ret = sendCommand("open " + file + " type " + getModeByExt(file) + " alias " + alias);
	if (ret == 0)
		_loaded.emplace_back(alias);

	return ret;
}

unsigned AudioPlayer::unload(const std::string& alias)
{
	return sendCommand("close " + alias);
}

bool AudioPlayer::isLoaded(const std::string& file)
{
	for (const auto& loaded : _loaded)
	{
		if (loaded == file)
			return true;
	}

	return false;
}

std::string AudioPlayer::getStrError(unsigned code)
{
	char buff[MAXERRORLENGTH]{};
	const auto ret = mciGetErrorString(code, buff, MAXERRORLENGTH);
	if (ret)
		return "Unknown error.";

	return buff;
}

std::string AudioPlayer::getModeByExt(const std::string &file)
{
	const auto ext = getFileExt(file);

	if (ext == "mp3")
		return "mpegvideo";
	else if (ext == "wav")
		return "WaveAudio";
	else if (ext == "mid" || ext == "rmi")
		return "sequencer";
	else if (ext == "avi")
		return "AVIVideo";

	throw std::runtime_error("Unsupported audio extension.");
}

unsigned AudioPlayer::sendCommand(const std::string& command)
{
	return mciSendString(command.c_str(), nullptr, 0, nullptr);
}

unsigned AudioPlayer::play2(const std::string &file)
{
	auto name = rndStr();
	auto ret = load(file, name);
	if (ret)
		return ret;

	ret = play(name);
	if (ret)
		return ret;

	return unload(name);
}


