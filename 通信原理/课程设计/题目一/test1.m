x=-10:1:10;
y=x;
for i=1:length(x)
    SNR=x(i);%�ŵ��������
    sim('BPSK');%���з�����򣬽��õ���������ʱ����ڹ�����������
    y(i)=mean(BitErrorRate);%����BitErrorRate��ƽ��ֵ��Ϊ������
end
semilogy(x,y);%��yȡ������ͼ
hold on;
xlabel('��˹�������ŵ��е�SNR');
ylabel('������');
title('BPSK������������');
hold on;
grid on;