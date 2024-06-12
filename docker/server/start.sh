#!/bin/bash

gcc -o mini_server hello_world_fcgi.c -lfcgi
spawn-fcgi -p 8080 ./mini_server
nginx -g 'daemon off;'
nginx -s reload
