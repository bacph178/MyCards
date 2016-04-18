#ifndef  _NETWORK_MANAGER_H_
#define  _NETWORK_MANAGER_H_

#include <vector>
#include <string>

#if WIN32
	#pragma comment(lib, "libprotobuf.lib")
#endif


#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <thread>

using namespace std;

class NetworkManager
{
public:
	NetworkManager();
	virtual ~NetworkManager();	

	static NetworkManager* getInstance();

	google::protobuf::Message* initPingMessage(int = 0);
	google::protobuf::Message* initLoginMessage(string = "sanglx", string = 
		"12345678");
	google::protobuf::Message* initRegisterMessage(string = "register", string 
		= "12345678", string="register");
	google::protobuf::Message* initInitializeMessage(string = "0", string = "1"
		, string = "vn", string = "vi", string = "00000000", string = 
		"Samsung galaxy S2",  string = "127.0.0.1");

	google::protobuf::Message* initFilterRoomMessage(int zone_id = 5, bool 
		vip_room = false, int first_result = -1, int max_result = -1);

	google::protobuf::Message* initEnterRoomMessage(int room_index = 0, std::string password = "");

	google::protobuf::Message* initQuickPlayMessage(string = "", string = "");
	google::protobuf::Message* initOpenIdLoginMessage(int channelId = 0, string openId = "");
	google::protobuf::Message* initEnterZoneMessage(int zoneId);
	google::protobuf::Message* initCreateRoomMessage(int zone_id, int 
		room_group_id, bool vip_room, int min_bet, int player_size, 
		std::string password = "");
	
	void connectServer(const char* , const int);
	void recvMessage();
	void listenData();


	void getRegisterMessageFromServer(string, string, string);
	void getLoginMessageFromServer(string, string);
	void getQuickPlayMessageFromServer(string, string);
	void getInitializeMessageFromServer(string cp, string appversion, string
        country, string language, string device_id, string device_info, string
        ipaddress);
	void getPingMessageFromServer();
	void getEnterRoomMessageFromServer(int room_index,  string password);
	void getFilterRoomMessageFromServer(int zone_id, bool vip_room, int first_result, int max_result);
	void getOpenIdLoginMessageFromServer(int channelId, string openId);
	void getEnterZoneMessageFromServer(int zoneId);
	void getCreateRoomMessageFromServer(int zone_id, int room_group_id, bool 
		vip_room, int min_bet, int player_size, std::string password);

	void requestMessage(google::protobuf::Message *, int, int, string);

	char* initData(google::protobuf::Message* ,int ,int ,std::string ,int &);
	// static void callNetwork(char* , int); 
	static std::vector<std::pair<google::protobuf::Message*, int>> parseFrom(std::vector<char>, int);

	static void setInitialize(bool _isInitialize);
	static bool isInitialized(); 
	static bool _initialized;

	static vector<std::vector<std::pair<google::protobuf::Message*, int>>> listEvent;

	 static const int REGISTER = 1000;
	 static const int LOGIN = 1001;
	 static const int QUICK_PLAY = 1002;
	 static const int OPEN_ID_LOGIN = 1003;
	 static const int LOGOUT = 1004;
	 static const int ENTER_ZONE = 1005;
	 static const int FILTER_ROOM = 1006;
	 static const int CREATE_ROOM = 1007;
	 static const int ENTER_ROOM = 1008;
	 static const int NEW_PLAYER_ENTER_ROOM = 1009;
	 static const int START_MATCH = 1010;
	 static const int TURN = 1011;

	 static const int LEFT_ROOM = 1010;
	//special message
	 static const int INITIALIZE = 1111;
	 static const int PING = 8888;
	 static const int EXPIRED_SESSION = 9999;
	private: 
		static NetworkManager* _instance; 
};

#endif // _NETWORK_MANAGER_H_

