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
			beginSta = "知春路";
			endSta = "五道口";
			route = net.getRouteB(beginSta, endSta);
			calcRoute = net.changeRouteToString(route);
			//expectRoute = net.changeRouteToString(net.getRouteB(beginSta, endSta));
			//expectRoute.push_back("2");
			//expectRoute.push_back("知春路");
			//expectRoute.push_back("五道口");
			//Assert::AreEqual(expectRoute, calcRoute);
			//Assert::AreEqual(233,233);
		}

	};
}