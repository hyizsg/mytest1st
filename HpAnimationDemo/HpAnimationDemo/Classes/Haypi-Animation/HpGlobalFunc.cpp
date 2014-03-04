/**
 * @author mingjiang.bai@gmail.com
 * @date 20121213
 *
 *
 */

#include "HpGlobalFunc.h"
#include "cstdlib"

using namespace std;

NS_CC_BEGIN

CCPoint makeCCPointFromString(char *p_string){
    CCPoint ret = CCPointZero;
    do{
        float x, y;
        char* items = strtok(p_string, ",");
        if(items == NULL)
            break;
        x = (float)atof(items);
        items = strtok(NULL, ",");
        if(items != NULL)
            break;
        y = (float)atof(items);

        ret = CCPointMake(x, y);
    } while(0);

    return ret;
}

double sign(double x){
    return x > 1e-6 ? 1.0 : x< -1e-6 ? -1.0 : 0;
}


NS_HPAM_END