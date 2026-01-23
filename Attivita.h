#ifndef ATTIVITÀ_H
#define ATTIVITÀ_H
#include <string>


class Attivita {
    public:
    Attivita(std::string descrizione, std::string orarioinizio, std::string orariofine);
    void set_descrizione(std::string new_descrizione);
    std::string get_descrizione() const;
    void set_orarioinizio(int new_orarioinizio);
    std::string get_orarioinizio() const;
    void set_orariofine(int new_orariofine);
    std::string get_orariofine() const;

private:
    std::string descrizione;
    std::string orarioinizio;
    std::string orariofine;

};



#endif //ATTIVITÀ_H
