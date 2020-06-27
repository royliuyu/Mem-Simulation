TARGET = btree
CC = gcc
CCP = g++
CSRCS = $(wildcard *.c)
CPPSRCS = $(wildcard *.cpp)
OBJS = $(CSRCS:.c=.o) $(CPPSRCS:.cpp=.o)
DEBUG_FLAG =
INC_PATH =
LIB_PATH =

$(TARGET) : $(OBJS)
	$(CCP) $(DEBUG_FLAG) $^ -o $@;
	@echo "Made it successfully!"
%.o : %.c
	$(CC) $(DEBUG_FLAG) $< -c -o $@ $(INC_PATH) $(LIB_PATH)

%.o : %.cpp
	$(CCP) $(DEBUG_FLAG) $< -c -o $@ $(INC_PATH) $(LIB_PATH)

.PHONY:clean
clean:
	rm -f $(OBJS) $(TARGET)
