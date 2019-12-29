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


//退出窗口管理程序
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

    //启动GTK
    gtk_init(NULL,NULL);
    //创建窗口，TOPLEVEL 顶层窗口，有边框
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //标题设置
    gtk_window_set_title(GTK_WINDOW(window),"System Time");
    //窗口伸缩设置 TURE->可伸缩
    gtk_window_set_resizable(GTK_WINDOW(window),TRUE);
    //窗口在显示器位置,GTK_WIN_POS_NONE -> 不固定
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_NONE);
    //退出调用函数
    g_signal_connect(G_OBJECT(window),"DESTORY",G_CALLBACK(destory_progress),NULL);
    //窗口边框宽度
    gtk_container_set_border_width(GTK_CONTAINER(window),20);

    //创建一个纵向组装盒,参数为FALSE，组装盒建立5个不同大小的按钮
    vbox = gtk_vbox_new(FALSE,10);
    //纵向组装盒的边框宽度
    gtk_container_border_width(GTK_CONTAINER(vbox),100);
    //纵向组装盒控件加入窗口控件中
    gtk_container_add(GTK_CONTAINER(window),vbox);
    //vbox显示
    gtk_widget_show(vbox);
    //标签
    label = gtk_label_new(ctime(&t));
    //在vbox中从前往后进行排列，不随窗口拉伸而改变的大小
    gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,10);
    //显示标签
    gtk_widget_show(label);
    //显示窗口
    gtk_widget_show(window);
    //每隔1000ms刷新 显示系统时间
    g_timeout_add(1000,systime,(gpointer)label);
    //初始化
    gtk_main();
}

