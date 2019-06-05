/*
 * VIMS系统实现
 *
 * @author Afeng
 * @date 2019/04/16
 */

#include <fstream>
#include <cassert>
#include "vims.h"
using namespace vims;

VIMS::VIMS() :tree(new RBTree<Data>()),
option(""), id(""), message("检索"), data(), node()
{
	system("title VIMS");
	system("mode con cols=100 lines=36");
	system("color F1");

	Sleep(800);
	setxy(20, 14);
	cout << "    *       *     * * *        *     *           * * *     " << endl;
	Sleep(800);
	setxy(20, 15);
	cout << "     *     *        *         * *   * *        *           " << endl;
	Sleep(800);
	setxy(20, 16);
	cout << "      *   *         *        *   * *   *        * * *      " << endl;
	Sleep(800);
	setxy(20, 17);
	cout << "       * *          *       *     *     *             *    " << endl;
	Sleep(500);
	setxy(20, 18);
	cout << "        *         * * *    *             *     * * * *     " << endl;

	Sleep(1500);
	system("cls");
	setxy(35, 14);
	cout << "+----------------------------------+" << endl;
	setxy(35, 15);
	cout << "|     欢迎使用视频信息管理系统     |";
	setxy(35, 16);
	cout << "+----------------------------------+" << endl;
	setxy(42, 20);
	cout << "VIMS系统加载中";
	for (int i = 0; i < 6; ++i)
	{
		Sleep(500);
		cout << "*";
	}
}

/*
 * 设置光标位置
 *
 * 参数说明:
 *		x(short)/y(short):  光标坐标
 */
void VIMS::setxy(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*
 * 从数据源获取信息，并存入红黑树中
 */
void VIMS::loadData()
{
	loadData(tree);
}

void VIMS::loadData(RBTree<Data>* tree)
{
	ifstream infile("./data.txt");
	assert(infile.is_open());
	
	getline(infile, id);
	while (!infile.eof())
	{
		infile >> data;
		tree->insert(data);
	}
	infile.close();
}


/*
 * 将数据从红黑树存储至文本文件中
 */
void VIMS::saveData()
{
	saveData(tree);
}

void VIMS::saveData(RBTree<Data>* tree)
{
	ofstream outfile("./data.txt", ios::trunc);
	assert(outfile.is_open());

	tree->saveAllNode(outfile);
	outfile.close();
}

/*
 * 显示菜单，并获取用户操作选项
 */
void VIMS::showMenu()
{
	system("cls");
	setxy(28, 2);
	cout << "+----------------------------------------------+" << endl;
	setxy(28, 3);
	cout << "|++++**************************************++++|" << endl;
	setxy(28, 4);
	cout << "|++++**************************************++++|" << endl;
	setxy(28, 5);
	cout << "|||||                菜单                  |||||" << endl;
	setxy(28, 6);
	cout << "|++++**************************************++++|" << endl;
	setxy(28, 7);
	cout << "|++++**************************************++++|" << endl;
	setxy(28, 8);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 9);
	cout << "|   |           1.视频信息搜索             |   |" << endl;
	setxy(28, 10);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 11);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 12);
	cout << "|   |           2.视频信息添加             |   |" << endl;
	setxy(28, 13);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 14);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 15);
	cout << "|   |           3.视频信息修改             |   |" << endl;
	setxy(28, 16);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 17);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 18);
	cout << "|   |           4.视频信息删除             |   |" << endl;
	setxy(28, 19);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 20);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 21);
	cout << "|   |           5.视频信息相关             |   |" << endl;
	setxy(28, 22);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 23);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 24);
	cout << "|   |           6.退出系统                 |   |" << endl;
	setxy(28, 25);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 26);
	cout << "+----------------------------------------------+" << endl;
	getOption();
}

/*
 * 判断菜单用户操作(option)合法性
 */
bool VIMS::option_legal()
{
	return (!option.empty()) &&
		atoi(option.c_str()) >= 1 && atoi(option.c_str()) <= 6;
}

/*
 * 判断输入视频ID(id)是否合法
 */
