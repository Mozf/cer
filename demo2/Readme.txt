��c��MATLAB���˵����

һ�� ǰ��
  1���Ѱ�װMATLAB
  2��matlab engine����/bin/csh������Ŀǰ������Ĭ��/bin/bash�����Ȱ�װcsh;�л���csh��������

������Ҫ�ļ���·��
	�����ļ���libmx.so��libmex.so��libmat.so
	ͷ�ļ���engine.h��matrix.h��tmwtypes.h
	����Ŀ¼��/usr/local/MATLAB/R2016b/extern/include
	��Ŀ¼��/usr/local/MATLAB/R2016b/bin/glnxa64
	ע��test.m�ļ�����·����ӵ�MATLAB����·����

	���й��̻���ʱ����data.mat�ļ�����СΪ1KB��ÿ�����л��Զ����ǣ���

������������
	1���״�����engine��Ƚϳ�ʱ�䣨6s���ң���
	2��Mtest.m��net.mat�ֱ��������µ��㷨�ļ���ѵ�����硣
	3���������µڶ����㷨�Ŀ�ʹ�ð汾

demo������cer�ϱ��룺
gcc  -L /work/matlab2016/bin/glnxa64 -I /work/matlab2016/extern/include demo.c -o demo -lmat -lmx -leng -Wl,-rpath=/work/matlab2016/bin/glnxa64

demo�ڱ���linux�ϱ��룺
gcc  -L/usr/local/MATLAB/R2016b/bin/glnxa64 -I /usr/local/MATLAB/R2016b/extern/include demo.c -o demo -lmat -lmx -leng -Wl,-rpath=/usr/local/MATLAB/R2016b/bin/glnxa64

����./demo
level��0403



��ע��
�������Ի�����ubuntu��gcc-7.3.0��matlab_R2016b��
���������Ի�����Centos6.8��gcc-4.8.5��matlab_R2016b��

