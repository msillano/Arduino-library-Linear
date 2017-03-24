#ifndef Linear_h
#define Linear_h

#include <Smooth.h>

class Linear : public Smooth {
  private:
    float avgVal[2];
    float tara[2];
    float m;
    float q;
    int count;
    void _adjust(int avg = 0);
    
  public:
    Linear(int points, int refmV = 5000);
    void begin(float scale = 1.0, float offset = 0.0);
    void tarature4Point(float fromLow, float fromHigh, float toLow, float toHigh);
    void taraturePoint(float val);
    int dataReady();
    float get();

    float getSmooth();
    String getTarature();

};

#endif
