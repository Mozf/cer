function varargout = SRnet(varargin)
% SRNET MATLAB code for SRnet.fig
%      SRNET, by itself, creates a new SRNET or raises the existing
%      singleton*.
%
%      H = SRNET returns the handle to a new SRNET or the handle to
%      the existing singleton*.
%
%      SRNET('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SRNET.M with the given input arguments.
%
%      SRNET('Property','Value',...) creates a new SRNET or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before SRnet_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to SRnet_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help SRnet

% Last Modified by GUIDE v2.5 25-Apr-2019 09:11:16

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @SRnet_OpeningFcn, ...
                   'gui_OutputFcn',  @SRnet_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT

end
% --- Executes just before SRnet is made visible.
function SRnet_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to SRnet (see VARARGIN)

% Choose default command line output for SRnet
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes SRnet wait for user response (see UIRESUME)
% uiwait(handles.figure1);


end
% --- Outputs from this function are returned to the command line.
function varargout = SRnet_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

end
% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filelist,path]=uigetfile({'*.nos','NOS Files(*.nos)'},'选择A类训练样本','MultiSelect','on');
if iscell(filelist) 
	filenum=size(filelist,2); 
elseif filelist==0 
    return
end
train_data1=[];
for i=1:1:filenum
    train_data1=[train_data1;read_NOS_data([path,filelist{i}])];
end

end
% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filelist,path]=uigetfile({'*.nos','NOS Files(*.nos)'},'选择B类训练样本','MultiSelect','on');
if iscell(filelist) 
	filenum=size(filelist,2); 
elseif filelist==0 
    return
end
train_data2=[];
for i=1:1:filenum
    train_data2=[train_data2;read_NOS_data([path,filelist{i}])];
end
end
% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filelist,path]=uigetfile({'*.nos','NOS Files(*.nos)'},'选择C类训练样本','MultiSelect','on');
if iscell(filelist) 
	filenum=size(filelist,2); 
elseif filelist==0 
    return
end
train_data3=[];
for i=1:1:filenum
    train_data3=[train_data3;read_NOS_data([path,filelist{i}])];
end
end
% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[filelist,path]=uigetfile({'*.nos','NOS Files(*.nos)'},'选择D类训练样本','MultiSelect','on');
if iscell(filelist) 
	filenum=size(filelist,2); 
elseif filelist==0 
    return
end
train_data4=[];
for i=1:1:filenum
    train_data4=[train_data4;read_NOS_data([path,filelist{i}])];
end
end