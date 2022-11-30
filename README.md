# POKEMEN REMAKE

## 没有代码基础的可以去看图文版的PDF文件

## 配置环境

* 本项目应在基于MSVC编译器的环境下运行，这里采用Visual Studio 2022(Community)

* 本项目使用C++图形库：EasyX

* 本项目基于C/C++进行开发

  > EasyX官网：https://easyx.cn/

## 程序运行准备

### 安装VS

* 进入VS官网：https://visualstudio.microsoft.com/
* 点击下载Visual Studio Community2022
* 运行setup程序，选择“为桌面开发的C/C++”和“Visual Studio拓展”，点击下载
* 要记住下载的文件地址哦

### 安装EasyX

* 在官网下载EasyX，这里采用EasyX_20200902版本

  下载地址：https://easyx.cn/easyx


* 打开文件地址，选择解压文件


* 接下来将include中的easyx.h和graphics.h粘贴到vs目录下的include文件夹中

  我的文件路径如下

  Microsoft Visual Studio\2022\Community\VC\Auxiliary\VS\include

* 打开解压文件中的lib\VC2015,将x64和x86中的两个文件分别粘贴到vs目录下的x64和x86文件夹中

  我的lib目录位置为

  C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\VS\lib

* 重启VS，就可以使用了

### 创建项目

* 点击创建项目，项目类型为空项目

* 打开文件管理器，打开项目所在的文件夹，将pokemen.cpp, pokemenformat.c, level.txt, trap.txt, takePart.txt五个文件复制到文件夹中

  * 这五个文件在我的**GitHub仓库**里：https://github.com/asIsinkintowest/POKEMEN_REMAKE/tree/main
  * 要注意是第二个project文件，不是第一个


* 点击源文件->添加->现有项，选择pokemen.cpp文件

* 点击源文件->添加->现有项，选择pokemenformat.c文件

* 点击上方的项目->属性->高级->字符集，选择多字节字符集，点击确定


## 程序运行

1. 进入vs中的项目，点击上方的绿色小箭头（本地Windows调试器）
2. 开始玩游戏

## 游戏说明

### 难度

* 难度界面可以选择困难、一般和简单模式

### 图鉴

* 图鉴界面可以看到所有宝可梦的信息
* 可以看到自己抓到了哪些宝可梦
* 可以选择让哪些宝可梦出战，队伍上限是三只宝可梦

### 开始游戏

* **！！！进入游戏要先切换到英文输入法**
* w a s d 分别对应上 左 下 右
* q 可以回到开始界面
* 走到地貌附近按下空格即可开始对战
* 不要走出地图边界

### 对战

* 可以进行战斗、捕捉或者逃跑
* 对战时首先要选择自己想要出战的宝可梦
* 要注意宝可梦招式之间的属性克制
* 只能捕捉虚弱的宝可梦，血量太高的宝可梦一定抓不到哦
* 感觉自己打不过的时候就逃跑吧: )

### 存档

* 游戏有自动存档，不需要担心辛苦抓到的宝可梦丢失







