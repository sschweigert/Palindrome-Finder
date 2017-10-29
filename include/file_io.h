#ifndef _FILE_IO_H_
#define _FILE_IO_H_

#include <vector>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

// Macro to stringify expanded macro
#define xstr(a) str(a)
#define str(a) #a

constexpr const char* topPath = xstr(TOP_PATH);

void saveToHomeDir(const std::vector<std::string>& data, std::string path);

std::string homeDir();

#endif
