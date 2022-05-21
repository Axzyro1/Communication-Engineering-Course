clc
hold off;
x=-10:1:15;
y=x;
for i=1:length(x)
    SNR=x(i);%信道的信噪比
    sim('compare');%运行仿真程序，将得到的误比特率保存在工作区变量中
    y(i)=mean(BPSKBitErrorRate);%计算BPSKBitErrorRate的平均值作为误码率
end
semilogy(x,y,'r');%对y取对数画图
hold on;
for i=1:length(x)
    SNR=x(i);%信道的信噪比
    sim('compare');%运行仿真程序，将得到的误比特率保存在工作区变量中
    y(i)=mean(FSKBitErrorRate);%计算FSKBitErrorRate的平均值作为误码率
end
semilogy(x,y,'g');%对y取对数画图
hold on;
for i=1:length(x)
    SNR=x(i);%信道的信噪比
    sim('compare');%运行仿真程序，将得到的误比特率保存在工作区变量中
    y(i)=mean(DBPSKBitErrorRate);%计算DBPSKBitErrorRate的平均值作为误码率
end
semilogy(x,y,'b');%对y取对数画图
hold on;
xlabel('高斯白噪声信道中的SNR');
ylabel('误码率');
legend('BPSK','2FSK','DBPSK');
hold on;
grid on;