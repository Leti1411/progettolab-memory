#include "gtest/gtest.h"
#include "../Attivita.h"
#include "../Registro.h"

class AttivitaSuite : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(AttivitaSuite, CostruttoreEGetters) {
    Attivita a("Partita", "10:00", "12:00");
    ASSERT_EQ(a.get_descrizione(), "Partita");
    ASSERT_EQ(a.get_orarioinizio(), "10:00");
    ASSERT_EQ(a.get_orariofine(), "12:00");
}

TEST_F(AttivitaSuite, OrarioValido) {
    Attivita a1("Valid", "10:00", "11:00");
    ASSERT_TRUE(a1.orarioValido());

    Attivita a2("Invalid", "12:00", "11:00");
    ASSERT_FALSE(a2.orarioValido());
}

TEST_F(AttivitaSuite, OperatoreMinore) {
    Attivita prima("Prima", "08:00", "09:00");
    Attivita dopo("Dopo", "20:00", "21:00");

    ASSERT_TRUE(prima < dopo);
    ASSERT_FALSE(dopo < prima);
}

class RegistroSuite : public ::testing::Test {
protected:
    Registro* registro;

    void SetUp() override {
        registro = new Registro();
    }

    void TearDown() override {
        delete registro;
    }
};

TEST_F(RegistroSuite, AggiuntaAttivita) {
    Attivita a("Nuoto", "10:00", "11:00");
    registro->add_attivita(a, "10-02-2026");

    std::vector<Attivita> lista = registro->get_attivita("10-02-2026");
    ASSERT_EQ(lista.size(), 1);
    ASSERT_EQ(lista[0].get_descrizione(), "Nuoto");
}

TEST_F(RegistroSuite, AggiuntaAttivitaNonValida) {
    Attivita a("Errata", "12:00", "11:00");
    registro->add_attivita(a, "10-02-2026");

    std::vector<Attivita> lista = registro->get_attivita("10-02-2026");
    ASSERT_EQ(lista.size(), 0);
}

TEST_F(RegistroSuite, OrdinamentoAutomatico) {
    Attivita a1("Sera", "20:00", "21:00");
    Attivita a2("Mattina", "08:00", "09:00");

    registro->add_attivita(a1, "10-02-2026");
    registro->add_attivita(a2, "10-02-2026");

    std::vector<Attivita> lista = registro->get_attivita("10-02-2026");
    ASSERT_EQ(lista.size(), 2);
    ASSERT_EQ(lista[0].get_descrizione(), "Mattina");
    ASSERT_EQ(lista[1].get_descrizione(), "Sera");
}

TEST_F(RegistroSuite, RimozioneAttivita) {
    Attivita a("Corsa", "18:00", "19:00");
    registro->add_attivita(a, "10-02-2026");

    bool rimossa = registro->remove_attivita(0, "10-02-2026");

    ASSERT_TRUE(rimossa);
    ASSERT_EQ(registro->get_attivita("10-02-2026").size(), 0);
}

TEST_F(RegistroSuite, RimozioneIndiceErrato) {
    bool rimossa = registro->remove_attivita(0, "10-02-2026");
    ASSERT_FALSE(rimossa);
}