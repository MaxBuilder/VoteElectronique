# VoteElectronique

Projet TER

***

## 🔴 ToDo

### Non dépendants de la partie chiffrement

- [x] Lecture du fichier config
- [x] `check_timestamp`
- [ ] Confirmer le passage du Verifier en fonctions statiques (et non plus en tant qu'objet à instancier)
- [ ] `check_complete_vote`
- [ ] `transmit_results` de la nationale pour séparer les votes de la somme claire
- [ ] Implémenter DSA pour la signature des votes 

### Partie chiffrement

- [ ] Génération des clés
  - [ ] Génération prime et safe prime test
- [ ] Chiffrement
- [ ] Preuve de validité d'un vote
- [ ] Preuve d'égalité entre chiffrés
- [ ] Vérifications des preuves (méthodes statiques Verifier)
- [ ] Déchiffrement (à seuil via Combiner)
- [ ] Publication des résultats (`transmit_results`)

### Plus tard

- [ ] Génération de certificats pour les pseudos de chaque votant(§ 10.4)

