#include <gtest/gtest.h>
#include "Attivita.h"
#include "Registro.h"

TEST(AttivitaTest, CostruttoreEGetters) {
    std::string descrizione = "TEST ATTIVITA'";
    std::string inizio = "9:00";
    std::string fine = "12:00";

    Attivita a(descrizione, inizio, fine);

    EXPECT_EQ(a.get_descrizione(), descrizione);
    EXPECT_EQ(a.get_orarioinizio(), inizio);
    EXPECT_EQ(a.get_orariofine(), fine);

}

TEST(AttivitaTest, OrarioValido) {
    Attivita valida("Giusta", "09:00", "11:00");
    Attivita invalida("Sbagliata", "10:00", "07:00");
    Attivita uguale("Uguale", "09:00", "09:00");

    EXPECT_TRUE(valida.orarioValido());
    EXPECT_FALSE(invalida.orarioValido());
    EXPECT_FALSE(uguale.orarioValido());
}

TEST(AttivitaTest, OperatoreMinore) {
    Attivita presto("Presto", "09:00", "11:00");
    Attivita tardi ("Tardi", "17:00", "19:00");

    EXPECT_TRUE(presto < tardi);
    EXPECT_FALSE(tardi < presto);
}

TEST(RegistroTest, AggiungAttivita) {
    Registro r;
    Attivita a("Lavoro", "09:00", "11:00");
    r.add_attivita(a, "12-02-2026");
    std::vector<Attivita> lista = r.get_attivita("12-02-2026");

    ASSERT_EQ(lista.size(), 1);
    EXPECT_EQ(lista[0].get_descrizione(), "Lavoro");
}

TEST(RegistroTest, RifiutaOrarioInvalido) {
    Registro r;
    Attivita a("Errore", "13:00", "12:00"); // Orario sbagliato

    r.add_attivita(a, "13-01-2026");

    std::vector<Attivita> lista = r.get_attivita("13-01-2026");

    EXPECT_TRUE(lista.empty());
}

TEST(RegistroTest, OrdinamentoAutomatico) {
    Registro r;

    // ordine sbagliato
    Attivita sera("Cena", "20:00", "21:00");
    Attivita mattina("Colazione", "07:00", "08:00");
    Attivita pranzo("Pranzo", "13:00", "14:00");

    r.add_attivita(sera, "14-11-2026");
    r.add_attivita(mattina, "14-11-2026");
    r.add_attivita(pranzo, "14-11-2026");

    std::vector<Attivita> lista = r.get_attivita("14-11-2026");

    ASSERT_EQ(lista.size(), 3);

    // verifico l'ordine corretto
    EXPECT_EQ(lista[0].get_descrizione(), "Colazione");
    EXPECT_EQ(lista[1].get_descrizione(), "Pranzo");
    EXPECT_EQ(lista[2].get_descrizione(), "Cena");
}

TEST(RegistroTest, GiorniDiversi) {
    Registro r;
    Attivita a1("Vigilia", "10:00", "11:00");
    Attivita a2("Natale", "10:00", "11:00");

    r.add_attivita(a1, "24-12-2025");
    r.add_attivita(a2, "25-12-2025");

    EXPECT_EQ(r.get_attivita("24-12-2025").size(), 1);
    EXPECT_EQ(r.get_attivita("25-12-2025").size(), 1);

    EXPECT_EQ(r.get_attivita("24-12-2025")[0].get_descrizione(), "Vigilia");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}