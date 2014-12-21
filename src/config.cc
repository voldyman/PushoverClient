#include "config.h"

const std::string CONFIG_FILENAME = ".pushover.config";

static
std::string GetHomeDir()
{
  passwd *pw = getpwuid(getuid());
  return pw->pw_dir;
}

static
std::string GetConfigFile()
{
  std::string path = GetHomeDir() + "/" + CONFIG_FILENAME;
  return path;
}

static
std::map<std::string, std::string> GetConfigMap()
{
  std::string line;
  std::map<std::string, std::string> data;
  std::ifstream file(GetConfigFile());

  while(std::getline(file, line))
  {
    std::size_t pos = line.find('=');
    if (pos != std::string::npos) {
      data[line.substr(0, pos)] = line.substr(pos+1);
    }
    
  }
  return data;
}

static
void StoreConfigMap(std::map<std::string, std::string> data)
{
  std::vector<std::string> lines;
  for(auto& row: data) {
    std::string line = row.first + "=" + row.second;
    lines.push_back(line);
  }

  std::ofstream file(GetConfigFile());

  for(auto& line: lines) {
    file <<line << std::endl;
  }
}

std::string GetUserKey(std::string user) throw(std::string)
{
  auto data = GetConfigMap();

  if (data.find(user) == data.end()) {
    throw "User Not Found";
  } else {
    return data[user];
  }
}

std::vector<std::string> GetUsers()
{
  std::vector<std::string> users;

  auto data = GetConfigMap();

  for(auto& row: data) {
    users.push_back(row.first);
  }
  return users;
}

void AddUser(std::string user, std::string key)
{
  auto data = GetConfigMap();
  data[user] = key;

  StoreConfigMap(data);
}

void RemoveUser(std::string user)
{
  auto data = GetConfigMap();
  data.erase(user);

  StoreConfigMap(data);
}


