#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "all_processes.h"
#include "system.h"
#include "format.h"

using std::string;
using std::vector;

Processor& System::Cpu() { return cpu_; }

All_Processes& System::Processes() { return processes_; }

string System::Kernel() { return string(LinuxParser::Kernel()); }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

long int System::UpTime() { return LinuxParser::UpTime(); }