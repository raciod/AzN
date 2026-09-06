# AzN

Lightweight C command-line tool for direct peer-to-peer file and text sharing over raw TCP sockets on Unix/Linux systems.

[English](#english) | [Français](#français)

---

## English

### Overview
AzN is a minimalist C program that transfers files or text directly between two machines without third-party dependencies or external servers. It uses standard POSIX TCP sockets and a custom header format (`TYPE/NAME/SIZE`) to negotiate transfers.

### Key Features
* **Zero External Dependencies:** Built with pure C and standard POSIX networking APIs.
* **Text & File Transfer:** Handles plain text messages and binary file streams seamlessly.
* **Custom Protocol Header:** Lightweight line-based metadata parsing before payload transmission.

### Prerequisites & Build

Ensure you have `gcc` and `make` installed.

```bash
make

```

### Usage

```bash
# Receiver (listen for incoming connection)
./main -r

# Sender (send text or a file path)
./main -s <RECEIVER_IP> "Hello from AzN"
./main -s <RECEIVER_IP> path/to/file.ext

```

#### Local Test

```bash
# Terminal 1 (Receiver)
./main -r

# Terminal 2 (Sender)
./main -s 127.0.0.1 testfile.txt

```

---

## Français

### Aperçu

AzN est un outil en ligne de commande écrit en C qui permet de transférer du texte ou des fichiers directement entre deux machines, sans dépendances externes ni serveur tiers. Il s'appuie sur les sockets TCP POSIX et un format d'en-tête personnalisé (`TYPE/NAME/SIZE`).

### Caractéristiques

* **Sans dépendances externes :** Développé en C pur avec les API réseau POSIX standard.
* **Support texte et fichier :** Gère l'envoi de messages texte bruts et de fichiers binaires.
* **Protocole personnalisé :** Analyse d'en-tête légère pour transférer les métadonnées avant les données.

### Compilation

Nécessite `gcc` et `make`.

```bash
make

```

### Utilisation

```bash
# Récepteur (en écoute)
./main -r

# Expéditeur (envoi de texte ou d'un fichier)
./main -s <IP_RECEPTEUR> "Message de test"
./main -s <IP_RECEPTEUR> chemin/vers/fichier.ext

```

#### Test en local

```bash
# Terminal 1 (Récepteur)
./main -r

# Terminal 2 (Expéditeur)
./main -s 127.0.0.1 testfile.txt

```

---

## Project Structure / Structure du Projet

```text
AzN/
├── src/
│   ├── sender.c     — Socket creation, connection setup, and sending loop
│   ├── receiver.c   — Port binding, socket listening, and receiving loop
│   └── header.c     — Header construction and line-by-line parsing
├── include/
│   ├── sender.h
│   ├── receiver.h
│   └── header.h
├── main.c           — CLI entry point and flag parsing (-s / -r)
└── Makefile

```

Whenever you're ready, share the details for your **second** and **third** projects, and I'll generate their READMEs in the exact same format.

```
