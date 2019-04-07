# 以cer的服务器为例
tshark -i eth2 -f "tcp dst port 31422"
1. -i:捕获eth2网卡；
2. -f:只捕获协议为tcp，目的端口为31422；
