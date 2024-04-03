#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <iomanip> // For setw

// Constants for formatting
const int PID_WIDTH = 10;
const int NAME_WIDTH = 25;
const int STATUS_WIDTH = 15;

// Function to read and parse the /proc filesystem to gather process information
std::vector<std::vector<std::string>> getProcessInfo() {
    std::ifstream procFile("/proc");
    std::string line;
    std::vector<std::vector<std::string>> processInfo;

    while (std::getline(procFile, line)) {
        // Simulate process information gathering (example: process IDs, names, and statuses)
        if (line.find("pid") != std::string::npos) {
            std::istringstream iss(line);
            std::vector<std::string> processData;
            std::string pid, name, status;
            iss >> pid >> name >> status; // Simulated data
            processData.push_back(pid);
            processData.push_back(name);
            processData.push_back(status);
            processInfo.push_back(processData);
        }
    }

    return processInfo;
}

// Function to display process information
void displayProcessInfo(const std::vector<std::vector<std::string>>& processInfo) {
    std::cout << std::setw(PID_WIDTH) << "PID" << std::setw(NAME_WIDTH) << "Name" << std::setw(STATUS_WIDTH) << "Status\n";
    for (const auto& processData : processInfo) {
        std::cout << std::setw(PID_WIDTH) << processData[0] << std::setw(NAME_WIDTH) << processData[1] << std::setw(STATUS_WIDTH) << processData[2] << "\n";
    }
}

// Function to count the number of running processes
int countRunningProcesses(const std::vector<std::vector<std::string>>& processInfo) {
    int count = 0;
    for (const auto& processData : processInfo) {
        if (processData[2] == "Running") {
            count++;
        }
    }
    return count;
}

// Function to calculate the total memory usage of all processes
long calculateTotalMemoryUsage(const std::vector<std::vector<std::string>>& processInfo) {
    long totalMemory = 0;
    for (const auto& processData : processInfo) {
        // Simulated memory usage data
        totalMemory += std::stoi(processData[0]) * 1024; // Converting PID to KB (simplified)
    }
    return totalMemory;
}

int main() {
    // Example: Continuously gather and display process information
    while (true) {
        // Gather process information
        std::vector<std::vector<std::string>> processInfo = getProcessInfo();

        // Display process information
        displayProcessInfo(processInfo);

        // Count the number of running processes
        int runningProcesses = countRunningProcesses(processInfo);
        std::cout << "Number of Running Processes: " << runningProcesses << "\n";

        // Calculate total memory usage
        long totalMemoryUsage = calculateTotalMemoryUsage(processInfo);
        std::cout << "Total Memory Usage: " << totalMemoryUsage << " KB\n";

        // Sleep for 1 second before next iteration
        sleep(1);
    }

    return 0;
}
