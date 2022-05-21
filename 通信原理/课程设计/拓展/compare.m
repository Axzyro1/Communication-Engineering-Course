clc
hold off;
x=-10:1:15;
y=x;
for i=1:length(x)
    SNR=x(i);%�ŵ��������
    sim('compare');%���з�����򣬽��õ���������ʱ����ڹ�����������
    y(i)=mean(BPSKBitErrorRate);%����BPSKBitErrorRate��ƽ��ֵ��Ϊ������
end
semilogy(x,y,'r');%��yȡ������ͼ
hold on;
for i=1:length(x)
    SNR=x(i);%�ŵ��������
    sim('compare');%���з�����򣬽��õ���������ʱ����ڹ�����������
    y(i)=mean(FSKBitErrorRate);%����FSKBitErrorRate��ƽ��ֵ��Ϊ������
end
semilogy(x,y,'g');%��yȡ������ͼ
hold on;
for i=1:length(x)
    SNR=x(i);%�ŵ��������
    sim('compare');%���з�����򣬽��õ���������ʱ����ڹ�����������
    y(i)=mean(DBPSKBitErrorRate);%����DBPSKBitErrorRate��ƽ��ֵ��Ϊ������
end
semilogy(x,y,'b');%��yȡ������ͼ
hold on;
xlabel('��˹�������ŵ��е�SNR');
ylabel('������');
legend('BPSK','2FSK','DBPSK');
hold on;
grid on;