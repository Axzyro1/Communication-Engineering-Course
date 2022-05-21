x=-10:1:10;
y=x;
for i=1:length(x)
    SNR=x(i);%信道的信噪比
    sim('BPSK');%运行仿真程序，将得到的误比特率保存在工作区变量中
    y(i)=mean(BitErrorRate);%计算BitErrorRate的平均值作为误码率
end
semilogy(x,y);%对y取对数画图
hold on;
xlabel('高斯白噪声信道中的SNR');
ylabel('误码率');
title('BPSK的误码率曲线');
hold on;
grid on;