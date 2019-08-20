# ubuntu安装git

1. 使用`git`查看是否已经安装git；
2. 如果没有则输入`sudo apt install git`安装；
3. 安装完之后配置用户`git config --global user.name "xxx"`和邮箱`git config --global user.email "你的邮箱地址"`；
4. 创建公钥`ssh-keygen -C 'you email address@gmail.com' -t rsa`；
5. 进入文件夹`cd ~/.ssh`并打开文件`gedit id_rsa.pub`并复制全部内容；
6. 从网页打开你的github账户，点击右上角的头像，点击settings之后，在左边点击进入SSH and GPG keys之后，点击New SSH key，把第5步复制的信息粘贴到key中，并在Title中输入一个名字（这个名字最好让你知道是这个主机，以方便以后管理）；
7. 回到本地，在任意你可以管理的地方创建一个文件夹，如`mkdir ~/gitworkspace`，然后进入这个文件夹`cd ~/gitworkspace`，初始化为一个git仓库`git init`；
8. 最后`git clone 你的项目`
