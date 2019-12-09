#!/bin/bash
xterm -e npm run serve &
xterm -e go run server.go &
xterm -e ./ngrok http --subdomain drawstick 8080 &
xterm -e ./ngrok http --subdomain drawstickserver 9080
