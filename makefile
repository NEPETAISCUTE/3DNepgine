P_SEP := /

TARGET := main
EXT  := cpp
COMP := g++

SRC_DIR := src/
OBJ_DIR := objs/
INC_DIR := include/
INC_DIR := $(addprefix -I , $(sort $(dir $(INC_DIR))))

SRC_FILES := $(wildcard $(SRC_DIR)/*.$(EXT)) $(wildcard $(SRC_DIR)/**/*.$(EXT))
#to manually add files
SRC_FILES := $(SRC_FILES) glad/glad.c

OBJ_FILES := $(patsubst %.$(EXT),%.o, $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC_FILES)))


OBJ_FLAGS := -std=c++20 -g
LIB_FLAGS := -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl


build: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(COMP) $^ -o $@ $(OBJ_FLAGS) $(LIB_FLAGS) $(INC_DIR)

start:
	./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

# Obj and Header files compiling

objects: $(OBJ_FILES)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(EXT)
	$(COMP) -c $< -o $@ $(OBJ_FLAGS) $(INC_DIR)

# File Cleaners

cleanall:
	$(RM) $(OBJ_DIR)$(P_SEP)*.o
	$(RM) $(OBJ_DIR)$(P_SEP)**$(P_SEP)*.o
	$(RM) $(TARGET)

clean: 
	$(RM) $(TARGET)

# Makefile Debugging/Usefull Functions

subdir:
	mkdir -p $(sort $(dir $(OBJ_FILES)))
	touch -f $(addsuffix DO_NOT_REMOVE,$(sort $(dir $(OBJ_FILES))))

restart: 
	make build
	make start

rebuild:
	make clean
	make build

redebug:
	make clean
	make debug

# Makefile Debugging/Usefull Functions

showFiles:
	@echo Source files
	@echo $(SRC_FILES)
	@echo 
	@echo Object files
	@echo $(OBJ_FILES)
	@echo 