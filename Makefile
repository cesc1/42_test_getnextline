# --------------------------------------------------------------------------
# Variables ----------------------------------------------------------------
# --------------------------------------------------------------------------

# CONFIG

CC = cc

TEST_DIR := src
BUILD_ROOT := build
UNITY_DIR := unity

GNL_FILES = ../get_next_line.c ../get_next_line_utils.c
CPP_FILES = $(UNITY_DIR)/unity.c $(GNL_FILES)
GNL_HEADER := ../.

UNITY_URL_BASE := https://raw.githubusercontent.com/ThrowTheSwitch/Unity/refs/heads/master/src

BUFFER_SIZES := 1 5 10 50 1000

# CC FLAGS

CFLAGS += -Wall -Wextra -Werror -I$(GNL_HEADER) -I$(TEST_DIR) -I$(UNITY_DIR)
DEBUG_FLAGS := -g

# BUILD

ifdef BONUS
	BUILD_DIR := $(BUILD_ROOT)/bonus
	GNL_FILES := $(patsubst %.c,%_bonus.c,$(GNL_FILES))
	CFLAGS += -D TEST_BONUS
else
	BUILD_DIR := $(BUILD_ROOT)/normal
endif

# FILES

TEST_FILES := $(wildcard $(TEST_DIR)/*.c)

OBJ := $(patsubst $(TEST_DIR)/%.c,$(BUILD_DIR)/%.o,$(TEST_FILES))

UNITY_FILES := $(addprefix $(UNITY_DIR)/, unity.c unity.h unity_internals.h)

TEST_BINS := $(addprefix $(BUILD_DIR)/test, \
	$(addsuffix .exe, 0 $(BUFFER_SIZES)))


# ------------------------------------------------------------------------
# Methods ----------------------------------------------------------------
# ------------------------------------------------------------------------

.PHONY: all test test_all test_bonus clean fclean unity_init unity_clean

# Test

test: $(BUILD_DIR)/test0.exe
	./$<

test_all: $(TEST_BINS)
	@for size in 0 $(BUFFER_SIZES); do \
		echo "==================="; \
		if [ $$size -eq 0 ]; then \
			echo "Default BUFFER_SIZE |"; \
		else \
			echo "BUFFER_SIZE = $$size |"; \
		fi; \
		echo "==================="; \
		./$(BUILD_DIR)/test$$size.exe || exit $$?; \
	done

test_bonus:
	$(MAKE) BONUS=1 test_all

# Compilation

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

$(BUILD_DIR)/test%.exe: $(OBJ) $(UNITY_FILES) Makefile
	@mkdir -p $(@D)
	$(CC) $(OBJ) $(CPP_FILES) $(CFLAGS) $(DEBUG_FLAGS) -o $@ \
	$(if $(filter 0,$*),,-D BUFFER_SIZE=$*)

clean:
	rm -rf $(BUILD_ROOT)

fclean: clean unity_clean

# ###########
# Unity setup
# ###########

unity_init: $(UNITY_FILES)

unity_clean:
	rm -rf unity

$(UNITY_DIR):
	mkdir -p $@

$(UNITY_DIR)/unity.c: | $(UNITY_DIR)
	wget --quiet -O $@ $(UNITY_URL_BASE)/unity.c

$(UNITY_DIR)/%.h: | $(UNITY_DIR)
	wget --quiet -O $@ $(UNITY_URL_BASE)/$(@F)
