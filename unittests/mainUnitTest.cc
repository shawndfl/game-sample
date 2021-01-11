
#include <string>
#include <iomanip>
#include <map>

#include "core/Logging.h"

#include "UnitTest++/UnitTest++.h"

class Reporter : public UnitTest::TestReporter {

   virtual void ReportTestStart(UnitTest::TestDetails const& test) {
      if(suites_.find(test.suiteName) == suites_.end()) {
         std::cout << std::setfill(' ')  << "Suite: " << test.suiteName << std::endl;
         suites_[test.suiteName] = 1;
      }
   }

   virtual void ReportFailure(UnitTest::TestDetails const& test, char const* failure){
      std::cout << test.filename << "(" << test.lineNumber << ") " << failure << std::endl;
   }

   virtual void ReportTestFinish(UnitTest::TestDetails const& test,
         float secondsElapsed){
      std::cout << std::setfill(' ') <<"  " << std::setw(20) << test.testName << ": " << std::setw(20) << std::fixed << (secondsElapsed * 1000)  << " (ms)" << std::endl;

   }

   virtual void ReportSummary(int totalTestCount, int failedTestCount,
         int failureCount, float secondsElapsed) {
      std::cout << std::endl;
      std::cout << "Finished" << std::endl;
      std::cout << " tests       : " << totalTestCount << std::endl;
      std::cout << " failed test : " << failedTestCount << std::endl;
      std::cout << " failures    : " << failureCount << std::endl;
      std::cout << " time        : " << secondsElapsed << "(s)" << std::endl;
   }
private:
   std::map<std::string, int> suites_;

};

int main(int argc, char *argv[]) {

   std::map<std::string, int> suites;
   UnitTest::Test* curTest = UnitTest::Test::GetTestList().GetHead();

   while (curTest != 0) {
      suites[curTest->m_details.suiteName] = 0;
      curTest = curTest->m_nextTest;
   }

   char* selectedSuite = nullptr;

   if(argc > 1 ) {
      if(argv[1] == nullptr || suites.find(argv[1]) == suites.end()) {
         LOGI("Pass in one of the following suites: ");
         for(auto pair: suites) {
            LOGI("  " << pair.first);
         }
         return 1;
      } else {
         selectedSuite = argv[1];
      }
   }

   Reporter reporter;
   UnitTest::TestRunner runner(reporter);
   return runner.RunTestsIf(UnitTest::Test::GetTestList(), selectedSuite, UnitTest::True(), 0);
}
