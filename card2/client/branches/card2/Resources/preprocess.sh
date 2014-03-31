#!/bin/sh

# next 4 values must be configured according to your project
DOC=$(PWD)/../../../../docs
LANG_FILE=$DOC/策划文档/数值/BattleShip多语言.xls
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
mkdir -p $OUT/public_res/lang/
mkdir -p $OUT/public_res/game/
mkdir -p $OUT/public_res/config/
mkdir -p $OUT/public_res/maps/
mkdir -p $OUT/public_res/music/



./copy_files.sh $DOC $OUT

