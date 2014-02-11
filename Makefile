CC = gcc
CFLAGS = -std=c99 -g -Wall
LDFLAGS = -lpthread
TARGET = client

default: $(TARGET)

$(TARGET): $(TARGET).o
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(TARGET).o
	
$(TARGET).o: $(TARGET).c $(TARGET).h
	@$(CC) $(CFLAGS) -c $(TARGET).c

clean:
	@rm $(TARGET) *.o
