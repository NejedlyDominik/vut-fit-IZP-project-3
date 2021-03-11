/**
 * @file proj3.h
 * @mainpage Projekt 4 - Dokumentace zdrojovych kodu
 * @brief Dokumentace ke 3. projektu (Jednoducha shlukova analyza)
 * @author Dominik Nejedly
 * @date 10/12/2018
 */

/**
 * @brief Struktura objektu nesouci jeho unikatni oznaceni a souradnice ve dvourozmernem (2D) prostoru.
 */

struct obj_t {
    int id;     /**< jednoznacny celociselny identifikator */
    float x;    /**< souradnice osy x */
    float y;    /**< souradnice osy y */
};

/**
 * @brief Struktura shluku objektu nesouci k sobe prirazene objekty.
 */

struct cluster_t {
    int size;           /**< pocet objektu, ktere jsou aktualne ve shluku */
    int capacity;       /**< aktualni maximalni kapacita shluku (pocet objektu, pro ktere je aktualne alokovana pamet) */
    struct obj_t *obj;  /**< ukazatel na pole objektu daneho shluku*/
};

/**
 * @defgroup shluk Operace se shluky
 * @{
 */

/**
 * Funkce inicializuje shluk 'c' a alokuje pamet pro jeho kapacitu objektu "cap".
 *
 * @pre Ukazatel na shluk 'c' (1. parametr) nesmi byt roven NULL.
 * @pre Kapacita "cap" (2. parametr) nesmi byt mensi nez 0.
 *
 * @post Shluk 'c' je inicializovan a je pro nej alokovana pamet odpovidajici kapacite "cap" (2. parametr).
 *
 * @param c - shluk urceny k inicializaci
 * @param cap - kapacita nove inicializovaneho shluku - pocet objektu, ktere ma dany shluk pojmout(pro ktere ma mit shluk alokovanou pamet)
 *
 * @note Pokud je ukazatel na shluk 'c' roven NULL nebo je kapacita "cap" mensi nez 0, funkce neprovede vubec nic.
 *
 * @warning Pokud pri alokaci nastane problem a pozadovanou pamet se nepovede alokovat. Ukazatel na pole objektu shluku 'c'
 * je rovnen NULL a kapacita shluku 'c' je rovna 0.
 */
void init_cluster(struct cluster_t *c, int cap);

/**
 * Funkce odstrani vsechny objekty daneho shluku a inicializuje jej na prazdny shluk.
 *
 * @pre Ukazatel na shluk 'c' nesmi roven NULL.
 *
 * @post Kapacita shluku je rovna 0, shluk neobsahuje zadne objekty (pocet objektu je nulovy) a pamet alokovana pro objekty je uvolnena.
 *
 * @param c - shluk urceny k "vycisteni" (dealokaci pameti objektu a anulaci kapacity a aktualniho poctu objektu)
 *
 * @note Pokud je ukazatel na shluk 'c' roven NULL, funkce neprovede vubec nic.
 */
void clear_cluster(struct cluster_t *c);

/**
 * Kapacita objektu shluku pri alokaci shluku, pripadne mnozstvi objektu, o ktere se zvetsi kapacita shluku pri realokaci.
 */
extern const int CLUSTER_CHUNK;

