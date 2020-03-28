//
// Created by wang on 2020/3/26.
//

#include "include/Client.h"
#include "include/Utils.h"

Client::Client(string name){

    client_name = name;
    isWork = true;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
}

int Client::connect_server() {
    int sockfd = 0;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
       perror("sock init error");
       printf("%s\n", strerror(errno));
       exit(-1);
    }

    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("sock connect error");
        printf("%s\n", strerror(errno));
        exit(-1);
    }

    return sockfd;
}

void Client::close_connect(int sock){
    close(sock);
    cout << "**********chat over**********" << endl;
}

void Client::client_read(int sockfd, char recvBuf[Max_Buffer]) {
    memset(recvBuf, 0, Max_Buffer);
    int len = recv(sockfd, recvBuf, Max_Buffer-1, 0);
    if(len < 0){
        cout << "recv error, and chat is over" << endl;
        isWork = false;
    } else if (len > 0){
        recvBuf[len] = '\0';
        string recv_string = ch_string(recvBuf);
//        if(recv_string != "no message ~"){
            cout << "recv:" << recvBuf << endl;
            printf("\n");
//        }
    }else{
        //do nothing
    }
}

void Client::client_write(int sockfd, char sendBuf[Max_Buffer]) {
    cout << "send:";
    memset(sendBuf, 0, Max_Buffer);
    cin.getline(sendBuf, Max_Buffer);
    if(strcmp(sendBuf, QUIT) == 0){
        isWork = false;
    }
    if(send(sockfd, sendBuf, strlen(sendBuf)+1, 0) < 0){
        cout << "send error, and chat is over" << endl;
        isWork = false;
    }
    cout << endl;
}

int Client::client_heartbeat() {
    char buff[Max_Buffer] = {};
    int sockfd = 0;
    while(isWork){
        sockfd = connect_server();
        char beat[16] = {};
        char *beatPtr = beat;
        string split = ";";
        for(auto c : BEAT + split + client_name){
            *beatPtr = c;
            beatPtr++;
        }
        *beatPtr = '\0';
        if(send(sockfd, beat, strlen(beat)+1, 0) < 0){
            cout << "send error, and chat is over" << endl;
            isWork = false;
        }
        client_read(sockfd, buff);
        std::chrono::milliseconds dura( 1000);
        std::this_thread::sleep_for(dura);
    }
    close_connect(sockfd);
    return 0;
}

int Client::client_send_msg() {
    char buff[Max_Buffer] = {};
    char buff_1[Max_Buffer] = {};
    int sockfd = 0;
    while(isWork){
        sockfd = connect_server();
        client_write(sockfd, buff);
        client_read(sockfd, buff_1);
    }
    close_connect(sockfd);
    return 0;
}

void Client::start_work() {
    cout << "*********Connect2Server:" << SERVER_IP << ":" << SERVER_PORT << "*********" << endl;
//    thread t_beat(mem_fn(&Client::client_heartbeat), std::ref(*this));
    thread t_send(mem_fn(&Client::client_send_msg), std::ref(*this));
//    t_beat.join();
    t_send.join();
}

string Client::ch_string(char temp[Max_Buffer]) {
    string temp_string;
    char *p = temp;
    while(*p != '\0'){
        temp_string += *p;
        p++;
    }
    return temp_string;
}
