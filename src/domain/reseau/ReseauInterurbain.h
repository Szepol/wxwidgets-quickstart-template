/*****************************************************************//**
 * \file    ReseauInterurbain.h
 * \brief   Representation of a Interurban network, can find the shortest
 * path between each station (node).
 * \author  Szepol
 * \date    May 2022
 * \license This project is released under MIT license.
 *********************************************************************/

#pragma once

#include <domain/reseau/Graph.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <climits>
#include <map>
#include <list>

namespace reseau_interurbain
{
namespace domain
{
struct Chemin
{
	std::vector<std::string> listeVilles;

	float dureeTotale;
	float coutTotal;
	bool reussi;
};

class ReseauInterurbain {

public:
	ReseauInterurbain(std::string p_nodeName, int p_x, int p_y, std::string p_networkName);
	~ReseauInterurbain();

	Chemin rechercheCheminDijkstra(const std::string& origine, const std::string& destination, bool dureeCout) const;

	std::vector<std::vector<std::string>> algorithmeKosaraju();

private:

	Graph m_network;
	std::string m_networkName;

};
} // namespace domain
} // namespace reseau_interurbain
