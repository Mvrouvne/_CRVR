# CRVR

## Overview

The **CRVR** project involves building a simple HTTP server from scratch, compliant with a subset of the HTTP/1.1 protocol. This project mimics the functionality of real-world web servers, such as handling requests and serving responses.

## Features

- **HTTP/1.1 Compliance**: Implements request parsing, response formatting, and proper handling of HTTP methods (e.g., GET, POST, DELETE).
- **Static and Dynamic Content**: Serves static files and supports dynamic responses.
- **Multiple Connections**: Handles multiple client requests simultaneously using non-blocking I/O or multi-threading.
- **Configuration Parsing**: Reads and applies server settings (e.g., ports, routes, file paths) from a configuration file.
- **Error Handling**: Responds with appropriate HTTP status codes (e.g., 404 Not Found, 500 Internal Server Error).

### Example

The server can process requests like:

```bash
curl -X GET http://localhost:8080/index.html
```

And respond with the requested file or an error message if not found.

## Key Concepts

- **Socket Programming**: Use system calls like `socket`, `bind`, `listen`, and `accept` to manage client-server communication.
- **HTTP Protocol**: Parse requests and construct responses according to the HTTP/1.1 standard.
- **Concurrency**: Manage multiple client connections using multi-threading or event-driven architectures.
- **Configuration Management**: Design a flexible parser for server configuration.

## Learning Outcomes

By completing **CRVR**, you will:

- Understand the inner workings of web servers and the HTTP protocol.
- Gain hands-on experience with low-level socket programming.
- Learn techniques for handling concurrency and asynchronous I/O.
- Improve problem-solving and debugging skills in system-level programming.

This project bridges network programming and web development, offering a deep dive into the mechanics of web servers and their interaction with clients.
