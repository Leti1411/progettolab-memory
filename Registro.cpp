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
      bool Registro::remove_attivita(int indice, std::string data){

            if (registro.find(data) == registro.end()) {
                  return false;
            }
            std::vector<Attivita>& listaData = registro[data];

            if (indice < 0 || indice >= listaData.size()) {
                  return false;
            }

            listaData.erase(listaData.begin() + indice);

            if (listaData.empty()) {
                  registro.erase(data);
            }

            return true;
      }

      std::vector<Attivita> Registro::get_attivita(std::string data) {
            if (registro.find(data) == registro.end()) {
              return {};
            }
            return registro.at(data);
      }
      std::map<std::string, std::vector<Attivita>> Registro::show_tuttoRegistro() const {
            return registro;
      }







