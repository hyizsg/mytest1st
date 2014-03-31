#!/bin/sh

# next 4 values must be configured according to your project
DOC=$(PWD)/../../../../docs
LANG_FILE=$DOC/策划文档/数值/
OUT=$(PWD)/out
PROJECT_RESOURCE=$(PWD)/../proj.ios/Resources

echo "DOC: $DOC"
echo "LANG_FILE: $LANG_FILE"
echo "OUT: $OUT"
echo "PROJECT_RESOURCE: $PROJECT_RESOURCE"

cd $DOC
svn up
cd -

mkdir -p $OUT/public_res/layout/
mkdir -p $OUT/public_res/ui/
mkdir -p $OUT/public_res/ui2/
mkdir -p $OUT/public_res/lang/
mkdir -p $OUT/public_res/game/
mkdir -p $OUT/public_res/config/
mkdir -p $OUT/public_res/maps/
mkdir -p $OUT/public_res/music/

mkdir -p $OUT/public_res_ld/layout/
mkdir -p $OUT/public_res_ld/ui/
mkdir -p $OUT/public_res_ld/ui2/
mkdir -p $OUT/public_res_ld/lang/
mkdir -p $OUT/public_res_ld/game/
mkdir -p $OUT/public_res_ld/config/
mkdir -p $OUT/public_res_ld/maps/
mkdir -p $OUT/public_res_ld/music/


./copy_files_all.sh $DOC $OUT


cd ./TexturePackers

 	./texturePacker_pvr_img.sh $OUT/public_res/game  		PVRTC4
 	./texturePacker_pvr_img.sh $OUT/public_res/game/effect  RGBA8888
 	./texturePacker_pvr_img.sh $OUT/public_res/game/img    	PVRTC4
	./texturePacker.sh ./ui $OUT/public_res/ $OUT/public_res_ld/ Png
	./texturePacker.sh ./ui2 $OUT/public_res/ $OUT/public_res_ld/ Png
	
	#./texturePacker_pvr_img.sh $OUT/public_res/game  		Png
 	#./texturePacker_pvr_img.sh $OUT/public_res/game/effect  Png
 	#./texturePacker_pvr_img.sh $OUT/public_res/game/img    	Png
	#./texturePacker.sh ./ui $OUT/public_res/ $OUT/public_res_ld/ Png
	#./texturePacker.sh ./ui2 $OUT/public_res/ $OUT/public_res_ld/ Png

cd -


mv -f $OUT/public_res/game/effect/* $OUT/public_res/game/

#加载函数文件
source $PWD/function.sh

#替换plist文件sheet: png->pvr.ccz
replace_sheet $OUT/public_res/game


#转换plist为plistb的二进制文件
pro_plist_bin $OUT/public_res/ui
pro_plist_bin $OUT/public_res/ui2
pro_plist_bin $OUT/public_res/game




