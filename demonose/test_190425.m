load net;
% load_test_data
% [filelist,path]=uigetfile({'*.nos','NOS Files(*.nos)'},'选择测试样本');
% if iscell(filelist) 
% 	filenum=size(filelist,2); 
% elseif filelist==0 
%     return
% end
% test_data=read_NOS_data([path,filelist]);

% load_data为云平台传入的数据
test_data=load_data';

% 特征提取
feature1=mean(test_data(1:120,:));
feature2=std(test_data(1:120,:));
feature3=var(test_data(1:120,:));
test_input=[feature1,feature2,feature3]';

y1=sim(net11,test_input);
y2=sim(net21,test_input);
y3=sim(net31,test_input);
y4=sim(net41,test_input);
y5=sim(net51,test_input);

[~,kind1]=max(y1);
[~,kind2]=max(y2);
[~,kind3]=max(y3);
[~,kind4]=max(y4);
[~,kind5]=max(y5);

sg1=0;
sg2=0;
sg3=0;
sg4=0;
kind_select=[kind1;kind2;kind3;kind4;kind5];

for j=1:1:size(kind_select,1)
    if kind_select(j)==4
       sg1=sg1+1;
    elseif kind_select(j)==3
       sg2=sg2+1;
    elseif kind_select(j)==2
       sg3=sg3+1;
    else
       sg4=sg4+1;
    end
end

[~,kind_num]=max([sg1,sg2,sg3,sg4]);

if kind_num==1
    kind='0x01';
elseif kind_num==2
    kind='0x02';
elseif kind_num==3
    kind='0x03';
elseif kind_num==4
    kind='0x04';
else
    kind='0x00';
end
