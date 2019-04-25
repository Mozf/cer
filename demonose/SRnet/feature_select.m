function [ feature ] = feature_select( input_data )
%FEATURE_SELECT �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
[row,~]=size(input_data);
feature=[];
for i=1:120:row
    feature1=mean(input_data(i:i+119,:));
    feature2=std(input_data(i:i+119,:));
    feature3=var(input_data(i:i+119,:));
    feature=[feature;feature1,feature2,feature3];
end

end

