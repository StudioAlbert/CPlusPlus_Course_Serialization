// Partie 4 — Solution 1 : mémoire brute (reinterpret_cast).
//
// Pour une struct trivialement copiable, save = un seul fwrite.
// On démontre :
//   (a) le cas qui MARCHE : tableau de Tile (POD) -> bloc binaire.
//   (b) le cas qui CASSE  : Bad contient un std::string -> on écrirait
//       le POINTEUR interne, pas les caractères.

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

struct Tile {
    int  id{};
    bool walkable{};
};
static_assert(std::is_trivially_copyable_v<Tile>);

struct Bad {
    std::string name;       // possède un pointeur tas
};
static_assert(!std::is_trivially_copyable_v<Bad>,
              "std::string casse la trivialite par construction");

int main() {
    // --- (a) Cas valide : tableau de POD ---
    std::vector<Tile> map{{1,true},{2,false},{3,true},{4,true}};

    const auto path = std::filesystem::temp_directory_path() / "level.bin";
    {
        std::ofstream os(path, std::ios::binary);
        os.write(reinterpret_cast<const char*>(map.data()),
                 static_cast<std::streamsize>(map.size() * sizeof(Tile)));
    }

    std::vector<Tile> reloaded(map.size());
    {
        std::ifstream is(path, std::ios::binary);
        is.read(reinterpret_cast<char*>(reloaded.data()),
                static_cast<std::streamsize>(reloaded.size() * sizeof(Tile)));
    }

    std::cout << "[POD] aller-retour : ";
    for (const auto& t : reloaded)
        std::cout << '(' << t.id << ',' << t.walkable << ") ";
    std::cout << '\n';

    // --- (b) Démo de l'erreur : std::string ---
    // On NE FAIT PAS fwrite(&bad,...). On illustre simplement pourquoi :
    Bad bad{"un nom trop long pour entrer dans le Small-String Optimization buffer"};
    const void* string_object_address = static_cast<const void*>(&bad.name);
    const void* heap_chars_address    = static_cast<const void*>(bad.name.data());
    std::cout << "\n[BAD] objet std::string @ " << string_object_address << '\n'
              << "[BAD] caracteres alloues sur le tas @ " << heap_chars_address << '\n'
              << "Un fwrite(&bad, sizeof(Bad), ...) ecrirait l'adresse,\n"
              << "pas les caracteres. Au reload, le pointeur serait invalide.\n";

    std::cout << "\nRegle : reinterpret_cast convient AUX FEUILLES POD seulement.\n";
}
