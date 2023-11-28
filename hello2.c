#include <hello1.h>

MODULE_AUTHOR("Kostia Hrihoriev");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint counter = 1;

module_param(counter, uint, 0);
MODULE_PARM_DESC(counter, "mycounter");

static int __init init_hello(void)
{
	pr_info("hello2 has been initiated\n");
	print_hello(counter);
	return 0;
}

static void __exit exit_hello(void)
{
	pr_info("hello2 has been unloaded\n");
}

module_init(init_hello);
module_exit(exit_hello);
