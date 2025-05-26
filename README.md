# mogus_LV
Arduino 2D piedzīvojumu spēle par kosmonautu, kas vāc kastītes kosmosa kuģī.

####  MOGUS spēle  ####

Programmas autors: Kārlis Sondors
Programma izstrādāta: 22.01.2024.
Komentāri pievienoti: 26.05.2025.


####  Apraksts  ####

Šī ir Arduino Uno platformai izstrādāta 2D piedzīvojumu spēle, kur grafiskais saturs tiek rādīts uz ekrāna un varonis tiek vadīts ar vienu pogu. 

Spēles ideja:
- Kosmonauts, kam kosmosa kuģī (kosmosā) ir jāsavāc kastītes vairākās istabās. 
- Kosmonauts nepārtraukti kustās vienā no 4 virzieniem, un pogas nospiešana maina virzienu pretēji pulksteņa rādītāja virzienam.
- Lai tiktu uz katru nākamo istabu, ir jāsavāc visas kastītes konkrētajā istabā. 
- Kopā ir 8 istabas ar pieaugošu sarežģītības līmeni: sākot ar statiskiem un turpinot ar dinamiskiem, grūtākiem šķēršļiem.
- Ja kosmonauts ieskrien sienā vai šķērslī, spēle beidzas un parādās zaudēšanas ekrāns.
- Ja tiek izietas visas istabas - parādās uzvaras ekrāns.
- Pēc spēles beigām (uzvara vai zaudējums) spēle var tikt spēlēta atkārtoti.


####  Tehniskais raksturojums  ####

- Plaforma: Arduino Uno vai Nano.
- Ievade: poga (iekodēta uz digital pin 5).
- Izvade: 128*32 oled ekrāns (Adafruit SSD1306)
- Tehniski spēle darbojas tā, ka ikkatra istaba ir programmēta kā while cikls, kur katrā iterācijā tiek nolasīta lietotāja ievade, nodzēsts ekrāns un ar display.display(); tiek uzzīmēts jauns ekrāna saturs, ietverot pārvietoto galvenā varoņa atrašanās vietu, kastes, statiskos un dinamiskos šķēršļus.
- Šāds kodējums un ekrāna pārzīmēšana veido animāciju.


####  Pielikumi  ####

- mogus.ino: Arduino programmatūra, atverama ar Arduino IDE
- mogus_kods_cpp.cpp: C++ failā ielikta mogus.ino programmatūra, ja neizdodas atvērt mogus.ino
- mogus_kods_txt.txt: txt failā ielikta mogus.ino programmatūra, ja neizdodas atvērt nevienu no augstāk aprakstītajiem failiem
- victory run.mov: video, kurā tiek veiksmīgi izieta visa spēle.
- zaude.MP4: video, kurā kosmonauts ieskrien sienā un spēle ir zaudēta.
- uno.png: uz Arduino Uno izveidota aparatūras konfigurācija spēlei
- nano.png: uz Arduino Nano izveidota aparatūras konfigurācija spēlei
