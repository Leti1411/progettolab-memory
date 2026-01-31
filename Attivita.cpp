#include "Attivita.h"



    Attivita::Attivita(std::string descrizione, std::string orarioinizio, std::string orariofine) : descrizione(descrizione), orarioinizio(orarioinizio), orariofine(orariofine) {}
    void Attivita::set_descrizione(std::string new_descrizione) {
        descrizione = new_descrizione;
    }
   std::string Attivita::get_descrizione() const {
       return descrizione;
   }
    void Attivita::set_orarioinizio(int new_orarioinizio) {
        orarioinizio = new_orarioinizio;
    }
    std::string Attivita::get_orarioinizio() const {
        return orarioinizio;
    }
    void Attivita::set_orariofine(int new_orariofine) {
        orariofine = new_orariofine;
    }
    std::string Attivita::get_orariofine() const {
        return orariofine;
    }
    bool Attivita::operator<(const Attivita &other) const {
        return this->get_orarioinizio() < other.get_orarioinizio();
}
    bool Attivita::orarioValido() const {
        return get_orarioinizio() < get_orariofine();
    }








