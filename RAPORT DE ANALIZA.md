# SMART FLOWERPOT - RAPORT DE ANALIZA
## Echipa
  * Avadanei Antonia
  * Cinca Adrian
  * Cioboata Mihai - Catalin
  * Dariescu Marius - Teodor
  * Pantiru Luana -Catalina

## Cuprins
  1. Scopul aplicatiei
  2. Aria de acoperire a aplicației
  3. Grupurile de interese	
  4. Colectarea cerințelor	
      -	Metode directe	
        -	Cerințele echipei de proiect	
      -	Metode indirecte	
  5. Interpretarea cerințelor	
  6. Prioritizarea cerințelor	
  7. Specificații de analiză	
  8. Contribuția echipei	

## 1. Scopul aplicatiei
Dupa cum se stie, plantele de camera au nevoie de un vas cu pamant, apa si lumina, dar nu toate au nevoie de aceeasi cantitate de lumina sau apa. Aceste informatii nu sunt cunoscute de toti oamenii, ceea ce poate duce la o ingrijire neadecvata pentru o anumita planta. Acest lucru poate determina moartea plantei si sa il faca pe proprietar sa se gandeasca ca nu poate sa aiba grija de vreo  una, astfel renuntand sa isi mai puna plante prin casa. De asemenea, lipsa plantelor in casa nu este buna pentru sanatatea noastra.

SMART FLOWERPOT este o aplicatie care transforma un ghiveci normal, care poate sa aiba orice forma sau culoare, intr-unul care poate sa ajute orice om sa aiba grija de propria planta. Aceasta ne poate anunta cand sa udam planta si daca are destula lumina, toate informatiile find date de tipul plantei care se afla in respectivul ghiveci.

De ce am ales un ghiveci care sa ne ajute sa ingrijim o planta? Ghiveciul este singurul obiect fizic care poate fi folosit pentru a crea un canal de comunicare dintre om si planta. Este drept ca planta reactioneaza intr-un anumit mod atunci cand nu este ingrijita cum trebuie, de exemplu se poate ofili, doar ca oameni care nu au cunostinte in domeniul botanicii nu pot sa isi dea seama cum sa vindece planta. 

## 2.Aria de acoperire a aplicației
SMART FLOWERPOT este o aplicatie care trimite notificari legate de starea in care se afla o planta din ghiveciul nostru, nu este o aplicatie care sa ingrijeasca singura planta. De exemplu, functionalitatea de a se porni un sistem de irigare in interiorul ghiveciului nu se va regasi.

Aceasta aplicatie imbunatateste un ghiveci astfel incat sa ni se ofere diferite informatii legate de calitatile solului si ale ambientului. Fiecare planta are anumite conditii de mediu, iar in momentul in care una din caracteristici nu este indeplinita ghiveciul va trimite o notificare specifica.

## 3.Grupurile de interese
Aceasta aplicatie este destinata pentru orice iubitor de plante care vrea sa aiba mai multa grija de propriile plante, chiar daca are sau nu cunostintele si timpul necesar.

