#ifndef PDS2_AQUECEDOR_H
#define PDS2_AQUECEDOR_H

class Aquecedor{
private:
  double temperatura, temp_minima, temp_maxima, fat_inc;

public:
  Aquecedor();
  Aquecedor(double);
  Aquecedor(double, double);
  void aquecer();
  void resfriar();
  double get_temperatura();
  void set_fator_incremento(double);
};

#endif
