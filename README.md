# Progetto di Monitoraggio della Temperatura

## Obiettivo
Lo scopo di questo progetto è quello di creare un sistema di monitoraggio della temperatura utilizzando un microcontrollore ESP32, un server Flask e un sito HTML/JavaScript per la rappresentazione dei dati raccolti in una tabella. L'obiettivo finale è quello di ottenere un sito web che visualizzi i dati di temperatura in tempo reale provenienti dall'ESP32 attraverso una connessione Wi-Fi.

## Materiale
1. ESP32
2. Sensore di temperatura
3. Cavi di collegamento
4. Computer con Arduino IDE, il server Python e il sito web
5. Accesso a Internet

## Procedimento

### 1. Configurazione dell'ESP32 con Arduino
Tramite l'IDE Arduino sul computer, abbiamo configurato l'ESP32. Abbiamo poi scritto un programma in Arduino che collega l'ESP32 alla rete della scuola tramite il modulo Wi-Fi integrato, legge i dati dal sensore di temperatura e li invia a un server Flask.

### 2. Creazione del Server Flask
Utilizzando Python, abbiamo creato un server in grado di ricevere e registrare in un file CSV i dati inviati dall'ESP32 e di inviarli al sito web quando arriva la richiesta.

### 3. Sviluppo del Sito Web con HTML/JavaScript
Dopo il server, abbiamo creato il sito che utilizzeremo per visualizzare le temperature registrate dall'ESP32. Tramite JavaScript effettuiamo una richiesta al server Flask per ottenere i dati di temperatura, dopodichè creiamo la tabella con questi dati. La tabella si aggiorna dinamicamente quando arriva una nuova temperatura registrata.

## Conclusioni
Questo progetto ha dimostrato come sia possibile utilizzare l'ESP32 per creare un sistema di monitoraggio della temperatura in tempo reale. La combinazione di tutti gli strumenti utilizzati ha permesso di creare un sistema efficiente e flessibile, che potrebbe essere esteso e adattato per monitorare altre grandezze fisiche o parametri ambientali oltre che essere intercambiabile con gli altri progetti realizzati. L'esperienza acquisita durante lo sviluppo di questo progetto potrebbe essere utilizzata per creare soluzioni simili in ambiti come l'automazione domestica.

## Crediti
Questo progetto è stato sviluppato da Bennella Alessandro, Caricari Lorenzo e Gentile Francesco come parte del progetto interdisciplinare di TPS, TLC e Informatica.
