// Copyright 2022 Szepol
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <domain/reseau/Node.h>
#include <gtest/gtest.h>

#include <string>

using std::string;
using std::vector;

namespace reseau_interurbain {
namespace domain {
namespace test {
class NodeTestFixture : public ::testing::Test {
 protected:
    NodeTestFixture() : firstNodeName("FirstNode"),
        firstNodeX(1), firstNodeY(1),
        secondNodeName("SecondNode"), secondNodeX(-1), secondNodeY(-1),
        f_testFirstNode(firstNodeName, firstNodeX, firstNodeY),
        f_testSecondNode(secondNodeName, secondNodeX, secondNodeY) {
    }
    ~NodeTestFixture() override {
    }
    void SetUp() override {
        arcDuration = 60.0;
        arcCost = 25;
        f_testFirstNode.AddArc(&f_testSecondNode, arcDuration, arcCost);
    }

    string firstNodeName;
    string secondNodeName;
    int firstNodeX, firstNodeY;
    int secondNodeX, secondNodeY;
    float arcDuration, arcCost;
    Node f_testFirstNode;
    Node f_testSecondNode;
};
TEST(NodeTest, Constructor) {
    string testName = "TestNodeName";
    int x(-5), y(5);
    Node testNode = Node(testName, x, y);
    ASSERT_EQ(testNode.GetName(), testName);
    ASSERT_EQ(testNode.GetX(), x);
    ASSERT_EQ(testNode.GetY(), y);
}
TEST_F(NodeTestFixture, AddArcValid)    {
    ASSERT_FALSE(f_testSecondNode.AddArc(&f_testFirstNode, 60, 25));
    ASSERT_TRUE(f_testSecondNode.ArcExists(&f_testFirstNode));
    Ponderations testPonderation =
        f_testSecondNode.GetPonderation(&f_testFirstNode);
    ASSERT_EQ(testPonderation.duration, 60);
    ASSERT_EQ(testPonderation.cost, 25);
}
TEST_F(NodeTestFixture, AddArcInvalidDuplicate) {
    // Try to add an alreadly existing arc, should return false
    ASSERT_TRUE(f_testFirstNode.AddArc(&f_testFirstNode, 30, 5));
    ASSERT_FALSE(f_testFirstNode.ArcExists(&f_testFirstNode));
    Ponderations testPonderation =
        f_testFirstNode.GetPonderation(&f_testSecondNode);
    ASSERT_EQ(testPonderation.duration, arcDuration);
    ASSERT_EQ(testPonderation.cost, arcCost);
}
TEST_F(NodeTestFixture, AddArcInvalidSelf)  {
    ASSERT_TRUE(f_testFirstNode.AddArc(&f_testFirstNode, 15, 20));
    ASSERT_FALSE(f_testFirstNode.ArcExists(&f_testFirstNode));
}
TEST_F(NodeTestFixture, RemoveArcValid) {
    ASSERT_FALSE(f_testFirstNode.RemoveArc(&f_testSecondNode));
    ASSERT_FALSE(f_testFirstNode.ArcExists(&f_testSecondNode));
}
TEST_F(NodeTestFixture, RemoveArcInvalid)   {
    ASSERT_TRUE(f_testSecondNode.RemoveArc(&f_testFirstNode));
}
TEST_F(NodeTestFixture, ChangePonderationValid) {
    ASSERT_FALSE(f_testFirstNode.ChangePonderation(&f_testSecondNode, 30, 10));
    Ponderations testPonderation =
        f_testFirstNode.GetPonderation(&f_testSecondNode);
    ASSERT_EQ(testPonderation.duration, 30);
    ASSERT_EQ(testPonderation.cost, 10);
}
TEST_F(NodeTestFixture, ChangePonderationInvalid) {
    ASSERT_TRUE(f_testSecondNode.ChangePonderation(&f_testFirstNode, 30, 10));
    ASSERT_FALSE(f_testSecondNode.ArcExists(&f_testFirstNode));
}
TEST_F(NodeTestFixture, RenameNode) {
    f_testFirstNode.RenameNode("TestNode");
    ASSERT_EQ(f_testFirstNode.GetName(), "TestNode");
}
TEST_F(NodeTestFixture, ArcExistsValid) {
    ASSERT_TRUE(f_testFirstNode.ArcExists(&f_testSecondNode));
}
TEST_F(NodeTestFixture, ArcExitsInvalid) {
    ASSERT_FALSE(f_testSecondNode.ArcExists(&f_testFirstNode));
}
TEST_F(NodeTestFixture, GetName) {
    ASSERT_EQ(f_testFirstNode.GetName(), firstNodeName);
    ASSERT_EQ(f_testSecondNode.GetName(), secondNodeName);
}
TEST_F(NodeTestFixture, GetAdjNode) {
    vector<Node*> testAdjVector;
    testAdjVector.push_back(&f_testSecondNode);
    ASSERT_EQ(f_testFirstNode.GetAdjNodes(), testAdjVector);
}
TEST_F(NodeTestFixture, GetPonderation) {
    Ponderations testPonderation =
        f_testFirstNode.GetPonderation(&f_testSecondNode);
    ASSERT_EQ(testPonderation.duration, arcDuration);
    ASSERT_EQ(testPonderation.cost, arcCost);
    f_testFirstNode.ChangePonderation(&f_testSecondNode, 30.5, 5.5);
    testPonderation = f_testFirstNode.GetPonderation(&f_testSecondNode);
    ASSERT_EQ(testPonderation.duration, 30.5);
    ASSERT_EQ(testPonderation.cost, 5.5);
}
TEST_F(NodeTestFixture, GetX) {
    ASSERT_EQ(f_testFirstNode.GetX(), firstNodeX);
    ASSERT_EQ(f_testSecondNode.GetX(), secondNodeX);
}
TEST_F(NodeTestFixture, GetY) {
    ASSERT_EQ(f_testFirstNode.GetY(), firstNodeY);
    ASSERT_EQ(f_testSecondNode.GetY(), secondNodeY);
}
}  // namespace test
}  // namespace domain
}  // namespace reseau_interurbain
