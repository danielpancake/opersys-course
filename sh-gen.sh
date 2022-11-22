#!/bin/bash
# Creates default shell script for C program compilation
for path in $(find . -name "ex?.c" | sed "s/\.c//")
do
  file=$(echo $path | sed 's/.*\///')

  if [ ! -f "$path.sh" ]; then
    echo "#!/bin/bash" > $path.sh
    echo "gcc ./$file.c -o $file" >> $path.sh
    echo "./$file" >> $path.sh
    echo "rm $file" >> $path.sh
    chmod +x $path.sh

    echo "Created $path.sh"
  fi
done
