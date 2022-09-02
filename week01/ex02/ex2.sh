# Exercise 2

echo "Hi! I am a script!"
echo "I will create a directory called week1 in the home directory"

mkdir ~/week1 # Create a directory called week1 in the home directory
# in case it has not been created already

cd ~/week1 # Change directory to the week1

echo "\nThen I will show the prime factors of the number 6469693230"
factor 6469693230

echo "\nand finaly I will create a file contating the manual of the factor command."
man factor > factor.manual

echo "\nBye bye bye bye!!"
