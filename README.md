[![wakatime](https://wakatime.com/badge/github/Sala7-dine/Projet_Fin_SAS_Gestion_Des_Reclamations.svg)](https://wakatime.com/badge/github/Sala7-dine/Projet_Fin_SAS_Gestion_Des_Reclamations)
# 📁 Projet SAS : Gestion des Réclamations 📋
 
## 🌟 Introduction

Bienvenue dans le projet Fin SAS de gestion des réclamations ! Cette application console permet de gérer efficacement les réclamations des clients, de les traiter, de les modifier, et de générer des statistiques utiles. Ce Projet a été réalisé dans le cadre de la période de SAS à Youcode Nador 2023/2024, sous la supervision du formateur Hamza Bouchikhi.

---

## 📝 Contexte du Projet

L'application comprend un **Menu Principal** avec les fonctionnalités suivantes :

## 🎯 **Fonctionnalités principales :**

### 👥 **Gestion des utilisateurs :**

- **Création de compte utilisateur (Sign Up)**

  - 🔒 Longueur minimale du mot de passe : **8 caractères** 
  - 💡 Le mot de passe doit inclure :
    - 1 lettre majuscule
    - 1 lettre minuscule
    - 1 chiffre
    - 1 caractère spécial (ex. : !@#$%^&*)
  - ⚠️ Ne doit pas contenir le nom d'utilisateur

- **Connexion (Sign In)**

  - 🛑 Verrouillage du compte après plusieurs tentatives échouées
- **Rôles d'utilisateurs :**

  - **Administrateur** : Gestion complète (réclamations, utilisateurs, statistiques, rôles)
  - **Agent de réclamation** : Gérer les réclamations
  - **Client** : Soumettre et consulter ses réclamations

---

### 📝 **Gestion des réclamations :**

- **Ajouter une réclamation** :
  - 🎫 ID unique généré automatiquement
  - 🗂️ Motif, description, catégorie, et date ajoutée automatiquement
  - 🔄 Statut : En cours, résolu, rejeté
- **Afficher les réclamations** :
  - 🛡️ Accessible aux administrateurs et agents
  - 📋 Détails complets des réclamations
- **Modifier ou supprimer une réclamation** :
  - 🔧 Les administrateurs et agents peuvent modifier ou supprimer n’importe quelle réclamation
  - ⏳ Les clients peuvent modifier/supprimer leurs réclamations si elles sont non traitées et soumises il y a moins de 24 heures
- **Rechercher une réclamation** :
  - 🔍 Recherche par ID, nom de client, date, statut ou catégorie
- **Système de priorité** :
  - 🔝 Priorité attribuée automatiquement (basse, moyenne, haute) selon les mots-clés
  - 📊 Affichage trié par priorité (pour les administrateurs)

---

### 📊 **Statistiques et Rapports :**

- **Nombre total de réclamations**
- **Taux de résolution**
- **Délai moyen de traitement**
- **Rapport journalier** 

---

## ⚙️ Prérequis

- 🛠️ **GCC installé** (compilateur C)
- 💻 Un environnement de terminal sous Windows, Linux ou macOS

## 🪟 Compilation et Exécution sous Windows

1. Téléchargez et installez `gcc`.
2. Clonez ce dépôt dans votre répertoire local.
3. Naviguez vers le dossier du projet via le terminal ou l'invite de commandes.
4. Utilisez le script suivant pour compiler et exécuter le projet :

### 📜 Script de compilation

```cmd

gcc Gestion_des_reclamations.c -o Gestion_des_reclamations

``` 

🍏 Une fois la compilation réussie, exécutez le fichier généré :

 ./Gestion_des_reclamations ou bien Gestion_des_reclamations.exe

---

## 💡 **Technologies utilisées :**

- Langage : C
- Environnement : Visual studio code

---

## 📧 **Contact :**

Pour toute question ou amélioration, n’hésitez pas à me contacter à : **salahdaha7@gmail.com**

---

✨ **Merci d'avoir consulté le projet !** 🎉

---