## 4.Colectarea cerințelor

   * [Metode directe](https://forms.gle/8vfVHQBZgYVEoV9v5)

Conform datelor colectate din formular, am observat urmatoarele aspecte: 
   * 88% din respondenti au spus ca detin plante de interior
   * 56% au afirmatat ca au timp sa le ingrijeasca
   * 92% au declarat ca au intampinat probleme in ceea ce priveste intretinerea plantelor lor 
   * 84% au sustinut ca plantele detinute de ei au avut de suferit din cauza unei ingrijiri necorespunzatoare
   * 84% considera ca ar fi utila o aplicatie care sa ajute in procesul de ingrijire a unei plante 

Totodata, am analizat preferintele user-ului tinta, acestia ordonandu-le in ordinea prioritatilor dupa cum urmeaza:
![image](https://user-images.githubusercontent.com/48531779/111204525-e237d880-85ce-11eb-88bd-ee634e8114e0.png)


      
   * Metode indirecte
   
        - Articole, video-uri: 
            - https://www.arctic.ro/blog/cum-ingrijesti-plantele-si-florile-de-apartament/
            - https://www.youtube.com/watch?v=BWYiMcH0cRc&ab_channel=RachelAust
        - Alte aplicatii smart pot:
            - https://www.designboom.com/technology/lua-smart-planter-facial-expressions-07-15-2019/
            - https://www.lookoutpro.com/en/parrot-pot-the-smart-self-watering-flowerpot/
      
## 5.Interpretarea cerințelor

  * Determinarea umiditatii din sol -> cand umiditatea din sol e scazut se anunta ca planta trebuie udata
  * Determinarea cantitatii de apa care trebuie adaugata
  * Cantitatea de lumina -> atunci cand planta are nevoie de mai multa lumina se va semnala acest lucru
  * Temperatura ambientala -> atunci cand in incapere e prea frig pentru planta se va semnala acest lucru
  * Ph-ul solului -> atunci cand Ph solului nu este cel adecvat se va cere schimbarea solului
  * Nutrientii din sol -> se va semnala cand este nevoie de ingrasamant 
  * Sistem audio care pune muzica pentru stimularea cresterii
  * Sistem de inregistrare a vocii proprietarului pentru a fi pornita atunci cand nu este nimeni acasa pentru a nu se simti singura planta
  * Un ghid de ingrijire al plantei in functie de specificul acesteia si de mediul in care va creste.
  * Camera inteligenta pentru detectarea diferitelor boli
  * Un sistem care curata frunzele daca au praf
  * Un sistem care ne notifica atunci cand ghiveciul trebuie schimbat
  * Ghiveciul sa aiba diferite nuante de fundal pentru a se putea asorta cu planta si sa ii cante atunci cand este ofilită
  * Sa ne dea informatii de tipul "Stiati ca?"

## 6.Prioritizarea cerințelor

Toti membrii echipei au dat o nota de la 1 la 100 fiecarui feature, atat pentru efectul produs, cat si pentru usurinta de implementare.

**Notarea a fost urmatoarea:**

![image](https://github.com/LuanaPantiru/Smart-flowerpot/blob/main/images/clasificare_efect_cerinte.JPG)

![image](https://github.com/LuanaPantiru/Smart-flowerpot/blob/main/images/clasificare_usurinta_la_implementare.JPG)

**Ulterior am afisat grafic datele, rezultatul fiind acesta:**

![image](https://github.com/LuanaPantiru/Smart-flowerpot/blob/main/images/grafic_analiza_pareto.JPG)

Dupa acest pas, conform graficului precedent cerintele care ar avea un efect >= 50 au fost:

1. Determinarea umiditatii din sol
2. Indicarea cantitatii necesare de apa, daca umiditatea solului scade sub pragul critic
3. Monitorizarea cantitatii de lumina primita si implementarea unor alerte in conformitate cu nevoile plantei
4. Implementarea unei alerte daca temperatura ambientala nu este potrivita
5. Determinarea Ph-ului solului si a valorilor corespunzatoare speciei
6. Un sistem de analiza a nutrientior din sol
7. Sistem audio care pune muzica pentru stimularea cresterii
8. Ghiveciul sa aiba diferite nuante de fundal pentru a se putea asorta cu planta
9. Adaugarea unei rubrici de tipul "Stiati ca?" pentru pasionatii de gradinarit


**Urmatorul pas a fost sa cream un grafic care sa prezinte rezultatele Analizei Pareto (80% efect, 20% efort), acesta fiind:**

![image](https://user-images.githubusercontent.com/24314568/111199840-c978f400-85c9-11eb-8174-71be01e82f23.png)

Din cel de-al doilea grafic s-a dedus urmatoarea prioritizare a cerintelor:

1. Determinarea umiditatii din sol
2. Indicarea cantitatii necesare de apa, daca umiditatea solului scade sub pragul critic
3. Monitorizarea cantitatii de lumina primita si implementarea unor alerte in conformitate cu nevoile plantei
4. Implementarea unei alerte daca temperatura ambientala nu este potrivita
5. Un sistem de analiza a nutrientior din sol
6. Adaugarea unei rubrici de tipul "Stiati ca?" pentru pasionatii de gradinarit
7. Determinarea Ph-ului solului si a valorilor corespunzatoare speciei
8. Sistem audio care pune muzica pentru stimularea cresterii
9. Ghiveciul sa aiba diferite nuante de fundal pentru a se putea asorta cu planta

Avand in vedere rezultatele obtinute am decis sa implementam urmatoarele cerinte:

## 7.Specificații de analiză
   * Ca utilizator, as dori sa pot afla umiditatea solului
   * Ca utilizator, as dori sa stiu exact ce cantitate de apa are nevoie planta mea
   * Ca utilizator, as dori sa cunosc cantitatea de lumina necesara plantei
   * Ca utilizator, as dori sa fiu anuntat atunci cand temperatura ambientala poate dauna plantei
   * Ca utilizator, as dori sa stiu daca solul este propice dezvoltarii florii mele
   * Ca utilizator, as dori sa aflu informatii interesante din lumea plantelor
   * Ca utilizator, as dori sa stiu daca Ph ul solului este potrivit
   * Ca utilizator, as dori sa pot stimula suplimentar cresterea plantei
   * Ca utilizator, as dori sa pot integra ghiveciul cu decorul casei

## 8.Contribuția echipei
Contribuția fiecărui membru al echipei la realizarea analizei aplicației.
