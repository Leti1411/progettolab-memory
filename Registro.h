#ifndef REGISTRO_H
#define REGISTRO_H
#include <map>
#include <vector>

#include "Attivita.h"

class Registro{
public:
  Registro();
  std::vector<Attivita> attivita;
  std::map<std::string, std::vector<Attivita>> registro;  //mappa <data, attività>

  void add_attivita(Attivita& attivita, std::string data);
  std::vector<Attivita> get_attivita(std::string data);
};


#endif //REGISTRO_H
