#!/bin/sh

DIR=$1
OPT=$2

echo "texturePacker_img $DIR"

PVR8888=(
goodquality
);

packTexture() {
	for file in $1/*
	do
		if [ -d $file ]; then
			 echo $file
		else 
			if [[ ${file##*.} == "png" ]]; then
				TexturePacker --scale 1.0 --data ${file/.png/.md5.plist} 	--sheet ${file/.png/.pvr.ccz}  --texture-format pvr2ccz	 --padding 0  --disable-rotation --trim-mode None --size-constraints AnySize --opt $OPT $file
				rm $file
			elif [[ ${file##*.} == "jpg" ]]; then
				TexturePacker --scale 1.0 --data ${file/.jpg/.md5.plist} 	--sheet ${file/.jpg/.pvr.ccz}  --texture-format pvr2ccz	 --padding 0  --disable-rotation --trim-mode None --size-constraints AnySize --opt $OPT $file
				rm $file
			fi
		fi
	done
}

packTexture2() {
	for file in $1/*
	do
	  filename=${file##*/}
	  #echo $filename
		if [[ -d $file ]]; then
			 echo $file
		else
			pvrfile=""
			if [[ ${file##*.} == "png" ]]; then
			  pvrfile=${file/.png/.pvr.ccz}
			elif [[ ${file##*.} == "jpg" ]]; then
			  pvrfile=${file/.jpg/.pvr.ccz}
			elif [[ ${file##*.} == "JPG" ]]; then
			  pvrfile=${file/.JPG/.pvr.ccz}
			elif [[ ${file##*.} == "PNG" ]]; then
			  pvrfile=${file/.PNG/.pvr.ccz}
			elif [[ ${file##*.} == "jpeg" ]]; then
			  pvrfile=${file/.jpeg/.pvr.ccz}
			elif [[ ${file##*.} == "JPEG" ]]; then
			  pvrfile=${file/.JPEG/.pvr.ccz}
			fi
			
			if [[ $pvrfile != "" ]]; then
				md5=$(md5 $file | cut -d ' ' -f4)
				md5file=$file.md5
				md5check=''
				if [[ -f $md5file ]]; then
					md5check=$(cat $md5file);
				fi
				if [[ $md5 == $md5check ]]; then
  				filechanged='0'
				else
  				filechanged='1'
	  			echo $md5 > $md5file
				fi
				if [[ $filechanged == '1' ]]; then
					echo ----$OPT : "$filename is changed" : $md5-$md5check-$md5file-
					#TexturePacker --scale 1.0 --sheet $pvrfile $OPTIONS --opt $OPT $file
					TexturePacker --scale 1.0 --sheet $pvrfile  --texture-format pvr2ccz	 --padding 0  --disable-rotation --trim-mode None --size-constraints AnySize --opt $OPT $file
				fi
				rm $file
			fi
		fi
	done
}

packTexture2 $DIR
