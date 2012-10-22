/*
 *  hello.c
 */

#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/init.h>         /* Needed for the macros */
#define DRIVER_AUTHOR "Alain Horner <alain@whatever.org>"
#define DRIVER_DESC   "A test driver"

/*  How to define parameters */
static short int myshort = 1;

module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer");

static int __init init_hello(void)
{
    printk(KERN_INFO "Hello, world \n=============\n");
    printk(KERN_INFO "myshort is a short integer: %hd\n", myshort);
    return 0;
}

static void __exit cleanup_hello(void)
{
    printk(KERN_INFO "Goodbye, world \n");
}

module_init(init_hello);
module_exit(cleanup_hello);

MODULE_LICENSE("GPL");          /* License */
MODULE_AUTHOR(DRIVER_AUTHOR);   /* Who wrote this module? */
MODULE_DESCRIPTION(DRIVER_DESC);/* What does this module do */

/*
 *  This module uses /dev/testdevice.  The MODULE_SUPPORTED_DEVICE macro might
 *  be used in the future to help automatic configuration of modules, but is 
 *  currently unused other than for documentation purposes.
 */
MODULE_SUPPORTED_DEVICE("testdevice");