bool VIMS::id_legal()
{
	for (char c : id)
		if (c<'0' || c>'9')
			return false;
	return true;
}

/*
 *  响应用户操作
 *
 * 1.视频信息搜索
 * 2.视频信息添加
 * 3.视频信息修改
 * 4.视频信息删除
 * 5.视频信息相关
 * 6.退出系统
 */
void VIMS::getResponse()
{
	switch (atoi(option.c_str()))
	{
	case 1:
		searchID();
		break;
	case 2:
		appendID();
		break;
	case 3:
		alterID();
		break;
	case 4:
		deleteID();
		break;
	case 5:
		aboutAll();
		break;
	case 6:
		system("cls");
		setxy(40, 16);
		cout << "！！！系统退出！！！" << endl;
		saveData();
		getchar();
		exit(0);
		break;
	}
}

/*
 * 获取用户操作并存入option(string)中
 */
void VIMS::getOption()
{
	setxy(24, 28);
	cout << "请输入操作: ";
	cin >> option;
	cin.ignore(1024, '\n');//清除输入缓冲区的当前行 
	while (!option_legal())
	{
		cout << "输入有误！！！" << endl;
		cin.clear();
		cin.sync();
		cout << "\n#请重新输入操作: ";
		cin >> option;
		cin.ignore(1024, '\n');
	}
}

/*
 * 获取用户需要操作的ID
 * 并创建相应Data对象供操作使用
 */
void VIMS::getID()
{
	system("cls");
	cout << "#################视频" + message + "操作#################" << endl;
	message = "检索";
	cout << "请输入该视频ID: ";
	cin >> id;
	cin.ignore(1024, '\n');//清除输入缓冲区的当前行 
	while (!id_legal())
	{
		cout << "输入有误！！！" << endl;
		cin.clear();
		cin.sync();
		cout << "\n#请重新输入该视频ID: ";
		cin >> id;
		cin.ignore(1024, '\n');
	}
	data = Data(id);
}

/*
 * 根据ID检索红黑树
 * 在存在的前提下输出该条信息
 */
bool VIMS::searchID()
{
	getID();
	node = tree->search(data);
	if (node)
	{
		data = node->key;
		cout << "###########已检索到ID:" << string(data) << "###########" << endl;
		cout << data;
		return true;
	}
	else
	{
		cout << "###########未检索到ID:" << string(data) << "###########" << endl;
		return false;
	}
}

/*
 * 在不存在该ID的前提下
 * 添加视频信息
 */
void VIMS::appendID()
{
	message = "添加";
	if (searchID())
		cout << "#视频(ID:" << string(data) << ")已存在！"
			<< "无法重复添加！！！"<< endl;
	else
	{
		cout << "未检索到相同ID的视频信息，可放心添加！" << endl;
		if (cin >> data)
		{
			tree->insert(data);
			cout << data;
			cout << "###########视频信息添加成功###########" << endl;
		}
			
	}
}

/*
 * 在检索到该ID的前提下
 * 对该视频信息进行修改
 */
void VIMS::alterID()
{
	message = "修改";
	if (searchID())
	{
		cout << "进行修改中...\n" << endl;
		tree->remove(data);
		if (cin >> data)
		{
			tree->insert(data);
			cout << "###########已修改该视频信息###########" << endl;
		}
	}
	else
		cout << "#无法修改不存在的视频信息" << endl;
}

/*
 * 在检索到该ID的前提下
 * 删除该视频信息
 */
void VIMS::deleteID()
{
	message = "删除";
	if (searchID())
	{
		cout << "###########已删除该视频信息###########" << endl;
		tree->remove(data);
	}
	else
	{
		cout << "#无法删除不存在的视频信息" << endl;
	}
}

/*
 * 按升序输出视频信息
 * 并打印部分相关信息
 */
void VIMS::aboutAll()
{
	tree->inOrder();
	cout << "\n#################################" << endl;
	cout << "        共" << tree->getLength() << "条视频信息" << endl;
	cout << "#################################" << endl;
}
