# As seen in https://spin.atomicobject.com/2016/08/26/makefile-c-projects/ 

MAIN_EXEC ?= main.bin
MAIN_OMP_EXEC ?= main_omp.bin
PROPERTIES_EXEC ?= properties.bin

BUILD_DIR ?= ./build
BIN_DIR ?= ./bin
SRC_DIR ?= ./src

SRCS := main.c graph.c queue.c utils.c
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

SRCS_PROPERTIES := properties.c
SRCS_PROPERTIES := $(addprefix $(SRC_DIR)/, $(SRCS_PROPERTIES))

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

OBJS_PROPERTIES := $(SRCS_PROPERTIES:%=$(BUILD_DIR)/%.o)
DEPS_PROPERTIES := $(OBJS_PROPERTIES:.o=.d)

INC_DIR := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIR))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -O3

MKDIR_P ?= mkdir -p

all: $(BIN_DIR)/$(MAIN_EXEC) $(BIN_DIR)/$(PROPERTIES_EXEC)

# Main binary executable
$(BIN_DIR)/$(MAIN_EXEC): $(OBJS)
	@$(MKDIR_P) $(dir $@)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) 

# Properties binary executable
$(BIN_DIR)/$(PROPERTIES_EXEC): $(OBJS_PROPERTIES)
	@$(MKDIR_P) $(dir $@)
	$(CC) $(OBJS_PROPERTIES) -o $@ $(LDFLAGS)

# C source
$(BUILD_DIR)/%.c.o: %.c
	@$(MKDIR_P) $(dir $@)
	$(CC) -fopenmp $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean_build:
	$(RM) -r $(BUILD_DIR)

clean:
	$(RM) -r $(BUILD_DIR) $(BIN_DIR)

-include $(DEPS)
