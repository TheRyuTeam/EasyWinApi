#pragma once
#include <vector>
#include <string>

class AudioPlayer
{
public:
	static unsigned play2(const std::string& file);
	static unsigned play(const std::string& file);
	static void playAsync(const std::string& file, unsigned* ret = nullptr);
	static unsigned load(const std::string& file);
	static unsigned load(const std::string& file, const std::string& alias);
	static unsigned unload(const std::string& alias);

	static bool isLoaded(const std::string& file);

	static std::string getStrError(unsigned code);

private:
	static std::string getModeByExt(const std::string& file);
	static unsigned sendCommand(const std::string& command);

private:
	static std::vector<std::string> _loaded;
};
