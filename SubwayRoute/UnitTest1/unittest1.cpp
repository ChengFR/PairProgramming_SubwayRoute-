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

			//起点终点相同
			begin = "知春路";
			end = "知春路";
			expect.push_back("知春路");
			result = sn.getRouteB(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}

			//起点终点相邻
			expect.clear();
			begin = "知春路";
			end = "知春里";
			expect.push_back("知春路");
			expect.push_back("知春里");
			result = sn.getRouteB(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}

			//起点终点相距较远
			expect.clear();
			begin = "知春路";
			end = "东直门";
			expect.push_back("知春路");
			expect.push_back("大钟寺");
			expect.push_back("西直门");
			expect.push_back("积水潭");
			expect.push_back("鼓楼大街");
			expect.push_back("安定门");
			expect.push_back("雍和门");
			expect.push_back("东直门");
			result = sn.getRouteB(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}
			//多条路线选择
			expect.clear();
			begin = "大钟寺";
			end = "陶然亭";
			expect.push_back("大钟寺");
			expect.push_back("西直门");
			expect.push_back("车公庄");
			expect.push_back("阜成门");
			expect.push_back("复兴门");
			expect.push_back("长椿街");
			expect.push_back("宣武门");
			expect.push_back("菜市口");
			expect.push_back("陶然亭");
			result = sn.getRouteB(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}

			//错误的起点和终点，需不需要断言？
			expect.clear();
			begin = "阿斯达";
			end = "知春里";
			expect.push_back("阿斯达");
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

			//起点终点相同
			begin = "知春路";
			end = "知春路";
			expect.push_back("知春路");
			result = sn.getRouteC(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}
			//起点终点相邻
			expect.clear();
			begin = "知春路";
			end = "知春里";
			expect.push_back("知春路");
			expect.push_back("知春里");
			result = sn.getRouteC(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}
			//起点终点相距较远
			expect.clear();
			begin = "知春路";
			end = "东直门";
			expect.push_back("知春路");
			expect.push_back("五道口");
			expect.push_back("上地");
			expect.push_back("西二旗");
			expect.push_back("龙泽");
			expect.push_back("回龙观");
			expect.push_back("霍营");
			expect.push_back("立水桥");
			expect.push_back("北苑");
			expect.push_back("望京西");
			expect.push_back("芍药居");
			expect.push_back("光熙门");
			expect.push_back("柳芳");
			expect.push_back("东直门");
			result = sn.getRouteC(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}

			//有多个连续的换乘站
			expect.clear();
			begin = "大钟寺";
			end = "陶然亭";
			expect.push_back("大钟寺");
			expect.push_back("西直门");
			expect.push_back("新接口");
			expect.push_back("平安里");
			expect.push_back("西四");
			expect.push_back("灵境胡同");
			expect.push_back("西单");
			expect.push_back("宣武门");
			expect.push_back("菜市口");
			expect.push_back("陶然亭");
			result = sn.getRouteC(begin, end);
			for (i = 0; i < expect.size(); i++) {
				temp1 = result[i];
				temp2 = expect[i];
				Assert::AreEqual(temp1, temp2);
			}

			//错误的起点和终点
			expect.clear();
			begin = "阿斯达";
			end = "知春里";
			expect.push_back("阿斯达");
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
			begin = "大钟寺";
			end = "陶然亭";
			expect.push_back("大钟寺");
			expect.push_back("西直门");
			expect.push_back("车公庄");
			expect.push_back("阜成门");
			expect.push_back("复兴门");
			expect.push_back("长椿街");
			expect.push_back("宣武门");
			expect.push_back("菜市口");
			expect.push_back("陶然亭");
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
			begin = "大钟寺";
			end = "陶然亭";
			expect.push_back("大钟寺");
			expect.push_back("西直门");
			expect.push_back("新接口");
			expect.push_back("平安里");
			expect.push_back("西四");
			expect.push_back("灵境胡同");
			expect.push_back("西单");
			expect.push_back("宣武门");
			expect.push_back("菜市口");
			expect.push_back("陶然亭");
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

			//只有一站
			input.push_back("知春路");
			expect = "知春路";
			expect += "\n";
			result = sn.changeRouteToString(input);
			Assert::AreEqual(expect, result);

			//第一站是不是换乘站
			input.clear();
			input.push_back("大钟寺");
			input.push_back("西直门");
			input.push_back("车公庄");
			expect = "大钟寺";
			expect += "\n";
			expect = "西直门换乘地铁二号线";
			expect += "\n";
			expect = "车公庄";
			expect += "\n";
			result = sn.changeRouteToString(input);
			Assert::AreEqual(expect, result);

			//第一站是换乘站，第二站不是换乘
			input.clear();
			input.push_back("知春路");
			input.push_back("大钟寺");
			input.push_back("西直门");
			input.push_back("车公庄");
			expect = "知春路";
			expect += "\n";
			expect = "大钟寺";
			expect += "\n";
			expect = "西直门换乘地铁二号线";
			expect += "\n";
			expect = "车公庄";
			expect += "\n";
			result = sn.changeRouteToString(input);
			Assert::AreEqual(expect, result);

			//第一站是换乘站，第二站也是换乘
			input.clear();
			input.push_back("西直门");
			input.push_back("车公庄");
			input.push_back("阜成门");
			expect = "西直门";
			expect += "\n";
			expect = "车公庄";
			expect += "\n";
			expect = "阜成门";
			expect += "\n";
			result = sn.changeRouteToString(input);
			Assert::AreEqual(expect, result);
		}

	};
}