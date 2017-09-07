#!/bin/bash
function execute() {
	cd /usr/src
	sudo wget https://www.kernel.org/pub/linux/kernel/v3.x/linux-3.9.3.tar.xz
	sudo tar -xvJf linux-3.9.3.tar.xz
	cd linux-3.9.3
	sudo make menuconfig
	sudo make
	sudo make modules
	sudo make modules_install
	sudo make install
	echo "New kernel linux-3.9.3 compiled....run reboot command to verify this version"
}

execute
