#ifndef REGISTRO_H
#define REGISTRO_H
#include <map>
#include <vector>


#include "Attivita.h"

class Registro {
public:
  Registro();
  std::vector<Attivita> attivita;


  void add_attivita(Attivita& attivita, std::string data);
  bool remove_attivita(int indice, std::string data);
  std::vector<Attivita> get_attivita(std::string data);
  std::map<std::string, std::vector<Attivita>> show_tuttoRegistro() const;

private:
  std::map<std::string, std::vector<Attivita>> registro;
};


#endif //REGISTRO_H
