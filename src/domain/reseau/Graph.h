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


#pragma once

#include <domain/reseau/Node.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>

namespace reseau_interurbain {
namespace domain {
class Graph {
 public:
    Graph(const std::string& p_name, int p_x, int p_y);
    ~Graph();
    bool RenameNode(Node* p_src, const std::string& p_name);
    bool AddNode(Node* p_src, const std::string& p_name,
        int p_x, int p_y, float p_length, float p_cost);
    bool AddArc(Node* p_src, Node* p_dest, float p_length, float p_cost);
    bool RemoveArc(Node* p_src, Node* p_dest);
    bool ArcExists(Node* p_src, Node* p_dest) const;
    std::vector<Node*> GetAdjNodes(Node* p_src) const;
    const std::string& GetNodeName(Node* sommet) const;
    Node* GetNode(const std::string& p_name) const;
    std::vector<Node*> GetAllNodes() const;
    int GetNodeCount() const;
    int GetArcCount() const;
    Ponderations GetPonderationsArc(Node* p_src, Node* p_dest) const;

 private:
    std::vector<Node*> m_vNodes;
    size_t m_nArcs;
    bool NodeExists(Node* p_src) const;
};
}  // namespace domain
}  // namespace reseau_interurbain

