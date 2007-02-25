#include <Socket.h>
#include <string>
#include <utils.h>

NSC_WRAPPERS_MAIN();

class NSClientListener  : public simpleSocket::ListenerHandler {
private:
	simpleSocket::Listener<> socket;
	socketHelpers::allowedHosts allowedHosts;

public:
	NSClientListener();
	virtual ~NSClientListener();
	// Module calls
	bool loadModule();
	bool unloadModule();


	std::string getModuleName() {
		return "NSClient server";
	}
	NSCModuleWrapper::module_version getModuleVersion() {
		NSCModuleWrapper::module_version version = {0, 0, 1 };
		return version;
	}
	std::string getModuleDescription() {
		return "A simple server that listens for incoming NSClient (check_nt) connection and handles them.\nAlthough NRPE is the preferred method NSClient is fully supported and can be used for simplicity or for compatibility.";
	}

	std::string parseRequest(std::string buffer);
	void sendTheResponse(simpleSocket::Socket *client, std::string response);
	void retrivePacket(simpleSocket::Socket *client);
	bool isPasswordOk(std::string remotePassword);

	// simpleSocket::ListenerHandler implementation
	void onAccept(simpleSocket::Socket *client);
	void onClose();
	std::string getConfigurationMeta();

};