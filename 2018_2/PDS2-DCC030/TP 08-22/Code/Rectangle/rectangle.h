#ifndef PDS2_VPL_RECT_H
#define PDS2_VPL_RECT_H

class Rectangle{
private:
  float width, height;

public:
  Rectangle(float, float);
  Rectangle();
  float get_width();
  float get_height();
  void set_width(float);
  void set_height(float);
  float get_perimeter();
  float get_area();
};

#endif
