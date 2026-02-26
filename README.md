# PEHelper2
本项目是一个Windows PE系统下的GUI操作工具。程序编译后体积仅100kb左右，特别适合集成到超级精简版本的pe中。

# 如何使用？
编译源程序（main.c），或者直接从本项目的release页面下载二进制文件，就可以集成到pe系统里。

# 如何集成到pe中？
先用dism命令挂载boot.wim。
指令如下：  
dism /mount-image /imagefile:d:\mype\media\sources\boot.wim /index:1 /mountdir:d:\mype\mount2  
使用时需根据实际情况替换镜像文件和挂载目录   
挂载完之后，找到挂载目录，打开windows/system32/winpeshl.ini如果没有就新建一个，如果system32目录下同时存在StartNet.cmd，则需要删除它 
在winpeshl.ini中输入如下内容：  
[LaunchApps]  
PEHelper2.exe  
保存文件，卸载镜像。  
dism /unmount-image /mountdir:d:\mype\mount2 /commit  
注意卸载时要关闭挂载目录中所有的文件，否则会导致镜像卸载不彻底，需要另行清理

# 它的界面是什么样的？
![微信图片_20250110162517](https://github.com/user-attachments/assets/bbf3853c-5d53-4480-a080-3e152cdc4ae7)  

# FAQ  
## Q1.为什么我自己编译的程序在正常系统下可以正常运行，而在pe系统会报错
![b6a7ef6069b2004b7287800c69e9b5fe](https://github.com/user-attachments/assets/aeab22a4-f8b7-4f2f-ab60-7ad307d3ec56)
A1.在项目属性中，把运行库设置改成多线程(/MT)  可参考上面的图片
## Q2.为什么编译出来的文件体积过大  
A2.需要把编译目标切换为Release
