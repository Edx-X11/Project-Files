#!/bin/bash

# Function to list installed packages
list_packages() {
    local package_manager="$1"
    case $package_manager in
        apt)
            dpkg-query -l | awk '/^ii/ { print $2 }'
            ;;
        yum)
            rpm -qa
            ;;
        pacman)
            pacman -Qq
            ;;
        *)
            echo "Unsupported package manager."
            ;;
    esac
}

# Function to generate packages.json
generate_packages_json() {
    local package_manager="$1"
    local packages=$(list_packages "$package_manager")
    local json="{ \"packages\": ["
    for package in $packages; do
        json="$json \"$package\","
    done
    json="${json%,}"
    json="$json ] }"
    echo "$json" > packages.json
    echo "packages.json generated successfully."
}

# Check if package manager argument provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <package_manager>"
    echo "Note: This script only works with dpkg-query (for Debian-based systems) and rpm (for Red Hat-based systems)."
    exit 1
fi

# Generate packages.json
generate_packages_json "$1"
