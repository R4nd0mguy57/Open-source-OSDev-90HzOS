printf "Enter device: /dev/"
read DEVICE
sudo dd if=./90HzOS/boot/bin/bootloader of="/dev/$DEVICE" bs=512 count=1 conv=notrunc
sudo dd if=./90HzOS/kernel/bin/full/kernel.bin of="/dev/$DEVICE" bs=512 seek=2048 conv=notrunc
sync

