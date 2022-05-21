clc
hold off;
x=-10:1:10;
y=x;
BitRate=10000;%��Դ�����ı�����
MessageLength=4;%��Ϣλ
CodewordLength=7;%�볤
for i=1:length(x)
    SNR=x(i);%�����
    sim('BPSK_Hamming');%���з�����򣬵õ���������ʱ��浽����������BitErrorRate��
    y(i)=mean(BitErrorRate);%�Ծ����и��е������ʷֱ���ƽ��ֵ��ʾ������
end
semilogy(x,y,'-r');%y��ʹ�ö������
hold on;
MessageLength=11;
CodewordLength=15;
for i=1:length(x)
    SNR=x(i);
    sim('BPSK_Hamming');
    y(i)=mean(BitErrorRate);
end
semilogy(x,y,'-k');
hold on;
MessageLength=26;
CodewordLength=31;
for i=1:length(x)
    SNR=x(i);
    sim('BPSK_Hamming');
    y(i)=mean(BitErrorRate);
end
semilogy(x,y,'-b');
hold on;
xlabel('�����SNR��dB��');
ylabel('������Pe');
title('BPSK+�����������������');
legend('����=4/7','����=11/15','����=26/31');
axis([-10,10,1e-6,1]);
grid on;
