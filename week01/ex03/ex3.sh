# Exercise 3

mkdir ~/week1 # Create a directory called week1 in the home directory
# in case it has not been created already

cd ~/week1 # Change directory to the week1

# Create two folders for two new files
mkdir ./folder1
mkdir ./folder2

# Save the content of the root directory to the root.txt file
ls / -rt > ./folder1/root.txt

# Print the current date and sleep for 3 seconds
date
sleep 3s

# Save the content of the home directory to the home.txt file
ls ~ -rt > ./folder2/home.txt

# Output the content of the root.txt and home.txt files
echo "\nContent of the root.txt file:"
cat ./folder1/root.txt

echo "\nContent of the home.txt file:"
cat ./folder2/home.txt

# Output the contect of two folders
echo "\nItems of the folder 1:"
ls ./folder1

echo "\nItems of the folder 2:"
ls ./folder2
