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

boost::optional<std::vector<std::string>> importWordSet(std::string path)
{
	std::fstream fileStream;
	fileStream.open(path, std::fstream::in);

	if (fileStream.fail())
	{
		return boost::none;
	}

	std::vector<std::string> toReturn;

	while (!fileStream.eof())
	{
		std::string line;
		fileStream >> line;

		if (line.size() > 0)	
		{
			toReturn.push_back(line);
		}
	}
	fileStream.close();
	return toReturn;
}

boost::optional<std::vector<std::string>> importGoogleWords()
{
	boost::filesystem::path filePath = topPath;
	filePath /= "other_word_tests/google_words.txt";
	return importWordSet(filePath.string());
}
