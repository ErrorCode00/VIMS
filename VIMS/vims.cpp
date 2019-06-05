/*
 * VIMSϵͳʵ��
 *
 * @author Afeng
 * @date 2019/04/16
 */

#include <fstream>
#include <cassert>
#include "vims.h"
using namespace vims;

VIMS::VIMS() :tree(new RBTree<Data>()),
option(""), id(""), message("����"), data(), node()
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
	cout << "|     ��ӭʹ����Ƶ��Ϣ����ϵͳ     |";
	setxy(35, 16);
	cout << "+----------------------------------+" << endl;
	setxy(42, 20);
	cout << "VIMSϵͳ������";
	for (int i = 0; i < 6; ++i)
	{
		Sleep(500);
		cout << "*";
	}
}

/*
 * ���ù��λ��
 *
 * ����˵��:
 *		x(short)/y(short):  �������
 */
void VIMS::setxy(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*
 * ������Դ��ȡ��Ϣ��������������
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
 * �����ݴӺ�����洢���ı��ļ���
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
 * ��ʾ�˵�������ȡ�û�����ѡ��
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
	cout << "|||||                �˵�                  |||||" << endl;
	setxy(28, 6);
	cout << "|++++**************************************++++|" << endl;
	setxy(28, 7);
	cout << "|++++**************************************++++|" << endl;
	setxy(28, 8);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 9);
	cout << "|   |           1.��Ƶ��Ϣ����             |   |" << endl;
	setxy(28, 10);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 11);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 12);
	cout << "|   |           2.��Ƶ��Ϣ���             |   |" << endl;
	setxy(28, 13);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 14);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 15);
	cout << "|   |           3.��Ƶ��Ϣ�޸�             |   |" << endl;
	setxy(28, 16);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 17);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 18);
	cout << "|   |           4.��Ƶ��Ϣɾ��             |   |" << endl;
	setxy(28, 19);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 20);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 21);
	cout << "|   |           5.��Ƶ��Ϣ���             |   |" << endl;
	setxy(28, 22);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 23);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 24);
	cout << "|   |           6.�˳�ϵͳ                 |   |" << endl;
	setxy(28, 25);
	cout << "|   +--------------------------------------+   |" << endl;
	setxy(28, 26);
	cout << "+----------------------------------------------+" << endl;
	getOption();
}

/*
 * �жϲ˵��û�����(option)�Ϸ���
 */
bool VIMS::option_legal()
{
	return (!option.empty()) &&
		atoi(option.c_str()) >= 1 && atoi(option.c_str()) <= 6;
}

/*
 * �ж�������ƵID(id)�Ƿ�Ϸ�
 */
bool VIMS::id_legal()
{
	for (char c : id)
		if (c<'0' || c>'9')
			return false;
	return true;
}

/*
 *  ��Ӧ�û�����
 *
 * 1.��Ƶ��Ϣ����
 * 2.��Ƶ��Ϣ���
 * 3.��Ƶ��Ϣ�޸�
 * 4.��Ƶ��Ϣɾ��
 * 5.��Ƶ��Ϣ���
 * 6.�˳�ϵͳ
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
		cout << "������ϵͳ�˳�������" << endl;
		saveData();
		getchar();
		exit(0);
		break;
	}
}

/*
 * ��ȡ�û�����������option(string)��
 */
void VIMS::getOption()
{
	setxy(24, 28);
	cout << "���������: ";
	cin >> option;
	cin.ignore(1024, '\n');//������뻺�����ĵ�ǰ�� 
	while (!option_legal())
	{
		cout << "�������󣡣���" << endl;
		cin.clear();
		cin.sync();
		cout << "\n#�������������: ";
		cin >> option;
		cin.ignore(1024, '\n');
	}
}

/*
 * ��ȡ�û���Ҫ������ID
 * ��������ӦData���󹩲���ʹ��
 */
void VIMS::getID()
{
	system("cls");
	cout << "#################��Ƶ" + message + "����#################" << endl;
	message = "����";
	cout << "���������ƵID: ";
	cin >> id;
	cin.ignore(1024, '\n');//������뻺�����ĵ�ǰ�� 
	while (!id_legal())
	{
		cout << "�������󣡣���" << endl;
		cin.clear();
		cin.sync();
		cout << "\n#�������������ƵID: ";
		cin >> id;
		cin.ignore(1024, '\n');
	}
	data = Data(id);
}

/*
 * ����ID���������
 * �ڴ��ڵ�ǰ�������������Ϣ
 */
bool VIMS::searchID()
{
	getID();
	node = tree->search(data);
	if (node)
	{
		data = node->key;
		cout << "###########�Ѽ�����ID:" << string(data) << "###########" << endl;
		cout << data;
		return true;
	}
	else
	{
		cout << "###########δ������ID:" << string(data) << "###########" << endl;
		return false;
	}
}

/*
 * �ڲ����ڸ�ID��ǰ����
 * �����Ƶ��Ϣ
 */
void VIMS::appendID()
{
	message = "���";
	if (searchID())
		cout << "#��Ƶ(ID:" << string(data) << ")�Ѵ��ڣ�"
			<< "�޷��ظ���ӣ�����"<< endl;
	else
	{
		cout << "δ��������ͬID����Ƶ��Ϣ���ɷ�����ӣ�" << endl;
		if (cin >> data)
		{
			tree->insert(data);
			cout << data;
			cout << "###########��Ƶ��Ϣ��ӳɹ�###########" << endl;
		}
			
	}
}

/*
 * �ڼ�������ID��ǰ����
 * �Ը���Ƶ��Ϣ�����޸�
 */
void VIMS::alterID()
{
	message = "�޸�";
	if (searchID())
	{
		cout << "�����޸���...\n" << endl;
		tree->remove(data);
		if (cin >> data)
		{
			tree->insert(data);
			cout << "###########���޸ĸ���Ƶ��Ϣ###########" << endl;
		}
	}
	else
		cout << "#�޷��޸Ĳ����ڵ���Ƶ��Ϣ" << endl;
}

/*
 * �ڼ�������ID��ǰ����
 * ɾ������Ƶ��Ϣ
 */
void VIMS::deleteID()
{
	message = "ɾ��";
	if (searchID())
	{
		cout << "###########��ɾ������Ƶ��Ϣ###########" << endl;
		tree->remove(data);
	}
	else
	{
		cout << "#�޷�ɾ�������ڵ���Ƶ��Ϣ" << endl;
	}
}

/*
 * �����������Ƶ��Ϣ
 * ����ӡ���������Ϣ
 */
void VIMS::aboutAll()
{
	tree->inOrder();
	cout << "\n#################################" << endl;
	cout << "        ��" << tree->getLength() << "����Ƶ��Ϣ" << endl;
	cout << "#################################" << endl;
}
