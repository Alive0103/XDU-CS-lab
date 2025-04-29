#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/workqueue.h>
#include <linux/atomic.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("FuShengyuan");
MODULE_DESCRIPTION("deferred work with work queue and kernel thread");

// 定义结构体来存储 work queue 的上下文信息
struct work_ctx {
    struct work_struct work;  // work queue 的结构
    int current_id;           // 用于区分每个工作
};

// 定义延迟工作、线程和上下文数组
struct delayed_work my_work;
struct work_ctx works[10];
struct task_struct *threads[10];

// work queue 的执行体
void work_queue_handler(struct work_struct *work) {
    struct work_ctx *ctx = container_of(work, struct work_ctx, work); // 获取当前工作上下文
    printk("work queue : %d\n", ctx->current_id); // 打印当前 work queue 的 ID
}

// kernel thread 的执行体，仅执行一次
int kthread_handler(void *data) {
    struct work_ctx *ctx = (struct work_ctx *)data; // 获取线程对应的工作上下文
    printk("kernel thread : %d\n", ctx->current_id); // 打印当前线程的 ID
    return 0;
}

// delayed work 的执行体
void delayed_work_handler(struct work_struct *work) {
    printk("延迟执行的任务输出\n"); // 延迟执行的任务输出
}

// 内核模块初始化函数
int deferred_work_init(void) {
    printk(KERN_INFO "加载模块成功\n"); // 模块加载成功的提示
    int i;

    // 创建并初始化 work queue，并立即调度
    for (i = 0; i < 10; i++) {
        works[i].current_id = 894 + i;                // 学号后三位加1
        INIT_WORK(&works[i].work, work_queue_handler); // 初始化 work queue
        schedule_work(&works[i].work);                // 提交到全局 work queue 中
    }

    // 创建 kernel thread，每个线程只运行一次
    for (i = 0; i < 10; i++) {
        threads[i] = kthread_create(kthread_handler, &works[i], "kthread_%d", i); // 创建内核线程
        if (threads[i]) {
            wake_up_process(threads[i]);            // 启动内核线程
        }
    }

    // 初始化并调度 delayed work，延迟 5 秒后执行
    INIT_DELAYED_WORK(&my_work, delayed_work_handler); // 初始化延迟任务
    schedule_delayed_work(&my_work, 5 * HZ);           // 延迟5秒执行

    return 0;
}

// 内核模块退出函数
void deferred_work_exit(void) {
    int i;
    // 停止所有 kernel thread
    for (i = 0; i < 10; i++) {
        if (threads[i]) {
            kthread_stop(threads[i]);                // 停止内核线程
        }
    }
    printk(KERN_INFO "卸载模块\n"); // 卸载模块时的信息
}

// 指定模块加载和退出的入口
module_init(deferred_work_init);
module_exit(deferred_work_exit);
