#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
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
  std::ifstream stream(kProcDirectory + kVersionFilename);
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
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        std::cout << filename << std::endl;
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  string value;

  float memTotal;
  float memFree;

  std::ifstream filestream(kProcDirectory+kMeminfoFilename);
  if(filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream stringstream(line);
      while(stringstream >> key >> value) {
        if(key == "MemTotal:") {
          memTotal = std::stof(value);
        }
        if(key == "MemFree:") {
          memFree = std::stof(value);
        }
      }
    }
  }

  return memTotal - memFree; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  string value;

  std::ifstream filestream(kProcDirectory+kUptimeFilename);
  if(filestream.is_open()){
    getline(filestream, line);
    std::istringstream stringstream(line);
    stringstream >> value;
  }
  return std::stol(value);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line;
  string key;
  string value;
  std::vector<string> values;

  std::ifstream filestream(kProcDirectory+kStatFilename);
  if (filestream.is_open()){
    getline(filestream, line);
    std::istringstream stringstream(line);
    if(stringstream >> key){
      if(key == "cpu") {
        while(stringstream >> value){
          values.push_back(value);
        }
      }
    }
  }
  return values; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  string value;

  int v;
  std::ifstream filestream(kProcDirectory+kStatFilename);
  if (filestream.is_open()){
  while(std::getline(filestream, line)) {
      std::istringstream stringstream(line);
      while(stringstream >> key >> value) {
        if(key == "processes") {
          v = std::stoi(value);
        }
      }
    }
  }
  return v; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  return LinuxParser::Pids().size();
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line;

  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kCmdlineFilename);
  if(filestream.is_open()){
    getline(filestream, line);
  }
  return line; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  string value;
  string mem;

  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  if(filestream.is_open()){
    while(getline(filestream, line)){
      std::istringstream stringstream(line);
      stringstream >> key >> value;
      if(key == "VmSize:") {
        mem = value;
      }
    }
  }
  return mem; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value;
  string uid;

  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  if(filestream.is_open()){
    while(getline(filestream, line)){
      std::istringstream stringstream(line);
      stringstream >> key >> value;
      if(key == "Uid:") {
        uid = value;
      }
    }
  }
  return uid; 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string line;
  string key;
  string temp;
  string value;
  string user;

  string uid = LinuxParser::Uid(pid);

  std::ifstream filestream(kPasswordPath);
  if(filestream.is_open()){
    while(getline(filestream, line)){
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream stringstream(line);
      stringstream >> value >> temp >> key;
      if(key == uid) {
        user = value;
      }
    }
  }
  return user; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line;
  string value;

  std::ifstream filestream(kProcDirectory+std::to_string(pid)+kStatusFilename);
  if(filestream.is_open()){
    while(getline(filestream, line)){
      std::istringstream stringstream(line);
      for(int i = 0; i < 22; i++){
        stringstream >> value;
      }
    }
  }
  return std::stol(value); 
}