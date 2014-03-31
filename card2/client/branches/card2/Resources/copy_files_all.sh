#!/bin/sh

DOC=$1
OUT=$2

echo "copy_files $DOC to $OUT"


mkdir -p $OUT/public_res/game/img
mkdir -p $OUT/public_res/game/effect

./copy_files.sh $DOC $OUT


cp -rf $DOC/act/临时美术资源/特效/effect* $OUT/public_res/game/
cp -rf $DOC/act/临时美术资源/特效/法宝/magic* $OUT/public_res/game/
cp -rf $DOC/act/临时美术资源/特效/UI/effect* $OUT/public_res/game/
cp -rf $DOC/act/临时美术资源/特效/剧情动画/story* $OUT/public_res/game/
cp -rf $DOC/act/临时美术资源/特效/圣诞节/ui_mc* $OUT/public_res/game/
cp -rf $DOC/act/临时美术资源/特效/春节/ui_ny* $OUT/public_res/game/
cp -rf $DOC/act/临时美术资源/特效/门派/ui_mp* $OUT/public_res/game/

#cp -rf $DOC/act/UI/小助手/960/xzs_zixia.png	$OUT/public_res/game/


mv -f $OUT/public_res/game/effect_ui_askgod*  	$OUT/public_res/game/effect/
#mv -f $OUT/public_res/game/story* 				$OUT/public_res/game/effect/ 


cp -rf $DOC/act/UI/四象/960/sx_bg?.jpg  $OUT/public_res/game/img/
#cp -rf $DOC/act/UI/四格/sg_00?.png  $OUT/public_res/game/img/


cp -rf $DOC/act/UI/关卡/960/gk_paper.jpg		$OUT/public_res/game/img/
cp -rf $DOC/act/UI/关卡/960/gk_paper2.png		$OUT/public_res/game/img/
cp -rf $DOC/act/UI/主界面/960/zjm_bg.jpg		$OUT/public_res/game/img/
cp -rf $DOC/act/临时美术资源/特效/圣诞节/zjm_mc_bg.jpg		$OUT/public_res/game/img/
