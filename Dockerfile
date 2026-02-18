FROM gcc:latest

RUN apt-get update && apt-get install -y \
    gdb \
    binutils

WORKDIR /mnt
