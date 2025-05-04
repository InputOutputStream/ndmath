# 🧮 `ndmath` - Numerical & Data Math Library

`ndmath` est une bibliothèque en C pour la manipulation simple et efficace de tableaux numériques (`ndarray_t`), avec une attention particulière à la **génération aléatoire**, **l’indépendance de l’état**, et à la **copie explicite des données** (pas de vues partagées). Elle est conçue pour être **portable**, **légère**, et **intégrable facilement dans d'autres projets** via `libmath.so` ou `libmath.a`.

---

## 🔧 Compilation & Linking

### 1. Générer la bibliothèque

```bash
# Compilation statique
gcc -c -fPIC ndmath/array.c ndmath/random.c ndmath/helper.c
ar rcs libndmath.a array.o random.o helper.o

# Compilation dynamique
gcc -shared -o libndmath.so ndmath/array.c ndmath/random.c ndmath/helper.c
```

### 2. Utilisation dans un projet externe

#### a. Inclure l’en-tête

```c
#include <ndmath/array.h>
#include <ndmath/random.h>
#include <ndmath/helper.h>
```

#### b. Compiler et lier

```bash
gcc -I./ndmath main.c -L. -lndmath -lm
```

#### c. Exécution avec la bibliothèque dynamique

```bash
export LD_LIBRARY_PATH=.
./a.out
```

---

## 🧠 Principes fondamentaux

* Toutes les fonctions de génération (aléatoire ou transformation) retournent **une copie allouée dynamiquement** (`ndarray_t`), jamais une vue ou un alias.
* Gestion manuelle de la mémoire. Libérez les tableaux avec `free_array()` ou équivalent.
* Support multi-plateforme (Unix/Windows avec adaptation mineure).
* Utilise un **générateur congruent linéaire 64-bit** (LCG) pour des séquences pseudo-aléatoires contrôlées via `seed`.

---

## 📚 Fonctions disponibles

### `rand_array(int max, int min)`

Génère un tableau 2D aléatoire avec des entiers dans l'intervalle `[min, max]`.
**Dimensions aléatoires** entre `MIN_RAND` et `MAX_RAND`.

```c
ndarray_t a = rand_array(20, 5);
```

### `randu(size_t rows, size_t cols, size_t seed)`

Retourne un tableau rempli de **réels uniformes dans `[0, 1)`**.

```c
ndarray_t u = randu(3, 3, 12345);
```

### `randn(size_t rows, size_t cols, size_t seed)`

Retourne un tableau rempli de **réels suivant une loi normale standard (μ=0, σ=1)** via la méthode Box-Muller.

```c
ndarray_t n = randn(4, 4, 777);
```

### `randint(size_t rows, size_t cols, int max, int min, size_t seed)`

Retourne un tableau d'entiers uniformes dans `[min, max]`.

```c
ndarray_t ri = randint(5, 5, 100, 10, 42);
```

### `shuffle(ndarray_t *mat, size_t seed)`

Retourne une **copie du tableau** dont les valeurs ont été mélangées aléatoirement.

```c
ndarray_t s = shuffle(&a, 99);
```

### `randperm(size_t n, uint64_t seed)`

Génère une **permutation aléatoire** des entiers de `0` à `n-1` (comme `numpy.random.permutation(n)`).

```c
ndarray_t p = randperm(10, 987);
```

---

## 📦 Exemple complet d’utilisation

```c
#include <ndmath/array.h>
#include <ndmath/random.h>

int main() {
    ndarray_t u = randu(3, 3, 2025);
    print_array(&u);
    free_array(&u);

    ndarray_t r = randint(2, 2, 10, 1, 42);
    print_array(&r);
    free_array(&r);

    return 0;
}
```

---

## 💡 Remarques importantes

* `array(rows, cols)` alloue un tableau 2D (`ndarray_t`) initialisé à 0.
* `copy(ndarray_t *src)` retourne une copie profonde.
* Aucune fonction ne modifie en place. Il n’y a **jamais d’effets de bord** : à chaque appel, une nouvelle structure est renvoyée.
* La structure `ndarray_t` contient :

  ```c
  typedef struct {
      double **data;
      size_t shape[2]; // [rows, cols]
  } ndarray_t;
  ```

