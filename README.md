# POKEMEN REMAKE

## 配置环境

* 本项目应在基于MSVC编译器的环境下运行，这里采用Visual Studio 2022(community)

* 本项目使用C++图形库：EasyX

* 本项目基于C/C++进行开发

  > EasyX官网：https://easyx.cn/

## 程序运行准备

1. 安装VS

2. 安装EasyX

   * 在官网下载EasyX，这里采用EasyX_20200902版本

     下载地址：https://easyx.cn/easyx

     ![image-20221130084558347](C:\Users\Amo\AppData\Roaming\Typora\typora-user-images\image-20221130084558347.png)

   * 打开文件地址，选择解压文件

     ![image-20221130084822823](C:\Users\Amo\AppData\Roaming\Typora\typora-user-images\image-20221130084822823.png)

   * 接下来将include中的easyx.h和graphics.h粘贴到vs目录下的include文件夹中

     ![image-20221130085116061](C:\Users\Amo\AppData\Roaming\Typora\typora-user-images\image-20221130085116061.png)

     我的文件路径如下

     Microsoft Visual Studio\2022\Community\VC\Auxiliary\VS\include

     ![image-20221130085242961](C:\Users\Amo\AppData\Roaming\Typora\typora-user-images\image-20221130085242961.png)

   * 打开解压文件中的lib\VC2015,将x64和x86中的两个文件分别粘贴到vs目录下的x64和x86文件夹中

     ![image-20221130090819038](C:\Users\Amo\AppData\Roaming\Typora\typora-user-images\image-20221130090819038.png)

     ![image-20221130090837082](C:\Users\Amo\AppData\Roaming\Typora\typora-user-images\image-20221130090837082.png)

     ![image-20221130090902836](C:\Users\Amo\AppData\Roaming\Typora\typora-user-images\image-20221130090902836.png)

     ![image-20221130091123839](C:\Users\Amo\AppData\Roaming\Typora\typora-user-images\image-20221130091123839.png)

     我的vs目录位置为

     C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\VS\lib

     ![image-20221130091051197](C:\Users\Amo\AppData\Roaming\Typora\typora-user-images\image-20221130091051197.png)

     ![image-20221130091300174](C:\Users\Amo\AppData\Roaming\Typora\typora-user-images\image-20221130091300174.png)

   * 重启VS，就可以使用了

3. 创建新项目

   * 点击创建项目，项目类型为空项目
   * 点击源文件->添加->新建项，选择创建C/C++源文件，将pokemen.cpp复制上去
   * 在项目中新建pokemenformat.c文件，然后回到vs，点击源文件->添加->现有项，选择

   

   



