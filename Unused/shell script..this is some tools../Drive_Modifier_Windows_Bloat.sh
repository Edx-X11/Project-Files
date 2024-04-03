#!/bin/bash

# Function to display usage information
display_usage() {
    echo "Usage: $0 <file_size>"
    echo "Example: $0 1G"
    echo "Creates a file of the specified size to fill up remaining storage in the drive."
}

# Function to log messages to a file
log_message() {
    timestamp=$(date +"%Y-%m-%d %T")
    echo "[$timestamp] $1" >> bloat.log
}

# Function to handle errors and exit
handle_error() {
    echo "Error: $1"
    log_message "Error: $1"
    exit 1
}

# Check if the user provided the file size argument
if [ $# -ne 1 ]; then
    display_usage
    exit 1
fi

# Check if the provided file size is valid
file_size=$1
if ! [[ "$file_size" =~ ^[0-9]+[KMG]$ ]]; then
    handle_error "Invalid file size format. Please use a number followed by K, M, or G (e.g., 1G)."
fi

# Infinite loop to repeatedly create files
while true; do
    # Determine the remaining storage in the drive
    remaining_storage=$(df / --output=avail | tail -n 1)
    if [ $remaining_storage -lt 1 ]; then
        handle_error "No remaining storage in the drive."
    fi

    # Calculate the size of the file to be created
    # Subtracting 1 MB for safety margin
    required_size=$((remaining_storage - 1024))

    # Check if the required size is less than or equal to 0
    if [ $required_size -le 0 ]; then
        handle_error "Not enough remaining storage in the drive."
    fi

    # Check if the required size is less than the provided file size
    if [ $required_size -lt ${file_size::-1} ]; then
        handle_error "The specified file size is larger than the remaining storage in the drive."
    fi

    # Create the file to fill up the remaining storage
    log_message "Creating a file of size $required_size MB..."
    dd if=/dev/zero of=filler_file bs=1M count=$required_size &>> bloat.log

    log_message "File created successfully."
    echo "File created successfully."

    # Sleep for 5 seconds before creating the next file
    sleep 5
done
