# 基于Madplay的MP3音乐播放器 MP3 Player with Madplay
---
本音乐播放器是为了完成大三的课设而做的。它使用madplay且只能在linux下运行。在Red Hat Enterprise 5下是可以正常运行的，但是我没有测试过其他发行版的运行情况。
This player with madplay is designed for my homework, which can run on linux only. It can work well on Red Hat Enterprise 5 while other releases are not tested.
---
# 特征 Features
支持MP3音乐格式。
Support MP3 music format.
在命令行下使用简单的命令就可控制音乐的播放。
Control the player with simply comands on command line.
.music_config文件保存着音乐目录。
The directory of musics is saved in the file named .music_config.
同一时刻只能播放一首音乐。
Only one music can play at once.
可以暂停或者继续播放。
Suspend playing or continue to play.
可以循环播放下一首或者上一首。
Play the next one or previous one in circulation.
---
# 安装 Installation
下载本库后使用make生成mp3player文件。运行mp3player即可。
Download this repository accompanied with a makefile. Make it and a file named as mp3player is available. Run it!
---
# 使用说明 Usage
输入h或者H来显示哪些命令可用。
Enter h or H key for help that will show you which command is valid.
---
# 存在的问题 Problem
一首音乐播放结束后播放或者播放下（上）一首时，可能出现“设备忙”的报错。
 When I want to play another music after the music is end or to play next one or previous one when the music is playing, an error said "Device or resource busy" occurs.
 
