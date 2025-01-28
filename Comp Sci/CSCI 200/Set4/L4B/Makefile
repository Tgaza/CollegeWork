# A line starting with a has is a comment, we'll build up
# the below example

TARGET = L4B
SRC_FILES = main.cpp test_suite.cpp LinkedList.cpp

# DO NOT EDIT BELOW HERE
CXX = g++
CFLAGS = -Wall -g -std=c++11
OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
else
	DEL = rm
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

.cpp.o:
	$(CXX) $(CFLAGS) -o $@ -c $<

clean:
	$(DEL) $(TARGET) $(OBJECTS)

# DEPENDENCIES
test_suite.o: test_suite.cpp test_suite.h LinkedList.h Node.h
LinkedList.o: LinkedList.cpp LinkedList.h Node.h
main.o: main.cpp test_suite.h Node.h
