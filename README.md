# VoteElectronique

Projet TER : Implémentation C++ d'un ensemble de protocoles sécurisés pour un système de vote électronique.

## Deadlines

- Scénario complet de votes, chiffrement, déchiffrement et publication des résultats au **15/04/2022** 
- Passage en déchiffrement à seuil (secrets partagés et algorithme de combinaison)
- Scénario complet présentable (avec ~10k votes) sans modèle client/serveur au **29/04/2022**
- Modèle client/serveur pour la simulation complète au **29/04/2022**

## 🔴 ToDo

### Hors chiffrement

- [x] Lecture du fichier config
- [x] `check_timestamp`
- [x] Confirmer le passage du Verifier en fonctions statiques
- [x] Publication des résultats (`transmit_results` de la nationale pour séparer les votes de la somme claire)
- [x] Ajouter un `int` pour la validité du vote dans le bulletin local
- [x] Modifier les sommes et produits de votes locaux pour ne pas prendre en compte les votes invalides
- [x] Modifier l'affichage des bulletins locaux
- [ ] Vérification des signatures des votes (à vérifier)


### Partie chiffrement et preuves

- [ ] Génération des clés
  - [ ] Génération prime et safe prime test
  - [x] Génération de PK et SK
- [x] Chiffrement (§ 10.2.1)
- [x] Preuve / vérification d'égalité des messages clairs (Zero-knowledge proof 3, § 10.3.3)
- [ ] Génération du challenge aléatoire e dans `[0, A[` (A est un entier de 80 bits d'après §1) (méthode `Verifier::get_challenge()`)
- [ ] Preuve de validité d'un vote (Zero-knowledge proof 2, § 10.3.2)
- [ ] Vérifications des preuves
- [ ] Méthode de comparaison des résultats après tally des autorités et ajout d'un checkmark sur le bulletinboard

### Déchiffrement et publication des résultats

- [x] Premier déchiffrement (sans shares ni combiner pour un scénario test)
- [x] Déchiffrement partagé (§ 10.2.1)
  - [ ] Génération d'une preuve de bon déchiffrement (Vk)
- [x] Algorithme de combinaison
- [ ] Faire fonctionner `transmit_results()` pour la publication des résultats (depuis la combinaison finale mod N de l'autorité nationale)
- [ ] Comprendre pourquoi le déchiffrement ne passe plus avec des p,q autre que 5,7

### Plus tard

- [x] Implémenter RSA pour la signature des votes
  - [x] Ajouter la clé publique de l'utilisateur au bulletin local
- [ ] Génération de certificats pour les pseudos de chaque votant(§ 10.4)
- [ ] Receipt-free property (§ 10.5)
- [ ] Rendre notre dossier exécutable statiquement (la librairie `jsoncpp` doit être avec le projet)
