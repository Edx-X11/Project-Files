#!/bin/bash

# This script allows the user to add or remove a user from the system.
# It also provides options to set the user's home directory, default shell, and additional groups.

# Function to add a user
add_user() {
    # Prompt for the username
    read -p "Enter the username you want to add: " username

    # Prompt for the home directory (default: /home/username)
    read -p "Enter the home directory for $username (press Enter for default): " home_dir
    home_dir=${home_dir:-/home/$username}

    # Prompt for the default shell (default: /bin/bash)
    read -p "Enter the default shell for $username (press Enter for default): " default_shell
    default_shell=${default_shell:-/bin/bash}

    # Prompt for additional groups (comma-separated, if any)
    read -p "Enter additional groups for $username (comma-separated, press Enter for none): " additional_groups

    # Add the user with specified options
    useradd -m -d $home_dir -s $default_shell $username

    # Add additional groups if provided
    if [ -n "$additional_groups" ]; then
        usermod -aG $additional_groups $username
    fi

    echo "User '$username' added successfully."
}

# Function to remove a user
remove_user() {
    # Prompt for the username to remove
    read -p "Enter the username you want to remove: " username

    # Remove the user and their home directory
    userdel -r $username

    echo "User '$username' removed successfully."
}

# Prompt the user for action
read -p "Enter 'add' to add a user or 'remove' to remove a user: " action

# Perform the action based on user input
case $action in
    add)
        add_user
        ;;
    remove)
        remove_user
        ;;
    *)
        echo "Invalid action. Please enter 'add' or 'remove'."
        ;;
esac
