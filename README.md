# PiHttp2Server
Http2 server for Raspberry Pi based on nghttp2.

Cross compilation is done using Docker.

Basic file server is mounted on top of http2:

![screenshot](https://user-images.githubusercontent.com/30145878/36399229-39902974-15cb-11e8-991a-b3e1783811cb.png)

Rest API on top of HTTP2 using MongoDB to store data (Not complete):

External nodes can store information about current cryptomining status, and consult several statistics based on the stored data.

# Requirements
Docker

# Compilation
run ./build.sh

build.tgz will be generated including binary and related libraries


