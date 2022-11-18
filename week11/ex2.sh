#!/bin/bash
echo "daniel" > lofsdisk/file1
echo "satarov" > lofsdisk/file2

gcc -static ex2.c -o lofsdisk/ex2.out

# Based on: https://www.maketecheasier.com/use-chroot-linux/
harvest_dependencies() {
  deps="$(ldd $1 | grep -o '/lib.*\.[0-9]')"

  for i in $deps; do
    if [ ! -f "$2/$i" ]; then
      cp --parents "$i" "$2"
      echo "Copied $i to lofsdisk$i"
    fi
  done
}

copy_with_dependencies() {
  cp "$1" "$2$1"
  harvest_dependencies "$1" "$2"
}

# Create directories for the environment
cd lofsdisk

if ! [ -d "bin"   ]; then mkdir bin;   fi
if ! [ -d "lib"   ]; then mkdir lib;   fi
if ! [ -d "lib64" ]; then mkdir lib64; fi

# Copy bash, cat, echo, and ls with their dependencies to lofsdisk
copy_with_dependencies /bin/bash .
copy_with_dependencies /bin/cat .
copy_with_dependencies /bin/echo .
copy_with_dependencies /bin/ls .

sudo chroot . /ex2.out > ex2.txt

echo "" >> ex2.txt

./ex2.out >> ex2.txt
mv ex2.txt ..
