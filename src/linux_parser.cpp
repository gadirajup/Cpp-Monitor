#include <dirent.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "parser_helper.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(LinuxParser::kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(LinuxParser::kProcDirectory +
                       LinuxParser::kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(LinuxParser::kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() {
  float memTotal = ParserHelper::GetValueByKey<int>(
      LinuxParser::filterMemTotalString, LinuxParser::kMeminfoFilename);
  float memFree = ParserHelper::GetValueByKey<int>(
      LinuxParser::filterMemFreeString, LinuxParser::kMeminfoFilename);

  float memory = (memTotal - memFree) / memTotal;

  return memory;
}

long LinuxParser::UpTime() {
  string line;
  long upTime = ParserHelper::GetValue<long>(LinuxParser::kUptimeFilename);
  return upTime;
}

int LinuxParser::TotalProcesses() {
  return ParserHelper::GetValueByKey<int>(LinuxParser::filterProcesses,
                                          LinuxParser::kStatFilename);
}

int LinuxParser::RunningProcesses() {
  return ParserHelper::GetValueByKey<int>(LinuxParser::filterRunningProcesses,
                                          LinuxParser::kStatFilename);
}

string LinuxParser::UserByUID(int UID) {
  string line, user, x;
  int fileUid;

  std::ifstream filestream(LinuxParser::kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> user >> x >> fileUid) {
        if (fileUid == UID) {
          return user;
        }
      }
    }
  }
  return user;
}