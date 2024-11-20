//hello−5.c − Demonstrates command line argument passing to a module.
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Peter Jay Salzman");

static int peso = 0;
static int talla = 0;
static char *HM = "-";
/*
* module_param(foo, int, 0000)
* The first param is the parameters name
* The second param is it's data type
* The final argument is the permissions bits,
* for exposing parameters in sysfs (if non−zero) at a later stage.
*/
module_param(peso, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(peso, "Peso kg");
module_param(talla, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(talla, "Talla cm");
module_param(HM, charp, 0000);
MODULE_PARM_DESC(HM, "Genero");

static int __init hello_5_init(void){
	printk(KERN_INFO "Hello, world 5\n=============\n");
	printk(KERN_INFO "peso: %d\n", peso);
	printk(KERN_INFO "talla %d\n", talla);
	printk(KERN_INFO "HM: %s\n", HM);

	return 0;
}

static void __exit hello_5_exit(void)
{
	int IMC = (peso*10000)/(talla*talla);
	if(IMC < 21) printk(KERN_INFO "DESNUTRICION, IMC = %d\n", IMC);
	else if(IMC > 21 && IMC < 26) printk(KERN_INFO "NORMAL, IMC = %d\n", IMC);
	else printk(KERN_INFO "SOBREPESO, IMC = %d\n", IMC);
}
module_init(hello_5_init);
module_exit(hello_5_exit);
