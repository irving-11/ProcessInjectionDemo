### uprobe使用



需要在编译内核时开启CONFIG_UPROBE_EVENTS=y选项。通过/sys/kernel/debug/tracing/uprobe_events添加探针，通过/sys/kernel/debug/tracing/events/uprobes/<EVENT>/enable将其激活。

使用uprobe需要**用户**计算探针点在目标中的**偏移**。

<img src="../images/image-20220321100156998.png" alt="image-20220321100156998" style="zoom:80%;" />



uprobe试用

找待跟踪函数的偏移

![image-20220321103453598](../images/image-20220321103453598.png)

添加uprobe与uretprobe

![image-20220321145009240](../images/image-20220321145009240.png)



format of events

![image-20220321145108800](../images/image-20220321145108800.png)

激活探针并跟踪

![image-20220321145243363](../images/image-20220321145243363.png)



执行待观测函数

![image-20220321145324416](../images/image-20220321145324416.png)

查看结果

![image-20220321145547486](../images/image-20220321145547486.png)

参考：https://www.kernel.org/doc/html/latest/trace/uprobetracer.html

