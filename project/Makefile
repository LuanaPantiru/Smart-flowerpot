CC=g++
CFLAGS= -std=c++1z -Wall -Wextra
NAME=a.out # numele executabilului final

SRCS_CPP := $(wildcard src/*.cpp)
SRCS_HPP := $(wildcard src/include/*.hpp)
SRCS_O := $(SRCS:%.cpp=%)
	
compile: $(SRCS_CPP) $(SRCS_HPP)
	@$(CC) $(CFLAGS) $(SRCS_CPP) -o $(NAME) -lpistache -lcrypto -lssl -lpthread -lpaho-mqttpp3 -lpaho-mqtt3as
	@echo "\nCompile finished"

run:
	./$(NAME)
