#include<iostream>
#include<utility>  // 用于pair类型
#include<cstdlib>  // 用于system函数
#include<ctime>    // 时间相关（代码中未直接使用，可能是历史遗留）
#include<windows.h> // Windows API，用于控制台操作
#include<limits>    // 用于数值限制
#include"dfs.h"     // AI算法头文件
using namespace std;

// 设置控制台文本颜色
// color参数：1-8分别代表不同的颜色组合
void ColorChoose(int color){
	switch(color){
	case 1:  // 青色（绿+蓝）
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
		break;
	case 2:  // 绿色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
		break;
	case 3:  // 黄色（红+绿）
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
		break;
	case 4:  // 红色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
		break;
	case 5:  // 紫色（红+蓝）
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);
		break;
	case 6:  // 白色（红+绿+蓝）
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		break;
	case 7:  // 蓝色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
		break;
	case 8:  // 灰色（低强度白色）
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		break;
	}
}

// 隐藏控制台光标
void HideCursor(){
	CONSOLE_CURSOR_INFO cursor_info={1,0};  // 第二个参数0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}

// 检查玩家是否获胜
// map: 3x3棋盘，值为0表示空，奇数为玩家1，偶数为玩家2
// player: 当前玩家编号（1或2）
// 返回true如果当前玩家获胜
bool checkWin(int map[3][3],int player){
	int p=player%2;  // 转换为奇偶判断：玩家1为1，玩家2为0
	
	// 检查三行
	for(int i=0;i<3;i++){
		bool win=true;
		for(int j=0;j<3;j++){
			if(map[i][j]==0||map[i][j]%2!=p){  // 有空位或不是当前玩家的棋子
				win=false;
				break;
			}
		}
		if(win)return true;
	}
	
	// 检查三列
	for(int j=0;j<3;j++){
		bool win=true;
		for(int i=0;i<3;i++){
			if(map[i][j]==0||map[i][j]%2!=p){
				win=false;
				break;
			}
		}
		if(win)return true;
	}
	
	// 检查主对角线（左上到右下）
	bool diag1=true;
	for(int d=0;d<3;d++){
		if(map[d][d]==0||map[d][d]%2!=p){
			diag1=false;
			break;
		}
	}
	if(diag1)return true;
	
	// 检查副对角线（右上到左下）
	bool diag2=true;
	for(int d=0;d<3;d++){
		if(map[d][2-d]==0||map[d][2-d]%2!=p){
			diag2=false;
			break;
		}
	}
	if(diag2)return true;
	
	return false;  // 未获胜
}

// 获取即将消失的棋子编号
// step: 当前步数（从1开始）
// 返回-1表示没有棋子消失（前5步）
// 第6步消第1子，第7步消第2子，以此类推
int getDisappearingPiece(int step){
	if(step>=7){
		return step-6;  // 计算要消失的棋子编号
	}
	return -1;  // 前6步没有棋子消失
}

// 打印棋盘
// map: 3x3棋盘
// disappearingPiece: 即将消失的棋子编号，-1表示没有
void printMap(int map[3][3],int disappearingPiece=-1,bool fir=false){
	if(!fir)
		cout<<endl;
	
	// 打印列号
	ColorChoose(3);  // 黄色
	cout<<"   ";
	for(int j=0;j<3;j++){
		cout<<" "<<j+1<<"  ";
	}
	cout<<endl;
	
	// 打印棋盘内容
	for(int i=0;i<3;i++){
		ColorChoose(3);  // 黄色
		cout<<" "<<i+1<<" ";  // 行号
		
		for(int j=0;j<3;j++){
			// 打印列分隔线
			if(j>0){
				ColorChoose(3);
				cout<<"│";
			}
			
			// 根据棋子状态选择颜色和符号
			if(map[i][j]==disappearingPiece){  // 即将消失的棋子
				ColorChoose(5);  // 紫色
				if(map[i][j]%2==1){
					cout<<" X ";
				}else{
					cout<<" O ";
				}
			}
			else if(map[i][j]==0){  // 空位
				ColorChoose(8);  // 灰色
				cout<<" . ";
			}
			else if(map[i][j]%2==1){  // 玩家1（奇数编号）
				ColorChoose(4);  // 红色
				cout<<" X ";
			}
			else{  // 玩家2（偶数编号）
				ColorChoose(1);  // 青色
				cout<<" O ";
			}
		}
		cout<<endl;
		
		// 打印行分隔线（最后一行不打印）
		if(i<2){
			ColorChoose(3);
			cout<<"   ";
			for(int j=0;j<3;j++){
				if(j>0)cout<<"┼";
				cout<<"───";
			}
			cout<<endl;
		}
	}
	ColorChoose(6);  // 白色
	cout<<endl;
}

// 根据棋子编号在棋盘中查找位置
// map: 3x3棋盘
// k: 要查找的棋子编号
// 返回位置坐标对，如果未找到返回(-1,-1)
pair<int,int>findPosByNum(int map[3][3],int k){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(map[i][j]==k)
				return make_pair(i,j);
		}
	}
	return make_pair(-1,-1);
}

