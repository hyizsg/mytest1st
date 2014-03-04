#include "Hpheaders.h"

NS_HPAM_BEGIN

const char* skip_file_prefix(const char* path,size_t n) {

    char* _path = (char*)path;
    int from = strlen(path) - n;

    if( from > 0 )
        return _path + from;
    else
        return _path;
}



NS_HPAM_END