---

## 🧪 Tests

Ajoute des tests unitaires dans `test/` et compile avec :

```bash
gcc -I./ndmath -o test_rand test/test_rand.c -L. -lndmath -lm
```

---

## 🧹 Nettoyage

```bash
rm -f *.o libndmath.a libndmath.so
```

---

Excellent retour ! Ajoutons une **section complète et détaillée** sur l'intégration de `ndmath` dans un projet tiers. On va couvrir **les trois méthodes classiques** : linking statique, linking dynamique, et intégration directe du code source.

---

## 🔗 Intégration dans un projet tiers

Tu veux utiliser `ndmath` dans un autre projet ? Voici **trois façons de faire**, selon ton environnement, tes besoins en portabilité, et ton goût pour le statique ou le dynamique.

---

### 🧱 1. Utilisation **statique** (`libndmath.a`)

> Idéal si tu veux **tout embarquer** dans ton binaire final, sans dépendance externe.

#### Étapes :

1. **Compiler la bibliothèque :**

```bash
gcc -c -fPIC ndmath/*.c
ar rcs libndmath.a *.o
```

2. **Inclure les headers dans ton projet :**
   Dans ton fichier source :

```c
#include "ndmath/array.h"
#include "ndmath/random.h"
#include "ndmath/helper.h"
```

3. **Compiler ton projet avec la lib :**

```bash
gcc -I./ndmath main.c -L. -lndmath -lm
```

4. **Exécuter :**
   Pas besoin de `LD_LIBRARY_PATH`, tout est lié statiquement.

---

### 🧪 2. Utilisation **dynamique** (`libndmath.so`)

> Plus souple, plus légère. Permet des mises à jour de la lib sans recompiler ton projet.

#### Étapes :

1. **Compiler en lib partagée :**

```bash
gcc -fPIC -shared -o libndmath.so ndmath/*.c
```

2. **Inclure les headers comme ci-dessus.**

3. **Compiler ton code :**

```bash
gcc -I./ndmath main.c -L. -lndmath -lm
```

4. **Exécuter avec LD\_LIBRARY\_PATH :**

```bash
export LD_LIBRARY_PATH=.
./a.out
```

5. *(Facultatif)* Installer globalement :

```bash
sudo cp libndmath.so /usr/local/lib/
sudo ldconfig
```

---

### 📦 3. Intégration **directe** des sources

> Option "brute force" : embarquer tout le code `.c` et `.h` directement dans ton projet.

#### Étapes :

1. Copie le dossier `ndmath/` dans ton projet.
2. Dans ton `main.c` :

```c
#include "ndmath/array.h"
#include "ndmath/random.h"
#include "ndmath/helper.h"
```

3. Compile avec tous les `.c` :

```bash
gcc main.c ndmath/*.c -lm
```

---

### 💼 Exemple avec Makefile

Voici un `Makefile` type pour un projet externe :

```makefile
CC = gcc
CFLAGS = -I./ndmath -Wall -O2
LDFLAGS = -L. -lndmath -lm

SRC = main.c
OBJ = $(SRC:.c=.o)

all: main

main: $(OBJ)
	$(CC) $(OBJ) -o main $(CFLAGS) $(LDFLAGS)

clean:
	rm -f main *.o
```

---

### 📁 Organisation suggérée pour ton projet externe

```
my_project/
├── ndmath/               # Copié depuis le dépôt officiel
│   ├── array.c
│   ├── random.c
│   ├── ...
├── libndmath.a           # ou .so si tu préfères le dynamique
├── main.c
├── Makefile
```

---

### 🔎 Pour vérifier que tout fonctionne

```bash
nm -g libndmath.a | grep randu
# ou
nm -D libndmath.so | grep randu
```

Tu devrais voir : `randu`, `randn`, etc. => la lib est bien générée.

---

## ⚠️ Avertissements

* Pour garantir un comportement déterministe, toujours **initialiser les fonctions avec une `seed`**.
* **Pas de gestion mémoire automatique** : toujours appeler `clean(array_name, NULL)` pour éviter les fuites.

