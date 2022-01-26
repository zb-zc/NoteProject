# 《Python编程 从入门到实践》读书笔记  
## 字符串 
### 基本语法  
用引号括起来的都是字符串，其中引号可以是单引号，也可以是双引号   

    "This is a string."  
    'This is also a string.'  
    
### 在字符中使用变量  
要在字符串中插入变量的值，可在前引号前加上字母f，再将要插入的变量放在花括号内。  

    first_name = "ada"
    last_name = "lovelace"
    ❶ full_name = f"{first_name} {last_name}"
    print(full_name)  
## 列表
在python中用[]表示列表，并用逗号分隔开其中的的元素  

    bicycles = ['trek', 'cannondale', 'redline', 'specialized']
    print(bicycles)
#### 访问列表元素
只需将该元素的位置（索引） 告诉Python即可  

    bicycles = ['trek', 'cannondale', 'redline', 'specialized']
    print(bicycles[0])  
#### 修改元素  

    motorcycles = ['honda', 'yamaha', 'suzuki']
    print(motorcycles)
    ❷ motorcycles[0] = 'ducati'
    print(motorcycles)
    
#### 添加元素  
* **在列表末尾添加元素**    


        motorcycles = ['honda', 'yamaha', 'suzuki']
        print(motorcycles)
        ❶ motorcycles.append('ducati')
        print(motorcycles)
 方法append()将元素'ducati'添加到列表末尾（见❶） ， 而不影
响列表中的其他所有元素
* **在列表中插入元素**  
使用方法insert()可在列表的任何位置添加新元素。为此，你需要指定新元素的索引和值  


        motorcycles = ['honda', 'yamaha', 'suzuki']
        ❶ motorcycles.insert(0, 'ducati')
        print(motorcycles)
        
#### 删除元素 
* **使用del语句删除元素**  
如果知道要删除的元素在列表中的位置， 可使用del语句  


        motorcycles = ['honda', 'yamaha', 'suzuki']
        print(motorcycles)
        ❶ del motorcycles[0]
        print(motorcycles)
* **使用pop()删除元素**   
有时候， 你要将元素从列表中删除，并接着使用它的值。方法pop()删除列表末尾的元素，并让你能够接着使用它。   


         motorcycles = ['honda', 'yamaha', 'suzuki']
        print(motorcycles)
        ❷ popped_motorcycle = motorcycles.pop()
        ❸ print(motorcycles)
        ❹ print(popped_motorcycle)

* **删除列表中任何位置的元素**   
实际上， 可以使用pop()来删除列表中任意位置的元素，只需在圆括号中指定要删除元素的索引即可。  


        motorcycles = ['honda', 'yamaha', 'suzuki']
        ❶ first_owned = motorcycles.pop(0)
        ❷ print(f"The first motorcycle I owned was a {first_owned.title()}.")
        
* **根据值删除元素**  
    如果只知道要删除的元素的值， 可使用方法remove()。


        motorcycles = ['honda', 'yamaha', 'suzuki', 'ducati']
        print(motorcycles)
        ❶ motorcycles.remove('ducati')
        print(motorcycles)      
        
**使用remove()从列表中删除元素时，也可接着使用它的值。方法remove()只删除第一个指定的值。如果要删除的值可能在列表中出现多次，就需要使用循环来确保将每个值都删除。 这将在第7章中介绍**   


## 字典  
###  使用字典
在Python中，字典是一系列**键值对**，每个键都与一个值对应。通过键来访问相关联的值。字典用放在{}中的一系列键值对表示。键值对之间用**逗号**隔开

    alien_o = {'color': 'green','points': 5}  ①
    print(alien_o['color']) ②
    //
    ①中空格可有可无
    ②访问字典中的值
    // 
    
#### 添加键值对    
要添加键值对， 可依次指定字典名、 用方括号括起的键和相关联的值。  

    alien_0 = {'color': 'green', 'points': 5}
    print(alien_0)
    ❶ alien_0['x_position'] = 0
    
#### 创建一个空字典 

    alien_0 = {}
    alien_0 = {'color': 'green'}

#### 修改字典中的值
要修改字典中的值， 可依次指定字典名、 用方括号括起的键， 以及与该键相关联的新值。 

    alien_0 = {'color': 'green'}
    
*注意*：添加键值对使用[],修改键值对是{}。

#### 删除键值对 
del语句：使用del语句时，必须指定字典名和要删除的键  

    alien_0 = {'color': 'green', 'points': 5}
    print(alien_0)
    ❶ del alien_0['points']
    print(alien_0)
    
#### 由类似对象组成的字典  
字典存储的是一个对象（游戏中的一个外星人） 的多种信息， 可以使用字典来存储众多对象的同一种信息  

    favorite_languages = {
    'jen': 'python',
    'sarah': 'c',
    'edward': 'ruby',
    'phil': 'python',
    }

