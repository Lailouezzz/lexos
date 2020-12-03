#!/usr/bin/make -f
include Makefile.vars Makefile.msg

# ---
# General targets
# ---

# Build everything

all: all-kernel

# Create image

create-image: $(BOOTABLE_IMG)

# Run image on qemu

run-qemu: $(BOOTABLE_IMG)
	$(call qcmd,qemu-system-x86_64 -m 2G -smp 4 -hda $(BOOTABLE_IMG))

# Run image on qemu debug mode

run-qemu-debug: $(BOOTABLE_IMG)
	$(if $(DEBUG),, \
		$(call wmsg,Warning : debugging with qemu without debug symbols) \
	)
	$(call qcmd,qemu-system-x86_64 -m 2G -smp 4 -hda $(BOOTABLE_IMG) -S -s)

# Mostly clean (clean everything but the end result)

mostlyclean:
	$(call rmsg,Removing the object folder ($(OBJ_DIR)))
	$(call qcmd,$(RM) -rf $(OBJ_DIR))

mclean: mostlyclean

# Clean everything

clean: mostlyclean
	$(call rmsg,Removing the binary folder ($(BIN_DIR)))
	$(call qcmd,$(RM) -rf $(BIN_DIR))

fclean: clean

# To original state

mrproper: clean
	$(call rmsg,Removing the bootable image ($(BOOTABLE_IMG)))
	$(call qcmd,$(RM) -f $(BOOTABLE_IMG))
	$(call rmsg,Removing the makefile configuration)
	$(call qcmd,$(RM) -f Makefile.cfg)
	$(call rmsg,Cleaning submodule limine)
	$(call qcmd,$(MAKE) -C ./thirdparty/limine distclean)

# Remake everything

re: clean all

.PHONY: all create-image run-qemu run-qemu-debug mostlyclean mclean clean fclean mrproper re

# ---
# Build target for kernel
# ---

all-kernel: $(K_BIN)

$(K_BIN): $(K_LDSCRIPT) $(K_OBJS)
	$(call qcmd,$(MKDIR) -p $(@D))
	$(call bcmd,ld,$^,$(CC) -o $@ $(K_OBJS) $(K_LDFLAGS))
	$(call omsg,Kernel is stored at $(K_BIN))

# Build kernel C file
$(K_OBJ_DIR)%.c.o: $(K_SRC_DIR)%.c
	$(call qcmd,$(MKDIR) -p $(@D))
	$(call bcmd,cc,$<,$(CC) -o $@ $< $(K_CFLAGS))

# Build kernel ASM file
$(K_OBJ_DIR)%.s.o: $(K_OBJ_DIR)%.s
	$(call qcmd,$(MKDIR) -p $(@D))
	$(call bcmd,as,$<,$(AS) -o $@ $< $(K_ASFLAGS))

# Preprocessor for asm files
$(K_OBJ_DIR)%.s: $(K_SRC_DIR)%.S
	$(call qcmd,$(MKDIR) -p $(@D))
	$(call bcmd,pp,$<,$(CC) -E -o $@ $< $(K_ASPPFLAGS))

-include $(K_DEPS)

# ---
# Bootable image run qemu etc
# ---

$(BOOTABLE_IMG): $(K_BIN) limine.cfg ./thirdparty/limine/limine-install
	$(call qcmd,$(RM) -f $@)
	$(call qcmd,dd if=/dev/zero bs=1M count=0 seek=64 of=$@)
	$(call qcmd,parted -s $@ mklabel msdos)
	$(call qcmd,parted -s $@ mkpart primary 1 100%)
	$(call qcmd,echfs-utils -m -p0 $@ quick-format 32768)
	$(call qcmd,echfs-utils -m -p0 $@ import $(K_BIN) kernel.elf)
	$(call qcmd,echfs-utils -m -p0 $@ import limine.cfg limine.cfg)
	$(call qcmd,echfs-utils -m -p0 $@ import ../limine/stage2.map stage2.map)
	$(call qcmd,./thirdparty/limine/limine-install \
			./thirdparty/limine/limine.bin $@)
	$(call omsg,You can now run the $(BOOTABLE_IMG) on qemu (make run-qemu))

.PHONY: all-kernel

# ---
# Third pary targets
# ---

./thirdparty/limine/limine-install:
	$(call qcmd,$(MAKE) -C ./thirdparty/limine limine-install)

# ---
# Errors targets
# ---

Makefile.cfg:
	$(error "Makefile.cfg missing did you configure ?" )
