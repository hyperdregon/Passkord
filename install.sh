#!/bin/bash
INCLUDES="./Headers"
SOURCES=""
for s in $(find . -name "*.c")
do 
    SOURCES="$SOURCES $s"
done
for h in $(find $INCLUDES -type d)
do 
    INCLUDES="$INCLUDES -I$h"
done
INCLUDES="-I$INCLUDES"
gcc -DENC_KEY=$1 -DPASSWD=\"$2\" $INCLUDES $SOURCES -o passkord `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -rdynamic -fcommon && sudo mv passkord /usr/bin
echo "Warning: You can delete all the contents of this folder, except the UI folder. That is where the UI files are, and without that the program won't load."
