#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#ifndef WINVER
#define WINVER 0x0600
#endif

#include <ctime>
#include <fstream>
#include <graphics.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <windows.h>
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const double DRAW_INTERVAL = 0.02;
const double UPDATE_INTERVAL = 0.005;

#define COLOR_WHITE     RGB(255,255,255)
#define COLOR_GRAY      RGB(128,128,128)
#define COLOR_LIGHTGRAY RGB(200,200,200)
#define COLOR_BUTTON    RGB(66, 133, 244)
#define COLOR_DARKGRAY  RGB(64,64,64)
#define COLOR_AMBER     RGB(255,191,0)  // 琥珀色
#define COLOR_RED       RGB(255,0,0)
#define COLOR_BLUE      RGB(0,0,255)
#define COLOR_GREEN     RGB(0,255,0)
#define COLOR_LIGHTBLUE RGB(100,149,237)
#define COLOR_BLACK     RGB(0,0,0)

// 飞机状态
enum STATE { START, RUN, STOP };

// 飞机指令
enum ORDER { OSTART, OSTOP };

// 异常类型
enum ErrorType {
	ERR_N_SENSOR_SINGLE,		// 单个转速传感器故障（白色）
	ERR_N_SENSOR_SINGLE_ENG,	// 单发转速传感器故障（琥珀色）
	ERR_EGT_SENSOR_SINGLE,		// 单个EGT传感器故障（白色）
	ERR_EGT_SENSOR_SINGLE_ENG,	// 单发EGT传感器故障（琥珀色）
	ERR_N_EGT_SENSOR_DUAL,		// 双发转速/EGT传感器故障（红色）
	ERR_FUEL_LOW,				// 燃油余量低于1000（琥珀色）
	ERR_FUEL_SENSOR,			// 燃油余量故障（无效值，红色）
	ERR_FUEL_FLOW_OVER,			// 燃油流速超50（琥珀色）
	ERR_N_OVER_105,				// 超转1（N1>105，琥珀色）
	ERR_N_OVER_120,				// 超转2（N1>120，红色）
	ERR_T_OVER_850_START,		// 超温1（启动中T>850，琥珀色）
	ERR_T_OVER_1000_START,		// 超温2（启动中T>1000，红色）
	ERR_T_OVER_950_RUN,			// 超温3（稳态T>950，琥珀色）
	ERR_T_OVER_1100_RUN			// 超温4（稳态T>1100，红色）
};

// 告警级别
enum AlarmLevel {
	LEVEL_WHITE,    // 白色：传感器故障（仅告警，指示正常）
	LEVEL_AMBER,    // 琥珀色：警戒值
	LEVEL_RED,      // 红色：警告值（触发停车）
	LEVEL_INVALID   // 无效值（--）
};

// 告警信息结构体
struct AlarmInfo {
	ErrorType type;         // 异常类型
	AlarmLevel level;       // 告警级别
	string desc;            // 英文描述
	double trigger_time;    // 触发时间（秒）
	bool is_active;         // 是否当前激活（供界面高亮）
};

class Plane
{
private:
	STATE s;						// 飞机状态
	ORDER order;					// 飞机指令
	bool changed;					// 指令是否改变
	double N_l;						// 左发动机转速百分比，0-125，转速额定值为40000
	double N_r;						// 右发动机转速百分比，0-125，转速额定值为40000
	double T_l;						// 左发动机温度，-5-1200
	double T_r;						// 右发动机温度，-5-1200
	double C;						// 燃油余量，0-20000单位
	double V;						// 燃油变化率，0-50单位每秒
	int adjust;						// 增加/减少推力，存在正负
	uint64_t last_update_ms;		// 上次更新的时间戳，单位毫秒
	double t;						// 飞机运行时间，单位秒
	double t_start;					// 启动阶段累计时间
	double t_stop;					// 停车阶段累计时间
	double N_stop_l;				// 停车阶段左转速
	double N_stop_r;				// 停车阶段右转速
	double T_stop_l;				// 停车阶段左温度
	double T_stop_r;				// 停车阶段右温度
	const double T0 = 20.0;			// 环境温度常数
	const double N_rated = 40000.0;	// 额定转速
	const double N1_threshold = 95.0;	// 稳定阶段转速阈值（95%）
	ofstream csv_file;				// 飞行日程文件
	bool csv_file_created;			// 标记飞行日程文件是否已初始化
	string csv_filename;			// 飞行日程文件名
	ofstream log_file;              // 告警Log文件
	bool log_file_created;          // 标记Log文件是否初始化
	string log_filename;            // Log文件名
	vector<AlarmInfo> current_alarms; // 当前告警列表
	unordered_map<ErrorType, double> last_error_time; // 模拟传感器无效值（用于触发传感器故障异常）
	bool N_sensor_l1_invalid;       // 左发转速传感器1无效
	bool N_sensor_l2_invalid;       // 左发转速传感器2无效
	bool N_sensor_r1_invalid;       // 右发转速传感器1无效
	bool N_sensor_r2_invalid;       // 右发转速传感器2无效
	bool EGT_sensor_l1_invalid;     // 左发EGT传感器1无效
	bool EGT_sensor_l2_invalid;     // 左发EGT传感器2无效
	bool EGT_sensor_r1_invalid;     // 右发EGT传感器1无效
	bool EGT_sensor_r2_invalid;     // 右发EGT传感器2无效
	bool fuel_sensor_invalid;       // 燃油余量传感器无效

	// 生成-0.03到0.03之间的随机数
	double random1();
	// 生成0.03到0.05之间的随机数
	double random2();
	// 限幅函数
	double clamp(double val, double min_val, double max_val);
	// start阶段重置传感器状态
	void update_s(double dt);
	// run阶段重置传感器状态
	void update_r(double dt);
	// stop阶段重置传感器状态
	void update_p(double dt);
	// 更新状态
	void update_state();
	// 创建csv文件名
	string create_filename();
	// 创建log文件名
	string create_log_filename();
	// 保存数据到CSV文件
	void save_data();
	// 初始化Log文件
	void init_log_file();
	// 写入告警到Log文件
	void write_alarm_to_log(ErrorType type, AlarmLevel level, const string& desc);
	// 异常检测
	void detect_errors();
	// 角度转弧度
	double deg_to_rad(double deg);
	// 绘制扇形，6.283185307179586
	void draw_pie(int x, int y, double num, double max_num);
	// 绘制函数
	void draw();
	// 设置按钮指令
	void handle_mouse_input();
	// 主更新函数
	void update(double dt);

public:
	// 构造函数
	Plane();
	// 析构函数
	~Plane();
	// 运行函数
	void run();
};