#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <stdint.h>
#include <netinet/in.h>
#include "utils/types.h"
#include "utils/list.h"

struct http_server
{
    socket server_sock;

	uint16_t server_port;

	struct list_head clients;
};

struct http_client
{
	struct list_head node;

	pthread_t thread;

	socket client_sock;

	struct sockaddr_in name;
};

rc http_create(struct http_server **self, uint16_t server_port);

rc http_connect(struct http_server *self);

void http_close();