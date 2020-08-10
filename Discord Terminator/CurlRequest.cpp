/*
	FILE FROM PROJECT DISCORD TERMINATOR BY ANDRO24
	LICENSED UNDER GNU General Public License v3.0
*/

#include "CurlRequest.h"

//https://stackoverflow.com/a/36401787/13544464
size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s) {
	size_t newLength = size * nmemb;
	try {
		s->append((char*)contents, newLength);
	}
	catch (std::bad_alloc &e) {
		//handle memory problem
		return 0;
	}
	return newLength;
}

bool CurlRequest::patch(std::string url, curl_slist* header, std::string data, std::string& output) {
	CURL *curl = curl_easy_init();
	if (curl) {
		CURLcode res;

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");

		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);

		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		curl_slist_free_all(header);

		if (res != CURLE_OK) {
			throw std::exception(curl_easy_strerror(res));
		}
		return true;
	}
	else {
		throw std::exception("Unable to initialize CURL");
	}
	return false;
}