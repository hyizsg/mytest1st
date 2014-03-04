//
//  hpShaders.h
//  HpAnimationDemo
//
//  Created by zhou gang on 14-3-3.
//
//

#ifndef __HpAnimationDemo__hpShaders__
#define __HpAnimationDemo__hpShaders__

#include "CCGL.h"
#include "platform/CCPlatformMacros.h"

#include "Hpheaders.h"

NS_HPAM_BEGIN

extern const GLchar * ccPositionTextureColorExtra_vert;

extern const GLchar * ccPositionTextureColorExtra_HasPremultipliedAlpha_frag;
extern const GLchar * ccPositionTextureColorExtraAlpha_HasPremultipliedAlpha_frag;

/** For android ETC Texture with a same name Alpha texture
 * Ivalid now, to do add
 */
extern const GLchar * ccPositionTextureColorExtra_NoPremultipliedAlpha_frag;
extern const GLchar * ccPositionTextureColorExtraAlpha_NoPremultipliedAlpha_frag;

NS_HPAM_END

#endif /* defined(__HpAnimationDemo__hpShaders__) */
