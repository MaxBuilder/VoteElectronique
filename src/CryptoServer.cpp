#include "CryptoServer.hpp"


int CryptoServer::getId() { return id; }


cpp_int CryptoServer::computeDecryptionShare(cpp_int c) {
	
	cpp_int N2;
	N2 = boost::multiprecision::multiply(N2, N, N);

	cpp_int res = c;
	res = boost::multiprecision::powm(res, 2, N2);
	res = boost::multiprecision::powm(res, delta, N2);
	res = boost::multiprecision::powm(res, sk, N2);
	std::cout << "id" << getId() << " : " << res << std::endl;
	return res;
}