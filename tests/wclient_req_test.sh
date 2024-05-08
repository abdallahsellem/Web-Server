#!/bin/bash

# Number of requests to send
NUM_REQUESTS=100

# Server details
SERVER_HOST="localhost"
SERVER_PORT="8004"
REQUEST_PATH="/spin.cgi"

# Send multiple requests concurrently
for ((i=0; i<$NUM_REQUESTS; i++)); do
    ./wclient $SERVER_HOST $SERVER_PORT $REQUEST_PATH &
done
