#!/bin/bash
if [ -z "$(losetup -j lofs.img)" ]; then
  echo "lofs.img does not have a loopback device. Cannot proceed"
  exit 1
fi

loopdevice_name=$(losetup -j lofs.img | cut -d ':' -f 1)

sudo umount lofsdisk
sudo losetup -d $loopdevice_name
rm -rf lofsdisk
rm lofs.img
