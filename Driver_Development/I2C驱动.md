--- 
title: I2C驱动 
categories: Linux内核驱动 
---

I2C的硬件结构：I2C在硬件上是由两条数据线组成，一个是SCL 时钟线，一个是SDA 数据线，空闲的时候SCL 和SDA 要处于高电平，所以在硬件设计上这俩个线要加上拉电阻。  
I2C驱动结构：Linux 中定义了I2C 驱动的体系结构，即I2C 总线驱动和I2C 设备驱动。


<!--more-->  

### I2C总线驱动  
I2C总线驱动重点是 I2C适配器 (也就是 SOC的 I2C接口控制器 )驱动，这里要用到两个重要的数据结构： i2c_adapter和 i2c_algorithm Linux内核将 SOC的 I2C适配器 (控制器 )抽象成 i2c_adapter  。但是总线驱动一般不是驱动工程师的工作  
### I2C设备驱动  
I2C设备驱动重点关注两个数据结构： i2c_client和 i2c_driver。根据总线、设备和驱动模型，还剩下设备和驱动， i2c_client就是描述设备信息的， i2c_driver描述驱动内容。
**1.i2c_client**  
i2c_client结构体定义在 include/linux/i2c.h文件中，内容如下：

    struct i2c_client {
        unsigned short flags;	//标志
    #define I2C_CLIENT_PEC		0x04	/* Use Packet Error Checking */
    #define I2C_CLIENT_TEN		0x10	/* we have a ten bit chip address */
                        /* Must equal I2C_M_TEN below */
    #define I2C_CLIENT_SLAVE	0x20	/* we are the slave */
    #define I2C_CLIENT_HOST_NOTIFY	0x40	/* We want to use I2C host notify */
    #define I2C_CLIENT_WAKE		0x80	/* for board_info; true iff can wake */
    #define I2C_CLIENT_SCCB		0x9000	/* Use Omnivision SCCB protocol */
                        /* Must match I2C_M_STOP|IGNORE_NAK */

        unsigned short addr;		//芯片地址
                        /* addresses are stored in the	*/
                        /* _LOWER_ 7 bits		*/
        char name[I2C_NAME_SIZE];   //名字
        struct i2c_adapter *adapter;	/*对应的I2C总线（适配器）	*/
        struct device dev;		/* 设备结构体		*/
        int init_irq;			/* irq set at initialization	*/
        int irq;			/*中断	*/
        struct list_head detected;
    #if IS_ENABLED(CONFIG_I2C_SLAVE)
        i2c_slave_cb_t slave_cb;	/* callback for slave mode	*/
    #endif
    };
一个设备对应一个 i2c_client，每检测到一个 I2C设备就会给这个 I2C设备分配一个i2c_client
**2.i2c_driver结构体**  
i2c_driver类似 platform_driver，是我们编写 I2C设备驱动重点要处理的内容， i2c_driver结构体定义在 include/linux/i2c.h文件中，内容如下：  

    struct i2c_driver {
        unsigned int class;

        /* Standard driver model interfaces */
        int (*probe)(struct i2c_client *client, const struct i2c_device_id *id);//当 I2C设备和驱动匹配成功以后 probe函数就会执行，和 platform驱动一样。
        int (*remove)(struct i2c_client *client);

        /* New driver model interface to aid the seamless removal of the
        * current probe()'s, more commonly unused than used second parameter.
        */
        int (*probe_new)(struct i2c_client *client);

        /* driver model interfaces that don't relate to enumeration  */
        void (*shutdown)(struct i2c_client *client);

        /* Alert callback, for example for the SMBus alert protocol.
        * The format and meaning of the data value depends on the protocol.
        * For the SMBus alert protocol, there is a single bit of data passed
        * as the alert response's low bit ("event flag").
        * For the SMBus Host Notify protocol, the data corresponds to the
        * 16-bit payload data reported by the slave device acting as master.
        */
        void (*alert)(struct i2c_client *client, enum i2c_alert_protocol protocol,
                unsigned int data);

        /* a ioctl like command that can be used to perform specific functions
        * with the device.
        */
        int (*command)(struct i2c_client *client, unsigned int cmd, void *arg);

        struct device_driver driver;//驱动结构体，如果使用设备树的话，需要设置 device_driver的of_match_table成员变量，也就是驱动的兼容 (compatible)
        const struct i2c_device_id *id_table;

        /* Device detection callback for automatic device creation */
        int (*detect)(struct i2c_client *client, struct i2c_board_info *info);
        const unsigned short *address_list;
        struct list_head clients;

        bool disable_i2c_core_irq_mapping;
    };

对于我们 I2C设备驱动编写人来说，重点工作就是构建 i2c_driver，构建完成以后需要向Linux内核注册这个 i2c_driver。i2c_driver注册函数为 int i2c_register_driver，此函数原型为  

    int i2c_register_driver(struct module *owner, struct i2c_driver *driver)  
    //函数参数和返回值含义如下：
    owner 一般为 THIS_MODULE。
    driver：要注册的 i2c_driver。
    返回值： 0，成功；负值，失败。

i2c_add_driver就是对 i2c_register_driver做了一个简单的封装，只有一个参数，就是要注册的 i2c_driver
注销 I2C设备驱动的时候需要将前面注册的 i2c_driver从 Linux内核中注销掉，需要用到i2c_del_driver函数，此函数原型如下：  

    void i2c_del_driver(struct i2c_driver *driver)
    函数参数和返回值含义如下：
    driver：要注销的 i2c_driver。
    返回值： 无。

### 实例分析
1. i2c总线驱动（适配器）：一般由soc厂家提供
2. i2c设备驱动编写流程：这里我们使用设备树的情况。 
使用设备树的时候 I2C设备信息通过创建相应的节点就行了，如果在I2C1上接设备。只需要在i2c1节点下创建设备子节点。如下是devicetree i2c1节点  

        &i2c_1 {
            #address-cells = <1>;
            #size-cells = <0>;
            samsung,i2c-sda-delay = <100>;
            samsung,i2c-max-bus-freq = <400000>;
            pinctrl-0 = <&i2c1_bus>;
            pinctrl-names = "default";
            status = "okay";
        }
        //#address-cells以及size-cells属性在/linux-5.3.18/Documentation/devicetree/bindings/i2c-exynos5.txt文档中可知：  
                - #address-cells: always 1 (for i2c addresses)
                - #size-cells: always 0
        //对于samsung,i2c-sda-delay = <100>;属性；查看/linux-5.3.18/Documentation/devicetree/bindings/i2c-exynos5.txt文档中是没有的。
        但是用以下命令grep -r samsung,i2c-sda-delay /home/zhaobo/Work_place/itop4412_kernel_4_14_2_bsp/linux-4.14.2_iTop-4412_scp/Documentation/devicetree/ 
        搜得/home/zhaobo/Work_place/itop4412_kernel_4_14_2_bsp/linux-4.14.2_iTop-4412_scp/Documentation/devicetree/bindings/i2c/i2c-s3c2410.txt有关于这个属性的文档解释如下：
                - samsung,i2c-sda-delay: Delay (in ns) applied to data line (SDA) edges.
        //对于pinctrl-0属性同上也可搜得
                - pinctrl-0: Pin control group to be used for this controller.  
        //pinctrl-names属性同上可搜得  
                - pinctrl-names: Should contain only one value - "default"
        //samsung,i2c-max-bus-freq属性同上可搜得 
                - samsung,i2c-max-bus-freq: Desired frequency in Hz of the bus. If notspecified, the default value in Hz is 100000.
在i2c1节点下创建子节点 （先寻找文档）根据文档来写子节点可以参考一下3503A驱动


