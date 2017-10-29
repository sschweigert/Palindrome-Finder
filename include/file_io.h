#ifndef _FILE_IO_H_
#define _FILE_IO_H_

#include <vector>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <boost/optional.hpp>

// Macro to stringify expanded macro
#define xstr(a) str(a)
#define str(a) #a

constexpr const char* topPath = xstr(TOP_PATH);

void saveToHomeDir(const std::vector<std::string>& data, std::string path);

std::string homeDir();

boost::optional<std::vector<std::string>> importWordSet(std::string path);

boost::optional<std::vector<std::string>> importGoogleWords();


#endif
