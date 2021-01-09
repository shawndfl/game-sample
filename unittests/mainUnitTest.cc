
#include <string>
#include <iomanip>
#include <map>

#include "core/Logging.h"

#include "UnitTest++/UnitTest++.h"

class Reporter : public UnitTest::TestReporter {

   virtual void ReportTestStart(UnitTest::TestDetails const& test) {
      if(suites_.find(test.suiteName) == suites_.end()) {
         LOGI("Suite: " << test.suiteName);
         suites_[test.suiteName] = 1;
      }
   }

   virtual void ReportFailure(UnitTest::TestDetails const& test, char const* failure){
      LOGE("  Failed " << test.testName << ": " << failure);
   }

   virtual void ReportTestFinish(UnitTest::TestDetails const& test,
         float secondsElapsed){
      LOGI("  " << std::setw(20) << test.testName << ": " << std::setw(20) << std::fixed << (secondsElapsed * 1000)  << " (ms)");

   }

   virtual void ReportSummary(int totalTestCount, int failedTestCount,
         int failureCount, float secondsElapsed) {
      LOGI("Finished");
      LOGI(" testCount      : " << totalTestCount);
      LOGI(" failed Test    : " << failedTestCount);
      LOGI(" total failures : " << failureCount);
      LOGI(" time           : " << secondsElapsed << "(s)");
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
