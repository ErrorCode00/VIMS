/*
 * VIMS系统
 *
 * @author Afeng
 * @date 2019/04/16
 */

#ifndef __VIMS_H__
#define __VIMS_H__
#include <Windows.h>
#include "rbtree.h"
#include "tools.h"

namespace vims {
	using namespace rbtree;
	using namespace tools;

	class VIMS {
	public:
		VIMS();

		void loadData();	// 读取数据源
		void showMenu();	// 显示菜单
		void getResponse();	// 根据操作做出响应
		void saveData();	// 数据输出存储


	private:
		RBTree<Data>* tree;	// 用于操作红黑树
		RBTNode<Data>* node;	// 存储需要操作的结点
		Data data;			// 需要操作单个视频信息时使用
		string option;		// 存储用户操作
		string id;			// 存储过渡ID
		string message;		// 存储输入提示标题

		bool option_legal();	// 判断菜单操作合法性
		bool id_legal();		// 判断视频ID合法性
		void loadData(RBTree<Data>*);	// 读取数据源
		void saveData(RBTree<Data>*);	// 存储数据
		void getOption();	// 获取用户操作
		void getID();		// 获取用户需要操作的ID
		bool searchID();	// 检索视频信息
		void appendID();	// 添加视频信息
		void alterID();		// 修改视频信息
		void deleteID();	// 删除视频信息
		void aboutAll();	// 相关视频信息
		void setxy(short, short);	// 设置光标位置

	
	};
}

#endif