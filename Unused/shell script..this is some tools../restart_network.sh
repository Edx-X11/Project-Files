#!/bin/bash

# Function to display usage information
display_usage() {
    echo "Usage: $0"
    echo "Restarts network devices on the local machine."
}

# Function to restart network devices
restart_network_devices() {
    echo "Restarting network devices..."

    # Check if the network service exists
    if command -v systemctl &> /dev/null; then
        # Restart network service using systemctl (systemd)
        sudo systemctl restart network
    elif command -v service &> /dev/null; then
        # Restart network service using service (SysV init)
        sudo service network restart
    elif command -v ifdown &> /dev/null && command -v ifup &> /dev/null; then
        # Restart network interfaces using ifdown and ifup
        sudo ifdown -a && sudo ifup -a
    else
        echo "Error: Unable to restart network devices. No suitable method found."
        exit 1
    fi

    echo "Network devices restarted successfully."
}

# Check if the script is executed with root privileges
if [ "$(id -u)" -ne 0 ]; then
    echo "Error: This script must be run as root."
    exit 1
fi

# Restart network devices
restart_network_devices
