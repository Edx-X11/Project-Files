#!/bin/bash

# Function to display the main menu
display_menu() {
    clear
    echo "Basic File Manager"
    echo "------------------"
    echo "1. List files in current directory"
    echo "2. Create a new directory"
    echo "3. Create a new file"
    echo "4. Rename a file or directory"
    echo "5. Delete a file or directory"
    echo "6. Exit"
    echo
}

# Function to list files in the current directory
list_files() {
    echo "Files in $(pwd):"
    ls -l
    echo
    read -p "Press Enter to continue..."
}

# Function to create a new directory
create_directory() {
    read -p "Enter directory name: " dirname
    mkdir "$dirname"
    echo "Directory '$dirname' created successfully."
    read -p "Press Enter to continue..."
}

# Function to create a new file
create_file() {
    read -p "Enter file name: " filename
    touch "$filename"
    echo "File '$filename' created successfully."
    read -p "Press Enter to continue..."
}

# Function to rename a file or directory
rename_item() {
    read -p "Enter current name: " current_name
    read -p "Enter new name: " new_name
    mv "$current_name" "$new_name"
    echo "Item '$current_name' renamed to '$new_name' successfully."
    read -p "Press Enter to continue..."
}

# Function to delete a file or directory
delete_item() {
    read -p "Enter item name: " item
    rm -rf "$item"
    echo "Item '$item' deleted successfully."
    read -p "Press Enter to continue..."
}

# Main loop
while true; do
    display_menu
    read -p "Enter your choice: " choice
    case $choice in
        1) list_files ;;
        2) create_directory ;;
        3) create_file ;;
        4) rename_item ;;
        5) delete_item ;;
        6) echo "Exiting..."; break ;;
        *) echo "Invalid choice. Please enter a number between 1 and 6." ;;
    esac
done
