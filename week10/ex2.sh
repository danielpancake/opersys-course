#!/bin/bash

# If week01 directory does not exist, create it
if [ ! -d "./../week01" ]; then
  mkdir ./../week01 
fi

# Get the current directory
current_dir=$(pwd)

# Create a file in week01 directory
echo "Hello World!" > ./../week01/file.txt

# Get the path to the created file
cd ./../week01
path_to_file="$(pwd)/file.txt"
cd $current_dir

# Create a hard link to the file in week01 directory
link ./../week01/file.txt ./_ex2.txt

# Getting the inode number of the link _ex2.txt
inode_val=$(ls -i _ex2.txt | cut -d'_' -f 1)

# Print found files with the same inode number
found=$(find ~ -inum $inode_val)

echo "Found files with the same inode number as file.txt:" > ex2.txt

for file in $found; do
  if [ "$file" != "$path_to_file" ]; then
    echo "$file - removed" >> ex2.txt
    rm $file
  else
    echo "$file" >> ex2.txt
  fi
done
