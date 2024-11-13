#include "server.h"
#include <signal.h>

volatile sig_atomic_t stop_server = 0;

void handle_sigint(int sig)
{
	stop_server = 1;
}

void tlisten(Server *s, int port)
{
	int opt = 1;
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
	int new_socket;
	ssize_t valread;
	char buffer[1024] = {0};

	// signal(SIGINT, handle_sigint);

	if (setsockopt(s->fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(s->fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(s->fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if ((new_socket = accept(s->fd, (struct sockaddr *)&address, &addrlen)) < 0)
		{
			perror("read");
			continue;
		}
		valread = read(new_socket, buffer, 1024 - 1);
		if (valread == 0)
		{
			close(new_socket);
			continue;
		}
		if (valread < 0)
		{
			perror("read");
			continue;
		}
		buffer[valread] = '\0';
		handle_request(s, buffer, new_socket);
		close(new_socket);
	}

	printf("Server is shutting down...\n");

	close(s->fd);
	free_server(s);
	exit(0);
}
