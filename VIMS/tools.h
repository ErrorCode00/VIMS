/*
 * VIMSϵͳ����
 *
 * @author Afeng
 * @date 2019/04/16
 */

#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <istream>
#include <string>
namespace tools {
	using namespace std;

	/*
	 * Data������
	 *
	 * ��˵��:
	 *		��Data���е����ݲ������и��Ի�����
	 */
	class DataManager
	{
	public:
		/*
		 * ���캯��
		 */
		DataManager() : c(' ') {}

		/****************************/
		/*		Data���߹�����	*/
		/****************************/
		/*
		 * ��ȡ�û���Ӧ���룬�����д洢
		 */
		void get_input(string message, istream& is, string& where)
		{
			cout << endl << "������" + message + ": ";
			is >> where;
			while (be_sure(message + ": " + where))
			{
				cout << "#����������" + message + ": ";
				is >> where;
			}
		}

		/*
		 * ȷ������Ϣ����
		 *
		 * ����˵��:
		 *		message(string): �����Ϣ
		 */
		bool be_sure(const string message)
		{
			cout << endl << "?�Ƿ�ȷ��" << message << " (y/n)?  ";
			cin >> c;
			cin.ignore(1024, '\n');
			if (c == 'n' || c == 'N')
				return true;
			else
				return false;
		}
	private:
		char c;		// �洢�û�ȷ��ʱ�����ַ�
	};

	/*
	 *	 Data��: ���ڴ洢ÿ����Ϣ����
	 *
	 * ����˵��:
	 *		 avId: ��ƵID
	 *		title: ��Ƶ����
	 *		about: ��Ƶ����
	 *		 view: ������
	 *		 like: ������
	 *		 coin: Ͷ����
	 *		share: ������
	 */
	class Data {
	public:
		Data() :avId(""), title(""), about(""),
			view(0), like(0), coin(0), share(0) {}
		Data(string avId) :avId(avId), title(""), about(""),
			view(0), like(0), coin(0), share(0) {}

		/****************************/
		/*	  Data��������ز���	*/
		/****************************/
		operator string() { return avId; }
		bool operator< (Data data) const { return (atoi(avId.c_str()) < atoi(data.avId.c_str())); }
		bool operator== (Data data) const { return (avId == data.avId); }
		bool operator!= (Data data) const { return !operator==(data); }
		friend istream& operator>> (istream& is, Data& data)
		{
			while (data.manager.be_sure("��ƵID " + data.avId))
			{
				cout << "#������������ƵID: ";
				is >> data.avId;
			}
			data.manager.get_input("��Ƶ����", is, data.title);
			data.manager.get_input("��Ƶ����", is, data.about);
			do
			{
				cout << endl << "�����벥��������������Ӳ������������: \n\t";
				is >> data.view >> data.like
					>> data.coin >> data.share;
			} while (data.manager.be_sure("����������������Ӳ������������"));
			return is;
		}
		friend ostream& operator<< (ostream&os, Data& data)
		{
			cout << "\n#####################################" << endl;
			cout << "��ƵID: " << data.avId << endl;
			cout << "��Ƶ����: " << data.title << endl;
			cout << "��Ƶ����: " << data.about << endl;
			cout << "����: " << data.view << "  ����: " << data.like
				<< "  Ӳ��: " << data.coin << "  ����: " << data.share << endl;
			cout << "#####################################" << endl;
			return os;
		}
		
		friend ifstream& operator>> (ifstream& infile, Data& data)
		{
			getline(infile, data.avId);
			getline(infile, data.title);
			getline(infile, data.about);
			infile >> data.view >> data.like >> data.coin >> data.share;
			infile.ignore();
			return infile;
		}

		friend ofstream& operator<< (ofstream& outfile, Data& data)
		{
			outfile << '\n' << data.avId << '\n';
			outfile << data.title << '\n';
			outfile << data.about << '\n';
			outfile << data.view << ' ' << data.like << ' ' 
				<< data.coin << ' ' << data.share;
			return outfile;
		}

	private:
		DataManager manager;
		string avId, title, about;
		int view, like, coin, share;
	};

}

#endif