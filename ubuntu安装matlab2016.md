### 下载matlab 2016b

1. windows百度网盘下载：链接：https://pan.baidu.com/s/1eu3TgvYtjUTaBZp8vP5Dig  提取码：zblt；
2. 解压Crack；
3. 把东西放共享文件夹里面，包括一个文件夹和两个iso；

### 挂载镜像文件

1. `cd ~`
2. `mkdir matlab`
3. `sudo mount -t auto -o loop /mnt/hgfs/share/R2016b_glnxa64_dvd1.iso matlab/`



### 安装matlab

1. `sudo ./matlab/install`
2. 出现安装界面，依次点击“使用文件安装密钥”、“是”、“我已有我的许可证的文件安装密钥”并打开crack的readme复制第一段数字并粘贴上去、路径默认、选择组件并安装；
3. 安装进行到82%的时候，会弹出一个提示框，说请插入dvd2，这时候我们需要重新开一个终端，把dvd2挂载到matlab文件夹中：`sudo mount -t auto -o loop /mnt/hgfs/share/R2016b_glnxa64_dvd2.iso matlab/`；
4. 等安装结束，取消挂载`umount matlab/`这个命令可能要执行两次；
5. `sudo rm -r matlab/`。

### 激活matlab

1. `cd /usr/local/MATLAB/R2016b/bin`；
2. `sudo ./matlab`；
3. 在不使用internet的情况下手动激活；
4. 选择crack文件夹中的“license_standalone.lic”；
5. 把Crack文件夹中R2016b/Linux/R2016b/bin/glnxa64四个文件，复制到/usr/local/MATLAB/R2016b/bin/glnxa64目录下`sudo cp /mnt/hgfs/share/Matlab\ 2016b\ Linux64\ Crack/R2016b/bin/glnxa64/* /usr/local/MATLAB/R2016b/bin/glnxa64 `；