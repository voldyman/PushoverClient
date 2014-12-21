#include <map>
#include <vector>
#include <iostream>
#include <fstream>

// for GetHomeDir
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

std::string GetUserKey(std::string username) throw(std::string);

std::vector<std::string> GetUsers();

void AddUser(std::string user, std::string key);

void RemoveUser(std::string user);
