#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>


class Common {
public:
	static Common* getInstance(); 
	Common(std::string = "", std::string = "", std::string = "", std::string
		= "", std::string = "", std::string = "", std::string = "", int= 0,
		int = 0, std::string = "-1"); 
	~Common(); 
	std::string getDeviceId() const; 
	std::string getDeviceInfo() const; 
	std::string getAppVersion() const; 
	std::string getCp() const;
	std::string getLanguage() const; 
	std::string getCountry() const;
	std::string getIpaddress() const; 
	std::string getSessionId();
	void setSessionId(std::string _sessionid);
	int getOS(); 
	int getZoneId(int tag) const; 
	int getChannelId(); 

	static char* KEY_SESSION_ID;

private:
	static Common* instance; 
	static int FACEBOOK_CHANNEL;
	static int GOOGLE_CHANNEL;
	static int TIENLENMIENNAM_ZONE;
	static int ANDROID;
	static int IOS;
	
	std::string device_id; 
	std::string device_info; 
	std::string app_version; 
	std::string cp; 
	std::string language; 
	std::string country; 
	std::string ipaddress; 
	std::string sessionId;
	int os;
	int channelId;
};

#endif // __COMMON_H__
