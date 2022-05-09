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

#include <domain/reseau/ReseauInterurbain.h>

#include <sstream>
#include <fstream>
#include <functional>
#include <limits>
#include <numeric>
#include <utility>
#include <algorithm>
#include <map>
#include <list>
#include <vector>

namespace reseau_interurbain {
namespace domain {
ReseauInterurbain::ReseauInterurbain(
      std::string p_nodeName,
      int p_x,
      int p_y,
      std::string p_networkName = "Sans nom")
    : m_network(p_nodeName, p_x, p_y), m_networkName(p_networkName) {
}
ReseauInterurbain::~ReseauInterurbain() {
}
Chemin ReseauInterurbain::rechercheCheminDijkstra(const std::string& p_origin,
      const std::string& p_dest, bool dureeCout) const {
    auto networkNodes = m_network.GetAllNodes();
    std::vector<Node*> unsolvedNodes(networkNodes);
    std::map<Node*, Chemin> nodes;
    for (auto it = unsolvedNodes.begin(); it != unsolvedNodes.end(); it++) {
        nodes[*it] = {
            std::vector<std::string>(),
            std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(),
            false
        };
        if ((*it)->GetName() == p_origin) {
            unsolvedNodes.erase(it);
            it--;
        }
    }

    nodes.at(m_network.GetNode(p_origin)).dureeTotale = 0;
    nodes.at(m_network.GetNode(p_origin)).coutTotal = 0;

    std::function<std::vector<Node*>::iterator(std::vector<Node*>&)> min;
    std::function<std::vector<Node*>(std::vector<Node*>)> adj;

    min = [&dureeCout, &nodes](std::vector<Node*>& unsolved) {
        auto temp = std::make_pair(unsolved.end(),
            std::numeric_limits<float>::max());
        for (auto n = unsolved.begin(); n != unsolved.end(); n++) {
            if (!nodes[*n].reussi) {
                if (dureeCout) {
                    if (nodes[*n].dureeTotale < temp.second) {
                        temp = std::make_pair(n, nodes[*n].dureeTotale);
                    }
                } else {
                    if (nodes[*n].coutTotal < temp.second) {
                        temp = std::make_pair(n, nodes[*n].coutTotal);
                    }
                }
            }
        }
        return temp.first;
    };

    adj = [&nodes](const std::vector<Node*>& adjacent) {
        std::vector<Node*> temp;
        for (auto n : adjacent) {
            if (!nodes[n].reussi)
                temp.push_back(n);
        }
        return temp;
    };

    while (!unsolvedNodes.empty()) {
        auto u = min(unsolvedNodes);
        if (u == unsolvedNodes.end())
            break;
        nodes[*u].reussi = true;

        for (auto& n : adj(m_network.GetAdjNodes(*u))) {
            auto weight = m_network.GetPonderationsArc(*u, n);
            if (dureeCout) {
                float temp = nodes[*u].dureeTotale + weight.duration;
                if (temp < nodes[n].dureeTotale) {
                    nodes[n].dureeTotale = temp;
                    nodes[n].listeVilles.clear();
                    for (auto& t : nodes[*u].listeVilles)
                        nodes[n].listeVilles.push_back(t);
                    nodes[n].listeVilles.push_back(m_network.GetNodeName(*u));
                }
            } else {
                float temp = nodes[*u].coutTotal + weight.cost;
                if (temp < nodes[n].coutTotal) {
                    nodes[n].coutTotal = temp;
                    nodes[n].listeVilles.clear();
                    for (auto& t : nodes[*u].listeVilles)
                        nodes[n].listeVilles.push_back(t);
                    nodes[n].listeVilles.push_back(m_network.GetNodeName(*u));
                }
            }
        }
        unsolvedNodes.erase(u);
    }

    for (auto it = networkNodes.begin(); it != networkNodes.end(); it++) {
        nodes[*it].listeVilles.push_back(m_network.GetNodeName(*it));
    }

    return nodes.at(m_network.GetNode(p_dest));
}
std::vector<std::vector<std::string> > ReseauInterurbain::algorithmeKosaraju() {
    std::vector<std::vector<std::string>> composantesConnexes;
    std::map<Node*, bool> visited;

    auto networkNodes = m_network.GetAllNodes();

    std::map<Node*, std::vector<Node*>> inverse;
    for (auto it = networkNodes.begin(); it != networkNodes.end(); it++) {
        visited[*it] = false;
        for (auto j : m_network.GetAdjNodes(*it)) {
            inverse[j].push_back(*it);
        }
    }

    std::list<Node*> pile;
    std::function<void(Node*)> explore;
    explore = [&inverse, &visited, &pile, &explore](Node* x) {
        if (!visited[x]) {
            visited[x] = true;
            for (auto& n : inverse[x]) {
                if (!visited[n])
                    explore(n);
            }
            pile.push_back(x);
        }
    };
    for (auto it = visited.begin(); it != visited.end(); ++it) {
        if (!(it->second))
            explore(it->first);
    }

    std::vector<std::string> parcours;
    auto& network = m_network;
    explore = [&network, &visited, &parcours, &explore](Node* x) {
        parcours.push_back(network.GetNodeName(x));
        if (visited[x]) {
            visited[x] = false;
            for (auto& n : network.GetAdjNodes(x)) {
                if (visited[n])
                    explore(n);
            }
        }
    };

    while (!pile.empty()) {
        auto n = pile.back();
        pile.pop_back();
        if (visited[n]) {
            explore(n);
            composantesConnexes.push_back(parcours);
            parcours.clear();
        }
    }

    return composantesConnexes;
}
}  // namespace domain
}  // namespace reseau_interurbain
