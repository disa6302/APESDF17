#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xbba89470, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x916eb858, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x2265621a, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0xf04c0e09, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0xeb578354, __VMLINUX_SYMBOL_STR(gpiod_unexport) },
	{ 0x6bc3fbc0, __VMLINUX_SYMBOL_STR(__unregister_chrdev) },
	{ 0xb9f5c30e, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x5e106075, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x39dae10a, __VMLINUX_SYMBOL_STR(__register_chrdev) },
	{ 0xce01f638, __VMLINUX_SYMBOL_STR(gpiod_get_raw_value) },
	{ 0x1e438886, __VMLINUX_SYMBOL_STR(gpiod_export) },
	{ 0x2f199c7, __VMLINUX_SYMBOL_STR(gpiod_direction_output_raw) },
	{ 0x47229b5c, __VMLINUX_SYMBOL_STR(gpio_request) },
	{ 0xe5a0ff85, __VMLINUX_SYMBOL_STR(gpiod_set_raw_value) },
	{ 0x9af2fd11, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0x822137e2, __VMLINUX_SYMBOL_STR(arm_heavy_mb) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

