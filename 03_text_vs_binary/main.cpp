// Partie 3 — Texte vs Binaire, et la taxe cachée du binaire : endianness.
//
// On écrit le MÊME entier en texte et en binaire, on compare la taille,
// puis on montre la conversion hôte <-> "ordre réseau" (big-endian) faite
// à la main pour rester portable sans <winsock2.h> / <arpa/inet.h>.

#include <array>
#include <bit>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

constexpr std::uint32_t to_big_endian(std::uint32_t h) {
    if constexpr (std::endian::native == std::endian::big) return h;
    return  ((h & 0x000000FFu) << 24) |
            ((h & 0x0000FF00u) <<  8) |
            ((h & 0x00FF0000u) >>  8) |
            ((h & 0xFF000000u) >> 24);
}

constexpr std::uint32_t from_big_endian(std::uint32_t n) {
    return to_big_endian(n); // swap involutif
}

void hex_dump(const char* label, const void* p, std::size_t n) {
    std::cout << label << " (" << n << " octets): ";
    const auto* b = static_cast<const unsigned char*>(p);
    for (std::size_t i = 0; i < n; ++i)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << int(b[i]) << ' ';
    std::cout << std::dec << '\n';
}

int main() {
    const std::uint32_t hp = 1000; // 0x000003E8

    // --- Texte ---
    std::stringstream txt;
    txt << hp;
    std::cout << "Texte    : \"" << txt.str() << "\" (" << txt.str().size() << " octets)\n";

    // --- Binaire brut (dépendant de l'endianness de la machine) ---
    std::array<unsigned char, sizeof hp> raw{};
    std::memcpy(raw.data(), &hp, sizeof hp);
    hex_dump("Binaire brut (hote)   ", raw.data(), raw.size());

    // --- Binaire en ordre réseau (canonique, portable) ---
    const std::uint32_t net = to_big_endian(hp);
    std::array<unsigned char, sizeof net> wire{};
    std::memcpy(wire.data(), &net, sizeof net);
    hex_dump("Binaire ordre reseau  ", wire.data(), wire.size());

    // --- Aller-retour ---
    std::uint32_t received{};
    std::memcpy(&received, wire.data(), sizeof received);
    received = from_big_endian(received);
    std::cout << "Apres aller-retour reseau : " << received << '\n';

    std::cout << "\nLecon : le texte sacrifie la taille pour la portabilite\n"
                 "et la deboguabilite ; le binaire exige un format canonique.\n";
}