// 设置游戏选项
// a: 是否玩家先手（引用参数）
// b: 是否人机都参与（引用参数）
void setBool(bool&a,bool&b){
	int temp;
	// 设置游戏选项
	while(true){
		ColorChoose(2);  // 绿色
		cout << "请选择游戏方式：1.双人对弈2.人机对弈（你先手）3.人机对弈（AI先手）4.两个AI对弈" << endl; 
		ColorChoose(6);  // 白色
		cin>>temp;
		if(cin.fail()||(temp<1||temp>4)){
			ColorChoose(4);  // 红色
			cout<<"输入无效！请输入1到4之间的整数。"<<endl;
			ColorChoose(6);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
		}else{
			switch(temp){
				case 1:{
					a = true;
					b = false;
					break;
				}
				case 2:{
					a = true;
					b = true;
					break;
				} 
				case 3:{
					a = false;
					b = true;
					break;
				}
				case 4:{
					a = false;
					b = false;
					break;
				}
			}
			break;
		}
	}
}

void setDiff(){
	int temp;
	// 设置游戏选项
	while(true){
		ColorChoose(2);  // 绿色
		cout << "请选择游戏难度（AI强度）：1.简单2.中等3.困难4.王者" << endl; 
		ColorChoose(6);  // 白色
		cin>>temp;
		if(cin.fail()||(temp<1||temp>4)){
			ColorChoose(4);  // 红色
			cout<<"输入无效！请输入1到4之间的整数。"<<endl;
			ColorChoose(6);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
		}else{
			switch(temp){
				case 1:{
					set_diff(1); 
					break;
				}
				case 2:{
					set_diff(4);
					break;
				} 
				case 3:{
					set_diff(8);
					break;
				}
				case 4:{
					set_diff(16);
					break;
				}
			}
			break;
		}
	}
}

// 打印主菜单
void printMenu(){
	system("cls");  // 清屏
	ColorChoose(5);  // 紫色
	cout<<"╔══════════════════════════════════════╗\n";
	cout<<"║             井字棋Plus               ║\n";
	cout<<"╠══════════════════════════════════════╣\n";
	cout<<"║                                      ║\n";
	cout<<"║          ";
	ColorChoose(2);  // 绿色
	cout<<"1. 开始游戏";
	ColorChoose(5);
	cout<<"                 ║\n";
	cout<<"║                                      ║\n";
	cout<<"║          ";
	ColorChoose(3);  // 黄色
	cout<<"2. 游戏规则";
	ColorChoose(5);
	cout<<"                 ║\n";
	cout<<"║                                      ║\n";
	cout<<"║          ";
	ColorChoose(4);  // 红色
	cout<<"3. 退出游戏";
	ColorChoose(5);
	cout<<"                 ║\n";
	cout<<"║                                      ║\n";
	cout<<"╚══════════════════════════════════════╝\n";
	
	ColorChoose(6);  // 白色
}

