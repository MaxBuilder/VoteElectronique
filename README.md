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
- [x] Vérification des signatures des votes
- [ ] Modifier l'affichage des bulletins board :
  - [ ] Retirer l'affichage des votes et valeurs trop grandes
  - [ ] Garder dans la ligne sums les résultats mod N + une checkmark pour montrer qu'elles sont égales + le fait que le produit est calculé et prêt à être transférer
  - [ ] Rendre le tout compréhensible et léger pour un scénario simulation 
- [ ] Supprimer la classe Client et créer une superclasse pour contenir l'ensemble des autorités et les méthodes Client (Sign et Vote)
- [ ] Créer un scénario présentable sans modèle client/serveur
 
### Partie chiffrement et preuves

- [x] Génération des clés
  - [x] Génération prime et safe prime test
  - [x] Génération de PK et SK
- [x] Chiffrement (§ 10.2.1)
- [x] Preuve / vérification d'égalité des messages clairs (Zero-knowledge proof 3, § 10.3.3)
- [ ] Génération du challenge aléatoire e dans `[0, A[` (A est un entier de 80 bits d'après §1) (méthode `Verifier::get_challenge()`)
- [ ] Preuve de validité d'un vote (Zero-knowledge proof 2, § 10.3.2)
- [ ] Vérifications de la preuve
- [ ] Méthode de comparaison des résultats après tally des autorités et ajout d'un checkmark sur le bulletinboard

### Déchiffrement et publication des résultats

- [x] Premier déchiffrement (sans shares ni combiner pour un scénario test)
- [x] Déchiffrement partagé (§ 10.2.1)
  - [ ] Génération d'une preuve de bon déchiffrement (Vk)
  - [ ] Vérification des preuves : t+1 bons déchiffrement nécessaires à la combinaison
- [x] Algorithme de combinaison
- [x] Faire fonctionner `transmit_results()` pour la publication des résultats (depuis la combinaison finale mod N de l'autorité nationale)
- [x] Comprendre pourquoi le déchiffrement ne passe plus avec des p,q autre que 5,7
- [ ] S'assurer que le produit des votes chiffrés se fait sans aucun modulo ; comment faire pour de grands nombres ?

### Plus tard

- [x] Implémenter RSA pour la signature des votes
  - [x] Ajouter la clé publique de l'utilisateur au bulletin local
- [ ] Génération de certificats pour les pseudos de chaque votant (§ 10.4)
- [ ] Receipt-free property (§ 10.5)
- [x] Rendre notre dossier exécutable statiquement (la librairie `jsoncpp` doit être avec le projet)
- [ ] The commitments can be replaced by their hash values (§ 6)
