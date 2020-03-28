//
// Created by wang on 2020/3/26.
//

#ifndef CHATSTART_COMMON_H
#define CHATSTART_COMMON_H

#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
#define Max_Buffer 256
#define Max_Thread 10
#define SERVER_WELCOME_WORDS "欢迎使用ChartStart"
#define QUIT "q"
#define SEARCH "s"
#define BEAT "beat"

#endif //CHATSTART_COMMON_H

