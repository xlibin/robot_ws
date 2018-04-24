#include "ros/ros.h"
#include "std_msgs/String.h"
#include "asr_record/sr_order.h"

#include "../include/msc/msp_cmn.h"
#include "../include/msc/msp_errors.h"
#include "../include/asr_record/asr_record.h"

int16_t g_order = ORDER_NONE;
BOOL g_is_order_publiced = TRUE;

#define MAX_SIZE 100
int main(int argc, char **argv)
{
  ros::init(argc, argv, "asr_record");
  ros::NodeHandle nh;
  ros::Publisher chatter_pub = nh.advertise<asr_record::sr_order>("sr_order", 1000);
  ros::Rate loop_rate(10);

  //char current_absolute_path[MAX_SIZE];
  //获取当前程序绝对路径
  //int cnt = readlink("/proc/self/exe", current_absolute_path, MAX_SIZE);
  //getcwd(current_absolute_path, MAX_SIZE);
  //printf("current absolute path:%s\n", current_absolute_path);
//init iflytek
  const char *login_config    = "appid = 5add9519"; //登录参数
  UserData asr_data;
  int ret                     = 0 ;
  asr_record::sr_order order_send;

  ret = MSPLogin(NULL, NULL, login_config); //第一个参数为用户名，第二个参数为密码，传NULL即可，第三个参数是登录参数
  if (MSP_SUCCESS != ret) {
    printf("登录失败：%d\n", ret);
    goto exit;
  }

  memset(&asr_data, 0, sizeof(UserData));
  printf("构建离线识别语法网络...\n");
  ret = build_grammar(&asr_data);  //第一次使用某语法进行识别，需要先构建语法网络，获取语法ID，之后使用此语法进行识别，无需再次构建
  if (MSP_SUCCESS != ret) {
    printf("构建语法调用失败！\n");
    goto exit;
  }
  while (1 != asr_data.build_fini)
    usleep(300 * 1000);
  if (MSP_SUCCESS != asr_data.errcode)
    goto exit;
  printf("离线识别语法网络构建完成，开始识别...\n");

  while (1)
  {
//    std_msgs::String msg;
//    msg.data = "hello world";
    ret = run_asr(&asr_data);
    if(ros::ok() && g_is_order_publiced == FALSE){
      order_send.order = g_order;
      chatter_pub.publish(order_send);
      g_is_order_publiced = TRUE;
		}
    

    ros::spinOnce();

    //loop_rate.sleep();
  }
exit:
  MSPLogout();
  printf("请按任意键退出...\n");
  getchar();

  return 0;
}
