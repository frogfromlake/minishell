FROM debian:buster
RUN apt-get upgrade -y
RUN apt-get update -y
RUN apt-get install make nano valgrind gcc lib32readline7 lib32readline-dev  -y
