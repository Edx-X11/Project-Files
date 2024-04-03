#!/bin/bash

# Function to display the main menu
display_menu() {
    clear
    echo "System Wiper"
    echo "------------"
    echo "1. Wipe specific directory"
    echo "2. Wipe specific file"
    echo "3. Wipe entire system (USE WITH CAUTION!)"
    echo "4. Exit"
    echo
}

# Function to securely wipe a specific directory
wipe_directory() {
    read -p "Enter directory path to wipe: " directory
    echo -n "Wiping directory '$directory' securely..."
    progress_bar "$directory" &
    PID=$!
    find "$directory" -type f -exec shred -u {} \; >/dev/null 2>&1
    rm -rf "$directory"/* >/dev/null 2>&1
    kill $PID >/dev/null 2>&1
    wait $PID >/dev/null 2>&1
    echo "Done."
    read -p "Press Enter to continue..."
}

# Function to securely wipe a specific file
wipe_file() {
    read -p "Enter file path to wipe: " file
    echo -n "Wiping file '$file' securely..."
    progress_bar "$file" &
    PID=$!
    shred -u "$file" >/dev/null 2>&1
    kill $PID >/dev/null 2>&1
    wait $PID >/dev/null 2>&1
    echo "Done."
    read -p "Press Enter to continue..."
}

# Function to prompt user for confirmation
confirm() {
    read -p "$1 [y/N]: " response
    if [[ "$response" =~ ^([yY][eE][sS]|[yY])$ ]]; then
        return 0
    else
        return 1
    fi
}

# Function to securely wipe the entire system (USE WITH CAUTION!)
wipe_system() {
    confirm "Are you sure you want to wipe the entire system? This action cannot be undone."
    if [ $? -eq 0 ]; then
        echo "Wiping the entire system securely..."
        progress_bar "System" &
        PID=$!
        sudo find / -type f -exec shred -u {} \; >/dev/null 2>&1
        sudo rm -rf /* >/dev/null 2>&1
        kill $PID >/dev/null 2>&1
        wait $PID >/dev/null 2>&1
        echo "System wiped securely."
    else
        echo "System wipe aborted."
    fi
    read -p "Press Enter to continue..."
}

# Function to display a progress bar
progress_bar() {
    local progress=0
    while true; do
        echo -ne "\rProgress [$1]: ["
        printf "%-${progress}s" ">"
        printf "%-$((50 - progress))s" "]"
        echo -n " ($progress%)"
        sleep 1
        ((progress++))
        if [ $progress -eq 51 ]; then
            break
        fi
    done
}

# Main loop
while true; do
    display_menu
    read -p "Enter your choice: " choice
    case $choice in
        1) wipe_directory ;;
        2) wipe_file ;;
        3) wipe_system ;;
        4) echo "Exiting..."; break ;;
        *) echo "Invalid choice. Please enter a number between 1 and 4." ;;
    esac
done
