#include "HX711.h"

class Load_cell{

  public:
    HX711 scale;
    int dt_pin, sck_pin;
    float scale_val;

    Load_cell(int dtpin, int sckpin, float scaleval) : dt_pin(dtpin), sck_pin(sckpin), scale_val(scaleval){
    }

    void init(){

      scale.begin(dt_pin, sck_pin);   //initialize scale
      scale.set_scale(scale_val);      // set calibration value
      scale.tare();                   //

    }

    int weight(){

      float x = scale.get_units(10);
      int y = x*100;
      return y;
    }

}