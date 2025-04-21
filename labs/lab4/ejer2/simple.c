#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>

int simple_init(void)
{
  printk(KERN_INFO "Loading Module\n!Hola mundo!\n");
  return 0;
}

void simple_exit(void)
{
  printk(KERN_INFO "Removing Module\nAdiós mundo.\n");
}

module_init(simple_init);
module_exit(simple_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hola mundo probando el kernel de Linux");
MODULE_AUTHOR("Josué Say");
