#!/bin/bash
if [ ! -z "$(losetup -j lofs.img)" ]; then
  echo "lofs.img has an existing loopback device. Cannot proceed"
  exit 1
fi

truncate --size 50M lofs.img
sudo losetup -fP lofs.img

loopdevice_name=$(losetup -j lofs.img | cut -d ':' -f 1)

if [ ! -d lofsdisk ]; then
  mkdir lofsdisk
fi

sudo mkfs.ext4 $loopdevice_name
sudo mount $loopdevice_name lofsdisk
sudo chown $USER lofsdisk
