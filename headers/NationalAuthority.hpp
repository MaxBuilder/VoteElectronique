#ifndef __NATIONAL_AUTHORITY_H__
#define __NATIONAL_AUTHORITY_H__

#include "Center.hpp"
#include "NationalBulletin.hpp"

class NationalAuthority : public Center {

private:
    
public:
    NationalAuthority(PublicKey _pkey, cpp_int _skey) : Center(_pkey, _skey) {}
    
    // ToDo : process transmission de résultats à confirmer ou modifier (voir autre todo)
    void receive_results(cpp_int, std::vector<cpp_int>);

    void make_tally();

    /**
     * @brief Annonce les résultats de l'élection.
     */
    void transmit_results();

    /**
     * @brief Affiche le BulletinBoard d'une autorité sur la sortie standard.
     */
    virtual void print_board();

    virtual ~NationalAuthority() {};
};

#endif // __NATIONAL_AUTHORITY_H__
