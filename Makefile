SRC_DIR = src
INC_DIR = include
OBJ_DIR = build


C_SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_SRC_FILES = $(wildcard $(SRC_DIR)/*.s)
C_OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_SRC_FILES))
ASM_OBJ_FILES = $(patsubst $(SRC_DIR)/%.s,$(OBJ_DIR)/%.o,$(ASM_SRC_FILES))
OBJ_FILES = $(C_OBJ_FILES) $(ASM_OBJ_FILES)

CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -I$(INC_DIR) -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf os.iso

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		mkdir -p $(OBJ_DIR)
		$(CC) $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
		mkdir -p $(OBJ_DIR)
		$(AS) $(ASFLAGS) $< -o $@

kernel.elf: $(OBJ_FILES)
		ld $(LDFLAGS) $(OBJ_FILES) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
							-b boot/grub/stage2_eltorito    \
							-no-emul-boot                   \
							-boot-load-size 4               \
							-A os                           \
							-input-charset utf8             \
							-quiet                          \
							-boot-info-table                \
							-o os.iso                       \
							iso

clean:
	rm -rf $(OBJ_DIR) kernel.elf os.iso
