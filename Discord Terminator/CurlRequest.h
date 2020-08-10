/*
	FILE FROM PROJECT DISCORD TERMINATOR BY ANDRO24
	LICENSED UNDER GNU General Public License v3.0
*/

#pragma once
#define CURL_STATICLIB
#include <curl/curl.h>
#include <iostream>

#pragma comment(lib, "libcurl_a.lib")

class CurlRequest {
public:
	static bool patch(std::string url, curl_slist* header, std::string data, std::string& output);
};