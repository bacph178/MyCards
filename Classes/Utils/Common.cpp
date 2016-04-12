#include "Common.h"
#include <string>
#define TEST_ENVIRONMENT 1


Common::Common(std::string device_id, std::string device_info, std::string 
	app_version, std::string cp, std::string country, std::string language,
	std::string ipaddress
	) {
	this->device_id = device_id; 
	this->device_info = device_info; 
	this->app_version = app_version; 
	this->cp = cp; 
	this->country = country; 
	this->language = language; 
	this->ipaddress = ipaddress; 
}

Common::~Common() {
}

/* Singleton pattern */
Common* Common::instance = 0; 
Common* Common::getInstance() {
	if (!instance) {
		instance = new Common(); 
	}
	return instance;
}

std::string Common::getDeviceId() const {
	if (TEST_ENVIRONMENT)
		return "00000000";
}

std::string Common::getDeviceInfo() const {
	if (TEST_ENVIRONMENT)
		return "Samsung Galaxy S2";
}

std::string Common::getAppVersion() const {
	if (TEST_ENVIRONMENT)
		return "1";
}

std::string Common::getCp() const  {
	if (TEST_ENVIRONMENT)
		return "0";
}

std::string Common::getCountry() const {
	if (TEST_ENVIRONMENT)
		return "vn";
}

std::string Common::getLanguage() const {
	if (TEST_ENVIRONMENT)
		return "vi";
}

std::string Common::getIpaddress() const {
	if (TEST_ENVIRONMENT)
		return "127.0.0.1";
}

int Common::getOS() const {
	if (TEST_ENVIRONMENT)
		return 2;
}