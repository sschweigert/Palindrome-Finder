#include <file_io.h>
#include <fstream>

#include <boost/filesystem.hpp>

void saveToHomeDir(const std::vector<std::string>& data, std::string path)
{
	boost::filesystem::path savePath = homeDir();
	savePath /= path;

	std::fstream outputStream;
	outputStream.open(savePath.string(), std::fstream::out);

	for (const auto& line : data)
	{
		outputStream << line << std::endl;
	}
	outputStream.close();
}

std::string homeDir()
{
	char* homeDir;
	if ((homeDir = getenv("HOME")) == NULL)
	{
		homeDir = getpwuid(getuid())->pw_dir;
	}
	return homeDir;
}