/**
 * Funkce zmeni kapacitu shluku 'c' na kapacitu "new_cap" a alokuje pro ni prislusnou pamet.
 *
 * @pre Ukazatel na shluk 'c' nebude roven NULL.
 * @pre Kapacita shluku 'c' musi byt vetsi, nebo rovna 0.
 * @pre Parametr "new_cap" musi byt vetsi, nebo roven 0.
 *
 * @post Kapacita shluku 'c' bude rovna hodnote "new_cap".
 *
 * @param c - shluk, u ktereho ma byt zmenena kapacita
 * @param new_cap - nova kapacita urcena shluku 'c'
 *
 * @return Funkce vraci ukazatel na shluk se zmenenou kapacitou, pripadne NULL, pokud nastane chyba.
 *
 * @note V pripade, ze nova kapacita "new_cap" je mensi nebo rovna kapacitice shluku, fukce neprovede temer nic, pouze vrati ji predany ukazatel na shluk.
 *
 * @warning Realokace se nemusi vzdy zdarit (funkce vraci NULL).
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap);

/**
 * Funkce prida objekt "obj" na konec pole objektu shluku 'c'. V pripade potreby bude pole objektu shluku rozsireno (pokud se dany objekt do shluku nevejde).
 *
 * @pre Ukazatel na shluk 'c' nesmi byt roven NULL.
 *
 * @post Objekt "obj" je uspesne pridan na konec pole objektu daneho shluku a shluk je v pripade potreby uspesne rozsiren.
 *
 * @param c - Ukazatel na shluk, do ktereho ma byt pridan objekt
 * @param obj - Objekt, ktery ma byt pridan na konec pole objektu daneho shluku
 *
 * @note Pokud je ukazatel na shluk 'c' roven NULL, funkce neprovede vubec nic.
 *
 * @warning Pokud pri rosireni shluku dojde k chybe, ukazatel na shluk 'c' je roven NULL.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj);

/**
 * Funkce seradi objekty ve shluku vzestupne podle jejich identifikatoru.
 *
 * @post Objekty v danem shluku 'c' jsou uspesne serazeny podle velikosti jejich identifikatoru vzestupne (od nejmensiho ID po nejvetsi).
 *
 * @param c - shluk s objekty urcenymi k serazeni
 */
void sort_cluster(struct cluster_t *c);

/**
 * Funkce prida objekty shluku 'c2' do shluku 'c1'a v pripade potreby shluk 'c1' rozsiri.
 * Objekty ve shluku 'c1' budou serazeny podle jejich identifikatoru vzestupne (od nejmensiho po nejvetsi) a shluk 'c2' zustane nezmenen.
 *
 * @pre Ukazatel na shluk 'c1' nesmi byt roven NULL.
 * @pre Ukazatel na shluk 'c2' nesmi byt roven NULL.
 *
 * @post Objekty ze shluku 'c2' budou uspesne pridany do shluku 'c1' a objekty v rozsirenem shluku 'c1' budou uspesne serazeny vzestupne podle jejich identifikatoru.
 *
 * @param c1 - shluk, ktery ma byt rozsiren o objekty shluku 'c2'
 * @param c2 - shluk, ze ktereho maji byt objekty zkopirovany na konec shluku 'c1'
 *
 * @note Pokud je pocet objektu ve shluku 'c2' mensi nez 1, funkce neprovede vubec nic.
 *
 * @warning Pri rozsirovani shluku 'c1' muze dojit k chybe (pri realokaci).
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2);

/**
 * Funkce tiskne shluk 'c' a jeho objekty na standardni vystup.
 *
 * @post Vsechny objekty daneho shluku 'c' budou vytisteny na standardni vystup.
 *
 * @param c - shluk, jehoz objekty maji byt vytisteny na standardni vystup
 */
void print_cluster(struct cluster_t *c);

/**
 * @}
 */

/**
 * @defgroup shluky Operace s polem s hluku
 * @{
 */

/**
 * @defgroup vypocet_vzdalenosti Funkce pro vypocet vzdalenosti mezi shluky
 * @{
 */

 /**
  * Tato funkce slouzi k vypoctu Euklidovske vzdalenosti mezi dvema objekty.
  *
  * @pre Ukazatel na objekt 'o1' nesmi byt roven NULL.
  * @pre Ukazatel na objekt 'o2' nesmi byt roven NULL.
  *
  * @param o1 - 1. objekt
  * @param o2 - 2. objekt
  *
  * @return Funkce vraci Euklidovskou vzdalenost mezi objektem 'o1' a  objektem 'o2'.
  */
float obj_distance(struct obj_t *o1, struct obj_t *o2);

/**
 * Funkce slouzi k vypoctu vzdalenosti mezi dvema shluky (vzdalenost dvou nejblizsich objektu ze dvou ruznych shluku).
 *
 * @pre Ukazatel na shluk 'c1' nesmi byt roven NULL.
 * @pre Ukazatel na shluk 'c2' nesmi byt roven NULL.
 * @pre Pocet objektu shluku 'c1' musi byt vetsi nez 0.
 * @pre Pocet objektu shluku 'c2' musi byt vetsi nez 0.
 *
 * @param c1 - 1. shluk
 * @param c2 - 2. shluk
 *
 * @return Funkce vraci vzdalenost mezi shlukem 'c1' a shlukem 'c2'.
 */
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2);

