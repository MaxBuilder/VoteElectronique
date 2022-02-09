

class LocalAuthority : public Center {

private:
    int id;
    Center& regional_auth;
public:
    int get_id();

    /**
     * @brief Retourne une référence vers l'autorité régionale qui gère l'autorité locale.
     * 
     * @return Center& 
     */
    Center& get_regional_auth();

    /**
     * @brief Retourne les clés publiques de l'autorité locale et de ses deux autorités supérieures.
     * 
     * @return std::array<std::pair<cpp_int, cpp_int>, 3> 
     */
    std::array<std::pair<cpp_int, cpp_int>, 3> get_public_keys();
};
