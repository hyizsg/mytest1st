#!/bin/sh

DOC=$(PWD)/../../../../docs
LANG_FILE=$DOC/策划文档/数值/
OUT=$(PWD)/out
PROJECT_RESOURCE=$(PWD)/../proj.ios/Resources

cd $OUT

mv -f public_res.zip public_res.bak.zip
zip  -r public_res.zip public_res

cd -


rm $OUT/public_res/ui/*.plist
rm $OUT/public_res/ui2/*.plist

rm $OUT/public_res/game/*.plist
rm $OUT/public_res/game/*.xml
rm $OUT/public_res/game/*.md5
rm $OUT/public_res/game/*.xlsx
rm $OUT/public_res/game/img/*.md5
