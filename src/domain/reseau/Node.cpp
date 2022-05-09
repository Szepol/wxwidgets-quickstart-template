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

namespace reseau_interurbain {
namespace domain {
Node::Node(const std::string& p_name, int p_x, int p_y)
    : m_name(p_name), m_x(p_x), m_y(p_y) {
}
bool Node::AddArc(Node* p_dest, float p_duration, float p_cost) {
    if (ArcExists(p_dest) || p_dest == this)
        return true;
    m_vArcs.push_back(Arc(p_dest, p_duration, p_cost));
    return false;
}
bool Node::RemoveArc(Node* p_dest) {
    auto it = std::find_if(m_vArcs.begin(), m_vArcs.end(),
        [&p_dest](const Arc& x) {return x.m_dest == p_dest; });
    if (it == m_vArcs.end())
        return true;
    m_vArcs.erase(it);
    return false;
}
bool Node::ChangePonderation(Node * p_dest, float p_duration, float p_cost) {
    auto it = std::find_if(m_vArcs.begin(), m_vArcs.end(),
        [&p_dest](const Arc& x) {return x.m_dest == p_dest; });
    if (it == m_vArcs.end())
        return true;
    it->m_weight.duration = p_duration;
    it->m_weight.cost = p_cost;
    return false;
}
void Node::RenameNode(const std::string& p_name) {
    m_name = p_name;
}
bool Node::ArcExists(Node* p_dest) const {
    auto it = std::find_if(m_vArcs.begin(), m_vArcs.end(),
        [&p_dest](const Arc& x) {return x.m_dest == p_dest; });
    if (it == m_vArcs.end())
        return false;
    return true;
}
const std::string& Node::GetName() const {
    return m_name;
}
std::vector<Node*> Node::GetAdjNodes() const {
    std::vector<Node*> adjacentNodes;
    for (auto it : m_vArcs)
        adjacentNodes.push_back(it.m_dest);
    return adjacentNodes;
}
const Ponderations& Node::GetPonderation(Node * p_dest) const {
    // TODO(Szepol): Define behavior when passing unconnected Node.
    auto it = std::find_if(m_vArcs.begin(), m_vArcs.end(),
        [&p_dest](const Arc& x) {return x.m_dest == p_dest; });
    return it->m_weight;
}
int Node::GetX() const {
    return m_x;
}
int Node::GetY() const {
    return m_y;
}
}  // namespace domain
}  // namespace reseau_interurbain

