#!/bin/bash
rm _ex1_1.txt
rm _ex1_2.txt

echo "Hello World!" > _ex1.txt
ln _ex1.txt _ex1_1.txt
ln _ex1.txt _ex1_2.txt

ls -li > ex1.txt
