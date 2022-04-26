
#include "src/CryptoUtils.hpp"
#include "src/KeyGeneration.hpp"
#include "src/Combiner.hpp"
#include "src/Encryption.hpp"

#include <chrono>
#include <ctime>



int main(int argc, char const *argv[])
{
    
    // srand(clock());

 
    std::cout << "\033[0;32mTest du déchiffrement partagé\033[0m\n";

    // Vote clair
    cpp_int clear = 23;
    std::cout << "\033[0;33mClair: " << clear << "\033[0m\n";

    // Génération des clés
    // std::tuple<PKey, cpp_int> keys = KeyGeneration::generate_keys();
    // PKey public_key     = std::get<0>(keys);
    // cpp_int private_key = std::get<1>(keys);
    
    /*
    p: 5 | q: 7 | N: 35 | N^2 = 1225
    m = p'*q' = 6
    Beta: 24 | a: 23 | b: 31
    g = (1+N)^a * b^N mod N^2 = 1006

    > SK = beta*m = 144
    tetha = a*m*beta mod N = 22
    > PK = {g, N, tetha} = {1006, 35, 22}
    */
    // g, N, Tetha, Beta, m
    PKey public_key     = {1006, 35, 22, 24, 6};
    cpp_int private_key = 144;
    std::cout << "Clé publique:\n N: " << public_key.N << "\n g: " << public_key.g << "\n Tetha: " << public_key.tetha << "\n";

    int nbServersPerCombiner = 2;
    int t = 1;
    int delta = 4;
    Combiner *combiner = new Combiner(
        private_key, public_key, delta, public_key.N, nbServersPerCombiner, t, public_key.m);

    // Chiffrement
    CipherStruct cipher = Encryption::encrypt(public_key, clear);
    std::cout << "\033[0;33mChiffré: " << cipher.cipher << " | x: " << cipher.x << "\033[0m\n";

    // Déchiffrement
    combiner->calculateResults(cipher.cipher);
	cpp_int decrypted = combiner->combine();
    std::cout << "\033[0;33mDéchiffré: " << decrypted << "\033[0m\n";
    
    return 0;
}
