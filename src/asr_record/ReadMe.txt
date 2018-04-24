1.You need to change the work space path to your absolute path in arc_record.c 's 
const char * ASR_RES_PATH        = "fo|/home/trobot/robot_ws/src/asr_record/res/asr/common.jet"; //离线语法识别资源路径
const char * GRM_BUILD_PATH      = "/home/trobot/robot_ws/src/asr_record/res/asr/GrmBuilld"; //构建离线语法识别网络生成数据保存路径
const char * GRM_FILE            = "/home/trobot/robot_ws/src/asr_record/res/asr/call.bnf"; //构建离线识别语法网络所用的语法文件

 
