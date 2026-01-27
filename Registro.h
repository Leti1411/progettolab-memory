#ifndef REGISTRO_H
#define REGISTRO_H
#include <map>

#include "Attivita.h"

class Registro{
  public:
  Registro();
  Attivita* attivita;
  std::map<std::string, Attivita*> registro;  //mappa <giorno, attività>
  void add_attivita(Attivita* attivita, std::string orario_scelto);
  Attivita* get_attivita(std::string orario_scelto);


};



#endif //REGISTRO_H
