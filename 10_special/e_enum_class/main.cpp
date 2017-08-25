#include <iostream>
#include <cstdint>
#include <iomanip>

// standardni C-style vyctovy typ - v podstate jde jen o integer s omezenym definicnim oborem
// jelikoz nemusime uvozovat typem, vyplati se pojmenovat cleny odlisitelne, napr s prefixem DRINKTYPE_
enum DrinkType
{
    DRINKTYPE_COFFEE = 1,       // prvni prvek enumu inicializujeme, dalsi jsou "auto increment" +1 vzdy
    DRINKTYPE_TEA,
    DRINKTYPE_MILK,
    DRINKTYPE_BEER
};

// standardni C-style vyctovy typ, jen s urcenym storage typem - misto integeru mame uint8_t
// stale neni nutne uvozovat typem
enum DrinkType_u8 : uint8_t
{
    DRINKTYPE_U8_COFFEE = 1,    // to funguje vsude
    DRINKTYPE_U8_TEA,
    DRINKTYPE_U8_MILK,
    DRINKTYPE_U8_BEER
};

// silne typovany C++ vyctovy typ - jde jen o syntaktickou a semantickou odlisnost, pod tim vsim jde o uplne stejny enum jako predtim
// zde uz je nutne uvozovat typem, proto neni treba odlisovat vnitrek od okolnich konstant
enum class TDrinkType : uint8_t
{
    COFFEE = 1,                 // i zde
    TEA,
    MILK,
    BEER
};



int main(int argc, char** argv)
{
    // jde spise o syntakticke/semanticke zpestreni, nema moc vliv na funkcnost, max. v ohledu, ze redukuje pravdepodobnost, ze udelame chybu, apod.

    // musime uvodit typem
    TDrinkType dt = TDrinkType::COFFEE;
    //TDrinkType dtt = COFFEE; // nelze

    // obycejny enum muzeme typovat, muzeme uvodit typem vyctovy prvek, ale nemusime
    DrinkType dt_1 = DrinkType::DRINKTYPE_MILK;     // typovany, uvozeny
    DrinkType dt_2 = DRINKTYPE_MILK;                // typovany, neuvozeny
    int dt3;

                                                    // netypovany, neuvozeny; zde muze vzniknout vetsina problemu
    dt3 = DRINKTYPE_MILK;
    dt3 = DRINKTYPE_U8_MILK;

    // veskere prevody u silne typovanych enumeratoru musi byt explicitni, a to jak z vyctoveho na cislo, tak z cisla na vyctovy typ
    dt3 = (int)dt;
    dt = (TDrinkType)dt3;

    // enum class ale stale nema kontrolu, ze jde o platnou hodnotu vyctu; vsak ani nema smysl, aby takova kontrola existovala,
    // navic jde o zamaskovany integer, ne objektovy container jako v Jave
    dt = (TDrinkType)55;

    return 0;
}
