gcc -Ofast -pthread ex4.c -o ex4

> ex4.txt

for i in 1 2 4 10 100
do
  echo "Running the program with $i thread(s)" >> ex4.txt
  time -pa -o ex4.txt ./ex4 10000000 $i
  echo "" >> ex4.txt
done
