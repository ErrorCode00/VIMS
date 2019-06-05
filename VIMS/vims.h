/*
 * VIMSϵͳ
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

		void loadData();	// ��ȡ����Դ
		void showMenu();	// ��ʾ�˵�
		void getResponse();	// ���ݲ���������Ӧ
		void saveData();	// ��������洢


	private:
		RBTree<Data>* tree;	// ���ڲ��������
		RBTNode<Data>* node;	// �洢��Ҫ�����Ľ��
		Data data;			// ��Ҫ����������Ƶ��Ϣʱʹ��
		string option;		// �洢�û�����
		string id;			// �洢����ID
		string message;		// �洢������ʾ����

		bool option_legal();	// �жϲ˵������Ϸ���
		bool id_legal();		// �ж���ƵID�Ϸ���
		void loadData(RBTree<Data>*);	// ��ȡ����Դ
		void saveData(RBTree<Data>*);	// �洢����
		void getOption();	// ��ȡ�û�����
		void getID();		// ��ȡ�û���Ҫ������ID
		bool searchID();	// ������Ƶ��Ϣ
		void appendID();	// �����Ƶ��Ϣ
		void alterID();		// �޸���Ƶ��Ϣ
		void deleteID();	// ɾ����Ƶ��Ϣ
		void aboutAll();	// �����Ƶ��Ϣ
		void setxy(short, short);	// ���ù��λ��

	
	};
}

#endif