
#include "HpSplineInterpolator.h"
#include "HpGlobalFunc.h"
#include "Hpheaders.h"

#include "cmath"



using namespace std;
NS_HPAM_BEGIN


CCDictionary* HpSplineInterp::tires = NULL;

double HpSplineInterp::conventX2Time(double x){
    double a = -P0.x + 3.0 * P1.x - 3.0 * P2.x + P3.x;
    double b = 3.0 * P0.x - 6.0 * P1.x + 3.0 * P2.x;
    double c = -3.0 * P0.x + 3.0 * P1.x;
    double d = P0.x - x;

    double A = b * b - 3.0 * a * c;
    double B = b * c - 9.0 * a * d;
    double C = c * c - 3.0 * b * d;
    double delta = B * B - 4.0 * A * C;

    // 当A=B=0时，盛金公式①：
    // X1=X2=X3=－b/(3a)=－c/b=－3d/c。
    if (fabs(A) < 1e-6 && fabs(B) < 1e-6){
        return -c / b;
    }

    // 当Δ=B^2－4AC=0时，盛金公式③：
    // X1=－b/a+K；X2=X3=－K/2，
    // 其中K=B/A，(A≠0)。
    if (abs(delta) < 1e-6) {
        if (abs(A) > 1e-6) {
            double K = B / A;
            double X1 = -b / a + K;
            double X2 = -K / 2.0;

            return X1 >= 0 && X1 <= 1 ? X1 : X2;
        }
    }

    // 当Δ=B^2－4AC>0时，盛金公式②：
    // X1=(－b－(Y1)^(1/3)－(Y2)^(1/3))/(3a)；
    // X2，X3=(－2b+(Y1)^(1/3)+(Y2)^(1/3))/(6a)±3^(1/2)((Y1)^(1/3)－(Y2)^(1/3))i/(6a)，
    // 其中Y1，Y2=Ab+3a(－B±(B^2－4AC)^(1/2))/2，i^2=－1。
    if (delta > 0) {
        double Y1 = A * b + 3.0 * a * (-B + sqrt(delta)) / 2.0;
        double Y2 = A * b + 3.0 * a * (-B - sqrt(delta)) / 2.0;
        return (-b - sign(Y1) * pow(fabs(Y1), 1.0 / 3.0) - sign(Y2) * pow(fabs(Y2), 1.0 / 3.0)) / (3.0 * a);
    }

    // 当Δ=B^2－4AC<0时，盛金公式④：
    // X1=(－b－2A^(1/2)cos(θ/3))/(3a)；
    // X2，X3=(－b+A^(1/2)(cos(θ/3)±3^(1/2)sin(θ/3)))/(3a)，
    // 其中θ=arccosT，T= (2Ab－3aB)/(2A^(3/2))，(A>0，－1<T<1)。
    if (delta < 0) {
        if (A > 1e-6) {
            double T = (2.0 * A * b - 3.0 * a * B) / (2.0 * pow(A, 3.0 / 2.0));
            if (T > -1 && T < 1) {
                double theta = acos(T) / 3.0;
                double X1 = (-b - 2.0 * sqrt(A) * cos(theta / 3.0)) / (3 * a);
                double X2 = (-b + sqrt(A) * (cos(theta) + sqrt(3.0) * sin(theta))) / (3.0 * a);
                double X3 = (-b + sqrt(A) * (cos(theta) - sqrt(3.0) * sin(theta))) / (3.0 * a);

                return X1 >= 0 && X1 <= 1 ? X1 : X2 >= 0 && X2 <= 1 ? X2 : X3;
            }
        }
    }

    return x;
}


HpSplineInterp* HpSplineInterp::interp(CCString *p_ctrlpts){
    if(tires == NULL){
        tires = CCDictionary::create();
    }

    HpSplineInterp* spline = dynamic_cast<HpSplineInterp*> (tires->objectForKey(p_ctrlpts->getCString()));
    if(spline == NULL){
        spline = new HpSplineInterp;
//        spline->autorelease();
        HP_AUTO_RELEASE(spline);

        CCArray* splits = CCArray::create();
        char* items = strtok(const_cast<char*>(p_ctrlpts->getCString()), " ");
        while(items){
            splits->addObject(CCString::create(items));
            items = strtok(NULL, " ");
        }

        if(splits->count() >= 2){
            CCString* pStr1 = dynamic_cast<CCString*>(splits->objectAtIndex(0));
            CCString* pStr2 = dynamic_cast<CCString*>(splits->objectAtIndex(1));
            spline->P0 = CCPointMake(0, 0);
            spline->P1 = CCPointFromString(pStr1->getCString());
            spline->P2 = CCPointFromString(pStr2->getCString());
            spline->P3 = CCPointMake(1, 1);
        }
        tires->setObject(spline, p_ctrlpts->getCString());
    }

    return spline;
}

HpSplineInterp* HpSplineInterp::interp(float x1, float y1, float x2, float y2)
{
    CCString* ctrlpts = CCString::createWithFormat("{%.3f,%.3f} {%.3f,%.3f}", x1, y1, x2, y2);
    if (tires == NULL) {
        tires = new CCDictionary();
    }
    
    HpSplineInterp* spline = (HpSplineInterp*)tires->objectForKey(ctrlpts->m_sString);
    if (spline == NULL) {
        spline = new HpSplineInterp();
        spline->P0  = CCPointMake(0, 0);
        spline->P1.x = x1; spline->P1.y = y1;
        spline->P2.x = x2; spline->P2.y = y2;
        spline->P3 = CCPointMake(1, 1);
        tires->setObject(spline, ctrlpts->m_sString);
        spline->release();
    }
    
    return spline;
}

void HpSplineInterp::Purge(){
    tires->release();
    tires = NULL;
}


float HpSplineInterp::getFactorWithStart(int p_t1, int p_t2, float p_t){
    double x = (p_t - p_t1) * 1.0 / (p_t2 - p_t1);
    double t = conventX2Time(x);

    double factor = P0.y * ((1 - t) * (1 - t) * (1 - t))
            + P1.y * (3.0 * t * (1 - t) * (1 - t))
            + P2.y * (3.0 * t * t * (1 - t))
            + P3.y * (t * t * t);

    return factor;
}


NS_HPAM_END

