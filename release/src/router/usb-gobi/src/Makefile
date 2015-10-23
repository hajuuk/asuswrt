TOOLLIB=$(shell dirname $(shell which $(CXX)))/../lib

CFLAGS += -Iinclude
LDFLAGS += -Llib -lGobiConnectionMgmt -L$(TOOLLIB) -lrt -lpthread -lstdc++ -lm -ldl
#-lstdc++

SOURCE = sample/Sample_Main.cpp
TARGET = gobi gobi_api

all: $(TARGET)

gobi: $(SOURCE)
	$(CC) $(SOURCE) -o $@ $(LDFLAGS) $(CFLAGS)

gobi_api: sample/gobi_api.cpp
	$(CC) $^ -o $@ $(LDFLAGS) $(CFLAGS)

clean:
	rm -f $(TARGET)

install: $(TARGET)


.PHONY: all clean install

