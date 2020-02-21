#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>
#include <fstream>
#include "linux_parser.h"

using std::vector;
using std::string;

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
 int previdle;
 int previowait;
 int prevuser;
 int prevnice;
 int prevsystem;
 int previrq;
 int prevsoftirq;
 int prevsteal;

 void AssignPrevValues(vector<double>);
 vector<double> ReadFile();
};

#endif