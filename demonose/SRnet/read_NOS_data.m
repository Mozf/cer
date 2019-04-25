function sensor_data=read_NOS_data(file_path)
% function [fileinfo,channel,method,sensor_data]=read_NOS_data(file_path)
% 函数 read_NOS_data 读取 PEN-3 电子鼻的原始数据
% 输入：path -- 文件路径
%       filename -- 文件名
% 输出：fileinfo -- PEN-3的NOS文件的总体信息，主要是给出传感器通道数
%       channel -- 传感器名称、敏感特性及对应值
%       method -- 检测采样方法
%       sensor_data -- 传感数据
%===================
% get raw data
% 读取传感数据
%===================
% file_path=fullfile(path,filename);
% 通过 fullfile 函数把文件路径和文件名合成完整的文件读取路径

% 广东工业大学——仿生嗅觉/味觉传感技术实验室

file_format=file_path(end-3:end);
if ~strcmp(file_format,'.nos')
    error('Incorrect file format!');
end

fid=fopen(file_path);    % 通过 fopen 函数从指定的文件路径获取文件句柄

flag_done=0;
row=0;
sign=' =/+:()x';
while flag_done==0
    info=fgetl(fid);    % 利用 fgetl 函数逐行读取 NOS 文件内容
    row=row+1;
    switch info
        case '[FileInfo]'
            flag_fileinfo=0;
            while flag_fileinfo==0
                info=fgetl(fid);
                row=row+1;
                [s,info]=strtok(info,sign);
                if strcmp(s,'Channels')
                    flag_fileinfo=1;
                    [nchanl,info]=strtok(info,sign);
                    fileinfo.nchanl=str2num(nchanl);
                end
            end
        case '[Channels]'
            channel.name=[];
            channel.property=[];
            channel.value=[];
            for k=1:fileinfo.nchanl
                info=fgetl(fid);
                row=row+1;                    
                tab_point=find(double(info)==9);
                s1=info(1:tab_point(1)-1);
                s2=info(tab_point(1)+1:tab_point(2)-1);
                s3=info(tab_point(2)+1:end);
                channel.name{k}=s1;
                channel.property{k}=s2;
                channel.value{k}=str2num(s3);
            end
        case '[Measurement-Method]'
            flag_method=0;
            while flag_method==0
                info=fgetl(fid);
                row=row+1;
                [para_name,info]=strtok(info,sign);
                switch para_name
                    case 'Methodfile'
                        [s,info]=strtok(info,sign);
                        method.Methodfile=s;
                    case 'SampleInterval'
                        [s,info]=strtok(info,sign);
                        method.SampleInterval=str2num(s);
                    case 'PreSamplingTime'
                        [s,info]=strtok(info,sign);
                        method.PreSamplingTime=str2num(s);
                    case 'LongTimeInterval'
                        [s,info]=strtok(info,sign);
                        method.LongTimeInterval=str2num(s);
                    case 'MeasurementTime'
                        [s,info]=strtok(info,sign);
                        method.MeasurementTime=str2num(s);
                    case 'MeasurementCount'
                        [s,info]=strtok(info,sign);
                        method.MeasurementCount=str2num(s);
                    case 'FlushTime'
                        [s,info]=strtok(info,sign);
                        method.FlushTime=str2num(s);
                    case 'ZeroPointCount'
                        [s,info]=strtok(info,sign);
                        method.ZeroPointCount=str2num(s);
                    case 'ZeroPointCountAuto'
                        [s,info]=strtok(info,sign);
                        method.ZeroPointCountAuto=str2num(s);
                    case 'ChamberFlow'
                        [s,info]=strtok(info,sign);
                        method.ChamberFlow=str2num(s);
                    case 'InjectionFlow'
                        [s,info]=strtok(info,sign);
                        method.InjectionFlow=str2num(s);
                    case 'Dilution'
                        [s,info]=strtok(info,sign);
                        method.Dilution=str2num(s);
                    case 'DilutionChannel'
                        [s,info]=strtok(info,sign);
                        method.DilutionChannel=str2num(s);
                    case 'DilutionMax'
                        [s,info]=strtok(info,sign);
                        method.DilutionMax=str2num(s);
                    case 'FFTAdapt'
                        [s,info]=strtok(info,sign);
                        method.FFTAdapt=str2num(s);
                    case 'Used'
                        [s,info]=strtok(info,sign);
                        method.Used=str2num(s);
                        flag_method=1;
                end
            end
        case '[Data]'
            info=fgetl(fid);
            row=row+1;
            datarows=ceil(method.MeasurementTime/method.SampleInterval);
            raw_data=[];
            for i=1:datarows
                info=fgetl(fid);
                row=row+1;                
                sdata=str2num(info);
                raw_data=[raw_data;sdata];
            end
            sensor_num=fileinfo.nchanl-4;
            sensor_data=raw_data(:,1:sensor_num);
            flag_done=1;
    end
end