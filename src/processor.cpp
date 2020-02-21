#include "processor.h"
#include <string>
#include "linux_parser.h"

using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  string line;
  string cpu;
  float one;
  float two;
  float three;
  float four;
  float five;
  float six;
  float seven;
  float eight;
  float nine;
  float ten;

  std::ifstream filestream(LinuxParser::kProcDirectory+LinuxParser::kStatFilename);
  if(filestream.is_open()){
    while(getline(filestream, line)){
      std::istringstream stringstream(line);
      stringstream >> cpu >> one >> two >> three >> four >> five >> six >> seven >> eight >> nine >> ten;

    }
  }

  //std::this_thread::sleep_for(std::chrono::milliseconds(100));

  string cpu2;
  string line2;
  float one2;
  float two2;
  float three2;
  float four2;
  float five2;
  float six2;
  float seven2;
  float eight2;
  float nine2;
  float ten2;

  std::ifstream filestream2(LinuxParser::kProcDirectory+LinuxParser::kStatFilename);
  if(filestream.is_open()){
    while(getline(filestream2, line2)){
      std::istringstream stringstream2(line2);
      stringstream2 >> cpu2 >> one2 >> two2 >> three2 >> four2 >> five2 >> six2 >> seven2 >> eight2 >> nine2 >> ten2;

    }
  }

  const float activeTime = (one2 + two2 + three2 + six2 + seven2 + eight2 + nine2 + ten2) - (one + two + three + six + seven + eight + nine + ten);
  const float idleTime = (four2 + five2) - (four + five);
  const float totalTime = activeTime + idleTime;

  return 100*(activeTime / totalTime); 
}
