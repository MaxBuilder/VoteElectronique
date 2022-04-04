# VoteElectronique

Projet TER

***

## 🔴 ToDo

### Non dépendants de la partie chiffrement

- [x] Lecture du fichier config
- [x] `check_timestamp`
- [ ] Confirmer le passage du Verifier en fonctions statiques (et non plus en tant qu'objet à instancier)
- [ ] `check_complete_vote`
- [ ] Publication des résultats (`transmit_results` de la nationale pour séparer les votes de la somme claire)
- [ ] Implémenter DSA pour la signature des votes (bibliothèque Crypto. à inclure)
- [ ] Vérification des signatures des votes

### Partie chiffrement

- [ ] Génération des clés
  - [ ] Génération prime et safe prime test
  - [x] Génération de PK et SK
- [ ] Chiffrement (§ 10.2.1)
- [ ] Preuve de validité d'un vote (§ 10.3.2)
- [ ] Preuve d'égalité entre chiffrés (§ 10.3.3)
- [ ] Vérifications des preuves (méthodes statiques Verifier)

### Déchiffrement

- [ ] Premier déchiffrement (sans shares ni combiner pour un scénario test)
- [ ] Déchiffrement partagé (§ 10.2.1)
  - [ ] Génération d'une preuve de bon déchiffrement (Vk)
- [ ] Algorithme de combinaison 

### Plus tard

- [ ] Génération de certificats pour les pseudos de chaque votant(§ 10.4)
- [ ] Rendre notre dossier exécutable statiquement (la librairie `jsoncpp` doit être avec le projet) 

