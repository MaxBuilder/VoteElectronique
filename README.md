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
- [ ] Partie client : génération de clés de signature des votants (certificats), DSA ?

### Partie chiffrement pour débloquer le reste

- [ ] Génération des clés
  - [ ] Génération prime et safe prime test
- [ ] Chiffrement
- [ ] Into preuves, vérifications, déchiffrement, etc.

### Partie BulletinBoard – Version 18.02.22

- [ ] Revérifier que la clé publique de Bulletin est dans le bon format (selon l'algo de signature).
- [ ] Inclure Verifier dans BulletinBoard.
- [x] MakeTally dans les différents centres.