// 打印游戏规则
void printRules(){
	system("cls");
	
	ColorChoose(5);
	cout<<"╔══════════════════════════════════════╗\n";
	cout<<"║               游戏规则               ║\n";
	cout<<"╠══════════════════════════════════════╣\n";
	cout<<"║                                      ║\n";
	cout<<"║  ";
	ColorChoose(2);
	cout<<"基本规则：";
	ColorChoose(5);
	cout<<"                          ║\n";
	cout<<"║  ";
	ColorChoose(2);
	cout<<"1. 两个玩家轮流在3x3棋盘上下子";
	ColorChoose(5);
	cout<<"      ║\n";
	cout<<"║  ";
	ColorChoose(2);
	cout<<"2. 先连成一条长度为3直线（横、竖";
	ColorChoose(5);
	cout<<"    ║\n";
	cout<<"║     ";
	ColorChoose(2);
	cout<<"、斜）的玩家获胜";
	ColorChoose(5);
	cout<<"                 ║\n";
	cout<<"║                                      ║\n";
	cout<<"║  ";
	ColorChoose(3);
	cout<<"特殊规则（井字棋Plus）：";
	ColorChoose(5);
	cout<<"            ║\n";
	cout<<"║  ";
	ColorChoose(3);
	cout<<"1. 第6子落下后 → 消第1子";
	ColorChoose(5);
	cout<<"            ║\n";
	cout<<"║  ";
	ColorChoose(3);
	cout<<"2. 第7子落下后 → 消第2子";
	ColorChoose(5);
	cout<<"            ║\n";
	cout<<"║  ";
	ColorChoose(3);
	cout<<"3. 第8子落下后 → 消第3子";
	ColorChoose(5);
	cout<<"            ║\n";
	cout<<"║  ";
	ColorChoose(3);
	cout<<"4. 以此类推，循环消失";
	ColorChoose(5);
	cout<<"               ║\n";
	cout<<"║                                      ║\n";
	cout<<"║  ";
	ColorChoose(4);
	cout<<"棋子颜色说明：";
	ColorChoose(5);
	cout<<"                      ║\n";
	cout<<"║  ";
	ColorChoose(4);
	cout<<"红色X = 先手";
	ColorChoose(5);
	cout<<"                        ║\n";
	cout<<"║  ";
	ColorChoose(4);
	cout<<"天蓝色O = 后手";
	ColorChoose(5);
	cout<<"                      ║\n";
	cout<<"║  ";
	ColorChoose(4);
	cout<<"紫色棋子 = 即将消失的棋子";
	ColorChoose(5);
	cout<<"           ║\n";
	cout<<"║                                      ║\n";
	cout<<"╚══════════════════════════════════════╝\n\n";
	
	ColorChoose(6);
	system("pause");
}

