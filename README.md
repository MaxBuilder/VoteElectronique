# VoteElectronique

Projet TER : Implémentation C++ d'un ensemble de protocoles sécurisés pour un système de vote électronique.

## Deadlines

- Scénario complet de votes, chiffrement, déchiffrement et publication des résultats au **15/04/2022** 
- Passage en déchiffrement à seuil (secrets partagés et algorithme de combinaison)
- Scénario complet présentable (avec ~10k votes) sans modèle client/serveur au **29/04/2022**
- Modèle client/serveur pour la simulation complète au **29/04/2022**

## 🔴 ToDo

### Non dépendants de la partie chiffrement

- [x] Lecture du fichier config
- [x] `check_timestamp`
- [x] Confirmer le passage du Verifier en fonctions statiques
- [x] Publication des résultats (`transmit_results` de la nationale pour séparer les votes de la somme claire)
- [ ] Vérification des signatures des votes
- [ ] Ajouter un `int` pour la validité du vote dans le bulletin local
- [ ] Modifier les sommes et produits de votes locaux pour ne pas prendre en compte les votes invalides
- [ ] Modifier l'affichage des bulletins locaux pour avoir cet aperçu :

```
Board de l'autorité locale n°[1,2] :
|    | Timest.  | Sig. | Validité
|  1 | 15:08:22 | 2297 | ✅
|  2 | 15:08:34 | 2983 | ✅
|  3 | 15:09:02 | 3434 | ❌ Invalid timestamp
|  4 | 15:09:49 | 0421 | ✅
|  5 | 15:10:38 | 3823 | ❌ Invalid vote proof```


### Partie chiffrement

- [ ] Génération des clés
  - [ ] Génération prime et safe prime test
  - [x] Génération de PK et SK
- [x] Chiffrement (§ 10.2.1)
- [ ] Preuve de validité d'un vote (§ 10.3.2)
- [ ] 🔴 Preuve d'égalité entre chiffrés (§ 10.3.3) (En cours)
- [ ] Vérifications des preuves (méthodes statiques Verifier)

### Déchiffrement

- [ ] Premier déchiffrement (sans shares ni combiner pour un scénario test)
- [ ] Déchiffrement partagé (§ 10.2.1)
  - [ ] Génération d'une preuve de bon déchiffrement (Vk)
- [ ] Algorithme de combinaison

### Plus tard

- [ ] Implémenter DSA pour la signature des votes (bibliothèque Crypto. à inclure)
  - [ ] Ajouter la clé publique de l'utilisateur au bulletin local
- [ ] Génération de certificats pour les pseudos de chaque votant(§ 10.4)
- [ ] Receipt-free property (§ 10.5)
- [ ] Rendre notre dossier exécutable statiquement (la librairie `jsoncpp` doit être avec le projet)
