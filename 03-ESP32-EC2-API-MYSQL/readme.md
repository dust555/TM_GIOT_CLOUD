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

## aanmaken database en tabel in mysql
Ga in de mysql cli
```
sudo mysql
```
- gebruik het bestand sql.txt om een databank, gebruiker en tabel aan te maken

## connectie met mysql testen
- wijzig de gegevens in het bestand secrets.php
- plaats het bestand secrets.php mysql_connect.php en test.php in /var/www/html
- plaats de bestanden mockapi.php, api.php en list.php in /var/www/html
- Wijzig de tabelnaam in mockapi.php, api.php en list.php naar de naam van jouw tabel
- mockapi.php zal een random waarde in de databank zetten wanneer je deze pagina opent
- list.php toont de inhoud van de databank

## ESP temperatuur in databank
- voeg een https endpoint toe aan de rule die luistert naar jouw topic
- voeg in het https endpoint het webadres naar api.php
- voeg bij headers alle velden die je publiceert in de vorm van: Key: Temperature, Value: ${temperature}
- Bevestig het https endpoint (onder menupunt Act - Destinations) door de token op te zoeken in de apache logfiles: /var/log/apache2/access.log
```
tail /var/log/apache2/access.log
```

## test
- open de pagina list.php om te kijken of je 

## troubleshoot
- pas in het bestand /etc/php/7.4/apache2/php.ini de lijn "display_errors = off" naar "display_errors = on". Herstart apache met het volgende commando
```
sudo systemctl restart apache2
```
- indien de waarden niet binnen komen kan je bij je rule een error actie toevoegen. Voeg bijvoorbeeld s3 bucket toe om de error messages te zien