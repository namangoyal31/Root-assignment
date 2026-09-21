#ifndef _MYEVENT_
#define _MYEVENT_
#include <iostream>
#include "TObject.h"

class MyEvent{
 public:
  MyEvent(){ px = 0; py = 0; pt = 0;};
  virtual ~MyEvent(){};

  void setPx(float x_){ px = x_;};
  void setPy(float y_){ py = y_;};
  void setPt(float t_){ pt = t_;};

  float getPx(){return px;};
  float getPy(){return py;};
  float getPt(){return pt;};

 private:
  float px;
  float py;
  float pt;
  ClassDef(MyEvent,1)
};
#endif
