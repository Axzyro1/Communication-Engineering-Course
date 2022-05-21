clc
hold off;
x=-10:1:10;
y=x;
BitRate=100;%信源产生的比特率
bitrate=100;
MessageLength=4;%信息位
CodewordLength=7;%码长
for i=1:length(x)
    SNR=x(i);%信噪比
    sim('DSSSS');%运行仿真程序，得到的误比特率保存到工作区变量BitErrorRate中
    y(i)=mean(BitErrorRate);%对矩阵中各列的误码率分别求平均值表示误码率
end
semilogy(x,y,'r');%y轴使用对数标度
hold on;
bitrate=1000;
for i=1:length(x)
    SNR=x(i);%信噪比
    sim('DSSSS');%运行仿真程序，得到的误比特率保存到工作区变量BitErrorRate中
    y(i)=mean(BitErrorRate);%对矩阵中各列的误码率分别求平均值表示误码率
end
semilogy(x,y,'g');%y轴使用对数标度
hold on;
bitrate=10000;
for i=1:length(x)
    SNR=x(i);%信噪比
    sim('DSSSS');%运行仿真程序，得到的误比特率保存到工作区变量BitErrorRate中
    y(i)=mean(BitErrorRate);%对矩阵中各列的误码率分别求平均值表示误码率
end
semilogy(x,y);%y轴使用对数标度
hold on;
xlabel('信噪比SNR（dB）');
ylabel('误码率Pe');
title('DSSS的误码率性能与扩频增益间的关系');
%axis([-10,10,1e-6,1])
hold on;
legend('扩频增益10','扩频增益20','扩频增益30')
grid on;