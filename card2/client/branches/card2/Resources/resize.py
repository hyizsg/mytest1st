#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys,os
import PIL
import Image
import _imaging
# from biplist import *
#from datetime import datetime

scaleX = 0.5
scaleY = 0.5
src = ""
dst = ""
if len(sys.argv) > 4:
    scaleX = sys.argv[3]
    scaleY = sys.argv[4]
elif len(sys.argv) > 2:
    src = sys.argv[1]
    dst = sys.argv[2]
else:
    print "resize.py src dst [scaleX, scaleY]"
    sys.exit(0)

print "resize:", src, " to ", dst, " scale:", scaleX, ", ", scaleY

# def processMetadata(metadata):
#     size = metadata["size"]
#     textureFileName = metadata["textureFileName"]
#     format = metadata["format"]
#     print "size:", size, ", file:", textureFileName, ", format:", format
#     return textureFileName
    
# def processFrames(frames, img):
#     print len(frames)
#     for filename in frames:
#         data = frames[filename];
#         fx, fy, fw, fh = data["frame"].replace('{','').replace('}','').split(',')
#         rotated = data["rotated"]
#         scx, scy, scw, sch = data["sourceColorRect"].replace('{','').replace('}','').split(',')
#         sw, sh = data["sourceSize"].replace('{','').replace('}','').split(',')
#         offx, offy = data["offset"].replace('{','').replace('}','').split(',')
        
#         if rotated: 
#             box = (int(fx),int(fy),int(fx)+int(fh),int(fy)+int(fw))
#         else:
#             box = (int(fx),int(fy),int(fx)+int(fw),int(fy)+int(fh))
#         subImg = img.crop(box)
#         if rotated: subImg = subImg.transpose(Image.ROTATE_90)
#         #    subImg = subImg.rotate(90, Image.BILINEAR)
#         subImg.save("output/"+filename.split('.')[0]+".png")
        
def main():
    img = Image.open(src)
    print img.size
    width, height = img.size
    print "W:", width, ", H:", height
    targetImg = img.resize(((int)(width * scaleX), (int)(height * scaleY)), Image.ANTIALIAS) #Image.BILINEAR
    targetImg.save(dst);
    # try:
    #     if len(src) > 1:
    #         plist = readPlist(src)
    #     else:
    #         plist = readPlist("object1.plist")
    #     os.system("mkdir -p output")
    #     metadata = plist["metadata"]
    #     textureFileName = processMetadata(metadata)
        
    #     frames = plist["frames"]
    #     img = Image.open(textureFileName)
    #     print img.size
    #     processFrames(frames, img)
        
    # except (InvalidPlistException, NotBinaryPlistException), e:
    #     print "Not a plist", e

if __name__ == '__main__':
    main()