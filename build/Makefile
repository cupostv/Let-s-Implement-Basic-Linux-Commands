# (C) Mladen Stupar

include tools_path.mk

all: ls cp mv grep

mkbin:
	echo "Creating binaries folder $(BINARIES_PATH)..."
	mkdir -p $(BINARIES_PATH)
	echo "Done."

common:
	echo "Compiling common module..."
	make -C $(COMMON_PATH) all
	echo "Done."

# Commands here
ls: mkbin common
	echo "Compiling ls command..."
	mkdir -p $(BINARIES_PATH)/ls
	make -C $(CMD_PATH)/ls
	echo "Done."

cp: mkbin common
	echo "Compiling cp command..."
	mkdir -p $(BINARIES_PATH)/cp
	make -C $(CMD_PATH)/cp
	echo "Done."

mv: mkbin common
	echo "Compiling mv command..."
	mkdir -p $(BINARIES_PATH)/mv
	make -C $(CMD_PATH)/mv
	echo "Done."

grep: mkbin common
	echo "Compiling grep command..."
	mkdir -p $(BINARIES_PATH)/grep
	make -C $(CMD_PATH)/grep
	echo "Done."

# Clean all
clean:
	echo "Removing binaries folder $(BINARIES_PATH)..."
	rm -rf $(BINARIES_PATH)/
	echo "Done."
