#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/GLP");

static int hello_module_init(void) {
	printk(KERN_INFO "Hellow world~\n");
	return 0;
}

static void hello_module_exit(void) {
	printk(KERN_INFO "Goodbye world~\n");
}

module_init(hello_module_init);
module_exit(hello_module_exit);
