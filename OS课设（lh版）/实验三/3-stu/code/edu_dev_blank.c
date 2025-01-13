#include <asm/io.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/delay.h>
#include <linux/pid.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/atomic.h>
#include <linux/spinlock.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define EDU_DEV_MAJOR 200  /* 主设备号 */
#define EDU_DEV_NAME "edu" /* 设备名 */

struct edu_dev_info {
    resource_size_t io;
    long range, flags;
    void __iomem *ioaddr;
    int irq;
};

struct user_data {
    int id;
    atomic64_t data;
};

struct thread_data {
    struct user_data *user_data_ptr;
    int input_data;
};

// 声明函数
static int edu_driver_probe(struct pci_dev *dev, const struct pci_device_id *id);
static void edu_driver_remove(struct pci_dev *dev);

// 设备ID表
static struct pci_device_id id_table[] = {
    { PCI_DEVICE(0x1234, 0x11e8) }, // edu设备id
    { 0 } // 最后一组是0，表示结束
};

// PCI驱动结构体
static struct pci_driver pci_driver = {
    .name = "edu_driver",
    .id_table = id_table,
    .probe = edu_driver_probe,
    .remove = edu_driver_remove,
};

// 其他结构体定义
static struct edu_dev_info *edu_info;
static spinlock_t lock;
static int current_id = 0;

// 驱动的 Probe 函数
static int edu_driver_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
    int ret = 0;
    printk("executing edu driver probe function!\n");

    // 启用PCI设备
    ret = pci_enable_device(dev);
    if (ret) {
        printk(KERN_ERR "Failed to enable PCI device.\n");
        return -EIO;
    }

    // 分配内存给 edu_dev_info 实例
    edu_info = kmalloc(sizeof(struct edu_dev_info), GFP_KERNEL);
    if (!edu_info) {
        printk(KERN_ERR "Memory allocation for edu_dev_info failed.\n");
        return -ENOMEM;
    }

    // 请求设备的 I/O 和内存区域
    ret = pci_request_regions(dev, "edu_driver");
    if (ret) {
        printk("PCI request regions failed.\n");
        goto free_edu_info;
    }

    // 映射BAR的总线地址到系统内存的虚拟地址
    edu_info->ioaddr = pci_ioremap_bar(dev, 0); // 假设使用 BAR0
    if (!edu_info->ioaddr) {
        printk(KERN_ERR "Failed to map BAR to virtual memory.\n");
        goto release_regions;
    }

    // 将edu_dev_info实例与设备结构体 dev 关联
    pci_set_drvdata(dev, edu_info);

    printk("Probe succeeds. PCIE ioport addr starts at %llX, edu_info->ioaddr is 0x%p.\n", edu_info->io, edu_info->ioaddr);
    return 0;

release_regions:
    pci_release_regions(dev);
free_edu_info:
    kfree(edu_info);
    return ret;
}

// 驱动的 Remove 函数
static void edu_driver_remove(struct pci_dev *dev)
{
    struct edu_dev_info *info = pci_get_drvdata(dev);

    if (info) {
        iounmap(info->ioaddr);
        pci_release_regions(dev);
        kfree(info);
    }
    pci_disable_device(dev);
    printk("Device removed successfully.\n");
}

// 计算阶乘的内核线程
int kthread_handler(void *data)
{
    struct thread_data *thread_data_ptr = (struct thread_data *)data;
    uint64_t result = 1;
    int i;

    // 获取输入的数值并计算阶乘
    for (i = 1; i <= thread_data_ptr->input_data; i++) {
        result *= i;
    }

    // 加锁确保写入原子变量的原子性
    spin_lock(&lock);
    atomic64_set(&thread_data_ptr->user_data_ptr->data, result);
    spin_unlock(&lock);

    printk("Factorial computed: %llu\n", result);
    kfree(thread_data_ptr);
    return 0;
}

// open 函数
static int edu_dev_open(struct inode *inode, struct file *filp)
{
    struct user_data *user_data_ptr = kmalloc(sizeof(struct user_data), GFP_KERNEL);
    if (!user_data_ptr) {
        return -ENOMEM;
    }

    user_data_ptr->id = current_id++;
    atomic64_set(&user_data_ptr->data, 0);
    filp->private_data = user_data_ptr;
    return 0;
}

// close 函数
static int edu_dev_release(struct inode *inode, struct file *filp)
{
    struct user_data *user_data_ptr = filp->private_data;
    kfree(user_data_ptr); // 释放 open 时分配的内存
    return 0;
}

// ioctl 函数
long edu_dev_unlocked_ioctl(struct file *pfilp_t, unsigned int cmd, unsigned long arg)
{
    struct user_data *user_data_ptr = pfilp_t->private_data;
    if (cmd == 0) {
        // Write operation: Save the input argument (arg) into thread_data
        struct thread_data *data = kmalloc(sizeof(struct thread_data), GFP_KERNEL);
        if (!data) {
            printk(KERN_ERR "Memory allocation for thread_data failed.\n");
            return -ENOMEM;
        }
        data->user_data_ptr = user_data_ptr;
        data->input_data = arg;

        // Log the argument received for write operation
        printk("IOCTL Write: arg = %lu\n", arg);

        // Create a kernel thread to compute the factorial
        struct task_struct *task = kthread_create(kthread_handler, data, "factorial_thread");
        if (IS_ERR(task)) {
            kfree(data);
            return PTR_ERR(task);
        }
        wake_up_process(task); // Start the thread

        return 0;
    } else if (cmd == 1) {
        // Read operation: Return the computed result
        int result = atomic64_read(&user_data_ptr->data);

        // Log the result being read
        printk("IOCTL Read: result = %d\n", result);

        return result;
    }

    return -EINVAL; // Invalid command
}


// 文件操作结构体
static struct file_operations edu_dev_fops = {
    .open = edu_dev_open,
    .release = edu_dev_release,
    .unlocked_ioctl = edu_dev_unlocked_ioctl,
};

// 驱动初始化
static int __init edu_driver_init(void)
{
    int ret = register_chrdev(EDU_DEV_MAJOR, EDU_DEV_NAME, &edu_dev_fops);
    if (ret < 0) {
        printk("Failed to register char device\n");
        return ret;
    }

    ret = pci_register_driver(&pci_driver);
    if (ret) {
        unregister_chrdev(EDU_DEV_MAJOR, EDU_DEV_NAME);
        return ret;
    }

    spin_lock_init(&lock); // 初始化自旋锁
    printk("HELLO PCI\n");
    return 0;
}

// 驱动注销
static void __exit edu_driver_exit(void)
{
    unregister_chrdev(EDU_DEV_MAJOR, EDU_DEV_NAME);
    pci_unregister_driver(&pci_driver);
    printk("GOODBYE PCI\n");
}

MODULE_LICENSE("GPL");
module_init(edu_driver_init);
module_exit(edu_driver_exit);
