clc
clear
load net;
load data.mat;

string=input_data(1:end);
col=size(string,2);
ch1=string(1:8:col);
ch2=string(2:8:col);
ch3=string(3:8:col);
ch4=string(4:8:col);
ch5=string(5:8:col);
ch6=string(6:8:col);
ch7=string(7:8:col);
ch8=string(8:8:col);
str1=[ch1',ch2'];
str2=[ch3',ch4'];
str3=[ch5',ch6'];
str4=[ch7',ch8'];
col1=hex2dec(str1);
col2=hex2dec(str2);
col3=hex2dec(str3);
col4=hex2dec(str4);
testdata=[col1 col2 col3 col4];
[row,col]=size(testdata);

if mean(testdata(:,3))<=5
    target=1;
else
    target=0;
end
% 预处理
output_data=mapminmax('apply',testdata',train_ps3);
testdata=output_data';
% 特征选择
meantestdata=mean(testdata);
vartestdata=var(testdata);
mediantestdata=median(testdata);
input_data=[meantestdata,mediantestdata,vartestdata]';
% 仿真
y1=sim(net1,input_data);
y2=sim(net2,input_data);
y3=sim(net3,input_data);
y4=sim(net4,input_data);
y5=sim(net5,input_data);

[~,kind1]=max(y1);
[~,kind2]=max(y2);
[~,kind3]=max(y3);
[~,kind4]=max(y4);
[~,kind5]=max(y5);
% 投票
xy=0;
xs=0;
sg=0;
yq=0;
kind_select=[kind1;kind2;kind3;kind4;kind5];
for j=1:1:size(kind_select,1)
    if kind_select(j)==4
        xy=xy+1;
	elseif kind_select(j)==3
        xs=xs+1; 
	elseif kind_select(j)==2
        sg=sg+1;
    else
        yq=yq+1;
    end
end
    [~,kind_num]=max([xy,xs,sg,yq]);
%结果转化
if target==1
   kind='0x00';
else
if kind_num==1
    kind='0x01';
elseif kind_num==2
    kind='0x02';
elseif kind_num==3
    kind='0x03';
elseif kind_num==4
    kind='0x04';
else
    king='0x00';
end
end
% 浓度分级
data=input_data';
if strcmp(kind,'0x00')
    if data(1,3)>=0.5
        level='0x05';
    elseif data(1,3)>=0.3
        level='0x04';
    elseif data(1,3)>=0.2
        level='0x03';
    elseif data(1,3)>=0.1
        level='0x02';
    else
        level='0x01';
    end
elseif strcmp(kind,'0x01')
    if data(1,3)>=0.5
        level='0x05';
    elseif data(1,3)>=0.3
        level='0x04';
    elseif data(1,3)>=0.2
        level='0x03';
    elseif data(1,3)>=0.1
        level='0x02';
    else
        level='0x01';
    end

elseif strcmp(kind,'0x02')
    if data(1,3)>=0.5
        level='0x05';
    elseif data(1,3)>=0.3
        level='0x04';
    elseif data(1,3)>=0.2
        level='0x03';
    elseif data(1,3)>=0.1
        level='0x02';
    else
        level='0x01';
    end
elseif strcmp(kind,'0x03')
    if data(1,3)>=0.5
        level='0x05';
    elseif data(1,3)>=0.3
        level='0x04';
    elseif data(1,3)>=0.2
        level='0x03';
    elseif data(1,3)>=0.1
        level='0x02';
    else
        level='0x01';
    end
elseif strcmp(kind,'0x04')
    if data(1,3)>=0.5
        level='0x05';
    elseif data(1,3)>=0.3
        level='0x04';
    elseif data(1,3)>=0.2
        level='0x03';
    elseif data(1,3)>=0.1
        level='0x02';
    else
        level='0x01';
    end

else
    level='0x00';        
end
kind 
level
