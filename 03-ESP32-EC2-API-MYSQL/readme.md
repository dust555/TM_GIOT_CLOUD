# Werkwijze aanmaken https webserver

## EC2 aanmaken
	- T2.micro
	- Security group: ssh, http,https
	- Key downloaden

## Key omzetten
	- Puttygen openen
	- Load key: .pem die je gedownload hebt
	- Save private key: opslaan met dezelfde naam .ppk

## Inloggen op vm met putty
	- Ip adres is publiek adres van je EC2 instance
	- Onder ssh, auth de .ppk key selecteren
	- Gebruikersnaam: ubuntu

## Installeren apache2, php mysql

```
Apt update
Apt install apache2
Apt install php php-mysql
Apt install mysql-server
```


## Webserver testen
- publiek ip in browser in te geven
- Test.php pagina plaatsen in /var/www/html  
- Testen door publiekip/test.php in een browser in te geven


## Domainnaam aanvragen voor webserver
- Account aanmaken op noip
- Host aanmaken met publiek ip

## Webserver testen 
- .ddns.net domainnaam in te geven in browser

## certificaat aanvragen voor webserver
```
apt install certbot
apt install python3-certbot-apache
certbot --apache
```

## https webserver testen
- https webadres ingeven in browser

