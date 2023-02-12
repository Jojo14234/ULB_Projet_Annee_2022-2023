#ifndef _EXCEPTIONS_HPP
#define _EXCEPTIONS_HPP

#include <iostream>


// Server

class ServerException : public std::exception {
public:
    virtual const char* what() const noexcept override =0;
};

class CreateServerException : public ServerException {
    static inline const char* msg = "Error while creating server";
public:
    const char* what() const noexcept override { return msg; }
};

class ConnectClientServerException : public ServerException {
    static inline const char* msg = "Error while connecting a client";
public:
    const char* what() const noexcept override { return msg; }
};

class PipeServerException : public ServerException {
public:
    virtual const char* what() const noexcept override =0;
};

class ReadPipeServerException : PipeServerException {
    static inline const char* msg = "Error while reading in the socket";
public:
    const char* what() const noexcept override { return msg; }
};

class WritePipeServerException : PipeServerException {
    static inline const char* msg = "Error while writing in the socket";
public:
    const char* what() const noexcept override { return msg; }
};


// Client
class ClientException : public std::exception {
public:
    virtual const char* what() const noexcept override =0;
};

class ConnectServerClientException : public ClientException {
    static inline const char* msg = "Error while connecting to server";
public:
    const char* what() const noexcept override { return msg; }
};

class PipeClientException : public ClientException {
public:
    virtual const char* what() const noexcept override =0;
};

class ReadPipeClientException : PipeClientException {
    static inline const char* msg = "Error while reading in the socket";
public:
    const char* what() const noexcept override { return msg; }
};

class WritePipeClientException : PipeClientException {
    static inline const char* msg = "Error while writing in the socket";
public:
    const char* what() const noexcept override { return msg; }
};

#endif