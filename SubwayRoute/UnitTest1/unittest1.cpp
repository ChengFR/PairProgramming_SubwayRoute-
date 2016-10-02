#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SubwayRoute/subwayNet.h"
#include "../SubwayRoute/Main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestGetRouteB)
		{
			subwayNet sn;
			Route expect, result;
			string begin, end;
			int i = 0;
			string temp1, temp2;

			//����յ���ͬ
			begin = "֪��·";
			end = "֪��·";
			expect.push_back("֪��·");
			result = sn.getRouteB(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}

			//����յ�����
			expect.clear();
			begin = "֪��·";
			end = "֪����";
			expect.push_back("֪��·");
			expect.push_back("֪����");
			result = sn.getRouteB(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}

			//����յ�����Զ
			expect.clear();
			begin = "֪��·";
			end = "��ֱ��";
			expect.push_back("֪��·");
			expect.push_back("������");
			expect.push_back("��ֱ��");
			expect.push_back("��ˮ̶");
			expect.push_back("��¥���");
			expect.push_back("������");
			expect.push_back("Ӻ����");
			expect.push_back("��ֱ��");
			result = sn.getRouteB(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}
			//����·��ѡ��
			expect.clear();
			begin = "������";
			end = "��Ȼͤ";
			expect.push_back("������");
			expect.push_back("��ֱ��");
			expect.push_back("����ׯ");
			expect.push_back("������");
			expect.push_back("������");
			expect.push_back("������");
			expect.push_back("������");
			expect.push_back("���п�");
			expect.push_back("��Ȼͤ");
			result = sn.getRouteB(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}

			//����������յ㣬�費��Ҫ���ԣ�
			expect.clear();
			begin = "��˹��";
			end = "֪����";
			expect.push_back("��˹��");
			result = sn.getRouteB(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}
		}

		TEST_METHOD(TestGetRouteC) {
			subwayNet sn;
			Route expect, result;
			string begin, end;
			int i = 0;
			string temp1, temp2;

			//����յ���ͬ
			begin = "֪��·";
			end = "֪��·";
			expect.push_back("֪��·");
			result = sn.getRouteC(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}
			//����յ�����
			expect.clear();
			begin = "֪��·";
			end = "֪����";
			expect.push_back("֪��·");
			expect.push_back("֪����");
			result = sn.getRouteC(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}
			//����յ�����Զ
			expect.clear();
			begin = "֪��·";
			end = "��ֱ��";
			expect.push_back("֪��·");
			expect.push_back("�����");
			expect.push_back("�ϵ�");
			expect.push_back("������");
			expect.push_back("����");
			expect.push_back("������");
			expect.push_back("��Ӫ");
			expect.push_back("��ˮ��");
			expect.push_back("��Է");
			expect.push_back("������");
			expect.push_back("��ҩ��");
			expect.push_back("������");
			expect.push_back("����");
			expect.push_back("��ֱ��");
			result = sn.getRouteC(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}

			//�ж�������Ļ���վ
			expect.clear();
			begin = "������";
			end = "��Ȼͤ";
			expect.push_back("������");
			expect.push_back("��ֱ��");
			expect.push_back("�½ӿ�");
			expect.push_back("ƽ����");
			expect.push_back("����");
			expect.push_back("�龳��ͬ");
			expect.push_back("����");
			expect.push_back("������");
			expect.push_back("���п�");
			expect.push_back("��Ȼͤ");
			result = sn.getRouteC(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}

			//����������յ�
			expect.clear();
			begin = "��˹��";
			end = "֪����";
			expect.push_back("��˹��");
			result = sn.getRouteC(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}
		}
		TEST_METHOD(TestGetRouteG) {
			subwayNet sn;
			Route expect, result;
			string begin, end;
			int i = 0;
			string temp1, temp2;

			//-b
			begin = "������";
			end = "��Ȼͤ";
			expect.push_back("������");
			expect.push_back("��ֱ��");
			expect.push_back("����ׯ");
			expect.push_back("������");
			expect.push_back("������");
			expect.push_back("������");
			expect.push_back("������");
			expect.push_back("���п�");
			expect.push_back("��Ȼͤ");
			result = sn.getRouteG(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}

			//-c
			sn.getRouteC(begin, end);
			sn.getRouteC(begin, end);
			expect.clear();
			begin = "������";
			end = "��Ȼͤ";
			expect.push_back("������");
			expect.push_back("��ֱ��");
			expect.push_back("�½ӿ�");
			expect.push_back("ƽ����");
			expect.push_back("����");
			expect.push_back("�龳��ͬ");
			expect.push_back("����");
			expect.push_back("������");
			expect.push_back("���п�");
			expect.push_back("��Ȼͤ");
			result = sn.getRouteG(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}
		}
		TEST_METHOD(TestChangeRouteToString) {
			subwayNet sn;
			string expect, result;
			Route input;
			string begin, end;

			//ֻ��һվ
			input.push_back("֪��·");
			expect = "֪��·";
			expect += "\n";
			result = sn.changeRouteToString(input);
			Assert::AreEqual(expect, result);

			//��һվ�ǲ��ǻ���վ
			input.clear();
			input.push_back("������");
			input.push_back("��ֱ��");
			input.push_back("����ׯ");
			expect = "������";
			expect += "\n";
			expect = "��ֱ�Ż��˵���������";
			expect += "\n";
			expect = "����ׯ";
			expect += "\n";
			result = sn.changeRouteToString(input);
			Assert::AreEqual(expect, result);

			//��һվ�ǻ���վ���ڶ�վ���ǻ���
			input.clear();
			input.push_back("֪��·");
			input.push_back("������");
			input.push_back("��ֱ��");
			input.push_back("����ׯ");
			expect = "֪��·";
			expect += "\n";
			expect = "������";
			expect += "\n";
			expect = "��ֱ�Ż��˵���������";
			expect += "\n";
			expect = "����ׯ";
			expect += "\n";
			result = sn.changeRouteToString(input);
			Assert::AreEqual(expect, result);

			//��һվ�ǻ���վ���ڶ�վҲ�ǻ���
			input.clear();
			input.push_back("��ֱ��");
			input.push_back("����ׯ");
			input.push_back("������");
			expect = "��ֱ��";
			expect += "\n";
			expect = "����ׯ";
			expect += "\n";
			expect = "������";
			expect += "\n";
			result = sn.changeRouteToString(input);
			Assert::AreEqual(expect, result);
		}

	};
}