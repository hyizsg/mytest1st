
/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 */

#include "ccColorExtension.h"

ccColor4F cccLerp(ccColor4F p_a, ccColor4F p_b, float p_alpha){
    return cccAdd(cccScale(p_a, 1.f - p_alpha), cccScale(p_b, p_alpha));
}

ccColor4F cccAdd(ccColor4F p_a, ccColor4F p_b){
    return ccc4f(p_a.r + p_b.r, p_a.g + p_b.g, p_a.b + p_b.b, p_a.a + p_b.a);
}

ccColor4F cccMult(ccColor4F p_a, ccColor4F p_b){
    return ccc4f(p_a.r * p_b.r, p_a.g * p_b.g, p_a.b * p_b.b, p_a.a * p_b.a);
}

ccColor4F cccScale(ccColor4F p_a, float p_s){
    return ccc4f(p_a.r * p_s, p_a.g * p_s, p_a.b * p_s, p_a.a * p_s);
}
