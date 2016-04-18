#include "Common.h"
#include <string>
#include "cocos2d.h"
#define TEST_ENVIRONMENT 0

#if CC_TARGET_OS_MAC
	#include "NativeUtility.h"
#endif

#define ANDROID 2
#define IOS 1


Common::Common(std::string device_id, std::string device_info, std::string 
	app_version, std::string cp, std::string country, std::string language,
	std::string ipaddress, int os, int channelId, std::string sessionId
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
	this->sessionId = sessionId; 
}

Common::~Common() {
}

int Common::FACEBOOK_CHANNEL = 1; 
int Common::GOOGLE_CHANNEL = 2;
int Common::TIENLENMIENNAM_ZONE = 5; 
char* Common::KEY_SESSION_ID = "key_session_id";

std::string Common::getSessionId() {
	if (sessionId == "-1") {
		sessionId = cocos2d::UserDefault::getInstance()->getStringForKey(Common::KEY_SESSION_ID);
	}
	return sessionId;
}

void Common::setSessionId(std::string _sessionid) {
	sessionId = _sessionid; 
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
	#if CC_TARGET_OS_MAC
		  return NativeUtility::deviceID();
	#endif
	return "00000000";
}

std::string Common::getDeviceInfo() const {
	if (TEST_ENVIRONMENT)
		return "Samsung Galaxy S2";
	#if CC_TARGET_OS_MAC
        return NativeUtility::deviceName();
    #endif
	return "Samsung Galaxy S2";
}

std::string Common::getAppVersion() const {
	if (TEST_ENVIRONMENT)
		return "1";
	#if CC_TARGET_OS_MAC
        return NativeUtility::appVersion();
    #endif
		return "1";
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
		os = ANDROID;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		os =IOS;
#else
		os = IOS;
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

