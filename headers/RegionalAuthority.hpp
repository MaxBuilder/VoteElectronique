

class RegionalAuthority : public Center {

private:
    int id;
    Center& national_auth;
public:

    /**
     * @brief Get the id object
     * 
     * @return int 
     */
    int get_id();

    /**
     * @brief Retourne une référence vers l'autorité nationale qui gère l'autorité régionale.
     * 
     * @return Center& 
     */
    Center& get_national_auth();
};
