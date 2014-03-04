/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 */
#ifndef CCCOLOREXTENSION_H
#define CCCOLOREXTENSION_H

#include "ccTypes.h"
#include "cocos2d.h"

USING_NS_CC;

extern ccColor4F cccLerp(ccColor4F p_a, ccColor4F p_b, float p_f);
extern ccColor4F cccAdd(ccColor4F p_a, ccColor4F p_b);
extern ccColor4F cccMult(ccColor4F p_a, ccColor4F p_b);
extern ccColor4F cccScale(ccColor4F p_a, float p_s);

static const ccColor4F ccWhite4F = {1.f, 1.f, 1.f, 1.f};
static const ccColor4F ccClear4F = {0.f, 0.f, 0.f, 0.f};

#endif // CCCOLOREXTENSION_H
