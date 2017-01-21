#include <stdlib.h>
#include "http_server.h"
#include "utils/utils.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>

rc http_create(struct http_server **self, uint16_t server_port)
{
	struct http_server *http_server = malloc(sizeof (struct http_server));

	if (http_server == NULL) {
		eprintf("Failed allocate memory");
		return RC_ERROR;
	}

	http_server->server_port = server_port;

	http_server->clients = LIST_HEAD_INIT(http_server->clients);

	return RC_OK;
}

rc http_connect(struct http_server *self)
{
	rc ret_code = RC_ERROR;
	struct sockaddr_in serv_name = { 0 };

	socket serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	if (serv_sock < 0) {
		eprintf("cannot create server socket");
		return RC_ERROR;
	}

	self->server_sock = serv_sock;

	serv_name.sin_family = AF_INET;
	serv_name.sin_port = htons(self->server_port);
	serv_name.sin_addr.s_addr = htonl(INADDR_ANY);

	ret_code = bind(serv_sock, (struct sockaddr*)&serv_name, sizeof(struct sockaddr_in));

	if (ret_code < 0) {
		eprintf("bind failed");
		return ret_code;
	}

	if (self->server_port == DYNAMIC_PORT) {
		socklen_t socklen = sizeof serv_name;
		ret_code = getsockname(serv_sock, (struct sockaddr*)&serv_name, &socklen);

		if (ret_code < 0) {
			eprintf("getsockname failed");
			return ret_code;
		}
		self->server_port = htons(serv_name.sin_port);
	}

	ret_code = listen(self->server_sock, SOMAXCONN);

	if (ret_code < 0) {
		eprintf("listen failed");
		return ret_code;
	}

	return RC_OK;
}

static void* accept_request(void *self)
{
	struct http_client *client = self;



}

rc http_accept(struct http_server *self)
{
	struct http_client *client = calloc(1, sizeof (struct http_client));

	if (client == NULL) {
		eprintf("calloc failed");
		return RC_ERROR;
	}

	socklen_t socklen = sizeof (struct sockaddr_in);
	socket client_sock = accept(self->server_sock, (struct sockaddr*)&client->name, &socklen);

	if (client_sock < 0) {
		perror("accept failed");
		free (client);
		return RC_ERROR;
	}

	list_add(&client->node, &self->clients);

	pthread_create(&client->thread, NULL, accept_request, client);

}








