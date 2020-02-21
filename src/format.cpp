#include "format.h"
#include <iomanip>
#include <sstream>
#include <string>

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    long minutes = seconds / 60;
    long hours = minutes / 60;
    string time = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds % 60);
    return time;
}