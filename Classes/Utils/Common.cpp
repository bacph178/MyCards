#include "Common.h"
#include <string>
#define TEST_ENVIRONMENT 0

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "NativeUtility.h"
#endif


Common::Common(std::string device_id, std::string device_info, std::string 
	app_version, std::string cp, std::string country, std::string language,
	std::string ipaddress, int os, int channelId
	) {
	this->device_id = device_id; 
	this->device_info = device_info; 
	this->app_version = app_version; 
	this->cp = cp; 
	this->country = country; 
	this->language = language; 
	this->ipaddress = ipaddress; 
	this->os = os; 
	this->channelId = channelId; 
}

Common::~Common() {
}

int Common::FACEBOOK_CHANNEL = 1; 
int Common::GOOGLE_CHANNEL = 2; 
int Common::ANDROID = 1; 
int Common::IOS = 2;
int Common::TIENLENMIENNAM_ZONE = 5; 

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
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        return NativeUtility::deviceID();
    #endif
}

std::string Common::getDeviceInfo() const {
	if (TEST_ENVIRONMENT)
		return "Samsung Galaxy S2";
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        return NativeUtility::deviceName();
    #endif
}

std::string Common::getAppVersion() const {
	if (TEST_ENVIRONMENT)
		return "1";
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        return NativeUtility::appVersion();
    #endif
}

std::string Common::getCp() const  {
	// if (TEST_ENVIRONMENT)
		return "0";
    
}

std::string Common::getCountry() const {
	// if (TEST_ENVIRONMENT)
		return "vn";
    
}

std::string Common::getLanguage() const {
	// if (TEST_ENVIRONMENT)
		return "vi";
}

std::string Common::getIpaddress() const {
	// if (TEST_ENVIRONMENT)
		return "127.0.0.1";
}

int Common::getOS()  {
	if (os == 0) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		os = Common::ANDROID;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		os =Common::IOS;
#else
		os = 0;
#endif
	}
	return os; 
}

int Common::getZoneId(int tag) const {
	int result = -1;
	switch (tag)
	{
	default:
		result = Common::TIENLENMIENNAM_ZONE;
		break;
	}
	return result;
}

int Common::getChannelId() {
	if (channelId == 0) {
		if (TEST_ENVIRONMENT)
			channelId = Common::FACEBOOK_CHANNEL; //Facebook
	}
	return channelId;
}