/**
 * Funkce nalezne v poli shluku "carr" o velikosti "narr" dva nejblizsi shluky a identifikuje jejich indexy (v poli "carr"), ktere uklada do pameti na adresu 'c1' a 'c2'.
 *
 * @pre Pocet prvku ("narr") v poli shluku musi byt vetsi nez 0.
 *
 * @post Na adresach 'c1' a 'c2' budou uspesne ulozeny indexy dvou nejblizsich shluku.
 *
 * @param carr - pole shluku urcene k vyhledavani
 * @param narr - velikost pole shluku (pocet prvku v poli)
 * @param c1 - promenna slouzici pro ulozeni 1. indexu
 * @param c2 - promenna slouzici pro ulozeni 2. indexu
 */
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2);

/**
 * @}
 */

/**
 * @defgroup ostatni zakladni operace nad polem shluku
 * @{
 */

 /**
  * Funkce odstrani z pole shluku "carr" o velikosti "narr" shluk nachazejici se na indexu "idx" a vraci novy pocet shluku v poli.
  *
  * @pre Pocet shluku v poli shluku ("narr") musi byt vetsi nez 0.
  * @pre Idex shluku, ktery ma byt odstranen "idx" musi byt mensi nez pocet shluku v poli shluku ("narr").
  *
  * @post Shluk na danem indexu "idx" bude odstranen z pole shluku "carr" a celkovy pocet shluku v poli shluku bude o jeden mensi.
  *
  * @param carr - pole shluku, ze ktereho ma byt odstranen shluk
  * @param narr - pocet shluku v poli shluku
  * @param idx - index nalezici shluku, ktery ma byt odstranen
  *
  * @return Funkce vraci novy pocet shluku v poli shluku (tedy "narr" -1).
  */
int remove_cluster(struct cluster_t *carr, int narr, int idx);

/**
 * Funkce zkontroluje a nacte objekty ze souboru "filename", pro kazdy objekt vytvori shluk a ulozi jej do pole vsech shluku, pro ktere alokuje pamet.
 * Funkce take ulozi do pameti ukazatel na prvni polozku pole (ukazatel na prvni shluk v alokovanem poli shluku), kam se odkazuje parametr "arr".
 *
 * @pre Musi existovat soubor "filename" a je nutne, aby byl pristupny pro cteni.
 * @pre Parametr "arr" (ukazatel na ukazatel na prvni polozku pole shluku) nesmi byt roven NULL.
 *
 * @post Pri uspesnem skonceni funkce bude pro kazdy nacteny objekt ze vstupniho souboru vytvoren shluk, ktery bude ulozen v poli shluku, na ktere se odkazuje parametr "narr".
 * @post Pro tohle pole bude alokovana pamet, ktera odpovida poctu shluku, ktere se nactou ze vstupniho souboru, ve kterem je primo specifikovano (na 1. radku), kolik shluku se ma nacist.
 *
 * @param filename - jmeno souboru s objekty
 * @param arr - ukazatel na pole shluku (tedy ukazatel na ukazatel na 1. shluk pole shluku)
 *
 * @return Funkce vraci pocet uspesne nactenych shluku.
 *
 * @warning Pokud v prubehu funkce nastane chyba (napr. nepovede se alokace, spatny format vstupniho souboru,...),
 * funkce vraci vzdy 0 (nenacte tedy vubec nic) a do pameti, kam se odkazuje parametr "arr" uklada hodnotu NULL.
 */
int load_clusters(char *filename, struct cluster_t **arr);

/**
 * Funkce vytiskne pole shluku (jednotlive shluky a jejich objekty).
 *
 * @post Vsechny Objekty vsech shluku (v poli shluku "carr") budou vytisteny na standardni vystup (na kazdem radku stdout budou objekty jednoho shluku).
 *
 * @param carr - pole shluku urcene k vypsani na stdout
 * @param narr - pocet shluku, ktere maji byt vypsany (vzdy odpovida celkovemu poctu shluku v poli shluku)
 *
 */
void print_clusters(struct cluster_t *carr, int narr);

/**
 * @}
 */

/**
 * @}
 */
