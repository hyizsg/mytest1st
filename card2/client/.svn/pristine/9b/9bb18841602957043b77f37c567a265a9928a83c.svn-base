#!/bin/sh

DIR=$1
OUTH=$2
OUTL=$3
ARG=$4


echo "texturePacker $DIR"
echo "texturePacker $OUT"

packTexturePng() {
	for file in $1/*
	do
		if [ -d $file ]; then
			texturePacker $file
		else 
			if [[ ${file##*.} == "tps" ]]; then
				TexturePacker --scale 1.0 --data $OUTH${file/_hd.tps/.plist} 	--sheet $OUTH${file/_hd.tps/.png}	 	$file
				TexturePacker --scale 0.5 --data $OUTH${file/_hd.tps/_ld.plist} --sheet $OUTH${file/_hd.tps/_ld.png} 	$file
				TexturePacker --scale 0.5 --data $OUTL${file/_hd.tps/.plist} 	--sheet $OUTL${file/_hd.tps/.png} 		$file
			fi
		fi
	done
}

packTexturePvr() {
	for file in $1/*
	do
		if [ -d $file ]; then
			texturePacker $file
		else 
			if [[ ${file##*.} == "tps" ]]; then
				TexturePacker --scale 1.0 --data $OUTH${file/_hd.tps/.plist} 		--sheet $OUTH${file/_hd.tps/.pvr.ccz}  		--texture-format pvr2ccz --size-constraints AnySize $file
				TexturePacker --scale 0.5 --data $OUTH${file/_hd.tps/_ld.plist} 	--sheet $OUTH${file/_hd.tps/_ld.pvr.ccz}  	--texture-format pvr2ccz --size-constraints AnySize $file
				TexturePacker --scale 0.5 --data $OUTL${file/_hd.tps/.plist} 		--sheet $OUTL${file/_hd.tps/.pvr.ccz}  		--texture-format pvr2ccz --size-constraints AnySize $file
			fi
		fi
	done
}

packTexturePvr4() {
	for file in $1/*
	do
		if [ -d $file ]; then
			texturePacker $file
		else 
			if [[ ${file##*.} == "tps" ]]; then
				TexturePacker --scale 1.0 --data $OUTH${file/_hd.tps/.plist} 		--sheet $OUTH${file/_hd.tps/.pvr.ccz} 		--texture-format pvr2ccz	--opt PVRTC4 $file
				TexturePacker --scale 0.5 --data $OUTH${file/_hd.tps/_ld.plist} 	--sheet $OUTH${file/_hd.tps/_ld.pvr.ccz} 	--texture-format pvr2ccz	--opt PVRTC4 $file
				TexturePacker --scale 0.5 --data $OUTL${file/_hd.tps/.plist} 		--sheet $OUTL${file/_hd.tps/.pvr.ccz} 		--texture-format pvr2ccz  	--trim-mode None 	--size-constraints AnySize $file
			fi
		fi
	done
}

packTexturePvr16() {
	for file in $1/*
	do
		if [ -d $file ]; then
			texturePacker $file
		else 
			if [[ ${file##*.} == "tps" ]]; then
				TexturePacker --scale 1.0 --data $OUTH${file/_hd.tps/.plist} 		--sheet $OUTH${file/_hd.tps/.pvr.ccz}  		--texture-format pvr2ccz --opt RGBA4444 --dither-fs-alpha $file
				TexturePacker --scale 0.5 --data $OUTH${file/_hd.tps/_ld.plist} 	--sheet $OUTH${file/_hd.tps/_ld.pvr.ccz}  	--texture-format pvr2ccz --opt RGBA4444 --dither-fs-alpha $file
				TexturePacker --scale 0.5 --data $OUTL${file/_hd.tps/.plist} 		--sheet $OUTL${file/_hd.tps/.pvr.ccz}  		--texture-format pvr2ccz --opt RGBA4444 --dither-fs-alpha $file
			fi
		fi
	done
}


if [ -z $ARG ]; then
	ARG="Png" 
fi

case "$ARG" in 
	Png)
		packTexturePng $DIR
		;;
	Pvr)
		packTexturePvr $DIR
		;;
	Pvr4)
		packTexturePvr4 $DIR
		;;
	Pvr16)
		packTexturePvr16 $DIR
		;;
	*)
esac

