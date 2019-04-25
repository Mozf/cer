% 读取训练样本
% 读取A类训练样本
[filelist,path]=uigetfile({'*.nos','NOS Files(*.nos)'},'选择A类训练样本','MultiSelect','on');
if iscell(filelist) 
	filenum=size(filelist,2); 
elseif filelist==0 
    return
end
train_data1=[];
for i=1:1:filenum
    temp=read_NOS_data([path,filelist{i}]);
    train_data1=[train_data1;temp(1:120,:)];
end

% 读取B类训练样本
[filelist,path]=uigetfile({'*.nos','NOS Files(*.nos)'},'选择B类训练样本','MultiSelect','on');
if iscell(filelist) 
	filenum=size(filelist,2); 
elseif filelist==0 
    return
end
train_data2=[];
for i=1:1:filenum
    temp=read_NOS_data([path,filelist{i}]);
    train_data2=[train_data2;temp(1:120,:)];
end

% 读取C类训练样本
[filelist,path]=uigetfile({'*.nos','NOS Files(*.nos)'},'选择C类训练样本','MultiSelect','on');
if iscell(filelist) 
	filenum=size(filelist,2); 
elseif filelist==0 
    return
end
train_data3=[];
for i=1:1:filenum
    temp=read_NOS_data([path,filelist{i}]);
    train_data3=[train_data3;temp(1:120,:)];
end

% 读取D类训练样本
[filelist,path]=uigetfile({'*.nos','NOS Files(*.nos)'},'选择D类训练样本','MultiSelect','on');
if iscell(filelist) 
	filenum=size(filelist,2); 
elseif filelist==0 
    return
end
train_data4=[];
for i=1:1:filenum
    temp=read_NOS_data([path,filelist{i}]);
    train_data4=[train_data4;temp(1:120,:)];
end

% feature_select
train_data_feature1=feature_select(train_data1);
train_data_feature2=feature_select(train_data2);
train_data_feature3=feature_select(train_data3);
train_data_feature4=feature_select(train_data4);

% label
[row1,~]=size(train_data_feature1);
[row2,~]=size(train_data_feature2);
[row3,~]=size(train_data_feature3);
[row4,~]=size(train_data_feature4);

train_data_label1=repmat([0,0,0,1],row1,1);
train_data_label2=repmat([0,0,1,0],row2,1);
train_data_label3=repmat([0,1,0,0],row3,1);
train_data_label4=repmat([1,0,0,0],row4,1);

% input_data
input_data=[train_data_feature1;train_data_feature2;train_data_feature3;train_data_feature4]';

% output_data
output_data=[train_data_label1;train_data_label2;train_data_label3;train_data_label4]';

% net_build
% net_train
[net11]=net_building(input_data,output_data,10,'logsig','tansig');
[net21]=net_building(input_data,output_data,20,'tansig','tansig');
[net31]=net_building(input_data,output_data,10,'logsig','purelin');
[net41]=net_building(input_data,output_data,10,'tansig','purelin');
[net51]=net_building(input_data,output_data,20,'tansig','tansig');

save net net11 net21 net31 net41 net51