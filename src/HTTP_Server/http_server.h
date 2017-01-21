#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <stdint.h>

struct http_server
{
    int server_soc;
	uint16_t server_port;

};

int http_connect();

void http_close();