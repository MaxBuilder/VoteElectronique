#ifndef _CLIENT_H_
#define _CLIENT_H_

#define _CRT_SECURE_NO_WARNINGS

#include "Properties.hpp"
#include "authorities/LocalAuthority.hpp"
#include "bulletins/LocalBulletin.hpp"
#include "authorities/BulletinBoard.hpp"
#include "cryptosystem/Encryption.hpp"
#include "Verifier.hpp"

#include <ctime>

#define BITSIZE 8

class Client {

private:
	int client_id;
	cpp_int M;
	// Properties* props;
	CryptoUtils::SKeyRSA sk;
	LocalAuthority* loc;

public:

	Client(int id_, cpp_int M_, LocalAuthority* loc_) : client_id(id_), M(M_), loc(loc_)
	{
		sk = generateKeys();
		// props = Properties::getProperties();
	};


	CryptoUtils::SKeyRSA generateKeys();
	cpp_int signRSA(cpp_int message, CryptoUtils::SKeyRSA sk);
	void vote(int vote);
};

#endif