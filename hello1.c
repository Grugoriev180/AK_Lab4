#include <hello1.h>

MODULE_AUTHOR("Kostia Hrihoriev");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

struct timeit_list {
	struct list_head node;
	ktime_t before;
	ktime_t after;
};

static struct list_head head_node = LIST_HEAD_INIT(head_node);

int print_hello(uint counter)
{
	struct timeit_list *list, *tmp;
	uint i;


	if (counter == 0) {
		pr_warn("The parameter = 0\n");
	} else if (counter >= 5 && counter <= 10) {
		pr_warn("The parameter between 5 and 10\n");
	} else if (counter > 10) {
		pr_err("The parameter > 10\n");
		return -EINVAL;
	}

	for (i = 0; i < counter; i++) {
		list = kmalloc(sizeof(struct timeit_list), GFP_KERNEL);
		if (ZERO_OR_NULL_PTR(list))
			goto tidy_away;
		list->before = ktime_get();
		pr_info("Hello, world!\n");
		list->after = ktime_get();
		list_add_tail(&list->node, &head_node);
	}
	return 0;

tidy_away:
	list_for_each_entry_safe(list, tmp, &head_node, node) {
		list_del(&list->node);
		kfree(list);
	}
	pr_err("Error! No memory\n");
	return -1;
}
EXPORT_SYMBOL(print_hello);


static int __init init_hello(void)
{
	pr_info("hello1 has been initiated\n");
	return 0;
}

static void __exit exit_hello(void)
{
	struct timeit_list *list, *tmp;

	list_for_each_entry_safe(list, tmp, &head_node, node) {
		pr_info("Time: %lld", list->after - list->before);
		list_del(&list->node);
		kfree(list);
	}
	BUG_ON(!list_empty(&head_node));
	pr_info("hello1 has been unloaded\n");
}

module_init(init_hello);
module_exit(exit_hello);
