#!/bin/bash
python3 image_to_ascii.py "$1" temp_output.txt "$3"
./hw7.out temp_output.txt "$2" "$4"
rm temp_output.txt
