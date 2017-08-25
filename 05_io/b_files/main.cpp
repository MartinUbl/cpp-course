#include <iostream>
#include <fstream>
#include <string>

#include <cstdint>

/*

Obsah souboru prvni.txt:

Czechia;CZ
Germany;GE
Japan;JP

Obsah souboru obrazek.bmp - jakykoliv obrazek ulozeny ve formatu BMP
    - struktura, see: https://en.wikipedia.org/wiki/BMP_file_format#Bitmap_file_header

*/

#pragma pack(1)

// hlavicka (binarni) BMP souboru
struct BMPHeader
{
    char identifier[2];
    uint32_t length;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
};

#pragma pack()

// "parsovaci" operator >> pro BMP hlavicku
std::istream& operator>>(std::istream& is, BMPHeader &hdr)
{
    // oba pristupy samozrejme mozne

    // tento vzdy
    is.read(hdr.identifier, 2);
    is.read((char*)&hdr.length, 4);
    is.read((char*)&hdr.reserved1, 2);
    is.read((char*)&hdr.reserved2, 2);
    is.read((char*)&hdr.dataOffset, 4);

    // tento za pouziti structure packing (#pragma pack) pro strukturu vyse
    //is.read((char*)&hdr, sizeof(BMPHeader));


    // pozor, nelze pouzit operator >>, jelikoz jde o textove cteni (cetl by string a pokousel se ho prevadet na integer, atp.)

    return is;
}

// "formatovaci" debug operator >> pro BMP hlavicku
std::ostream& operator<<(std::ostream& os, BMPHeader &hdr)
{
    return os << "Identifier: " << std::string(hdr.identifier, 2) << ", length: " << hdr.length << ", dataOffset: " << hdr.dataOffset;
}








int main(int argc, char** argv)
{
    std::string s1, s2;

    // std::ifstream a std::ofstream sdileji podobne vlastnosti jako std::istringstream a std::ostringstream
    // - predevsim proto, ze dedi od stejnych predku: std::istream, resp. std::ostream, ktere slouzi jako zaklad
    // - stejne tak sstream a fstream maji analogicke schema dedicnosti

    std::cout << "----------- input fstream" << std::endl;

    // explicitni scope, aby nam RAII pristup soubor opet uzavrel (destruktor fstreamu)
    {
        // std::ios_base::in je priznak pro "pro cteni" - zde neni nutne uvadet, pro ifstream je implicitni

        std::ifstream ff("C:\\Temp\\prvni.txt", std::ios::in);

        // naivni parser, ale pro zakladni ulohy dostacuje
        while (std::getline(ff, s1, ';') && std::getline(ff, s2))
            std::cout << "Stat: " << s1 << ", zkratka: " << s2 << std::endl;
    }




    std::cout << "----------- input fstream - binarni soubor" << std::endl;

    // scope dalsiho ifstreamu
    {
        // precteme si hlavicku BMP obrazku
        std::ifstream ff("C:\\Temp\\obrazek.bmp", std::ios::in | std::ios::binary);

        BMPHeader header;
        ff.read(header.identifier, 2);
        ff.read((char*)&header.length, 4);
        ff.read((char*)&header.reserved1, 2);
        ff.read((char*)&header.reserved2, 2);
        ff.read((char*)&header.dataOffset, 4);

        // vypiseme informace
        std::cout << header << std::endl;
    }




    std::cout << "----------- input fstream - binarni soubor, vlastni parser" << std::endl;

    // scope dalsiho ifstreamu
    {
        // precteme si hlavicku BMP obrazku
        std::ifstream ff("C:\\Temp\\obrazek.bmp", std::ios::in | std::ios::binary);

        BMPHeader header;
        ff >> header;

        // vypiseme informace
        std::cout << header << std::endl;
    }




    std::cout << "----------- output fstream" << std::endl;

    // scope ofstreamu; zakladni priklad pouziti
    {
        std::ofstream ff("C:\\Temp\\vystup.txt"); // mode je opet implicitne std::ios_base::out

        ff << "Hello" << std::endl;
        ff << "World" << std::endl;
        ff << 69 << std::endl;
    }




    std::cout << "----------- output fstream, append" << std::endl;

    // scope ofstreamu; append za konec souboru
    {
        std::ofstream ff("C:\\Temp\\vystup.txt", std::ios::out | std::ios::app);

        ff << "'Member Chewbacca?" << std::endl;
    }




    std::cout << "----------- output fstream, binarni zapis" << std::endl;

    // scope ofstreamu; zakladni priklad pouziti
    {
        std::ofstream ff("C:\\Temp\\vystup.bin", std::ios::out | std::ios::binary);

        for (size_t i = 0; i < 10; i++)
        {
            ff.write((char*)&i, 4);
        }
    }

    return 0;
}
