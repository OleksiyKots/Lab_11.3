#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_11.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestFindFriendBySurnameFound) {
            string testFile = "test_friends.txt";
            ofstream file(testFile);
            file << "Ivanov Ivan Aries 15.08.1992\n";
            file << "Petrov Petr Taurus 20.05.1985\n";
            file.close();

            stringstream output;
            streambuf* oldCout = cout.rdbuf(output.rdbuf());
            findFriendBySurname(testFile, "Ivanov");
            cout.rdbuf(oldCout);

            string result = output.str();
            Assert::IsTrue(result.find("Ivanov Ivan Aries 15.8.1992") != string::npos);
        }

        // Тестуємо функцію findFriendBySurname для відсутнього друга
        TEST_METHOD(TestFindFriendBySurnameNotFound) {
            string testFile = "test_friends.txt";
            ofstream file(testFile);
            file << "Ivanov Ivan Aries 15.08.1992\n";
            file.close();

            stringstream output;
            streambuf* oldCout = cout.rdbuf(output.rdbuf());
            findFriendBySurname(testFile, "Sidorov");
            cout.rdbuf(oldCout);

            string result = output.str();
            Assert::IsTrue(result.find("не знайдено") != string::npos);
        }
	};
}
