clc
hold off;
x=-10:1:20;
y=x;
BitRate=10000;%信源产生的比特率
MessageLength=4;%信息位
CodewordLength=7;%码长
for i=1:length(x)
    SNR=x(i);%信噪比
    sim('FSK_Hamming');%运行仿真程序，得到的误比特率保存到工作区变量BitErrorRate中
    y(i)=mean(BitErrorRate);%对矩阵中各列的误码率分别求平均值表示误码率
end
semilogy(x,y,'-r');%y轴使用对数标度
hold on;
MessageLength=11;
CodewordLength=15;
for i=1:length(x)
    SNR=x(i);
    sim('FSK_Hamming');
    y(i)=mean(BitErrorRate);
end
semilogy(x,y,'-k');
hold on;
MessageLength=26;
CodewordLength=31;
for i=1:length(x)
    SNR=x(i);
    sim('FSK_Hamming');
    y(i)=mean(BitErrorRate);
end
semilogy(x,y,'-b');
hold on;
xlabel('信噪比SNR（dB）');
ylabel('误码率Pe');
title('2FSK+汉明码的误码率性能');
legend('码率=4/7','码率=11/15','码率=26/31');
grid on;