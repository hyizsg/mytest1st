//
//  hpShaders.cpp
//  HpAnimationDemo
//
//  Created by zhou gang on 14-3-3.
//
//

#include "hpShaders.h"

NS_HPAM_BEGIN

const char* ccPositionTextureColorLight_vert =
"													\n\
attribute vec4 a_position;							\n\
attribute vec2 a_texCoord;							\n\
attribute vec4 a_color;								\n\
attribute vec4 a_light;                             \n\
attribute float a_gray;                             \n\
\n\
#ifdef GL_ES										\n\
varying lowp vec4 v_fragmentColor;					\n\
varying mediump vec2 v_texCoord;					\n\
varying lowp vec4 v_fragmentLight;                  \n\
varying lowp float v_fragmentGray;                  \n\
#else												\n\
varying vec4 v_fragmentColor;						\n\
varying vec2 v_texCoord;							\n\
varying vec4 v_fragmentLight;                       \n\
varying float v_fragmentGray;                       \n\
#endif												\n\
\n\
void main()											\n\
{													\n\
    gl_Position = CC_MVPMatrix * a_position;		\n\
    v_fragmentColor = a_color;						\n\
    v_texCoord = a_texCoord;						\n\
    v_fragmentLight = a_light;                      \n\
    v_fragmentGray = a_gray;                        \n\
}													\n\
";

///
// texture->hasPremultipliedAlpha = true
//
const char* ccPositionTextureColorLight_HasPremultipliedAlpha_frag =
"											\n\
#ifdef GL_ES								\n\
precision lowp float;						\n\
#endif										\n\
\n\
varying vec4 v_fragmentColor;				\n\
varying vec2 v_texCoord;					\n\
varying vec4 v_fragmentLight;               \n\
varying float v_fragmentGray;               \n\
uniform sampler2D CC_Texture0;				\n\
\n\
void main()									\n\
{											\n\
    vec4 texcol = texture2D(CC_Texture0, v_texCoord);               \n\
    vec4 light = v_fragmentLight * v_fragmentColor.a * texcol.a;    \n\
    light.a = 0.0;                                                  \n\
    vec4 fragcol = v_fragmentColor * texcol + light;                \n\
    \n\
    float grey = dot(fragcol.rgb, vec3(0.299, 0.587, 0.114));       \n\
    fragcol.rgb = vec3(grey, grey, grey) * v_fragmentGray + fragcol.rgb * (1.0-v_fragmentGray); \n\
    \n\
    gl_FragColor = fragcol;                 \n\
}\n\
";



const char* ccPositionTextureColorLightAlpha_HasPremultipliedAlpha_frag =
"											\n\
#ifdef GL_ES								\n\
precision lowp float;						\n\
#endif										\n\
\n\
varying vec4 v_fragmentColor;				\n\
varying vec2 v_texCoord;					\n\
varying vec4 v_fragmentLight;				\n\
varying float v_fragmentGray;               \n\
uniform sampler2D CC_Texture0;				\n\
uniform sampler2D CC_TexAlpha;              \n\
\n\
void main()									\n\
{											\n\
    vec4 texcol = texture2D(CC_Texture0, v_texCoord);               \n\
    texcol *= texture2D(CC_TexAlpha, v_texCoord).a;                 \n\
    vec4 light = v_fragmentLight * v_fragmentColor.a * texcol.a;    \n\
    light.a = 0.0;                                                  \n\
    vec4 fragcol = v_fragmentColor * texcol + light;                \n\
    \n\
    float grey = dot(fragcol.rgb, vec3(0.299, 0.587, 0.114));       \n\
    fragcol.rgb = vec3(grey, grey, grey) * v_fragmentGray + fragcol.rgb * (1.0-v_fragmentGray); \n\
    \n\
    gl_FragColor = fragcol;                 \n\
}\n\
";


////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
// texture->hasPremultipliedAlpha = false
//
const char* ccPositionTextureColorLight_NoPremultipliedAlpha_frag =
"											\n\
#ifdef GL_ES								\n\
precision lowp float;						\n\
#endif										\n\
\n\
varying vec4 v_fragmentColor;				\n\
varying vec2 v_texCoord;					\n\
varying vec4 v_fragmentLight;				\n\
varying float v_fragmentGray;               \n\
uniform sampler2D CC_Texture0;				\n\
\n\
void main()									\n\
{											\n\
    vec4 texcol = texture2D(CC_Texture0, v_texCoord);               \n\
    vec4 light = v_fragmentLight;                                   \n\
    light.a = 0.0;                                                  \n\
    vec4 fragcol = v_fragmentColor * texcol + light;                \n\
    \n\
    float grey = dot(fragcol.rgb, vec3(0.299, 0.587, 0.114));       \n\
    fragcol.rgb = vec3(grey, grey, grey) * v_fragmentGray + fragcol.rgb * (1.0-v_fragmentGray); \n\
    \n\
    gl_FragColor = fragcol;                 \n\
}\n\
";



const char* ccPositionTextureColorLightAlpha_NoPremultipliedAlpha_frag =
"											\n\
#ifdef GL_ES								\n\
precision lowp float;						\n\
#endif										\n\
\n\
varying vec4 v_fragmentColor;				\n\
varying vec2 v_texCoord;					\n\
varying vec4 v_fragmentLight;				\n\
varying float v_fragmentGray;               \n\
uniform sampler2D CC_Texture0;				\n\
uniform sampler2D CC_TexAlpha;              \n\
\n\
void main()									\n\
{											\n\
    vec4 texcol = texture2D(CC_Texture0, v_texCoord);               \n\
    texcol.a = texture2D(CC_TexAlpha, v_texCoord).a;                \n\
    vec4 light = v_fragmentLight;                                   \n\
    light.a = 0.0;                                                  \n\
    vec4 fragcol = v_fragmentColor * texcol + light;                \n\
    \n\
    float grey = dot(fragcol.rgb, vec3(0.299, 0.587, 0.114));       \n\
    fragcol.rgb = vec3(grey, grey, grey) * v_fragmentGray + fragcol.rgb * (1.0-v_fragmentGray); \n\
    \n\
    gl_FragColor = fragcol;                 \n\
}\n\
";


NS_HPAM_END
