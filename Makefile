APP := studentmanager
SRC := main.c
CC  := gcc
CFLAGS := -Wall -Wextra -O2

all: $(APP)

$(APP): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(APP)

run: $(APP)
	./$(APP)

clean:
	rm -f $(APP)

.PHONY: run clean
