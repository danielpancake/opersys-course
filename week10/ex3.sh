#!/bin/bash

#if file exists
if [ -f "_ex3.txt" ]; then
  rm _ex3.txt
fi

echo "Hello World!" > _ex3.txt

# Removing execution permission from the file for everyone
chmod -x _ex3.txt
ls _ex3.txt | xargs stat --printf "%A %n - removed exec permission for all\n" > ex3.txt

# Granting all permissions to the owner and others (not group)
chmod uo+rwx _ex3.txt
ls _ex3.txt | xargs stat --printf "%A %n - granted all permissions to the owner and others\n" >> ex3.txt

# Making group permissions equal to user permissions
chmod g=u _ex3.txt
ls _ex3.txt | xargs stat --printf "%A %n - made group permissions equal to user permissions\n" >> ex3.txt


# Answering the questions
echo "\n--- Answering the questions ---" >> ex3.txt
# What does 660 mean for ex3.txt?
echo "What does 660 mean for ex3.txt?" >> ex3.txt
echo "The file permissions for ex3.txt are 660. This means that the owner and group have read and write permissions, other do not have any permissions" >> ex3.txt
echo "rw-rw----\n" >> ex3.txt

# What does 775 mean for ex3.txt?
echo "What does 775 mean for ex3.txt?" >> ex3.txt
echo "The file permissions for ex3.txt are 775. This means that the owner and group have read, write and execute permissions, and other has read and execute permissions" >> ex3.txt
echo "rwxrwxr-x\n" >> ex3.txt

# What does 777 mean for ex3.txt?
echo "What does 777 mean for ex3.txt?" >> ex3.txt
echo "The file permissions for ex3.txt are 777. This means that all has read, write and execute permissions" >> ex3.txt
echo "rwxrwxrwx" >> ex3.txt
