#ifndef ATTIVITA_H
#define ATTIVITA_H
#include <string>


class Attivita {
    public:
    Attivita(std::string descrizione, std::string orarioinizio, std::string orariofine);
    void set_descrizione(std::string new_descrizione);
    std::string get_descrizione() const;
    void set_orarioinizio(std::string new_orarioinizio);
    std::string get_orarioinizio() const;
    void set_orariofine(std::string new_orariofine);
    std::string get_orariofine() const;
    bool operator<(const Attivita &other) const;
    bool orarioValido() const;

private:
    std::string descrizione;
    std::string orarioinizio;
    std::string orariofine;

};



#endif //ATTIVITÀ_H
