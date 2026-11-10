GNL_FILES := ../get_next_line.c ../get_next_line_utils.c
GNL_HEADER := ../.

TEST_DIR := src
OBJ_DIR := obj

TEST_FILES := $(notdir $(wildcard $(TEST_DIR)/*.c))
OBJ := $(addprefix $(OBJ_DIR)/, $(TEST_FILES:.c=.o))
TEST_FILES := $(addprefix $(TEST_DIR)/,$(TEST_FILES))


UNITY_DIR := unity
UNITY_FILES := unity.c \
			   unity.h \
			   unity_internals.h
UNITY_FILES := $(addprefix $(UNITY_DIR)/,$(UNITY_FILES))

UNITY_URL_BASE := https://raw.githubusercontent.com/ThrowTheSwitch/Unity/refs/heads/master/src

#CBUFFER_SIZE := -D BUFFER_SIZE=1
CFLAGS := -I$(GNL_HEADER) -I$(TEST_DIR) -I$(UNITY_DIR) -Wall -Wextra -Werror
CFLAGS_DEBUG = -g
CLINKER := $(UNITY_DIR)/unity.c $(GNL_FILES)

# ------------------------------------------------------------------------
# Methods ----------------------------------------------------------------
# ------------------------------------------------------------------------

####################
# Tester compilation
####################

test: test0.exe
	./test0.exe

test_all: test0.exe test1.exe test5.exe test10.exe test50.exe test1000.exe
	@echo "Normal test |"
	@echo =============
	./test0.exe
	@echo "BUFFER_SIZE = 1 |"
	@echo =================
	./test1.exe
	@echo "BUFFER_SIZE = 5 |"
	@echo =================
	./test5.exe
	@echo "BUFFER_SIZE = 10 |"
	@echo ==================
	./test10.exe
	@echo "BUFFER_SIZE = 50 |"
	@echo ==================
	./test50.exe
	@echo "BUFFER_SIZE = 1000 |"
	@echo ====================
	./test1000.exe

test0.exe: $(UNITY_FILES) $(OBJ)
	cc $(OBJ) $(CLINKER) $(CFLAGS_DEBUG) -o $@

test1.exe: $(UNITY_FILES) $(OBJ)
	cc $(OBJ) $(CLINKER) $(CFLAGS_DEBUG) -o $@ -D BUFFER_SIZE=1

test5.exe: $(UNITY_FILES) $(OBJ)
	cc $(OBJ) $(CLINKER) $(CFLAGS_DEBUG) -o $@ -D BUFFER_SIZE=5

test10.exe: $(UNITY_FILES) $(OBJ)
	cc $(OBJ) $(CLINKER) $(CFLAGS_DEBUG) -o $@ -D BUFFER_SIZE=10

test50.exe: $(UNITY_FILES) $(OBJ)
	cc $(OBJ) $(CLINKER) $(CFLAGS_DEBUG) -o $@ -D BUFFER_SIZE=50

test1000.exe: $(UNITY_FILES) $(OBJ)
	cc $(OBJ) $(CLINKER) $(CFLAGS_DEBUG) -o $@ -D BUFFER_SIZE=1000

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	cc $(CFLAGS) $(CFLAGS_DEBUG) $(CFLAGS_MEMORY) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf obj

fclean: clean unity_clean
	rm -f test0.exe test1.exe test5.exe test10.exe test50.exe test1000.exe

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

$(UNITY_DIR)/unity.h: | $(UNITY_DIR)
	wget --quiet -O $@ $(UNITY_URL_BASE)/unity.h

$(UNITY_DIR)/unity_internals.h: | $(UNITY_DIR)
	wget --quiet -O $@ $(UNITY_URL_BASE)/unity_internals.h

.PHONY: test test_all test clean unity_init unity_clean
