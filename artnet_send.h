#ifdef __cplusplus
extern "C" {
#endif 

#ifndef __ARTNET_SEND_H__
#define __ARTNET_SEND_H__

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdint.h>

#define ARTNET_PORT 6454

typedef struct {
uint8_t data[512];
uint16_t length;
uint8_t universe;
char* artnet_node;

int socketDescriptor;
struct sockaddr_in serverAddress;
} artnet_send_t;

artnet_send_t* artnet_send_create(char* host, uint8_t universe, uint16_t length);

void artnet_send_deinit(artnet_send_t* descriptor);

void artnet_send_send(artnet_send_t* descriptor);

#endif

#ifdef __cplusplus
}
#endif
