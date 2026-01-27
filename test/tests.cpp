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

TEST(RegistroTest, AggiungieLeggiAttivita) {
    Registro registro;
    Attivita* a = new Attivita ("Nuoto", "15:00", "17:00");
    std::string giorno = "Lun 3";

    registro.add_attivita(a, giorno);
    Attivita* printAttivita = registro.get_attivita(giorno);

    ASSERT_NE(printAttivita, nullptr);
    EXPECT_EQ(printAttivita->get_descrizione(), "Nuoto");
}

TEST(RegistroTest, RecuperoAttivitaInesistente) {
    Registro registro;
    Attivita* nonesiste = registro.get_attivita("23:00");
    EXPECT_EQ(nonesiste, nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}