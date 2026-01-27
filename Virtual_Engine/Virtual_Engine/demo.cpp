//#define _CRT_SECURE_NO_WARNINGS
//#ifndef _WIN32_WINNT
//#define _WIN32_WINNT 0x0600
//#endif
//#ifndef WINVER
//#define WINVER 0x0600
//#endif
//
//#include <ctime>
//#include <fstream>
//#include <graphics.h>
//#include <iomanip>
//#include <iostream>
//#include <sstream>
//#include <string>
//#include <unordered_map>
//#include <vector>
//#include <windows.h>
//using namespace std;
//
//const int WINDOW_WIDTH = 800;
//const int WINDOW_HEIGHT = 600;
//const double DRAW_INTERVAL = 0.02;
//const double UPDATE_INTERVAL = 0.005;
//
//#define COLOR_WHITE     RGB(255,255,255)
//#define COLOR_GRAY      RGB(128,128,128)
//#define COLOR_DARKGRAY  RGB(64,64,64)
//#define COLOR_AMBER     RGB(255,191,0)  // 琥珀色
//#define COLOR_RED       RGB(255,0,0)
//#define COLOR_BLUE      RGB(0,0,255)
//#define COLOR_GREEN     RGB(0,255,0)
//#define COLOR_LIGHTBLUE RGB(100,149,237)
//#define COLOR_BLACK     RGB(0,0,0)
//
//// 飞机状态
//enum STATE { START, RUN, STOP };
//
//// 飞机指令
//enum ORDER { OSTART, OSTOP };
//
//// 异常类型
//enum ErrorType {
//	ERR_N_SENSOR_SINGLE,		// 单个转速传感器故障（白色）
//	ERR_N_SENSOR_SINGLE_ENG,	// 单发转速传感器故障（琥珀色）
//	ERR_EGT_SENSOR_SINGLE,		// 单个EGT传感器故障（白色）
//	ERR_EGT_SENSOR_SINGLE_ENG,	// 单发EGT传感器故障（琥珀色）
//	ERR_N_EGT_SENSOR_DUAL,		// 双发转速/EGT传感器故障（红色）
//	ERR_FUEL_LOW,				// 燃油余量低于1000（琥珀色）
//	ERR_FUEL_SENSOR,			// 燃油余量故障（无效值，红色）
//	ERR_FUEL_FLOW_OVER,			// 燃油流速超50（琥珀色）
//	ERR_N_OVER_105,				// 超转1（N1>105，琥珀色）
//	ERR_N_OVER_120,				// 超转2（N1>120，红色）
//	ERR_T_OVER_850_START,		// 超温1（启动中T>850，琥珀色）
//	ERR_T_OVER_1000_START,		// 超温2（启动中T>1000，红色）
//	ERR_T_OVER_950_RUN,			// 超温3（稳态T>950，琥珀色）
//	ERR_T_OVER_1100_RUN			// 超温4（稳态T>1100，红色）
//};
//
//// 告警级别
//enum AlarmLevel {
//	LEVEL_WHITE,    // 白色：传感器故障（仅告警，指示正常）
//	LEVEL_AMBER,    // 琥珀色：警戒值
//	LEVEL_RED,      // 红色：警告值（触发停车）
//	LEVEL_INVALID   // 无效值（--）
//};
//
//// 告警信息结构体
//struct AlarmInfo {
//	ErrorType type;         // 异常类型
//	AlarmLevel level;       // 告警级别
//	string desc;            // 英文描述
//	double trigger_time;    // 触发时间（秒）
//	bool is_active;         // 是否当前激活（供界面高亮）
//};
//
//class Plane
//{
//private:
//	STATE s;						// 飞机状态
//	ORDER order;					// 飞机指令
//	bool changed;					// 指令是否改变
//	double N_l;						// 左发动机转速百分比，0-125，转速额定值为40000
//	double N_r;						// 右发动机转速百分比，0-125，转速额定值为40000
//	double T_l;						// 左发动机温度，-5-1200
//	double T_r;						// 右发动机温度，-5-1200
//	double C;						// 燃油余量，0-20000单位
//	double V;						// 燃油变化率，0-50单位每秒
//	int adjust;						// 增加/减少推力，存在正负
//	uint64_t last_update_ms;		// 上次更新的时间戳，单位毫秒
//	double t;						// 飞机运行时间，单位秒
//	double t_start;					// 启动阶段累计时间
//	double t_stop;					// 停车阶段累计时间
//	double N_stop_l;				// 停车阶段左转速
//	double N_stop_r;				// 停车阶段右转速
//	double T_stop_l;				// 停车阶段左温度
//	double T_stop_r;				// 停车阶段右温度
//	const double T0 = 20.0;			// 环境温度常数
//	const double N_rated = 40000.0;	// 额定转速
//	const double N1_threshold = 95.0;	// 稳定阶段转速阈值（95%）
//	ofstream csv_file;				// 飞行日程文件
//	bool csv_file_created;			// 标记飞行日程文件是否已初始化
//	string csv_filename;			// 飞行日程文件名
//	ofstream log_file;              // 告警Log文件
//	bool log_file_created;          // 标记Log文件是否初始化
//	string log_filename;            // Log文件名
//	vector<AlarmInfo> current_alarms; // 当前告警列表
//	unordered_map<ErrorType, double> last_error_time; // 模拟传感器无效值（用于触发传感器故障异常）
//	bool N_sensor_l1_invalid;       // 左发转速传感器1无效
//	bool N_sensor_l2_invalid;       // 左发转速传感器2无效
//	bool N_sensor_r1_invalid;       // 右发转速传感器1无效
//	bool N_sensor_r2_invalid;       // 右发转速传感器2无效
//	bool EGT_sensor_l1_invalid;     // 左发EGT传感器1无效
//	bool EGT_sensor_l2_invalid;     // 左发EGT传感器2无效
//	bool EGT_sensor_r1_invalid;     // 右发EGT传感器1无效
//	bool EGT_sensor_r2_invalid;     // 右发EGT传感器2无效
//	bool fuel_sensor_invalid;       // 燃油余量传感器无效
//
//
//
//	// 生成-0.03到0.03之间的随机数
//	double random1() 
//	{
//		return ((double)rand() / RAND_MAX) * 0.06 - 0.03;
//	}
//
//	// 生成0.03到0.05之间的随机数
//	double random2() 
//	{
//		return ((double)rand() / RAND_MAX) * 0.02 + 0.03;
//	}
//
//	// 限幅函数
//	double clamp(double val, double min_val, double max_val) {
//		return max(min_val, min(val, max_val));
//	}
//
//	// 重置传感器状态
//	// start阶段
//	void update_s(double dt) {
//		t += dt;
//		t_start += dt;
//
//		if (t_start <= 2.0) {
//			N_l = clamp((10000.0 * t_start / N_rated * 100) * (1 + random1()) * (1 + adjust * random2()), 0.0, 125.0);
//			N_r = clamp((10000.0 * t_start / N_rated * 100) * (1 + random1()) * (1 + adjust * random2()), 0.0, 125.0);
//			T_l = clamp(T0 * (1 + random1()) * (1 + adjust * random2()), -5, 1200);
//			T_r = clamp(T0 * (1 + random1()) * (1 + adjust * random2()), -5, 1200);
//			V = clamp(((adjust + 5.0) * t_start) * (1 + random1()), 0.0, 50.0);
//		}
//		else {
//			double t_log = max(t_start - 1, 1.000001); // 避免log(0)错误
//			N_l = clamp((((23000 * log10(t_log) + 20000) / N_rated) * 100) * (1 + random1()) * (1 + adjust * random2()), 0.0, 125.0);
//			N_r = clamp((((23000 * log10(t_log) + 20000) / N_rated) * 100) * (1 + random1()) * (1 + adjust * random2()), 0.0, 125.0);
//			T_l = clamp((900 * log10(t_log) + T0) * (1 + random1()) * (1 + adjust * random2()), -5.0, 1200.0);
//			T_r = clamp((900 * log10(t_log) + T0) * (1 + random1()) * (1 + adjust * random2()), -5.0, 1200.0);
//			V = clamp(((42 * log10(t_log) + 10) + adjust * 1.0) * (1 + random1()), 0.0, 50.0);
//		}
//		C = clamp(C - V * dt, 0.0, 20000.0);
//	}
//
//	// run阶段
//	void update_r(double dt) {
//		t += dt;
//		/*N_l = clamp(95.0 * (1 + random1() * (1 + (adjust - 1.0) * 0.4 + random2())), 0.0, 125.0);
//		N_r = clamp(95.0 * (1 + random1() * (1 + (adjust - 1.0) * 0.4 + random2())), 0.0, 125.0);
//		T_l = clamp(704.348 * (1 + random1() * (1 + (adjust - 1.0) * 0.4 + random2())), -5.0, 1200.0);
//		T_r = clamp(704.348 * (1 + random1() * (1 + (adjust - 1.0) * 0.4 + random2())), -5.0, 1200.0);*/
//		N_l = clamp(95.0 * (1 + random1()) * (1 + adjust * random2()), 0.0, 125.0);
//		N_r = clamp(95.0 * (1 + random1()) * (1 + adjust * random2()), 0.0, 125.0);
//		T_l = clamp(704.348 * (1 + random1()) * (1 + adjust * random2()), -5.0, 1200.0);
//		T_r = clamp(704.348 * (1 + random1()) * (1 + adjust * random2()), -5.0, 1200.0);
//		V = clamp((42.87 + adjust * 1.0) * (1 + random1()), 0.0, 50.0);
//		C = clamp(C - V * dt, 0.0, 20000.0);
//	}
//
//	// stop阶段
//	void update_p(double dt) {
//		t_stop += dt;
//		t += dt;
//		V = 0.0;
//		if (t_stop >= 10.0) {
//			N_l = 0.0;
//			N_r = 0.0;
//			T_l = T0 * (1 + random1());
//			T_r = T0 * (1 + random1());
//			return;
//		}
//		N_l = clamp(N_stop_l * exp(-1 * t_stop) * (1 + random1()), 0.0, 125.0);
//		N_r = clamp(N_stop_r * exp(-1 * t_stop) * (1 + random1()), 0.0, 125.0);
//		T_l = clamp(T_stop_l * exp(-1 * t_stop) * (1 + random1()), T0 * (1 + random1()), 1200.0);
//		T_r = clamp(T_stop_r * exp(-1 * t_stop) * (1 + random1()), T0 * (1 + random1()), 1200.0);
//		C = clamp(C, 0.0, 20000.0);
//	}
//
//	// 更新状态
//	void update_state() {
//		if (order == OSTOP) {
//			adjust = 0;
//			if(s!= STOP) {
//				s = STOP;
//				t_stop = 0;
//				N_stop_l = N_l;
//				N_stop_r = N_r;
//				T_stop_l = T_l;
//				T_stop_r = T_r;
//			}
//		}
//		else {
//			if (N_l >= 95 * (1 + adjust * random2()) && N_r >= 95 * (1 + adjust * random2())) {
//				s = RUN;
//			}
//			else {
//				if (s == STOP) {
//					s = START;
//					if (N_l < 50) {
//						t_start = N_l / 25;
//					}
//					else {
//						t_start = 1 + pow(10, ((4 * N_l - 200) / 230));
//					}
//				}
//			}
//		}
//	}
//
//	// 创建csv文件名
//	string create_filename() {
//		time_t now = time(nullptr);
//		tm local_tm = *localtime(&now);
//		ostringstream oss;
//		oss << "../Virtual_Engine/"
//			<< "engine_data_"
//			<< setfill('0') << setw(4) << local_tm.tm_year + 1900
//			<< setfill('0') << setw(2) << local_tm.tm_mon + 1
//			<< setfill('0') << setw(2) << local_tm.tm_mday << "_"
//			<< setfill('0') << setw(2) << local_tm.tm_hour
//			<< setfill('0') << setw(2) << local_tm.tm_min
//			<< setfill('0') << setw(2) << local_tm.tm_sec
//			<< ".csv";
//		return oss.str();
//	}
//
//	// 创建log文件名
//	string create_log_filename() {
//		time_t now = time(nullptr);
//		tm local_tm = *localtime(&now);
//		ostringstream oss;
//		oss << "../Virtual_Engine/"
//			<< "engine_alarm_log_"
//			<< setfill('0') << setw(4) << local_tm.tm_year + 1900
//			<< setfill('0') << setw(2) << local_tm.tm_mon + 1
//			<< setfill('0') << setw(2) << local_tm.tm_mday << "_"
//			<< setfill('0') << setw(2) << local_tm.tm_hour
//			<< setfill('0') << setw(2) << local_tm.tm_min
//			<< setfill('0') << setw(2) << local_tm.tm_sec
//			<< ".log";
//		return oss.str();
//	}
//
//	// 保存数据到CSV文件
//	void save_data() {
//		// 首次调用
//		if (!csv_file_created) {
//			csv_filename = create_filename();
//			csv_file.open(csv_filename, ios::out | ios::trunc);
//			if (!csv_file.is_open()) {
//				cerr << "Unable to create csv_file!" << endl;
//				return;
//			}
//			csv_file << "time/s,"
//				<< "n_left/%,"
//				<< "n_right/%,"
//				<< "T_left/℃,"
//				<< "T_right/℃,"
//				<< "C,"
//				<< "V/s-1,"
//				<< "state,"
//				<< "adjust\n";
//			csv_file_created = true;
//		}
//		// 正式追加数据
//		if (csv_file.is_open()) {
//			string state_str;
//			if (s == START) state_str = "START";
//			else if (s == RUN) state_str = "RUN";
//			else if (s == STOP) state_str = "STOP";
//			csv_file << fixed << setprecision(3)
//				<< t << ","          // 运行时间（秒）
//				<< N_l << ","        // 左转速百分比
//				<< N_r << ","        // 右转速百分比
//				<< T_l << ","        // 左排气温度
//				<< T_r << ","        // 右排气温度
//				<< C << ","          // 燃油余量
//				<< V << ","          // 燃油流速
//				<< state_str << ","  // 当前状态
//				<< adjust << "\n";   // 推力调节值
//			csv_file.flush();
//		}
//	}
//
//	// 初始化Log文件
//	void init_log_file() {
//		if (!log_file_created) {
//			log_filename = create_log_filename();
//			log_file.open(log_filename, ios::out | ios::trunc);
//			if (!log_file.is_open()) {
//				cerr << "Unable to create log!" << endl;
//				return;
//			}
//			log_file << "Engine Alarm Log" << endl;
//			log_file << "Time(s), Alarm Level, Alarm Description" << endl;
//			log_file_created = true;
//		}
//	}
//
//	// 写入告警到Log文件
//	void write_alarm_to_log(ErrorType type, AlarmLevel level, const string& desc) {
//		init_log_file();
//		// 检查5秒内是否重复触发
//		auto it = last_error_time.find(type);
//		if (it != last_error_time.end() && (t - it->second) < 5.0) {
//			return;
//		}
//		// 记录本次触发时间
//		last_error_time[type] = t;
//		// 写入Log
//		string level_str;
//		if (level == LEVEL_WHITE) level_str = "WHITE";
//		else if (level == LEVEL_AMBER) level_str = "AMBER";
//		else if (level == LEVEL_RED) level_str = "RED";
//		else level_str = "INVALID";
//
//		log_file << fixed << setprecision(3)
//			<< t << ", "
//			<< level_str << ", "
//			<< desc << endl;
//		log_file.flush();
//		// 更新当前告警列表（供EasyX绘制）
//		AlarmInfo alarm{ type, level, desc, t, true };
//		for (vector<AlarmInfo>::iterator iter = current_alarms.begin(); iter != current_alarms.end();) {
//			if (iter->type == type) 
//			{
//				iter = current_alarms.erase(iter);
//			}
//			else {
//				iter++;
//			}
//		}
//		current_alarms.push_back(alarm);
//		// 红色告警触发停车
//		if (level == LEVEL_RED) {
//			order = OSTOP;
//		}
//	}
//
//	// 异常检测
//	void detect_errors() {
//		// 清空已失效的告警
//		for (vector<AlarmInfo>::iterator iter = current_alarms.begin(); iter != current_alarms.end();) {
//			if (t - iter->trigger_time > 5.0) {
//				iter = current_alarms.erase(iter);
//			}
//			else {
//				iter++;
//			}
//		}
//		int n_l_sensor_invalid = (N_sensor_l1_invalid ? 1 : 0) + (N_sensor_l2_invalid ? 1 : 0);
//		int n_r_sensor_invalid = (N_sensor_r1_invalid ? 1 : 0) + (N_sensor_r2_invalid ? 1 : 0);
//		int egt_l_sensor_invalid = (EGT_sensor_l1_invalid ? 1 : 0) + (EGT_sensor_l2_invalid ? 1 : 0);
//		int egt_r_sensor_invalid = (EGT_sensor_r1_invalid ? 1 : 0) + (EGT_sensor_r2_invalid ? 1 : 0);
//		// 1. 单个转速传感器故障（白色）
//		if (n_l_sensor_invalid == 1 || n_r_sensor_invalid == 1) {
//			write_alarm_to_log(ERR_N_SENSOR_SINGLE, LEVEL_WHITE, "Single engine speed sensor fault (invalid value)");
//		}
//		// 2. 单发转速传感器故障（琥珀色）
//		if (n_l_sensor_invalid == 2 || n_r_sensor_invalid == 2) {
//			write_alarm_to_log(ERR_N_SENSOR_SINGLE_ENG, LEVEL_AMBER, "Single engine speed sensor fault (engine alarm)");
//		}
//		// 3. 单个EGT传感器故障（白色）
//		if (egt_l_sensor_invalid == 1 || egt_r_sensor_invalid == 1) {
//			write_alarm_to_log(ERR_EGT_SENSOR_SINGLE, LEVEL_WHITE, "Single EGT sensor fault (invalid value)");
//		}
//		// 4. 单发EGT传感器故障（琥珀色）
//		if (egt_l_sensor_invalid == 2 || egt_r_sensor_invalid == 2) {
//			write_alarm_to_log(ERR_EGT_SENSOR_SINGLE_ENG, LEVEL_AMBER, "Single engine EGT sensor fault (engine alarm)");
//		}
//		// 5. 双发转速/EGT传感器故障（红色）
//		if ((n_l_sensor_invalid == 2 && n_r_sensor_invalid == 2) || (egt_l_sensor_invalid == 2 && egt_r_sensor_invalid == 2)) {
//			write_alarm_to_log(ERR_N_EGT_SENSOR_DUAL, LEVEL_RED, "Dual engine speed/EGT sensor fault (engine shutdown)");
//		}
//		// 6. 燃油余量低于1000（琥珀色，非停车/未启动）
//		if (C < 1000 && s != STOP && t > 0) {
//			write_alarm_to_log(ERR_FUEL_LOW, LEVEL_AMBER, "Low fuel level (below 1000 units)");
//		}
//		// 7. 燃油余量故障（无效值，红色）
//		if (fuel_sensor_invalid) {
//			write_alarm_to_log(ERR_FUEL_SENSOR, LEVEL_RED, "Fuel level sensor fault (invalid value)");
//		}
//		// 8. 燃油流速超过50（琥珀色）
//		if (V > 50.0) {
//			write_alarm_to_log(ERR_FUEL_FLOW_OVER, LEVEL_AMBER, "Fuel flow rate over 50 units per second");
//		}
//		// 9. 超转1（N1>105，琥珀色）
//		if (N_l > 105 || N_r > 105) {
//			write_alarm_to_log(ERR_N_OVER_105, LEVEL_AMBER, "Over speed 1 (N1 > 105%)");
//		}
//		// 10. 超转2（N1>120，红色）
//		if (N_l > 120 || N_r > 120) {
//			write_alarm_to_log(ERR_N_OVER_120, LEVEL_RED, "Over speed 2 (N1 > 120%, engine shutdown)");
//		}
//		// 11. 超温1（启动中T>850，琥珀色）
//		if (s == START && (T_l > 850 || T_r > 850)) {
//			write_alarm_to_log(ERR_T_OVER_850_START, LEVEL_AMBER, "Over temperature 1 (start phase, EGT > 850℃)");
//		}
//		// 12. 超温2（启动中T>1000，红色）
//		if (s == START && (T_l > 1000 || T_r > 1000)) {
//			write_alarm_to_log(ERR_T_OVER_1000_START, LEVEL_RED, "Over temperature 2 (start phase, EGT > 1000℃, engine shutdown)");
//		}
//		// 13. 超温3（稳态T>950，琥珀色）
//		if (s == RUN && (T_l > 950 || T_r > 950)) {
//			write_alarm_to_log(ERR_T_OVER_950_RUN, LEVEL_AMBER, "Over temperature 3 (steady phase, EGT > 950℃)");
//		}
//		// 14. 超温4（稳态T>1100，红色）
//		if (s == RUN && (T_l > 1100 || T_r > 1100)) {
//			write_alarm_to_log(ERR_T_OVER_1100_RUN, LEVEL_RED, "Over temperature 4 (steady phase, EGT > 1100℃, engine shutdown)");
//		}
//	}
//
//	// 角度转弧度
//	double deg_to_rad(double deg) {
//		return deg * 3.1415926 / 180.0;
//	}
//
//	// 绘制扇形，6.283185307179586
//	void draw_pie(int x, int y, double num, double max_num) {
//		COLORREF pie_color;
//		double pie_rad = 6.283185307179586;
//		// 如果是转速扇形
//		if(max_num == 125.0) {
//			if (num <= 105.0) pie_color = COLOR_WHITE;
//			else if (num <= 120.0) pie_color = COLOR_AMBER;
//			else pie_color = COLOR_RED;
//			pie_rad = 6.2831853071 - deg_to_rad(num / 125 * 210.0);
//		}
//		// 如果是温度扇形
//		else if (max_num == 1200.0) {
//			if (s == START) {
//				if (num <= 850.0) pie_color = COLOR_WHITE;
//				else if (num <= 1000.0) pie_color = COLOR_AMBER;
//				else pie_color = COLOR_RED;
//			}
//			else if (s == RUN) {
//				if (num <= 950.0) pie_color = COLOR_WHITE;
//				else if (num <= 1100.0) pie_color = COLOR_AMBER;
//				else pie_color = COLOR_RED;
//			}
//			else {
//				pie_color = COLOR_WHITE;
//			}
//			pie_rad = 6.2831853071 - deg_to_rad(num / 1205 * 210.0);
//		}
//		else {
//			pie_color = COLOR_WHITE;
//		}
//		// 角度为0到210度
//		setfillcolor(pie_color);
//		if (pie_rad < 6.27) {
//			solidpie(x - 90, y - 90, x + 90, y + 90, pie_rad, 6.2831853071);
//		}
//	}
//
//	// 绘制函数
//	void draw() {
//		setbkmode(TRANSPARENT);
//		// 0.显示adjust数值
//		settextcolor(COLOR_WHITE);
//		settextstyle(40, 0, _T("微软雅黑"));
//		TCHAR str_adjust[50];
//		swprintf_s(str_adjust, _countof(str_adjust), _T("%d"), abs(adjust));
//		if (adjust > 0) {
//			outtextxy(880, 90, str_adjust);
//		}
//		else if (adjust < 0) {
//			outtextxy(880, 180, str_adjust);
//		}
//		// 1.显示油量和流速
//		setfillcolor(COLOR_WHITE);
//		settextstyle(72, 0, _T("微软雅黑"));
//		TCHAR str[50];
//		solidrectangle(120, 495, 450, 575); // 油量
//		solidrectangle(120, 600, 450, 680); // 流速
//		swprintf_s(str, _countof(str), _T("C: %.2lf"), C);
//		if(fuel_sensor_invalid)settextcolor(COLOR_RED);
//		else if (C < 1000.0) settextcolor(COLOR_AMBER);
//		else settextcolor(COLOR_BLACK);
//		outtextxy(130, 500, str); // 油量
//		swprintf_s(str, _countof(str), _T("V: %.2lf"), V);
//		if (V > 50.0) settextcolor(COLOR_AMBER);
//		else settextcolor(COLOR_BLACK);
//		outtextxy(130, 605, str); // 流速
//		// 2.显示按钮上面的字
//		solidroundrect(570, 80, 690, 140, 5, 5); // START
//		solidroundrect(570, 170, 690, 230, 5, 5); // STOP
//		settextstyle(40, 0, _T("微软雅黑"));
//		settextcolor(COLOR_LIGHTBLUE);
//		outtextxy(584, 90, _T("START"));
//		outtextxy(591, 180, _T("STOP"));
//		solidroundrect(750, 80, 870, 140, 5, 5); // PULL UP
//		solidroundrect(750, 170, 870, 230, 5, 5); // PUSH DOWN
//		settextcolor(COLOR_DARKGRAY);
//		outtextxy(788, 90, _T("UP"));
//		outtextxy(757, 180, _T("DOWN"));
//		// 3.写当前状态
//		solidroundrect(600, 280, 840, 460, 10, 10);
//		settextstyle(72, 0, _T("微软雅黑"));
//		settextcolor(COLOR_BLACK);
//		if (s==RUN) outtextxy(620, 350, _T("RUN"));
//		else if (s==START) outtextxy(620, 290, _T("START"));
//		// 4.写当前告警，不用画边框
//		int alarm_num = (int)current_alarms.size();
//		const int top_start = 470;
//		const int line_height = 30;
//		if (alarm_num == 0) {
//			settextstyle(24, 0, _T("微软雅黑"));
//			settextcolor(COLOR_GREEN);
//			outtextxy(600, top_start, _T("No Alarms"));
//		}
//		else {
//			settextstyle(24, 0, _T("微软雅黑"));
//			for (int i = 0; i < alarm_num && i < 8; i++) {
//				if(i == 7 && alarm_num > 8) {
//					settextcolor(COLOR_DARKGRAY);
//					outtextxy(600, top_start + i * line_height, _T("..."));
//					break;
//				}
//				TCHAR alarm_str[200];
//				AlarmInfo& alarm = current_alarms[i];
//				string desc = alarm.desc;
//				const char* desc_cstr = desc.c_str();
//				mbstowcs_s(nullptr, alarm_str, desc_cstr, _countof(alarm_str));
//				// 根据告警级别设置颜色
//				if (alarm.level == LEVEL_WHITE) settextcolor(COLOR_BLACK);
//				else if (alarm.level == LEVEL_AMBER) settextcolor(COLOR_AMBER);
//				else if (alarm.level == LEVEL_RED) settextcolor(COLOR_RED);
//				else settextcolor(COLOR_DARKGRAY);
//				outtextxy(500, top_start + i * line_height, alarm_str);
//			}
//		}
//		// 5. 写转速和温度，用无填充矩形作为边框
//		setlinecolor(COLOR_GRAY);
//		settextcolor(COLOR_WHITE);
//		settextstyle(24, 0, _T("微软雅黑"));
//		draw_pie(150, 150, N_l, 125.0); // 左转速
//		rectangle(150, 100, 270, 150);
//		TCHAR str_Nl[50];
//		swprintf_s(str_Nl, _countof(str_Nl), _T("N_L: %.2lf%%"), N_l);
//		outtextxy(160, 112, str_Nl);
//		draw_pie(390, 150, N_r, 125.0); // 右转速
//		rectangle(390, 100, 510, 150);
//		TCHAR str_Nr[50];
//		swprintf_s(str_Nr, _countof(str_Nr), _T("N_R: %.2lf%%"), N_r);
//		outtextxy(400, 112, str_Nr);
//		draw_pie(150, 390, T_l, 1200.0); // 左温度
//		rectangle(150, 340, 270, 390);
//		TCHAR str_Tl[50];
//		swprintf_s(str_Tl, _countof(str_Tl), _T("T_L: %.2lf℃"), T_l);
//		outtextxy(160, 352, str_Tl);
//		draw_pie(390, 390, T_r, 1200.0); // 右温度
//		rectangle(390, 340, 510, 390);
//		TCHAR str_Tr[50];
//		swprintf_s(str_Tr, _countof(str_Tr), _T("T_R: %.2lf℃"), T_r);
//		outtextxy(400, 352, str_Tr);
//		outtextxy(260, 210, _T("N"));
//		outtextxy(260, 450, _T("T"));
//	}
//
//	// 设置按钮指令
//	void handle_mouse_input() {
//		// 获取鼠标消息
//		ExMessage msg;
//		while (peekmessage(&msg, EM_MOUSE)) {
//			if (msg.message == WM_LBUTTONDOWN) {
//				int x = msg.x;
//				int y = msg.y;
//				// START
//				if (x >= 570 && x <= 690 && y >= 80 && y <= 140) {
//					this->order = OSTART;
//				}
//				// STOP
//				else if (x >= 570 && x <= 690 && y >= 170 && y <= 230) {
//					this->order = OSTOP;
//				}
//				// PULL UP
//				else if (x >= 750 && x <= 870 && y >= 80 && y <= 140) {
//					if (adjust < 3) adjust += 1;
//				}
//				// PUSH DOWN
//				else if (x >= 750 && x <= 870 && y >= 170 && y <= 230) {
//					if (adjust > -3) adjust -= 1;
//				}
//			}
//		}
//	}
//
//	// 主更新函数
//	void update(double dt) {
//		update_state();
//		switch (s) {
//		case START:
//			update_s(dt);
//			break;
//		case RUN:
//			update_r(dt);
//			break;
//		case STOP:
//			update_p(dt);
//			break;
//		}
//		save_data();
//		detect_errors();
//	}
//
//public:
//	Plane() {
//			s = STOP;
//			order = OSTOP;
//			changed = false;
//			N_l = 0;
//			N_r = 0;
//			T_l = T0;
//			T_r = T0;
//			C = 20000;
//			V = 0;
//			adjust = 0;
//			last_update_ms = 0;
//			t = 0;
//			t_start = 0;
//			t_stop = 100;
//			N_stop_l = 0;
//			N_stop_r = 0;
//			T_stop_l = T0;
//			T_stop_r = T0;
//			srand((unsigned int)time(NULL)); // 初始化随机数种子
//			csv_file_created = false;
//			csv_filename = "";
//			log_file_created = false;
//			log_filename = "";
//			N_sensor_l1_invalid = false;
//			N_sensor_l2_invalid = false;
//			N_sensor_r1_invalid = false;
//			N_sensor_r2_invalid = false;
//			EGT_sensor_l1_invalid = false;
//			EGT_sensor_l2_invalid = false;
//			EGT_sensor_r1_invalid = false;
//			EGT_sensor_r2_invalid = false;
//			fuel_sensor_invalid = false;
//		}
//
//	~Plane() {
//			if (csv_file.is_open()) csv_file.close();
//			if (log_file.is_open()) log_file.close();
//		}
//
//	// 运行函数
//	void run() {
//		initgraph(960, 720);
//		BeginBatchDraw();
//		uint64_t base_update_ms = GetTickCount64();
//		uint64_t base_draw_ms = GetTickCount64();
//		this->last_update_ms = base_update_ms;
//
//		while (true) {
//			handle_mouse_input();
//			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
//				break;
//			}
//			uint64_t current_ms = GetTickCount64();
//			double real_dt = (current_ms - this->last_update_ms) / 1000.0;
//			real_dt = min(real_dt, 0.01);
//			if (current_ms - base_update_ms >= 5) {
//				update(real_dt); // 传入真实dt
//				base_update_ms = current_ms;
//				this->last_update_ms = current_ms;
//			}
//			if (current_ms - base_draw_ms >= 20) {
//				cleardevice();
//				draw();
//				FlushBatchDraw();
//				base_draw_ms = current_ms;
//			}
//			Sleep(0);
//		}
//
//		EndBatchDraw();
//		closegraph();
//	}
//};