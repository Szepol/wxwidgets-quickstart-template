/**
 * \file ReseauInterurbain.h
 * \brief Gestion d'un réseau de transport interurbain.
 * \author IFT-2008
 * \version 0.1
 * \date mars 2021
 *
 *  Travail pratique numéro 2
 *
 */

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
/**
 * \struct Chemin
 * \brief Structure utilise pour l'algorithme de dijsktra
 *
 *      L'algorithme de dijsktra utilise cette structure pour savoir si il existe un chemin possible entre le point d'origine
 *      et le point assigner a la structure, la structure contient une trace du chemin et le cout / la duree total(e) du deplacement.
 *
 * @tparam std::vector<std::string> <b>listeVilles</b> Contient la trace du chemin initiale jusqu'au point assigner au chemin coutnat
 * @tparam float <b>dureeTotale</b> Correspond a la duree totale du trajet en heures
 * @tparam float <b>coutTotal</b> Correspond au cout total en dollars du chemin entre la ville de depart et la ville de destination
 * @tparam bool <b>reussi</b> Un booleen qui vaut true si le chemin a ete trouve, false sinon
 */
struct Chemin
{
	//listeVilles doit contenir la liste des villes formant le chemin
	//La ville de départ du chemin correspond à l'élément d'indice 0 du vecteur
	//la ville d'arrivée correspond au dernier élément du vecteur.
	std::vector<std::string> listeVilles;

	float dureeTotale;		// Durée totale du trajet en heures
	float coutTotal;			// Cout total en dollars du chemin entre la ville de départ et la ville de destination
	bool reussi;				// Un booléen qui vaut true si le chemin a été trouvé, false sinon
};

/**
 * \class ReseauInterurbain
 * \brief Classe representant un Reseau interurbain
 *
 *      Permet de modeliser un reseau de transport interurbain a l'aide d'un graphe
 *      (oriente pondere et etiquete) constitue d'un ensemble de villes (sommets du graphe)
 *      et d'un ensemble de trajets de bus reliant ces villes (arcs du graphe). On peut retrouver
 *      sur chacun des trajets du reseau de transport interurbain deux types de ponderations (soit le cout et la duree).
 *      La classe permet de retrouver le plus court chemin entre deux ville selon le cout ou la duree a l'aide de l'algorithme
 *      de dijsktra. Elle permet aussi de retrouver tous les composantes fortement connexe a l'aide de l'algorithme de kosaraju.
 *      <br><b>Attributs:</b><br>
 *      Graphe <em>unReseau</em> Correspond au graphe du reseau interurbains <br>
 *      std::string <em>nomReseau</em> Le nom du reseau interurbain <br>
 */
class ReseauInterurbain {

public:

	// Constructeur
	ReseauInterurbain(std::string p_nodeName, int p_x, int p_y, std::string p_networkName);

	// Destructeur
	~ReseauInterurbain();

	// Charger un réseau à partir d'un fichier texte en entrée (voir format du fichier dans l'énoncé du Tp).
	// Construit un réseau routier à partir d'une liste de villes ainsi que leurs liens.
	// fichierEntree est ouvert corectement. 
	// fichierEntree n'est pas fermé par la fonction.
	// Exception logic_error si fichierEntree n'est pas ouvert correctement.
	//void chargerReseau(std::ifstream& fichierEntree);

	// Trouve le plus court chemin entre une ville source et une ville destination en utilsiant l'algorithme de Dijkstra
	// si dureeCout = true, on utilise la durée comme pondération au niveau des trajets
	// si dureeCout = false, on utilise le coût (en $) comme pondération au niveau des trajets
	// Exception std::logic_error si origine et/ou destination absent du réseau
	Chemin rechercheCheminDijkstra(const std::string& origine, const std::string& destination, bool dureeCout) const;

	// Trouve l’ensemble des composantes fortement connexes en utilisant l'algorithme de Kosaraju
	// Retourne un vecteur de vecteurs de chaînes caractères. Chaque sous-vecteur représente une composante.
	std::vector<std::vector<std::string>> algorithmeKosaraju();

	//Vous pouvez ajoutez d'autres méthodes publiques si vous sentez leur nécessité

private:

	Graph m_network;			//Le type ReseauRoutier est composé d'un graphe
	std::string m_networkName;		// Le nom du reseau (exemple: Orleans Express)

};
} // namespace domain
} // namespace reseau_interurbain
