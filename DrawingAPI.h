#include"cppH.h"

class DrawingAPI {
  public:
   virtual void drawCircle(double x, double y, double radius) = 0;
   virtual ~DrawingAPI() {}
};


class DrawingAPI1 : public DrawingAPI {
  public:
   void drawCircle(double x, double y, double radius);/* {
      cout << "API1.circle at " << x << ':' << y << ' ' << radius << endl;
   }*/
};

/* Concrete ImplementorB*/
class DrawingAPI2 : public DrawingAPI {
public:
   void drawCircle(double x, double y, double radius);/* {
      cout << "API2.circle at " << x << ':' << y << ' ' <<  radius << endl;
   }*/
};
