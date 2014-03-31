#!/bin/sh

src=$(PWD)/Classes
dst=$(PWD)/fileList.txt

rm -f dst

append_str=' \'

list_alldir() {
    for file in $1/*
    do
        if [ -f $file ]; then
            if [[ ${file##*.} == "cpp" ]];then
                echo '                   $(SRC_PATH)'${file##*$src}' \' #> dst
            elif [[ ${file##*.} == "c" ]]; then
                echo '                   $(SRC_PATH)'${file##*$src}' \' #> dst
            fi

            # echo $file$append_str | grep .cpp
        fi
        
        if [ -d $file ]; then
            list_alldir $file            
        fi
    done     
}

if [ $# -gt 0 ]; then
    list_alldir "$1"
else
    list_alldir $src
fi
