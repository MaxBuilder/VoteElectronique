# VoteElectronique
Projet TER

***

## 🔴 ToDo

### Non dépendants de la partie chiffrement :

- [x] Lecture du fichier config
- [ ] `check_timestamp`, `check_complete_vote`
- [ ] `transmit_results` de la nationale pour séparer les votes de la somme claire
- [ ] Partie client : génération de clés de signature des votants (certificats), DSA ?

### Partie chiffrement pour débloquer le reste :**

- [ ] Génération des clés
    - [ ] Génération prime et safe prime test 
- [ ] Chiffrement
- [ ] Into preuves, vérifications, déchiffrement, etc.

### Partie BulletinBoard – Version 18.02.22

- [ ] Revérifier que la clé publique de Bulletin est dans le bon format (selon l'algo de signature).
- [ ] Inclure Verifier dans BulletinBoard.
- [x] MakeTally dans les différents centres.
