# (C) Mladen Stupar

include tools_path.mk

all: ls cp mv grep

mkbin:
	mkdir -p $(BINARIES_PATH)

common:
	make -C $(COMMON_PATH) all

# Commands here
ls: mkbin common
	mkdir -p $(BINARIES_PATH)/ls
	make -C $(CMD_PATH)/ls

cp: mkbin common
	mkdir -p $(BINARIES_PATH)/cp
	make -C $(CMD_PATH)/cp

mv: mkbin common
	mkdir -p $(BINARIES_PATH)/mv
	make -C $(CMD_PATH)/mv

grep: mkbin common
	mkdir -p $(BINARIES_PATH)/grep
	make -C $(CMD_PATH)/grep

# Clean all
clean:
	rm -rf $(BINARIES_PATH)/
