#include "Registro.h"
#include "Attivita.h"
#include <vector>
#include <algorithm>


      Registro::Registro() {}
      void Registro::add_attivita(Attivita &nuova_attivita, std::string data) {
            if (!nuova_attivita.orarioValido()){ return;}
            registro[data].push_back(nuova_attivita);
            std::sort(registro[data].begin(), registro[data].end());
      }
      std::vector<Attivita> Registro::get_attivita(std::string data) {
            return registro[data];
      }







