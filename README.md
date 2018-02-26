# PiHttp2Server
Http2 server for Raspberry Pi based on nghttp2.

Cross compilation is done using Docker.

Basic file server is mounted on top of http2:

![screenshot](https://user-images.githubusercontent.com/30145878/36697529-9cdce072-1b47-11e8-844e-490a6fbf2edc.png)

Rest API on top of HTTP2 using MongoDB to store data (Not complete):

External nodes can store information about current cryptomining status, and consult several statistics based on the stored data.

# Requirements
Docker

# Compilation
run ./build.sh

build.tgz will be generated including binary and related libraries


