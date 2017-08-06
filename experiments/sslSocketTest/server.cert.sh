#!/bin/sh
openssl genrsa -out server.key 4096
openssl req -x509 -new -nodes -extensions v3_ca -key server.key -days 365 -out server.crt
