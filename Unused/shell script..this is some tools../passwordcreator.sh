#!/bin/bash

# Function to generate a random password
generate_password() {
    # Define character sets for password generation
    chars="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}|;:',.<>?/~"
    num_chars=${#chars}

    # Generate random password
    password=""
    for i in $(seq 1 $1); do
        random_index=$((RANDOM % num_chars))
        password="${password}${chars:random_index:1}"
    done

    # Output SHA256 hash of the password
    echo -n "$password" | sha256sum | awk '{print $1}'
}

# Number of passwords to generate
num_passwords=30

# Generate passwords and save to file
echo "Generating $num_passwords passwords..."
for ((i=1; i<=$num_passwords; i++)); do
    password=$(generate_password 12)  # Adjust password length as needed
    echo "Password $i: $password"
    echo "Password $i: $password" >> "you_may_need_this.txt"
done

echo "Passwords saved to you_may_need_this.txt"
