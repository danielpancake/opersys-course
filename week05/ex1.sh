gcc ./publisher.c -o pub
gcc ./subscriber.c -o sub

konsole -e ./pub $1 &

for i in $(seq $1); do
    konsole -e ./sub &
done
