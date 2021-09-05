# AutoSwitchDisplayFrequency

不知道什么原因，华硕的ASUSSmartDisplyControl不起作用，遂自己写一个

**功能：**
在笔记本交流电源连接状态改变时自动改变屏幕刷新率，断开电源时设置刷新率为60Hz，插上电源时设置刷新率为165hz。

**设置开机自启的方法：**
win10/win11下设置开机启动的程序，只要把快捷方式放到%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup文件夹里即可。