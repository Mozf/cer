function [ net ] = net_building( train_input,train_output,hidden_node,I_activation,H_activation)
%NET_BUILDING �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
net=newff(train_input,train_output,hidden_node,{   I_activation H_activation},'traingdx');
net.trainParam.show=50;    
net.trainParam.epochs=2000;
net.trainParam.goal=0.000001;  
net.trainParam.lr=0.02;
net.trainParam.showWindow=0;
net=train(net,train_input,train_output);

end
