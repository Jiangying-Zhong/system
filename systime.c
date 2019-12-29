#include <gtk/gtk.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _DEBUG_ 1
#define CK_TIME 1

gint systime(gpointer label)
{
    time_t t;
    time(&t);
    char string[100];
    sprintf(string,"%s",ctime(&t));
    gtk_label_set_text(label,string);
}


//�˳����ڹ������
void destory_progress(GtkWidget *widget)
{
    gtk_main_quit();
}

int main(void)
{
    time_t t;
    time(&t);

    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *button;
    GtkWidget *label;
    gpointer data;

    //����GTK
    gtk_init(NULL,NULL);
    //�������ڣ�TOPLEVEL ���㴰�ڣ��б߿�
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //��������
    gtk_window_set_title(GTK_WINDOW(window),"System Time");
    //������������ TURE->������
    gtk_window_set_resizable(GTK_WINDOW(window),TRUE);
    //��������ʾ��λ��,GTK_WIN_POS_NONE -> ���̶�
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_NONE);
    //�˳����ú���
    g_signal_connect(G_OBJECT(window),"DESTORY",G_CALLBACK(destory_progress),NULL);
    //���ڱ߿���
    gtk_container_set_border_width(GTK_CONTAINER(window),20);

    //����һ��������װ��,����ΪFALSE����װ�н���5����ͬ��С�İ�ť
    vbox = gtk_vbox_new(FALSE,10);
    //������װ�еı߿���
    gtk_container_border_width(GTK_CONTAINER(vbox),100);
    //������װ�пؼ����봰�ڿؼ���
    gtk_container_add(GTK_CONTAINER(window),vbox);
    //vbox��ʾ
    gtk_widget_show(vbox);
    //��ǩ
    label = gtk_label_new(ctime(&t));
    //��vbox�д�ǰ����������У����洰��������ı�Ĵ�С
    gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,10);
    //��ʾ��ǩ
    gtk_widget_show(label);
    //��ʾ����
    gtk_widget_show(window);
    //ÿ��1000msˢ�� ��ʾϵͳʱ��
    g_timeout_add(1000,systime,(gpointer)label);
    //��ʼ��
    gtk_main();
}

