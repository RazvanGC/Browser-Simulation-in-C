Pentru implementare au fost definite doua structuri principale:
- Arbore binar: fiecare nod contine un nume (concatenat din numele nodurilor copil, daca este un nod de legatura) si o frecventa.
- Min-Heap: utilizat pentru a extrage rapid cei doi sateliti cu cele mai mici frecvente in procesul de construire a arborelui.


### Cerinta 1
Aceasta cerinta este implementata in `task1()` atunci cand `task == 1`.
- Se citesc satelitii (frecventa si nume) si se creeaza cate un nod pentru fiecare.
- Se insereaza toate nodurile in Min-Heap.
- Se combina repetat cei doi sateliti cu frecvente minime intr-un nod parinte, al carui nume este concatenarea numelor copiilor, iar frecventa este suma lor.
- Se continua pana ramane un singur nod – radacina.
- Arborele este afisat pe niveluri cu `write_bfs()`.

### Cerinta 2
Implementata in `task1()` cu `task == 2`, care apeleaza `task2()`.
- Fiecare codificare binara este parcursa de la radacina arborelui.
- La `0` se merge in stanga, la `1` in dreapta.
- Cand se ajunge la o frunza, se afiseaza numele satelitului si se reia din radacina.

### Cerinta 3
Implementata in `task1()` cu `task == 3`, care apeleaza `task3()`.
- Se genereaza codificarile binare pentru fiecare satelit frunza folosind DFS (`generate_codes()`).
- Se citeste o lista de sateliti si se afiseaza codul corespunzator fiecaruia.

### Cerinta 4
Implementata in `task1()` cu `task == 4`, care apeleaza `task4()`.
- Se foloseste o functie `lca()` recursiva pentru a determina stramosul comun pentru doua noduri.
- Pentru mai multi sateliti, se aplica `lca()` in lant cu `multiple_lca()`.

### `binary_tree.c` si `binary_tree.h`
**Structuri:**
- `satelite`: structura care contine frecventa (`fq`) si numele (`name`) unui satelit.
- `node`: nod al arborelui binar care contine un pointer la un `satelite`, si doi pointeri catre copii (`left`, `right`).
- `binary_tree`: contine radacina arborelui (`root`).
**Functii:**
- `create_node(node *sat_left, node *sat_right, satelite *sat_new)`: creeaza un nou nod cu doi copii si datele unui nou satelit.
- `free_tree(node *root)`: elibereaza recursiv memoria arborelui.
- `write_bfs(node *root, FILE *fout, int n)`: afiseaza arborele pe niveluri in fisierul de iesire.

### `min_heap.c` si `min_heap.h`
**Structuri:**
- `heap_t`: structura heap ce contine bufferul de date, dimensiunea, capacitatea si comparatorul.
**Functii:**
- `min_heap_create()`: initializeaza un heap cu dimensiune si comparator date.
- `heap_insert()`: insereaza un element in heap.
- `heap_top()`: returneaza elementul minim fara sa-l elimine.
- `heap_pop()`: elimina elementul minim si rearanjeaza heap-ul.
- `heap_empty()`: verifica daca heap-ul este gol.
- `heap_free()`: elibereaza memoria alocata.

### `task1.c` si `task1.h`
**Functii:**
- `task1(FILE *fin, FILE *fout, int task)`: functie centralizata care rezolva toate cerintele:
  - `task == 1`: construieste arborele binar si afiseaza pe niveluri.
  - `task == 2`: decodeaza codificari binare.
  - `task == 3`: genereaza codificari pentru sateliti.
  - `task == 4`: determina stramosul comun.
Aceasta abordare a fost aleasa deoarece toate cerintele depind de arborele construit la cerinta 1.

### `task2.c` si `task2.h`
**Functii:**
- `task2(FILE *fin, FILE *fout, void *root)`: parcurge arborele conform codificarilor binare si afiseaza satelitii corespunzatori.

### `task3.c` si `task3.h`
**Functii:**
- `task3(FILE *fin, FILE *fout, void *root, int size)`: creeaza codurile binare pentru satelitii frunza si le afiseaza pentru o lista data.

### `task4.c` si `task4.h`
**Functii:**
- `task4(FILE *fin, FILE *fout, void *root)`: determina stramosul comun pentru o lista de sateliti folosind `lca()` si `multiple_lca()`.

### `main.c`
**Functiai
- `main()`**: verifica argumentele din linia de comanda si apeleaza `task1()` cu un cod care indica ce cerinta trebuie rezolvata (`-c1`, `-c2`, `-c3`, `-c4`).
