#include "artnet_send.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
char ID[8];
uint16_t opcode;
uint8_t ProtVerH;
uint8_t ProtVerL;
uint8_t Sequence;
uint8_t Physical;
uint8_t SubUni;
uint8_t Net;
uint8_t LengthHi;
uint8_t LengthLo;
uint8_t Data[512];
} __attribute__ ((packed)) artnet_datagram_t;

artnet_send_t* artnet_send_create(char* host, uint8_t universe, uint16_t length) {
artnet_send_t* descriptor;

descriptor = (artnet_send_t*) calloc(sizeof(artnet_send_t), 0);

if (descriptor == NULL) {
printf ("Zu wenig Speicherplatz zum Anlegen des Deskriptors für Artnet_send.\n");

return NULL;
}

descriptor->length = length;
descriptor->universe = universe;

if ((descriptor->socketDescriptor=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1) {
printf ("Fehler beim Anlegen des Sockets für Artnet_send.\n");

free(descriptor);

return NULL;
}

descriptor->serverAddress.sin_family = AF_INET;
    descriptor->serverAddress.sin_port = htons(ARTNET_PORT);
    if (inet_aton(host, &descriptor->serverAddress.sin_addr)==0) {
     printf ("Fehler beim Anlegen des Sockets für Artnet_send.\nHostname/adresse kann nicht gesetzt werden\n");

close(descriptor->socketDescriptor);
free(descriptor);

return NULL;
    }

return descriptor;
}

void artnet_send_deinit(artnet_send_t* descriptor) {

close(descriptor->socketDescriptor);
free(descriptor);
}

void artnet_send_send(artnet_send_t* descriptor) {
artnet_datagram_t datagram = {
.ID = {'A', 'r', 't', '-', 'N', 'e', 't', '\0'},
.opcode = 0x5000,
.ProtVerL = 1,
.SubUni = descriptor->universe,
.LengthHi = (uint8_t) ((descriptor->length >> 8) & 0xff),
.LengthLo = (uint8_t) (descriptor->length & 0xff)
};

memcpy(datagram.Data, descriptor->data, descriptor->length);

if (
sendto(descriptor->socketDescriptor,
(void *) &datagram,
18 + descriptor->length, // Header + Data
0,
(struct sockaddr *) &(descriptor->serverAddress),
sizeof(descriptor->serverAddress)
) < 0) {
printf("Could not send data to the server. \n");
}
}
