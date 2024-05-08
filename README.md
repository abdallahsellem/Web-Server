to run the server use this format :
`./wserver -d <rootdirectory> -p <port number> -t <number of threads>
`
example :
`
./wserver -d . -p 8004 -t 5

`



to Send Requests to running server use this format :
`./wclient <SERVER_HOST> <SERVER_PORT> <REQUEST_PATH>
`
example :
`
./wclient localhost  8004 /spin.cgi

`
