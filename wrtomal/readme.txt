《c和MATLAB混编说明》

一、 前提
  1、已安装MATLAB
  2、matlab engine依赖/bin/csh启动，目前服务器默认/bin/bash，须先安装csh;切换到csh下再运行

二、必要文件和路径
	链接文件：libmx.so，libmex.so和libmat.so
	头文件：engine.h，matrix.h，tmwtypes.h
	包含目录：/usr/local/MATLAB/R2016b/extern/include
	库目录：/usr/local/MATLAB/R2016b/bin/glnxa64
	注：test.m文件所在路径添加到MATLAB工作路径；


三、其他问题
	1、首次运行engine会比较长时间（6s左右）；
	2、这个程序实现了用c语言写入一个3*3的矩阵给matlab并求逆矩阵之后返回并显示；
	3、我也不知道这里放着这么多其他文件有什么用，但是好像真的没有这些就不行。

wrtomal编译在cer上编译：
gcc  -L /work/matlab2016/bin/glnxa64 -I /work/matlab2016/extern/include demo.c -o demo -lmat -lmx -leng -Wl,-rpath=/work/matlab2016/bin/glnxa64

wrtomal在本地linux上编译：
gcc  -L/usr/local/MATLAB/R2016b/bin/glnxa64 -I /usr/local/MATLAB/R2016b/extern/include demo.c -o demo -lmat -lmx -leng -Wl,-rpath=/usr/local/MATLAB/R2016b/bin/glnxa64

运行./demo
level：0403



备注：
本机测试环境（ubuntu，gcc-7.3.0，matlab_R2016b）
服务器测试环境（Centos6.8，gcc-4.8.5，matlab_R2016b）

