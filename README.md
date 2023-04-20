# info-f209-gr5-2022

## Dates importantes
 -[X] **Remise _SRD_** : Lundi 19 Décembre 23h59  
 -[X] **Remise version _terminal_**: Vendredi 3 Mars 23h59  
 -[ ] **Remise version _graphique_**: Vendredi 21 Avril 23h59

## Membres du groupe
- Loïc Blommaert
- Hugo Charels
- Yacoub Lahdo
- Rémy Ryckeboer
- Bao Tran
- Hà Uyên Tran
- Joachim Violon

## Infos cours

**Cours** : INFO-F-209  
**Nom** : Projet d'année 2  
**Université** : ULB  
**Asstistant responsable** : Nil Lojo Fernandez


# Capitali$t menu principal

Capitali$t est un jeu utilisant le modèle client-serveur. Chaque utilisateur doit avant de pouvoir jouer se créer un compte 
auquel il pourra par la suite se connecter. Une fois connecté à son compte l'utilisateur à accès à plusieurs choix :
- Créer une partie
- Rejoindre une partie
- Consulter le classement
- Gérer ses amis
- Envoyer des messages privés

## Connection
#### Se créer un compte
`/register [username] [password]`

#### Se connecter
`/login [username] [password]`

## Gestion partie
#### Créer une partie
`/create normal [startMoney] [maxPlayer] [maxHome] [maxHotel] [maxTimerForGame] [maxTimerForTurn]`  
`/create fast [startMoney] [maxPlayer] [maxHome] [maxHotel] [maxTimerForGame] [maxTimerForTurn]`

#### Rejoindre une partie
`/join [game_code]`

## Consulter le classement
#### Consulter sa propre position
`/rank pos`  
`/r pos`

#### Consulter le top 5
`/rank top`  
`/r top`

## Gérer ses amis
#### Envoyer une demande d'amis
`/friends add [username]`  
`/f add [username]`

#### Accepter/refuser une demande d'amis
`/friends {accept/refuse} [username]`  
`/f {accept/refuse} [username]`

#### Supprimer un amis
`/friends remove [username]`  
`/f remove [username]`  

#### Consulter sa liste d'amis
`/friends list`  
`/f list`

## Envoyer des messages

#### Envoyer
`/msg [username] [message]`  

#### Recevoir/voir les messages
`/msg show [username]`


# Capitali$t jeu

## Avant le début de la partie
#### Lancer la partie
`/start` -> Seul le créateur de la partie peut le faire

## Après le début de la partie lorsque c'est son tour

### Passer en mode construction et construire un bâtiment
`/build` -> `/select [propriété]`

### Passer en mode vente et vendre un bâtiment
`/sell` -> `/select [propriété]`

### Passer en mode hypothèque et hypothéquer une propriété
`/mortgage` -> `/select [propriété]`

### Passer en mode rachat d'hypothèque et racheter une propriété
`/liftMortgage` -> `/select [propriété]`

### Passer en mode échange et procéder à un échange avec un autre joueur
`/exchange` -> `/trade [propriété] [somme_proposé]`  

Le joueur possédant la propriété souhaité, aura **15 secondes** pour accepter ou refuser l'offre.  
`/accept` ou `/refuse`

### Sortir d'un mode : construction, vente, hypothèque, rachat, échange
`/leave`

### Lancer les dés
`/roll`

## Après le début de la partie lorsque ce n'est pas son tour

### Accepter / refuser un échange
`/accept`  
`/refuse`

## Quitter une enchère ou enchérir 
`/out`
`/bid [somme_proposé]`







