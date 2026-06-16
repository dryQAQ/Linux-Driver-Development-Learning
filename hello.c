#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

MODULE_LICENSE("Dual BSD/GPL");

static char* name ="none";
static int count=2;

module_param(name,charp,S_IRUGO);
module_param(count,int,S_IRUGO);


//内核模块的初始化
static int hello_init(void){
    int i;
    for(i=0;i<count;i++)
        printk(KERN_INFO "hello [%d]times, [%s] , the hello module has loaded.\n",i+1,name);
    return 0;

}

//内核模块卸载的时候调用
static void hello_exit(void){
    printk(KERN_INFO "goodbye ,hello模块退出.\n");

}

module_init(hello_init);
module_exit(hello_exit);

