CC=gcc
CFLAGS=-Wall -Wextra -g -std=gnu99 -I./include/
AR=ar
ARFLAGS=rsc

export BUILD=build
TARGET=$(BUILD)/lib/libcursel.a

SUBDIRS=$(shell cd src && find * -type d)
MKSUBDIRS=$(addprefix $(BUILD)/obj/, $(SUBDIRS))
SRCS=$(shell cd src && find * -type f -name '*.c')
OBJS=$(addprefix $(BUILD)/obj/, $(SRCS:.c=.o))

.PHONY: all
all: dirs $(MKSUBDIRS) $(TARGET) headers

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

.PHONY: dirs
dirs:
	mkdir -p $(BUILD)
	mkdir -p $(BUILD)/bin
	mkdir -p $(BUILD)/include/cursel
	mkdir -p $(BUILD)/obj
	mkdir -p $(BUILD)/lib

.PHONY: headers
headers:
	cp -R include/* $(BUILD)/include/cursel

.PHONY: examples
examples:
	$(MAKE) -C examples

# Mkdir template
define mk_subdir
$(BUILD)/obj/$(1):
	mkdir -p $$@
endef

# Build template
define compile_subdir
$(BUILD)/obj/$(1)%.o: src/$(1)%.c
	$(CC) $(CFLAGS) -c $$< -o $$@
endef

# Build root
$(eval $(call mk_subdir,))
$(eval $(call compile_subdir,))

# Build subdirectories
$(foreach subdir, $(SUBDIRS), $(eval $(call mk_subdir,$(subdir))))
$(foreach subdir, $(SUBDIRS), $(eval $(call compile_subdir,$(subdir))))

.PHONY: clean
clean:
	rm -rf build

# Formatting
FORMAT=clang-format
FORMAT_CHECK_FLAGS=--dry-run --Werror
FORMAT_FIX_FLAGS=-i

FORMAT_FILES=$(shell find src -type f)

.PHONY: checkformat
checkformat:
	$(FORMAT) $(FORMAT_CHECK_FLAGS) $(FORMAT_FILES)

.PHONY: format
format:
	$(FORMAT) $(FORMAT_FIX_FLAGS) $(FORMAT_FILES)
