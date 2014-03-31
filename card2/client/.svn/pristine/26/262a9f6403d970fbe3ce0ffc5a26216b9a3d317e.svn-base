#!/bin/sh

DOC=$1
OUT=$2

echo "copy_files $DOC to $OUT"

mkdir -p $OUT/public_res/layout/iphone
mkdir -p $OUT/public_res/game/img
mkdir -p $OUT/public_res/game/skill

cp -rf ./CCBuilder/Publish-IOS/iphone/*.ccbi $OUT/public_res/layout/iphone/

cp -rf ./TmpPlist/*.png $OUT/public_res/ui/
cp -rf ./TmpPlist/*.plist $OUT/public_res/ui/

cp -rf $DOC/act/UI/skillicon/new/*    $OUT/public_res/game/skill/
#cp -rf $DOC/act/UI/开始界面/960/Default*  $OUT/../../proj.ios/

cp -rf $DOC/design_docs/数值/out3/*.txt $OUT/public_res/config/


mkdir -p $OUT/public_res/game/card
mkdir -p $OUT/public_res/game/magic

cp -rf $DOC/act/UI/card/960/*_*_*.png $OUT/public_res/game/card/
cp -rf $DOC/act/卡牌内容/卡片大图*/*_a.jpg $OUT/public_res/game/card/
cp -rf $DOC/act/卡牌内容/卡片中图*/*_b.jpg $OUT/public_res/game/card/
cp -rf $DOC/act/卡牌内容/卡片小图*/*_c.jpg $OUT/public_res/game/card/

cp -rf $DOC/act/卡牌内容/*法宝*/*.png $OUT/public_res/game/magic/
cp -rf $DOC/act/卡牌内容/*法宝*/*.jpg $OUT/public_res/game/magic/


cp -rf $DOC/act/音乐音效/*.mp3 $OUT/public_res/music/

#cp -rf $DOC/act/临时美术资源/特效/effects*.chr $OUT/public_res/game/
#cp -rf $DOC/act/临时美术资源/特效/法宝/magic*.chr $OUT/public_res/game/
#cp -rf $DOC/act/临时美术资源/特效/UI/effect*.chr $OUT/public_res/game/
#


rm -rf $OUT/public_res/config/commodity_base.txt
rm -rf $OUT/public_res/config/LootLib.txt