
APP_NAME = signal
APP_OBJS = signal.o
CC = gcc
INC = ./
CFLAG += -g

.PHONY : all

all : $(APP_NAME) signal_send

$(APP_NAME) : $(APP_OBJS)
	$(CC) $(CFLAG) $(APP_OBJS) -o $(APP_NAME)

signal_send : signal_send.o
	$(CC) $(CFLAG) $^ -o $@
	
%.o : %.c
	$(CC) -c $(CFLAG) $^ -o $@

.PHONY : clean

clean :
	rm -f .o
	rm -f $(APP_NAME) $(APP_OBJS) signal_send