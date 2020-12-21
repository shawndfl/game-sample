#include "UnitTest++/UnitTest++.h"
#include "Logging.h"
#include "JsonNode.h"
#include "JsonParser.h"

SUITE(Math) {

TEST(Vector) {
   bsk::JsonNode node;
   bsk::JsonNode value;
   value.set(12);
   node.set("test", value);
   CHECK_EQUAL("{\"test\":12.000000}", node.toString());

}

TEST(Matrix) {
   bsk::JsonNode node;
   node.append() = 12;
   node.append() = 13;
   CHECK_EQUAL("[12.000000,13.000000]", node.toString());

}
}
