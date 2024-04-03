#!/bin/bash

# Function to display network configuration
display_network_info() {
    echo "Current network configuration:"
    ip addr show eth0
    ip route show
}

# Function to configure network using DHCP
configure_dhcp() {
    dhclient
    echo "Network configured using DHCP."
}

# Function to configure network using static IP
configure_static() {
    # Prompt for network configuration details
    read -p "Enter IP address: " ip_address
    read -p "Enter netmask: " netmask
    read -p "Enter gateway: " gateway

    # Configure network with provided static IP details
    ip addr add $ip_address/$netmask dev eth0
    ip route add default via $gateway

    echo "Network configured using static IP."
}

# Function to configure DNS
configure_dns() {
    read -p "Enter primary DNS server: " primary_dns
    read -p "Enter secondary DNS server (optional): " secondary_dns

    echo "nameserver $primary_dns" > /etc/resolv.conf

    if [ -n "$secondary_dns" ]; then
        echo "nameserver $secondary_dns" >> /etc/resolv.conf
    fi

    echo "DNS configured."
}

# Prompt user for network configuration
read -p "Enter 'dhcp' for DHCP, 'static' for static IP, or 'info' to display current network configuration: " config_type

# Configure network based on input
case $config_type in
    dhcp)
        configure_dhcp
        ;;
    static)
        configure_static
        ;;
    info)
        display_network_info
        ;;
    *)
        echo "Invalid configuration type. Please enter 'dhcp', 'static', or 'info'."
        ;;
esac
