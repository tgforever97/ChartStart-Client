#include "include/Client.h"

int main(int argc, char *argv[]) {
    if(argc != 0){
        Client client(argv[1]);
        client.start_work();
        return 0;
    }

}
