#include"head.h"

//在我知道报告不用写之前我已经把报告写好了，所以我一起打包发送了

void wait_for_enter()
{
    cout << endl;
    cout << "按回车键继续";
    while (_getch() != '\r');
    cout << endl;
}

int main()
{
    wait_for_enter();
    string filename1 = "snowball.jpg";
    string filename2 = "polyhedrosis.jpg";
    string filename3 = "ship.jpg";
    string filename4 = "brain.jpg";

    while (true) // 注意该循环退出的条件
    {
        system("cls");
        menu();
		char ch;
        int choice;

        cout << "请输入选择项：";
        cin >> choice;
        if (cin.fail()) {
			cout << "输入错误！" << endl;
			cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			wait_for_enter();
			continue;
        }

        switch (choice)
        {
        case 0:
            cout << "\n确定退出吗?" << endl;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
                return 0;
            else
                cout << "输入错误！" << endl;
            break;
        case 1:
            matriplus();
            break;
        case 2:
            nummulti();
            break;
        case 3:
            matritrans();
            break;
        case 4:
            matrimulti();
            break;
        case 5:
            hadamulti();
            break;
        case 6:
            conv();
            break;
        case 7:
            demo();
            break;
		case 8:
            OTSU();
			break;
		case 9:
			system("cls");
            char choice9;
			cout << "********************************************************" << endl;
			cout << "*                      请选择图片                      *" << endl;
            cout << "*  1.实验室前任团宠--雪球          2.多角星形          *" << endl;
            cout << "*  3.船舰                          4.脑部影像截取      *" << endl;
            cout << "*  5.隐藏惊喜                                          *" << endl;
			cout << "********************************************************" << endl;
            cout << "请输入序号：";
            cin >> choice9;
            switch (choice9)
            {
            case'1':
				extract(filename1, 7);
				break;
			case'2':
				extract(filename2, 5);
				break;
			case'3':
				extract(filename3, 5);
				break;
			case'4':
				extract(filename4, 13);
				break;
			case'5':
				extract("extra.jpg", 3);
				break;
			default:
				cout << "请输入正确的数字！" << endl;
				break;
            }
			break;
        default:
            cout << "输入错误！" << endl;
            break;
        }
        wait_for_enter();
    }

	return 0;
}