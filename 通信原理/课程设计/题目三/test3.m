clc
hold off;
x=-10:1:10;
y=x;
BitRate=100;%��Դ�����ı�����
bitrate=100;
MessageLength=4;%��Ϣλ
CodewordLength=7;%�볤
for i=1:length(x)
    SNR=x(i);%�����
    sim('DSSSS');%���з�����򣬵õ���������ʱ��浽����������BitErrorRate��
    y(i)=mean(BitErrorRate);%�Ծ����и��е������ʷֱ���ƽ��ֵ��ʾ������
end
semilogy(x,y,'r');%y��ʹ�ö������
hold on;
bitrate=1000;
for i=1:length(x)
    SNR=x(i);%�����
    sim('DSSSS');%���з�����򣬵õ���������ʱ��浽����������BitErrorRate��
    y(i)=mean(BitErrorRate);%�Ծ����и��е������ʷֱ���ƽ��ֵ��ʾ������
end
semilogy(x,y,'g');%y��ʹ�ö������
hold on;
bitrate=10000;
for i=1:length(x)
    SNR=x(i);%�����
    sim('DSSSS');%���з�����򣬵õ���������ʱ��浽����������BitErrorRate��
    y(i)=mean(BitErrorRate);%�Ծ����и��е������ʷֱ���ƽ��ֵ��ʾ������
end
semilogy(x,y);%y��ʹ�ö������
hold on;
xlabel('�����SNR��dB��');
ylabel('������Pe');
title('DSSS����������������Ƶ�����Ĺ�ϵ');
%axis([-10,10,1e-6,1])
hold on;
legend('��Ƶ����10','��Ƶ����20','��Ƶ����30')
grid on;