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

#include <domain/reseau/Graph.h>
#include <algorithm>

namespace reseau_interurbain {
namespace domain {
Graph::Graph(const std::string& p_name, int p_x, int p_y)
    : m_vNodes(1, new Node(p_name, p_x, p_y)), m_nArcs(0) {
}
Graph::~Graph() {
    for (auto it = m_vNodes.begin(); it != m_vNodes.end();) {
        delete (*it);
        m_vNodes.erase(it);
    }
}
bool Graph::RenameNode(Node* p_src, const std::string& p_name) {
    if (!NodeExists(p_src))
        return true;
    p_src->RenameNode(p_name);
    return false;
}
bool Graph::AddNode(
      Node* p_src,
      const std::string& p_name,
      int p_x, int p_y,
      float p_duration,
      float p_cost
    ) {
    if (GetNode(p_name) != nullptr || !NodeExists(p_src))
        return true;
    Node* node(new Node(p_name, p_x, p_y));
    m_vNodes.push_back(node);
    p_src->AddArc(node, p_duration, p_cost);
    m_nArcs++;
    return false;
}
bool Graph::AddArc(Node* p_src, Node* p_dest, float p_length, float p_cost) {
    if (p_src->ArcExists(p_dest) || !NodeExists(p_src) || !NodeExists(p_dest))
        return true;
    auto it = std::find(m_vNodes.begin(), m_vNodes.end(), p_src);
    (*it)->AddArc(p_dest, p_length, p_cost);
    m_nArcs++;
    return false;
}
bool Graph::RemoveArc(Node* p_src, Node* p_dest) {
    if (p_src->ArcExists(p_dest) || !NodeExists(p_src) || !NodeExists(p_dest))
        return true;
    p_src->RemoveArc(p_dest);
    m_nArcs--;
    return false;
}
bool Graph::ArcExists(Node* p_src, Node* p_dest) const {
    if (!NodeExists(p_src) || !NodeExists(p_dest))
        return false;
    return p_src->ArcExists(p_dest);
}
std::vector<Node*> Graph::GetAdjNodes(Node* p_src) const {
    return p_src->GetAdjNodes();
}
const std::string& Graph::GetNodeName(Node* p_src) const {
    return p_src->GetName();
}
Node* Graph::GetNode(const std::string& p_name) const {
    auto it = std::find_if(m_vNodes.begin(), m_vNodes.end(),
        [&p_name](const Node* arc) {return arc->GetName() == p_name; });
    if (it == m_vNodes.end())
        return nullptr;
    return (*it);
}
std::vector<Node*> Graph::GetAllNodes() const {
    return m_vNodes;
}
int Graph::GetNodeCount() const {
    return m_vNodes.size();
}
int Graph::GetArcCount() const {
    return m_nArcs;
}
Ponderations Graph::GetPonderationsArc(Node* p_src, Node* p_dest) const {
    if (!NodeExists(p_src) || !NodeExists(p_dest) || !p_src->ArcExists(p_dest))
        return Ponderations(0, 0);
    return p_src->GetPonderation(p_dest);
}
bool Graph::NodeExists(Node* p_src) const {
    auto it = std::find(m_vNodes.begin(), m_vNodes.end(), p_src);
    return !(it == m_vNodes.end());
}
}  // namespace domain
}  // namespace reseau_interurbain
