#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using namespace std;

Process::Process(int id) : pid_(id) {
    string line, skip;

    std::ifstream stream(LinuxParser::kProcDirectory + to_string(id) + LinuxParser::kStatFilename);
    getline(stream, line);
    istringstream linestream(line);
    istream_iterator<string> beg(linestream), end;
    vector<string> cpuNumbers(beg, end);

    utime_ = stof(cpuNumbers[13]);
    stime_ = stof(cpuNumbers[14]);
    cutime_ = stof(cpuNumbers[15]);
    cstime_ = stof(cpuNumbers[16]);
    starttime_ = stof(cpuNumbers[21]);
}

// TODO: Return this process's ID
int Process::Pid() { 
    return pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    long uptime = LinuxParser::UpTime();
    double total_time = utime_ + stime_ + cutime_ + cstime_;
    double seconds = uptime - starttime_;
    return total_time / seconds;
}

// TODO: Return the command that generated this process
string Process::Command() { 
  string line;
  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid_) + LinuxParser::kCmdlineFilename);
  if (filestream.is_open()) {
    getline(filestream, line);
  }
  return line;
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
  string line;
  string key;
  string value;

  string v { "" };

  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid_) + LinuxParser::kCmdlineFilename);
  if(filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream stringstream(line);
      while(stringstream >> key >> value) {
        if(key == "VmData:") {
          v = value;
        }
      }
    }
  }
  return v;
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
  string line;
  string key;
  string value;

  string v { "" };

  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid_) + LinuxParser::kStatusFilename);
  if(filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream stringstream(line);
      while(stringstream >> key >> value) {
        if(key == "Uid:") {
          v = value;
        }
      }
    }
  }
  return v;
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
  long uptime = LinuxParser::UpTime();
  long seconds = uptime - starttime_;

  return seconds;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  if(pid_ > a.pid_) {
    return true;
  } else { 
    return false; 
  }
}