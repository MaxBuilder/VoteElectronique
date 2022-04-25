#ifndef _CLIENT_H_
#define _CLIENT_H_

#define _CRT_SECURE_NO_WARNINGS

#include "CryptoUtils.hpp"
#include "Properties.hpp"
#include "authorities/LocalAuthority.hpp"
#include "bulletins/LocalBulletin.hpp"
#include "authorities/BulletinBoard.hpp"
#include "Encryption.hpp"
#include "Verifier.hpp"

#include <ctime>

#define BITSIZE 8

class Client {

private:
	int client_id;
	Properties* props;
	CryptoUtils::SKeyRSA sk;
	LocalAuthority* loc;

public:

	Client(int id_, LocalAuthority* loc_) : client_id(id_), loc(loc_)
	{
		sk = generateKeys();
		props = Properties::getProperties();
	};


	CryptoUtils::SKeyRSA generateKeys();
	cpp_int signRSA(cpp_int message, CryptoUtils::SKeyRSA sk);
	void vote(int vote);
};

#endif