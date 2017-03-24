

/* 
Extends the Smooth library doing a linear conversion of readings, to transform mV (as from Smooth) to fisical units uning a linear equation: y = m*x + q:
   x = the avg mV value
   y = the fisical value
   m = default 1.0 (scale factor)
   q = default 0.0 (offset)
 TaraturePoint(), for user interactive tarature.
 Tarature can be done also programmatically - see begin(q,m) and 
    tarature4Point(fromLow, fromHigh, toLow, toHigh)
 The function dataReady() returns TRUE only if the first interactive tarature was done.
 The function get() returns the fisical value, getSmooth() returns the Avg value
 Uses Smooth lib: https://github.com/msillano/Arduino-library-smooth
*/

#include <Linear.h>

Linear::Linear(int points, int refmV)
  :  Smooth(points, refmV)  {
    m = 1.0;
    q = 0.0;
    count = 0;
}

float Linear::get() {
    return ((Smooth::get() * m) + q);
}

float Linear::getSmooth() {
    return  Smooth::get();
}

void Linear::begin(float scale, float offset) {
    if (scale != 0.0){
        tarature4Point(1.0, 100.0, (1.0 * scale) + offset, (100.0 * scale) + offset) ;
    }
}


// like map(), but using 4 float
void  Linear::tarature4Point(float fromLow, float fromHigh, float toLow, float toHigh) {
    if ((fromLow !=  fromHigh) && (toLow != toHigh)) {
        avgVal[0] = fromLow;
        avgVal[1] = fromHigh;
        tara[0] = toLow;
        tara[1] = toHigh;
        _adjust();
        count = 0;
    }
} 

// true if done some interactive taratures
int  Linear::dataReady() {
    return ( available() ? count : 0);
}

// get infos about interactive taratures
String  Linear::getTarature() {
    switch (count) {
        case 0:
            return ("Default tarature: m=" + String(m) + " q=" + String(q));
        case 1:
            return ("1 point @" + String( tara[1]));
        case 2:
            return ("2 points, last @" + String( tara[1]));
        default:
            return ("3+ points, last @" + String( tara[1]));
  }
}

// interactive taratures
void  Linear::taraturePoint(float val) {
   float vx = Smooth::get();
   if ((val != tara[1]) && (vx != avgVal[1])) {
        tara[0]   = tara[1];
        avgVal[0] = avgVal[1];      
        avgVal[1] = vx;
        tara[1]   = val;
        _adjust(1);
        if ( count < 3) {
            count++;
        }
    }
 }

void  Linear::_adjust(int avg) {
  float m1 = ( tara[0] -  tara[1]) / ( avgVal[0] -  avgVal[1]);
  float q1 =   tara[1] -  (m1 * avgVal[1]);
  // avg
  if (avg) {
    m = (m + 2 * m1) / 3.0;
    q = (q + 2 * q1) / 3.0;
    } else {
    m = m1;
    q = q1;
    }
 }
