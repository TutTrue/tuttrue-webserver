#include "server.h"

void tlisten(Server *s, int port)
{
	int opt = 1;
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
	int new_socket;
	ssize_t valread;
	char buffer[1024] = {0};

	if (setsockopt(s->fd, SOL_SOCKET,
				   SO_REUSEADDR | SO_REUSEPORT, &opt,
				   sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(s->fd, (struct sockaddr *)&address,
			 sizeof(address)) < 0)
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

		if ((new_socket = accept(s->fd, (struct sockaddr *)&address,
								 &addrlen)) < 0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}
		valread = read(new_socket, buffer,
					   1024 - 1);
		if (valread < 0)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}

		handle_request(s, buffer, new_socket);
		close(new_socket);
	}

	close(s->fd);
	free(s);
}