确定需要使用多行来定义字典时， 要在输入左花括号后按回车键。 在下一行缩进四个空格，指定第一个键值对，并在它后面加上一个逗号。此后再按回车键时， 文本编辑器将自动缩进后续键值对，且缩进量与第一个键值对相同。定义好字典后，在最后一个键值对的下一行添加一个右花括号， 并缩进四个空格， 使其与字典中的键对齐。
#### 使用get()来访问值

    alien_0 = {'color': 'green', 'speed': 'slow'}
    point_value = alien_0.get('points', 'No point value assigned.')
    print(point_value)
    
方法get()的第一个参数用于指定键， 是必不可少的； 第二个参数为指
定的键不存在时要返回的值， 是可选的：

### 遍历字典   
***For循环***

    user_0 = {
    'username': 'efermi',
    'first': 'enrico',
    'last': 'fermi',
    }
    ❶ for key, value in user_0.items():
    ❷ print(f"\nKey: {key}")
    ❸ print(f"Value: {value}")

**如**❶**所示， 要编写遍历字典的for循环， 可声明两个变量， 用于存储键值对中的键和值**   
**for语句的第二部分包含字典名和方法items()**（见❶）**， 它返回一个
键值对列表。接下来，for循环依次将每个键值对赋给指定的两个变量。**   
#### 遍历字典中的所有键 
在不需要使用字典中的值时， 方法**keys()**很有用。  
    
    for name in favorite_languages.keys():
    
## 用户输入 
函数input()让程序暂停运行， 等待用户输入一些文本。 获取用户输入
后， Python将其赋给一个变量， 以方便你使用  

    message = input("Tell me something, and I will repeat it back to you: ")
    print(message)
*       prompt = "If you tell us who you are, we can personalize the messages you see."
        prompt += "\nWhat is your first name? "
        name = input(prompt)
        print(f"\nHello, {name}!")

*       If you tell us who you are, we can personalize the messages you see.
        What is your first name? Eric
        Hello, Eric!


#### 使用Int()来获取数值输入        
使用函数input()时， Python将用户输入解读为字符串。函
数int()将数的字符串表示转换为数值表示。如下  

    >>> age = input("How old are you? ")
    How old are you? 21
    ❶ >>> age = int(age)
    >>> age >= 18
    True
    
#### 求模运算符
它将两个数相除并返回余数。求模运算符不会指出一个数是另一个数的多少倍， 只指出余数是多少。  

## While循环  
for循环用于针对集合中的每个元素都执行一个代码块， 而while循环
则不断运行， 直到指定的条件**不满足**为止  

    current_number = 1
    while current_number <= 5:
    print(current_number)
    current_number += 1
    
#### 让用户选择何时退出  

    ❶ prompt = "\nTell me something, and I will repeat it back to you:"
    prompt += "\nEnter 'quit' to end the program. "
    ❷ message = ""
    ❸ while message != 'quit':
    message = input(prompt)
    print(message)  
    
#### 使用break退出循环  
要立即退出while循环， 不再运行循环中余下的代码， 也不管条件测试
的结果如何， 可使用break语句。  

    prompt = "\nPlease enter the name of a city you have visited:"
    prompt += "\n(Enter 'quit' when you are finished.) "
    ❶ while True:
        city = input(prompt)
        if city == 'quit':
            break
        else:
            print(f"I'd love to go to {city.title()}!")  
            
#### 在循环中使用continue  
要返回循环开头， 并根据条件测试结果决定是否继续执行循环， 可使
用continue语句， 它不像break语句那样不再执行余下的代码并退出整
个循环。 例如， 来看一个从1数到10但只打印其中奇数的循环：  

    current_number = 0
    while current_number < 10:
    ❶ current_number += 1
    if current_number % 2 == 0:
    continue
    print(current_number)
    
    首先将current_number设置为0， 由于它小于10， Python进入while循
    环。 进入循环后， 以步长1的方式往上数（见❶） ， 因
    此current_number为1。 接下来， if语句检查current_number与2的
    求模运算结果。 如果结果为0（意味着current_number可被2整除） ，
    就执行continue语句， 让Python忽略余下的代码， 并返回循环的开
    头。 如果当前的数不能被2整除， 就执行循环中余下的代码， 将这个数
    打印出来：
    
#### 使用while循环处理列表和字典   
#### 删除为特定值的所有列表元素  
假设你有一个宠物列表， 其中包含多个值为'cat'的元素。 要删除所有
这些元素， 可不断运行一个while循环， 直到列表中不再包含
值'cat'， 如下所示g'v
    
    

    