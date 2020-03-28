//
// Created by wang on 2020/3/26.
//

#ifndef CHATSTART_CLIENT_H
#define CHATSTART_CLIENT_H

#include <string>
#include <thread>
#include "Common.h"
using namespace std;
class Client{
public:

    Client(string name);

    int connect_server();

    void close_connect(int sock);

    void start_work();

    void client_read(int sock, char buff[Max_Buffer]);

    void client_write(int, char buff[Max_Buffer]);

    int client_heartbeat();

    int client_send_msg();

    string ch_string(char temp[Max_Buffer]);

private:

    string client_name;

    bool isWork;

    struct sockaddr_in server_addr;
};
#endif //CHATSTART_CLIENT_H
