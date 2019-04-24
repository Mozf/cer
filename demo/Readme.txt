					《c和MATLAB混编说明》

一、 前提
  1、已安装MATLAB
  2、matlab engine依赖/bin/csh启动，目前服务器默认/bin/bash，须先安装csh;切换到csh下再运行

二、必要文件和路径
	链接文件：libmx.so，libmex.so和libmat.so
	头文件：engine.h，matrix.h，tmwtypes.h
	包含目录：/usr/local/MATLAB/R2015b/extern/include
	库目录：/usr/local/MATLAB/R2015b/bin/glnxa64
	注：test.m文件所在路径添加到MATLAB工作路径；

	运行过程会临时生成data.mat文件（大小为1KB，每次运行会自动覆盖）。

三、其他问题
	1、首次运行engine会比较长时间（6s左右）；
	2、Mtest.m，net.mat分别是所更新的算法文件、训练网络。
	3、硬件上传数据格式为：数据头+全零数据+校验位（在服务器或demo里面做截取）
	AAAA007C060103000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000D9


本地编译：
gcc  -L/usr/local/MATLAB/R2016b/bin/glnxa64 -I//usr/local/MATLAB/R2016b/extern/include demo.c -o demo -lmat -lmx -leng -Wl,-rpath=/usr/local/MATLAB/R2016b/bin/glnxa64

centos编译：
gcc  -L /work/matlab2016/bin/glnxa64 -I /work/matlab2016/extern/include demo.c -o demo -lmat -lmx -leng -Wl,-rpath=/work/matlab2016/bin/glnxa64
运行./demo
level：0403



备注：
本机测试环境（Centos7.4，gcc-6.1.0，matlab_R2016b）
服务器测试环境（Centos7.3，gcc-4.8.5，matlab_R2015b）

