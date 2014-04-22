SRC_PATH = ./src
BUILD_PATH = ./build

CPP = g++
CFLAGS = -ggdb -std=c++11 -Werror -DDEBUG
LFLAGS =

APP_NAME = calc
APP_PATH = $(BUILD_PATH)/$(APP_NAME)

BUILD_OBJECTS = $(BUILD_PATH)/main.o

.PHONY: build
build:	$(APP_PATH)

.PHONY: run
run: build 
	$(APP_PATH)

$(APP_PATH): $(BUILD_OBJECTS)
	$(CPP) $(LFLAGS) $(BUILD_OBJECTS) -o $@

$(BUILD_PATH)/main.o: $(SRC_PATH)/main.cpp $(SRC_PATH)/*.h
	$(CPP) $(CFLAGS) -c $< -o $@

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp $(SRC_PATH)/*.h
	$(CPP) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_PATH)/*.o $(APP_PATH) 
