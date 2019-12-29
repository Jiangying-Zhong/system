#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>

#define BUFF_SIZE 1024

asmlinkage int sys_copy(const char* s_file, const char* t_file)
{
    int to_fd,copy_fd;
    int rnum,wnum;
    char buf[100]; //һ�ζ�ȡ100�ֽ�

    mm_segment_t old_fs;
    old_fs = get_fs();  //����ԭ���Ķ�
    set_fs(KERNEL_DS);  //����Ϊ���ݶ�

    //������ ֻ��
    if ((copy_fd = sys_open(s_file, O_RDONLY,0)) == -1)
    {
       return -1;
    }

    // Ŀ��·�����ļ�  û���򴴽�
    if ((to_fd = sys_open(t_file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1){
        return -1;
    }

    while(1)
    {
        //read
        rnum = sys_read(copy_fd, buf, sizeof(buf));
        if(rnum == -1)
        {
            return -1;
        }
        else if (rnum>0)
        {
            //write
            wnum = sys_write(to_fd, buf, rnum);
            if (wnum != rnum)
            {
                return -1;
            }
        }
        else if(rnum == 0 ) break;
    }
    set_fs(old_fs);
    return 0;
}
