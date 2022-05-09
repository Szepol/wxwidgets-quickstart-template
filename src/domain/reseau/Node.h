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

#include <string>
#include <vector>

namespace reseau_interurbain {
namespace domain {
struct Ponderations {
    float duration;
    float cost;
    Ponderations(float d, float c) : duration(d), cost(c) {}
};
class Node {
 public:
    Node(const std::string& p_name, int p_x, int p_y);
    ~Node() {}
    bool AddArc(Node* p_dest, float p_duration, float p_cost);
    bool RemoveArc(Node* p_dest);
    bool ChangePonderation(Node* p_dest, float p_duration, float p_cost);
    void RenameNode(const std::string& p_name);
    bool ArcExists(Node* p_dest) const;
    const std::string& GetName() const;
    std::vector<Node*> GetAdjNodes() const;
    const Ponderations& GetPonderation(Node* p_dest) const;
    int GetX() const;
    int GetY() const;

 private:
    struct Arc {
        Ponderations m_weight;
        Node* m_dest;
        Arc(Node* p_dest, float p_length, float p_cost)
            : m_dest(p_dest), m_weight(p_length, p_cost) {}
    };
    std::string m_name;
    std::vector<Arc> m_vArcs;
    int m_x;
    int m_y;
};
}  // namespace domain
}  // namespace reseau_interurbain

