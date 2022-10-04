gcc -Ofast -pthread ex3.c -o ex3

> ex3.txt

for i in 1 2 4 10 100
do
  echo "Running the program with $i thread(s)" >> ex3.txt
  time -pa -o ex3.txt ./ex3 10000000 $i
  echo "" >> ex3.txt
done
