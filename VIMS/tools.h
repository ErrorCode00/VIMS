/*
 * VIMS系统工具
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
	 * Data管理类
	 *
	 * 类说明:
	 *		对Data类中的数据操作进行个性化管理
	 */
	class DataManager
	{
	public:
		/*
		 * 构造函数
		 */
		DataManager() : c(' ') {}

		/****************************/
		/*		Data工具管理函数	*/
		/****************************/
		/*
		 * 获取用户响应输入，并进行存储
		 */
		void get_input(string message, istream& is, string& where)
		{
			cout << endl << "请输入" + message + ": ";
			is >> where;
			while (be_sure(message + ": " + where))
			{
				cout << "#请重新输入" + message + ": ";
				is >> where;
			}
		}

		/*
		 * 确定该信息内容
		 *
		 * 参数说明:
		 *		message(string): 相关信息
		 */
		bool be_sure(const string message)
		{
			cout << endl << "?是否确认" << message << " (y/n)?  ";
			cin >> c;
			cin.ignore(1024, '\n');
			if (c == 'n' || c == 'N')
				return true;
			else
				return false;
		}
	private:
		char c;		// 存储用户确认时输入字符
	};

	/*
	 *	 Data类: 用于存储每条信息内容
	 *
	 * 变量说明:
	 *		 avId: 视频ID
	 *		title: 视频标题
	 *		about: 视频详情
	 *		 view: 播放量
	 *		 like: 点赞量
	 *		 coin: 投币数
	 *		share: 分享数
	 */
	class Data {
	public:
		Data() :avId(""), title(""), about(""),
			view(0), like(0), coin(0), share(0) {}
		Data(string avId) :avId(avId), title(""), about(""),
			view(0), like(0), coin(0), share(0) {}

		/****************************/
		/*	  Data运算符重载部分	*/
		/****************************/
		operator string() { return avId; }
		bool operator< (Data data) const { return (atoi(avId.c_str()) < atoi(data.avId.c_str())); }
		bool operator== (Data data) const { return (avId == data.avId); }
		bool operator!= (Data data) const { return !operator==(data); }
		friend istream& operator>> (istream& is, Data& data)
		{
			while (data.manager.be_sure("视频ID " + data.avId))
			{
				cout << "#请重新输入视频ID: ";
				is >> data.avId;
			}
			data.manager.get_input("视频标题", is, data.title);
			data.manager.get_input("视频详情", is, data.about);
			do
			{
				cout << endl << "请输入播放量、点赞量、硬币数、分享数: \n\t";
				is >> data.view >> data.like
					>> data.coin >> data.share;
			} while (data.manager.be_sure("播放量、点赞量、硬币数、分享数"));
			return is;
		}
		friend ostream& operator<< (ostream&os, Data& data)
		{
			cout << "\n#####################################" << endl;
			cout << "视频ID: " << data.avId << endl;
			cout << "视频标题: " << data.title << endl;
			cout << "视频详情: " << data.about << endl;
			cout << "播放: " << data.view << "  点赞: " << data.like
				<< "  硬币: " << data.coin << "  分享: " << data.share << endl;
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