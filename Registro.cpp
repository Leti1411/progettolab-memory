#include "Registro.h"
#include "Attivita.h"

Registro::Registro() {}

Attivita* attivita;
void Registro::add_attivita(Attivita *nuova_attivita, std::string orario_scelto) {
      registro[orario_scelto] = nuova_attivita;
}
Attivita* Registro::get_attivita(std::string orario_scelto) {
      return registro[orario_scelto];
}






