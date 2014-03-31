#!/bin/sh


replace_sheet() {
	DOC=$1
	cd $DOC
	UIFILES=(`ls *.plist`)
	for (( i = 0 ; i < ${#UIFILES[@]} ; i++ ))
	do
		filename=${UIFILES[$i]}
		echo $filename
		sed -i '' 's/png<\/string>/pvr.ccz<\/string>/' $filename
	done
	cd -
}

pro_plist_bin(){
	for file in $1/*
	do 
		if [[ -f $file ]]; then
			if [[ ${file##*.} == "plist" ]]; then
				./plist2binary $file
			fi
		fi
	done
}


## no used follow

process_file() {
	for file in $1/*
	do
		if [[ -d $file ]]; then
			process_file $file
		else 
			if [[ ${file##*.} == "png" ]]; then
				./res_des -e $file $file
			elif [[ ${file##*.} == "jpg" ]]; then
				./res_des -e $file $file
			elif [[ ${file##*.} == "jpeg" ]]; then
				./res_des -e $file $file
			elif [[ ${file##*.} == "plist" ]]; then
				./res_des -e $file $file
			elif [[ ${file##*.} == "strings" ]]; then
				./res_des -e $file $file
			elif [[ ${file##*.} == "mdat" ]]; then
				./res_des -e $file $file
			elif [[ ${file##*.} == "data" ]]; then
				./res_des -e $file $file
			fi
		fi
	done
}



replace() {

	SRC=$1
	DST=$2
	DIR=$3
	
	echo "texturePacker $SRC to $DST in $DIR"
	
	for file in $1/*
	do
		if [ -d $file ]; then
			replace $file
		else 
			if [[ ${file##*.} == "tps" ]]; then
				# sed "s#$1#$2#g" $file > $file
				sed "s#$SRC#$DST#g" $file > $file.bak
				mv -f $file.bak $file
			fi
		fi
	done
}





#sh ./update_ver.sh
#cp  -f ./ver $OUT/public_res/config/
# svn ci ./ver -m "update version for resource.dat"

# svn delete --force  $PROJECT_RESOURCE/resource.dat
# svn ci $PROJECT_RESOURCE -m "del resource.dat"

# process_file $OUT/public_res
#rm -f $PROJECT_RESOURCE/resource.dat
#cd $OUT/public_res
# zip -r $PROJECT_RESOURCE/resource.dat ./* -x "./game/.svn/*" "./ui/.svn/*" "./lang/.svn/*" "./layout/.svn/*" "./config/.svn/*" "./maps/.svn/*" "./layout/iphone/.svn/*" "./music/.svn/*" "./game/card/.svn/*" "./game/magic/.svn/*"
#cd -
# ./restore.sh $OUT/public_res

# mv $OUT/public_res/ui/*_hd* $OUT/res_hd/
