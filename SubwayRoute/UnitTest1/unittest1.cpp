#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SubwayRoute/subwayNet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			subwayNet net;
			string beginSta, endSta;
			string expectRoute, calcRoute;
			Route route;
			beginSta = "֪��·";
			endSta = "�����";
			route = net.getRouteB(beginSta, endSta);
			calcRoute = net.changeRouteToString(route);
			//expectRoute = net.changeRouteToString(net.getRouteB(beginSta, endSta));
			//expectRoute.push_back("2");
			//expectRoute.push_back("֪��·");
			//expectRoute.push_back("�����");
			//Assert::AreEqual(expectRoute, calcRoute);
			//Assert::AreEqual(233,233);
		}

	};
}