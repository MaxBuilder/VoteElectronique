# VoteElectronique

Projet TER : Implémentation C++ d'un ensemble de protocoles sécurisés pour un système de vote électronique.

## Deadlines

- Scénario complet de votes, chiffrement, déchiffrement et publication des résultats au **15/04/2022**
- Passage en déchiffrement à seuil (secrets partagés et algorithme de combinaison)
- Scénario complet présentable (avec ~10k votes) sans modèle client/serveur au **29/04/2022**
- Modèle client/serveur pour la simulation complète au **29/04/2022**

## 🔴 ToDo

- [x] Supprimer la classe Client et créer une superclasse pour contenir l'ensemble des autorités et les méthodes Client (Sign et Vote)
- [ ] Modifier l'affichage des bulletins board :
  - [ ] Retirer l'affichage des votes et valeurs trop grandes
  - [ ] Garder dans la ligne sums les résultats mod N + une checkmark pour montrer qu'elles sont égales + le fait que le produit est calculé et prêt à être transférer
  - [ ] Rendre le tout compréhensible et léger pour un scénario simulation
- [ ] Implémenter une façon de générer les clés en amont et de lancer la simu avec un fichier de clés
- [ ] Créer un autre scénario pour tester le retrait des votes frauduleux (par timestamp, signature, preuve de vote et preuve d'égalité)
- [ ] Créer un scénario présentable sans modèle client/serveur

### Partie chiffrement et preuves

- [x] Génération des clés
  - [x] Génération prime et safe prime test
  - [x] Génération de PK et SK
- [x] Chiffrement (§ 10.2.1)
- [x] Preuve / vérification d'égalité des messages clairs (Zero-knowledge proof 3, § 10.3.3)
- [x] Génération du challenge aléatoire e dans `[0, A[` (A est un entier de 80 bits d'après §1) (méthode `Verifier::get_challenge()`)
- [ ] Preuve de validité d'un vote (Zero-knowledge proof 2, § 10.3.2)
- [ ] Vérifications de la preuve
- [ ] Méthode de comparaison des résultats après tally des autorités et ajout d'un checkmark sur le bulletinboard

### Déchiffrement et publication des résultats

- [x] Premier déchiffrement (sans shares ni combiner pour un scénario test)
- [ ] Génération d'une preuve de bon déchiffrement (Vk)
- [ ] Vérification des preuves : t+1 bons déchiffrement nécessaires à la combinaison
- [x] Déchiffrement partagé (§ 10.2.1)
- [x] Algorithme de combinaison
- [x] Méthode `transmit_results()` d'extraction des résultats depuis la combinaison finale mod N de l'autorité nationale (somme claire)  pour la publication des résultats
- [ ] Vérifier que les tailles de clés sont assez grande pour un nombre important de vote
- [ ] Fixer la modification du nombre de serveurs pour le combiner

### Plus tard

- [x] Implémenter RSA pour la signature des votes
  - [x] Ajouter la clé publique de l'utilisateur au bulletin local
- [ ] Génération de certificats pour les pseudos de chaque votant (§ 10.4)
- [ ] Receipt-free property (§ 10.5)
- [x] Rendre notre dossier exécutable statiquement (la librairie `jsoncpp` doit être avec le projet)
- [ ] The commitments can be replaced by their hash values (§ 6)