// 开始游戏主函数
void startGame(){
	system("cls");
	
	int map[3][3]={0};  // 初始化棋盘，0表示空
	int step=1;         // 当前步数，从1开始
	bool humanTurn=true; // 是否轮到玩家
	bool use_ai=true;    // 是否使用AI
	
	// 打印游戏标题
	ColorChoose(5);
	cout<<"╔════════════════════════════╗\n";
	cout<<"║         井字棋Plus         ║\n";
	cout<<"╚════════════════════════════╝\n\n";
	
	// 打印规则说明
	ColorChoose(6);
	cout<<"规则：\n";
	ColorChoose(2);
	cout<<"第6子落下后→消第1子，第7子不能下在第1子原位置\n";
	cout<<"第7子落下后→消第2子，第8子不能下在第2子原位置\n";
	cout<<"第8子落下后→消第3子，第9子不能下在第3子原位置\n";
	cout<<"以此类推，循环消失\n\n";
	
	// 打印棋子颜色说明
	ColorChoose(5);
	cout<<"说明：紫色棋子表示将在下一回合消失\n\n";
	
	ColorChoose(4);
	cout<<"X=先手";
	ColorChoose(6);
	cout<<"，";
	ColorChoose(1);
	cout<<"O=后手\n\n";
	ColorChoose(6);
	
	// 获取游戏设置
	setBool(humanTurn,use_ai);
	if(use_ai || !humanTurn)
		setDiff(); 
	system("cls");
	// 游戏主循环
	while(true){
		int disappearingPiece=getDisappearingPiece(step);  // 获取即将消失的棋子
		printMap(map,disappearingPiece,true);  // 打印棋盘
		
		// 处理棋子消失逻辑
		int ban_x=-1,ban_y=-1;  // 禁止下子的位置（刚消失的位置）
		if(step>=7){
			int del_num=step-6;  // 要删除的棋子编号
			pair<int,int>p_del=findPosByNum(map,del_num);
			ban_x=p_del.first;
			ban_y=p_del.second;
			
			if(ban_x!=-1&&ban_y!=-1){
				map[ban_x][ban_y]=0;  // 移除棋子
			}
		}
		
		// 检查玩家1是否获胜
		if(checkWin(map,1)){
			ColorChoose(4);  // 红色
			cout<<"\n╔════════════════════════════╗\n";
			cout<<"║         先手赢了！         ║\n";
			cout<<"╚════════════════════════════╝\n";
			ColorChoose(6);
			system("pause");
			break;
		}
		
		// 检查玩家2（AI）是否获胜
		if(checkWin(map,2)){
			ColorChoose(1);  // 青色
			cout<<"\n╔════════════════════════════╗\n";
			cout<<"║         后手赢了！         ║\n";
			cout<<"╚════════════════════════════╝\n";
			ColorChoose(6);
			system("pause");
			break;
		}
		
		// 检查是否平局
		bool full=true;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				if(map[i][j]==0)full=false;
		
		if(full){
			ColorChoose(3);  // 黄色
			cout<<"\n╔════════════════════════════╗\n";
			cout<<"║            平局！          ║\n";
			cout<<"╚════════════════════════════╝\n";
			cout<<"翻代码的人呐，你在想些啥？";  //这里没有彩蛋！
			ColorChoose(6);
			system("pause");
			break;
		}
		
		if(ban_x!=-1&&ban_y!=-1){
			if(humanTurn){
				ColorChoose(3);
				cout<<"第"<<step-6<<"子已消失，位置("<<ban_x+1<<","<<ban_y+1<<")本回合不能下。"<<endl;
				ColorChoose(6);
			}
		}
		
		// 恢复被暂时移除的棋子（为了显示效果）
		if(ban_x!=-1)
			map[ban_x][ban_y]=step-6;
		
		// 玩家回合
		if(humanTurn){
			int x,y;
			while(true){
				ColorChoose(2);
				cout<<"请输入行和列（1-3，用空格分隔）：";
				ColorChoose(6);
				cin>>x>>y;
				
				// 输入验证
				if(cin.fail()){
					ColorChoose(4);
					cout<<"输入无效！请重新输入。"<<endl;
					ColorChoose(6);
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
					continue;
				}
				
				x--;y--;  // 转换为0-based索引
				
				// 检查是否为禁止位置
				bool isBan=false;
				if(step>=7){
					isBan=(x==ban_x&&y==ban_y);
				}
				
				// 位置有效性检查
				if(x<0||x>2||y<0||y>2||map[x][y]!=0||isBan){
					if(isBan){
						ColorChoose(4);
						cout<<"本回合不能下在消失棋子的原位置！重新输入。"<<endl;
					}
					else{
						ColorChoose(4);
						cout<<"位置非法或已被占用，重新输入。"<<endl;
					}
					ColorChoose(6);
				}else{
					break;
				}
			}
			map[x][y]=step;  // 放置棋子
		}
		// AI回合
		else{
			ColorChoose(7);  // 蓝色
			cout<<"AI思考中";
			// 模拟AI思考的动画效果
			for(int i=0;i<3;i++){
				cout<<".";
				cout.flush();
				Sleep(300);
			}
			cout<<endl;
			ColorChoose(6);
			
			// 获取AI选择的落子位置
			pair<int,int>p;
			while(true){
				p=find(map);  // 调用AI算法（在dfs.h中定义）
				int x=p.first;
				int y=p.second;
				
				// 确保AI不下在禁止位置
				bool isBan=false;
				if(step>=7){
					isBan=(x==ban_x&&y==ban_y);
				}
				if(!isBan)break;  // 找到合法位置
			}
			
			int x=p.first;
			int y=p.second;
			map[x][y]=step;  // AI落子
			
			ColorChoose(1);
			cout<<"AI下在("<<x+1<<","<<y+1<<")"<<endl;
			ColorChoose(6);
		}
		
		// 真正移除即将消失的棋子
		map[ban_x][ban_y]=0;
		step++;  // 步数增加
		
		// 如果使用AI，切换回合
		if(use_ai)
			humanTurn=!humanTurn;
		if(humanTurn && use_ai || !use_ai && !humanTurn){
			int disappearingPiece2=getDisappearingPiece(step);  // 获取即将消失的棋子
			printMap(map,disappearingPiece2);  // 打印棋盘
			system("pause");
		} 
		system("cls");
	} 
}

// 主函数
int main(){
	SetConsoleTitle("“智弈”升级版井字棋 - 休闲小游戏的新选择");  // 设置控制台窗口标题
	HideCursor();  // 隐藏光标
	
	// 主循环
	while(true){
		printMenu();  // 显示菜单
		int choice;
		ColorChoose(2);
		cout<<"请选择(1-3)：";
		ColorChoose(6);
		cin>>choice;
		
		// 输入验证
		if(cin.fail()){
			ColorChoose(4);
			cout<<"输入无效！请重新选择。"<<endl;
			ColorChoose(6);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			Sleep(1000);
			continue;
		}
		
		// 处理用户选择
		switch(choice){
		case 1:
			startGame();  // 开始游戏
			break;
		case 2:
			printRules();  // 显示规则
			break;
		case 3:
			ColorChoose(4);
			cout<<"\n感谢游玩，再见！\n\n";
			ColorChoose(6);
			system("pause");
			ExitProcess(0);  // 退出程序
		default:
			ColorChoose(4);
			cout<<"无效选择！请输入1-3之间的数字。"<<endl;
			ColorChoose(6);
			Sleep(1000);
		}
	}
	return 0;
}
