#include <gtk/gtk.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _DEBUG_ 1
#define CK_TIME 1

int n = 0, i = 1;

gint sum(gpointer label)
{
    char string[50];
    n += i;
    i++;
    sprintf(string,"sum(1-%d) = %d", i-1,n);
    gtk_label_set_text(label, string);
    if (i > 100)
    {
        i = 1;
        n = 0;
    }
}

//�˳����ڹ������
void destory_progress(GtkWindow *widget, gpointer data)
{
    gtk_main_quit ();
}

int main(int argc, char **argv)
{
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *button;
    GtkWidget *label;
    gpointer data;

    gtk_set_locale();
    //����GTK
    gtk_init(&argc,&argv);
    //�������ڣ�TOPLEVEL ���㴰�ڣ��б߿�
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //��������
    gtk_window_set_title(GTK_WINDOW(window),"sum");
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
    label = gtk_label_new("sum");
    //��vbox�д�ǰ����������У����洰��������ı�Ĵ�С
    gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,10);
    //��ʾ��ǩ
    gtk_widget_show(label);
    //ÿ��1000msˢ�� ��ʾϵͳʱ��
    g_timeout_add(1000,sum,(gpointer)label);
    //��ʾ����
    gtk_widget_show(window);
    //��ʼ��
    gtk_main();
}


