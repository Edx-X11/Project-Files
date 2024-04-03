#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // For system() function
#include <unistd.h> // For fork(), setsid(), sleep()
#include <sys/stat.h> // For umask()
#include <fcntl.h> // For open()

// Function to enable or disable a firewall rule using iptables
void setFirewallRule(const std::string& rule, bool enable) {
    std::string command = "sudo iptables ";
    command += (enable ? "-A " : "-D "); // Append "-A" for add or "-D" for delete
    command += "INPUT -p tcp --dport " + rule + " -j ACCEPT"; // Example rule: allow TCP traffic on a specific port
    int result = system(command.c_str()); // Execute the iptables command

    if (result != 0) {
        std::cerr << "Failed to set firewall rule." << std::endl;
        // You can add additional error handling logic here, such as logging errors to a file or sending alerts
    }
}

// Function to display the current firewall rules
void displayFirewallRules() {
    system("sudo iptables -L INPUT -n"); // Display the current firewall rules using iptables
}

int main() {
    // Fork the process to run as a background daemon
    pid_t pid = fork();

    // If fork() fails, exit with an error
    if (pid < 0) {
        std::cerr << "Failed to fork process." << std::endl;
        return 1;
    }

    // If fork() succeeds and the parent process, exit
    if (pid > 0) {
        std::cout << "Dynamic Firewall Manager is running as a background process with PID: " << pid << std::endl;
        return 0;
    }

    // If fork() succeeds and the child process, continue executing as a daemon
    umask(0); // Set the file mode creation mask to 0

    // Create a new session
    if (setsid() < 0) {
        std::cerr << "Failed to create new session." << std::endl;
        return 1;
    }

    // Redirect standard I/O streams to /dev/null
    int fd = open("/dev/null", O_RDWR);
    if (fd < 0) {
        std::cerr << "Failed to open /dev/null." << std::endl;
        return 1;
    }
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    close(fd);

    // Example: Continuously toggle a firewall rule (e.g., port 8080) every 5 seconds
    bool ruleEnabled = false;
    std::string ruleToToggle = "8080"; // Example rule: allow traffic on port 8080

    while (true) {
        // Toggle the firewall rule
        setFirewallRule(ruleToToggle, !ruleEnabled);
        ruleEnabled = !ruleEnabled;

        // Display the current state of the firewall rule
        std::cout << "Firewall Rule " << ruleToToggle << " is now " << (ruleEnabled ? "enabled" : "disabled") << std::endl;

        // Display the current firewall rules
        std::cout << "\nCurrent Firewall Rules:\n";
        displayFirewallRules();

        // Sleep for 5 seconds before toggling the rule again
        sleep(5);
    }

    return 0;
}
