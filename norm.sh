#!/bin/bash
for FILE in src/*/*
do
	if [ "$FILE" != "src/utils/display.c" ]
	then
		norminette $FILE;
    fi
done