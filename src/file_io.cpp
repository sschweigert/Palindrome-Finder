#include <file_io.h>
#include <fstream>
#include <iostream>

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
	std::fstream fileStream(path, std::fstream::in);

	if (fileStream.fail())
	{
		return boost::none;
	}

	std::vector<std::string> toReturn;

	std::string line;
	while (std::getline(fileStream, line))
	{
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
	filePath /= "other_word_sets/google_words.txt";
	return importWordSet(filePath.string());
}

EnumMap< WordType, std::vector<std::string> > importTypedWords()
{
	boost::filesystem::path directoryPath = topPath;
	directoryPath /= typedWordDirectory;

	EnumMap< WordType, std::vector<std::string> > toReturn;

	for (auto element : typedWordFilenames)
	{
		boost::filesystem::path fullPath = directoryPath / element.second;
		auto importedWords = importWordSet(fullPath.string());	

		if (importedWords)
		{
			toReturn[element.first] = *importedWords;
		}
	}

	return toReturn;
}
