clc
%2FSK�ڼ��Ը�˹�������ŵ��µ������������������֮��Ĺ�ϵ
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
xlabel('�����SNR��dB��');
ylabel('������Pe');
title('�ڼ��Ը�˹�������ŵ��µ������������������֮��Ĺ�ϵ');
legend('����=4/7');
axis([-10,10,1e-6,1]);
grid on;