#!/bin/bash

# Gather system information
echo "=== System Information ===" > system_info.txt
echo "Hostname: $(hostname)" >> system_info.txt
echo "Kernel Version: $(uname -r)" >> system_info.txt
echo "CPU Info: $(lscpu)" >> system_info.txt
echo "Memory Info: $(free -m)" >> system_info.txt
echo "Disk Usage: $(df -h)" >> system_info.txt
echo "Network Info: $(ip addr)