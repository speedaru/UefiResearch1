# UEFI Research — composants publics (uefi-research)

**Type :** dépôt public — éléments pédagogiques et utilitaires  
**Objectif :** partager des composants non sensibles d'un travail de recherche pré‑OS (implémentation d'une structure `String`, utilitaires de parsing/filesystem, exemples de techniques d'obfuscation de chaînes pour recherche/évaluation d'anti‑reverse).  
**Remarque importante :** le code complet du POC original contenant des parties potentiellement sensibles n'est **pas** publié ici. Ce dépôt est à but **éducatif / recherche** uniquement.

---

## Contenu du dépôt (fichiers laissés publiquement)

```
│ compile.bat
│ main.c # logique sensible enlevée (POC spoof retiré)
│ main.h
│ UefiResearch1.dec
│ UefiResearch1.dsc
│ UefiResearch1.inf
│
├───crypto
│     sha256.c
│     sha256.h
│     xor_str.cpp
│     xor_str.hpp
│     xor_str_export.h
│     xxtea.c
│     xxtea.h
│
├───structs
│     string.c
│     string.h
│
├───utils
│     filesystem.c
│     filesystem.h
│     parser.c
│     parser.h
│     str_ext.c
│     str_ext.h
```

### Description rapide des composants publics
- **`structs/string.c` / `structs/string.h`**  
  Implémentation d'une structure `String` adaptée à des environnements contraints. Montre l'allocation manuelle, les opérations de copie/concaténation et les checks basiques de taille. Valeur pédagogique : gestion mémoire manuelle et design d'API C pour code bas‑niveau.

- **`utils/str_ext.*`**  
  Fonctions utilitaires simples : `StrSubA` (extraction/sous‑chaîne) et `StrFindA` (recherche de caractères / sous‑chaînes). Outils d'accompagnement pour manipuler les chaînes implémentées ci‑dessus.

- **`utils/filesystem.*`**  
  Fonctions basiques pour lire des fichiers dans une application EFI. Fournit des helpers utiles pour prototyper/valider des comportements sans exécuter de code sensible en pré‑OS.

- **`crypto/*`**  
  - `sha256.*`, `xxtea.*` : fichiers issus de bibliothèques publiques (utilisés ici pour tests / prototypes). Voir la section “Attribution” plus bas.  
  - `xor_str.*` : composant de **string obfuscation** (technique de compilation/obfuscation simple visant à rendre l'analyse statique plus longue). **Usage :** recherche/expérimentation anti‑reverse uniquement. Ne doit pas être utilisé pour des activités malveillantes.

- **EDK2 / meta files** (`UefiResearch1.dsc`, `.inf`, `.dec`) et `compile.bat`  
  Fichiers de projet EDK2 / script de build indiqués pour reproduire un build de test local. **Important :** `main.c` a été nettoyé pour retirer la logique sensible du POC original. Ce dépôt ne contient pas le code d’installation ou les composants modifiant l’identité matérielle.

---

## Build / test (exemple) pour Windows avec MSVC
> Ces instructions servent à builder la partie démonstration / tests en environnement contrôlé. Ne pas utiliser pour déployer sur des systèmes de production ou pour des usages non-éthiques.

1. Cloner le dépôt :
```bash
git clone https://github.com/speedaru/UefiResearch1.git
cd UefiResearch1
edksetup.bat
cd UefiResearch1
compile.bat
```

le fichier .efi est maintenant disponible dans: Build\UefiResearch1\RELEASE_VS2022\X64\UefiResearch1.efi
pour lancer le fichier on peut utiliser un emulateur comme qemu ou le mettre sur une cle usb et démarer depuis
cette cle USB.

Limitations & disclaimers
But pédagogique uniquement. Le dépôt ne contient VOLONTAIREMENT pas les parties sensibles du POC original.

Ne pas utiliser ces composants pour contourner protections, masquer identifiants matériels ou pour toute activité illégale.

Le propriétaire du dépôt se réserve le droit de refuser l'accès au code complet à des demandes ne respectant pas un objectif académique/technique légitime.

Demande d'accès au code complet / revue technique
Le code complet du POC (contenant des composants non‑publics) est disponible uniquement pour revue technique sous NDA. Pour demander l'accès, merci d'envoyer une demande professionnelle à : ton.email@example.com (ou via le contact de mon profil GitHub). Indiquez le motif technique de la revue et l'organisation requérante.

Attribution
Certains fichiers cryptographiques (sha256.*, xxtea.*) proviennent de projets open‑source publics et sont inclus ici pour tests/validation. Voir les en‑têtes de fichiers et licences correspondantes pour les détails.

Toute réutilisation doit tenir compte des licences d'origine des composants inclus.

