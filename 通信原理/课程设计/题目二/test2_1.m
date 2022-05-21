clc
%2FSK在加性高斯白噪声信道下的误码率性能与信噪比之间的关系
hold off;
x=-10:1:10;
y=x;
BitRate=10000;%信源产生的比特率
MessageLength=4;%信息位
CodewordLength=7;%码长
for i=1:length(x)
    SNR=x(i);%信噪比
    sim('BPSK_Hamming');%运行仿真程序，得到的误比特率保存到工作区变量BitErrorRate中
    y(i)=mean(BitErrorRate);%对矩阵中各列的误码率分别求平均值表示误码率
end
semilogy(x,y,'-r');%y轴使用对数标度
hold on;
xlabel('信噪比SNR（dB）');
ylabel('误码率Pe');
title('在加性高斯白噪声信道下的误码率性能与信噪比之间的关系');
legend('码率=4/7');
axis([-10,10,1e-6,1]);
grid on;