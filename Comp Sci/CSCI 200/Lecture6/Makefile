TARGET = Lecture06
SRC_FILES = lecture06.cpp

## DO NOT EDIT ANYTHING BELOW THIS LINE

CXX = g++
CFLAGS = -Wall -g

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
else
	DEL = rm
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $^

debug: CFLAGS += -DDEBUG
debug: clean $(TARGET)

%.o: %.cpp
	$(CXX) -o $@ -c $<

clean:
	$(DEL) $(TARGET) $(OBJECTS)
