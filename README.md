# ReseauInterurbain

*ReseauInterurbain* est une application graphique multiplateforme qui permet à l'utilisateur de créer un réseau de transport interurbain et d'effectuer des simulations. Le but de l'application est de pouvoir visualiser differentes implémentations d'algorithmes du plus court chemin.

## Installation

### Binaire

En attente

### Source

#### Dépendances :
* [wxWidgets-3.1.5](https://www.wxwidgets.org/)


#### Windows - Visual Studio 2019

Pour installer wxWidgets en utilisant le gestionnaire de dépendances [vcpkg](https://github.com/Microsoft/vcpkg) :

```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg integrate install
vcpkg install wxwidgets
```
Pour compiler le projet : 

Simplement ouvrir le fichier `build\msw\ReseauInterurbain.sln`, sélectionner la configuration appropriée et construire la solution.

## License
[MIT](https://github.com/Szepol/ReseauInterurbain/blob/main/LICENSE)