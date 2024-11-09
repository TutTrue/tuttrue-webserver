# tuttrue-WebServer

This project is a simple HTTP web server implemented in C, designed to handle HTTP requests, route them to the appropriate handlers, and send responses back to the client. The server is built from scratch and includes basic routing, request parsing, and response handling.

## Project Structure

```plaintext
├── bin
├── build
├── include
│   ├── request.h
│   ├── response.h
│   └── server.h
├── lib
├── main.c
├── makefile
├── README.md
└── src
    ├── compare_route.c
    ├── create_response.c
    ├── create_server.c
    ├── excute.c
    ├── get_status_text.c
    ├── handle_request.c
    ├── params.c
    ├── parse_request.c
    ├── route.c
    └── tlisten.c
```

- **bin**: Contains compiled binaries.
- **build**: Directory for build artifacts.
- **include**: Header files for server components.
- **lib**: External libraries or shared modules.
- **src**: Source files for server implementation.
- **main.c**: Entry point for the application.
- **makefile**: Build automation file.

## Features

- [x] Basic HTTP request handling
- [x] Request parsing
- [x] Routing to specific endpoints
- [x] Sending HTTP responses
- [x] Customizable status messages
- [x] Configurable port and IP binding
- [x] Logger
- [x] Dynamic routing -> /hello/:id
- [x] Middlewares
- [ ] Query parameters
- [ ] Response utilities like JSON(), html() and text()
- [ ] Multi-threading for concurrent request handling
- [ ] SSL/TLS support

## Usage

The following example shows how to create a server, define routes, and start the server:

```c
#include "server.h"

void say_hello(Request* req, Response* res)
{
  res->status_code = 200;
  res->content_type = "text/html";
  res->body = "<html><h1>Hello Route</h1></html>";
}

void say_hi(Request* req, Response* res)
{
  res->status_code = 200;
  res->content_type = "text/html";
  res->body = "<html><h1>Hi Route</h1></html>";
}

void say_hi_with_params(Request *req, Response *res)
{
  char *id = get_param(req, "id");
  char *name = get_param(req, "name");
  char *age = get_param(req, "age");
  char *not_found = get_param(req, "NOTFOUND");

  printf("id: %s\n", id);
  printf("name: %s\n", name);
  printf("age: %s\n", age);
  printf("not_found: %s\n", not_found);

  res->status_code = 200;
  res->content_type = "text/json";
  res->body = "{\"JSON?\": \"Kinda JSON\"}";
}

int main()
{
  Server* tut = create_server();

  route(tut, "GET", "/hello", say_hello);
  route(tut, "POST", "/hi", say_hi);
  route(tut, "GET", "/hi/:id/hello/:name/:age/hola", say_hi_with_params);

  tlisten(tut, 4000);

  return 0;
}
```

### Explanation of the Syntax

- **`create_server()`**: Initializes a new server instance.
- **`route(Server* server, const char* method, const char* path, void (*handler)(Request*, Response*))`**: Defines a route for the server. Parameters:

  - **`server`**: Pointer to the server instance.
  - **`method`**: HTTP method (e.g., "GET", "POST").
  - **`path`**: Endpoint path (e.g., "/hello").
  - **`handler`**: Function pointer to the handler function for this route.

- **`tlisten(Server* server, int port)`**: Starts the server, listening on the specified port. Here, `tut` listens on port `4000`.

- **Handler Functions (e.g., `say_hello`, `say_hi`)**:
  - Each handler function takes a `Request*` and `Response*` as parameters.
  - Inside the handler, you set response attributes:
    - **`status_code`**: HTTP status code (e.g., `200` for OK).
    - **`content_type`**: MIME type of the response (e.g., `"text/html"`).
    - **`body`**: The HTML content or response body sent to the client.

## Getting Started

1. **Build the Project**:

   ```sh
   make
   ```

2. **Send a request**:

   ```sh
   curl -X POST localhost:4000/hi \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer YOUR_ACCESS_TOKEN" \
     -d '{"key1":"value1", "key2":"value2"}'
   ```

3. **Configure**:
   Modify parameters in `main.c` or extend features by adding additional files in `src` and headers in `include`.
