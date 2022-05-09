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

#include <domain/reseau/Graph.h>
#include <string>
#include <vector>

namespace reseau_interurbain {
namespace domain {
struct Chemin {
    std::vector<std::string> listeVilles;
    float dureeTotale;
    float coutTotal;
    bool reussi;
};
class ReseauInterurbain {
 public:
    ReseauInterurbain(std::string p_nodeName, int p_x,
        int p_y, std::string p_networkName);
    ~ReseauInterurbain();
    Chemin rechercheCheminDijkstra(const std::string& origine,
        const std::string& destination, bool dureeCout) const;
    std::vector<std::vector<std::string>> algorithmeKosaraju();

 private:
    Graph m_network;
    std::string m_networkName;
};
}  // namespace domain
}  // namespace reseau_interurbain
