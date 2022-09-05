# Exercise 1

mkdir ~/week1 # Create a directory called week1 in the home directory
cd ~/week1 # Change directory to the week1

# List the contents of /usr/bin, use grep for entries containing "gcc"
# and output the last 5 lines to ex1.txt
echo "Output has been saved to ~/week1/ex1.txt"
ls /usr/bin | grep gcc | tail -n 5 > ex1.txt 
