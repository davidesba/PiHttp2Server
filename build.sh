#!/bin/bash

docker build -t crosscompile . | awk '{if (($1 == "Step")||($1 == "--->")){print $0;}print $0 > "build.log"; if ($0 ~ /returned a non-zero code/) {exit 1;}}'
retval=$?

if [ $retval -ne 0 ]; then
   echo "Error generating build. Please check build.log for details"
   exit $retval
fi

docker run -u root --entrypoint=/bin/sh --rm -i -v `pwd`:/build crosscompile << COMMANDS
echo "Copy build files to host..."
cd /root/raspberry/
tar -zcf build.tgz ./bin ./lib
cp -f /root/raspberry/build.tgz /build
echo Changing owner from \$(id -u):\$(id -g) to $(id -u):$(id -u)
chown -R $(id -u):$(id -u) /build
COMMANDS
