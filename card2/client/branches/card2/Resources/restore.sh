#!/bin/sh

OUT=$1

echo "restore $OUT"

restore_file() {
	for file in $1/*
	do
		if [ -d $file ]; then
			restore_file $file
		else 
			if [[ ${file##*.} == "png" ]]; then
				./res_des -d $file $file
			elif [[ ${file##*.} == "jpg" ]]; then
				./res_des -d $file $file
			elif [[ ${file##*.} == "jpeg" ]]; then
				./res_des -d $file $file
			elif [[ ${file##*.} == "plist" ]]; then
				./res_des -d $file $file
			elif [[ ${file##*.} == "strings" ]]; then
				./res_des -d $file $file
			elif [[ ${file##*.} == "mdat" ]]; then
				./res_des -d $file $file
			elif [[ ${file##*.} == "data" ]]; then
				./res_des -d $file $file
			fi
		fi
	done
}

restore_file $OUT
