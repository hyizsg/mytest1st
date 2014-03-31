#!/bin/sh

while read one
do
	str=$one
done < ./ver

echo "old ver: $str"

ver=$((${str}+1))

echo $ver > ./ver

echo "new ver: $ver"
