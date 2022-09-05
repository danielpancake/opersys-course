# Exercise 3

mkdir ~/week1 # Create a directory called week1 in the home directory
# in case it has not been created already

cd ~/week1 # Change directory to the week1

# Create two folders for two new file
echo "Creating new directory '~/week1/rt_dir':"
mkdir ./rt_dir

# Print the current date and sleep for 3 seconds
date
sleep 3s

echo "\nCreating new directory '~/week1/hm_dir':"
mkdir ./hm_dir

# Print the current date and sleep for 3 seconds
date
sleep 3s

# Save the content of the root directory to the root.txt file
echo "\nSaving the content of the root directory to '~/week1/rt_dir/':"
ls / -rt > ./rt_dir/root.txt

# Print the current date and sleep for 3 seconds
date
sleep 3s

# Save the content of the home directory to the home.txt file
echo "\nSaving the content of the home directory to '~/week1/hm_dir/':"
ls ~ -rt > ./hm_dir/home.txt

# Print the current date and sleep for 3 seconds
date
sleep 3s

# Output the content of the root.txt and home.txt files
echo "\nContent of the root.txt file:"
cat ./rt_dir/root.txt

echo "\nContent of the home.txt file:"
cat ./hm_dir/home.txt

# Output the contect of two folders
echo "\nItems of the '~/week1/rt_dir':"
ls ./rt_dir

echo "\nItems of the '~/week1/hm_dir':"
ls ./hm_dir
