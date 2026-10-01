#!/bin/bash

set -e

UF2="$HOME/embedded-machine-monitor/firmware/build/machine_monitor.uf2"
MOUNT_POINT="/mnt/pico"

echo "Looking for Pico W in BOOTSEL mode..."

DEVICE=$(lsblk -rpno NAME,LABEL | awk '$2 == "RPI-RP2" {print $1; exit}')

if [ -z "$DEVICE" ]; then
    echo "Error: Pico W not found in BOOTSEL mode."
    exit 1
fi

if [ ! -f "$UF2" ]; then
    echo "Error: Firmware file not found:"
    echo "$UF2"
    exit 1
fi

echo "Found Pico at $DEVICE"

sudo mkdir -p "$MOUNT_POINT"

# Clean up an old mount if one exists.
sudo umount "$MOUNT_POINT" 2>/dev/null || true

echo "Mounting Pico..."
sudo mount "$DEVICE" "$MOUNT_POINT"

echo "Flashing firmware..."
sudo cp "$UF2" "$MOUNT_POINT/"

sync

echo "Flash complete."
