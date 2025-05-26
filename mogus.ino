/*
Programmu izstrādāja Kārlis Sondors 22.01.2024.
Programmai tika pievienoti komentāri 26.05.2025.
*/

const int poga = 5;  // pogas pin
const int LED = 13;    // LED pin
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED displeja platums pikseļos
#define SCREEN_HEIGHT 32 // OLED displeja augstums pikseļos
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/* zemāk ir bloks, kurā ir main character varonis 2 stāvokļi uz katru pusi, lai tie, sekvenciāli mainoties, izskatītos pēc animētas staigāšanas */

//  varonis iet pa kreisi, abas pozīcijas
#define left1_width  8
#define left1_height 8
static unsigned char left1[] = {
 0x3c,0x7a,0x85,0x85,0x7d,0x82,0xba,0xc6};

#define left2_width  8
#define left2_height 8
static unsigned char left2[] = {
 0x3c,0x7a,0x85,0x85,0x7d,0x42,0x56,0x6c};

// varonis iet pa labi, abas pozīcijas
#define right1_width  8
#define right1_height 8
static unsigned char right1[] = {
 0x3c,0x5e,0xa1,0xa1,0xbe,0x41,0x5d,0x63};

#define right2_width  8
#define right2_height 8
static unsigned char right2[] = {
 0x3c,0x5e,0xa1,0xa1,0xbe,0x42,0x6a,0x36};

// varonis iet uz augšu, abas pozīcijas
#define up1_width  8
#define up1_height 8
static unsigned char up1[] = {
 0x3c,0x42,0xbd,0xa5,0xa5,0x76,0x6a,0x06
};
#define up2_width  8
#define up2_height 8
static unsigned char up2[] = {
 0x3c,0x42,0xbd,0xa5,0xa5,0x6e,0x56,0x60
};

// varonis iet uz leju, abas pozīcijas
#define down1_width  8
#define down1_height 8
static unsigned char down1[] = {
 0x3c,0x7e,0xc3,0xc3,0xbd,0x4a,0x56,0x60
};
#define down2_width  8
#define down2_height 8
static unsigned char down2[] = {
 0x3c,0x7e,0xc3,0xc3,0xbd,0x52,0x6a,0x06
};


void setup() {
  pinMode(LED, OUTPUT);
  pinMode(poga, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC);
  Serial.begin(9600);
  display.setTextColor(WHITE);
}

void loop() {
  menu(); // izvēlnes ekrāns
  spele(); // spēle
}

void spele(){
  // uzstādām sākotnējās vērtības, kas tiks padotas kā parametrs pirmajai istabai

  int xj=2, yj=2, x=-7, y=24, istaba=1; // sākuma pozīcija un pirmā istaba
  bool zaude=false; // true = spēle beidzas. uzliekas, ja ieskrien kādā šķērslī vai sienā
  bool pass=false; // true = var tikt uz nākamo istabu
  bool xPieaug=true, xSamazinas=false, yPieaug=false, ySamazinas=false; // sākotnējais pārvietošanās virziens. Doma šiem mainīgajiem ir tāda, ka ir viens kvadrants ar x un y asi, un tajā var vai nu pieaugt vai samazināties x koordināta, tāpat ar y. 
  //pēc spēles izstrādes secināju, ka te varēja iztikt tikai ar diviem mainīgajiem - xPieaug un yPieaug, un tos atbilstoši kombinēt ar true un false kombinācijām. 

  //definējums true=redzams, false=neredzams, kuras kastes ir redzamas, tām bool vērtība katrā istabā tiks mainīta
  bool kaste1=true, kaste2=true, kaste3=true, kaste4=true, kaste5=false, kaste6=false, kaste7=false, kaste8=false, kaste9=false, kaste10=false, kaste11=false, kaste12=false, kaste13=false, kaste14=false, kaste15=false, kaste16=false, kaste17=false, kaste18=false, kaste19=false, kaste20=false; 

  //istabas, parametros sākuma koordinātas, istaba, pārvietošanās sākotnējais virziens, bool par iespēju tikt uz nākamo istabu, kastu redzamība un bool par zaudēšanu
  istaba1(xj,yj,x,y,istaba, xPieaug, xSamazinas, yPieaug, ySamazinas, pass, kaste1, kaste2, kaste3, kaste4, zaude);
  istaba2(xj,yj,x,y,istaba, xPieaug, xSamazinas, yPieaug, ySamazinas, pass, kaste5, kaste6, kaste7, zaude);
  istaba3(xj,yj,x,y,istaba, xPieaug, xSamazinas, yPieaug, ySamazinas, pass, kaste8, kaste9, kaste10, zaude);
  istaba4(xj,yj,x,y,istaba, xPieaug, xSamazinas, yPieaug, ySamazinas, pass, kaste11, kaste12, kaste13, kaste14, kaste15, kaste16, zaude);
  istaba5(xj,yj,x,y,istaba, xPieaug, xSamazinas, yPieaug, ySamazinas, pass, kaste17, kaste18, kaste19, kaste20, zaude);
  istaba6(xj,yj,x,y,istaba, xPieaug, xSamazinas, yPieaug, ySamazinas, pass, zaude);
  istaba7(xj,yj,x,y,istaba, xPieaug, xSamazinas, yPieaug, ySamazinas, pass, zaude);
  istaba8(zaude);
  if (zaude) zaudeFN();
  display.clearDisplay();
}

// 1. istaba bez šķēršļa
void istaba1 (int &xj,int &yj,int &x,int &y,int &istaba, bool &xPieaug, bool &xSamazinas, bool &yPieaug, bool &ySamazinas, bool &pass, bool &kaste1, bool &kaste2, bool &kaste3, bool &kaste4, bool &zaude){
  zaude=false;
  while (x>=-7 && x<=128 && y>=-7 && y<=32 && istaba==1){

    //ja kaste ir true, tas nozīmē, ka tā nav savākta un to zīmējam uz ekrāna
    if (kaste1) display.drawRect(15,15,5,5,WHITE);
    if (kaste2) display.drawRect(90,10,5,5,WHITE);
    if (kaste3) display.drawRect(75,2,5,5,WHITE);
    if (kaste4) display.drawRect(40,18,5,5,WHITE);

    // ja varoņa koordinātas sakrīt ar kastes malām, tā tiek savākta jeb kaste = false
    if (x>=10 && x+8<=24 && y>=10 && y+8<=23) {
      kaste1=false;
    }
    if (x>=85 && x+8<=99 && y>=5 && y+8<=19) {
      kaste2=false;
    }
    if (x>=70 && x+8<=84 && y>=-3 && y+8<=11) {  //x75 y2    x ir -5 un +9,  y-5 un +9
      kaste3=false;
    }
    if (x>=35 && x+8<=49 && y>=13 && y+8<=27) { //x40 un y18
      kaste4=false;
    }

    // ja visas kastes ir savāktas, parādās iespēja tikt nākamajā istabā
    // tad tiek uzzīmētas durvis
    if (!kaste1 && !kaste2 && !kaste3 && !kaste4) {
      pass=true;
      display.drawLine(120,5,129,5,WHITE);
      display.drawLine(120,23,129,23,WHITE);

    }

    // ja ir iespēja tikt nākamajā istabā un varonis iziet pa durvīm, dodamies uz nākamo istabu
    if (pass && y>=6 && y+8<=22 && x==128) istaba++;

    zvaigznes(); // pārzīmējam jaunas zvaigznes katrā iterācijā
    virziens(xPieaug, xSamazinas, yPieaug, ySamazinas,x,y,xj,yj); // pārzīmējam varoni katrā iterācijā
    display.display(); // parādām ekrāna saturu
    display.clearDisplay(); // nodzēšam ekrāna saturu
  }
  if (istaba==1) zaude=true; // ja esam izgājuši no while cikla un istaba joprojām ir 1, tas nozīmē, ka esam zaudējuši
  else zaude=false;
  
}

// tieši tādā pašā stilā visas pārējās istabas zemāk

void istaba2(int &xj,int &yj,int &x,int &y,int &istaba, bool &xPieaug, bool &xSamazinas, bool &yPieaug, bool &ySamazinas, bool &pass, bool &kaste5, bool &kaste6, bool &kaste7, bool &zaude){
  int skerslis1X = 50, skerslis1Y=15, skerslis1GAR=20, skerslis1AUGST=10; //statisks šķērslis
  pass=false;
  kaste5=true;
  kaste6=true;
  kaste7=true;
  if (zaude) return;
  x=-7; // pārvietojam varoni uz šo x koordinātu, bet y koordināta paliek no iepriekšējās istabas tāda pati, padodas ar parametru

  // analoģisks while cikls kā 1. istabā
  while (x>=-7 && x<=128 && y>=-7 && y<=32 && istaba==2){

    // ja ieskrienam šķērslī
    if ((x+8>=skerslis1X && x<=skerslis1X+skerslis1GAR) && (y+8>=skerslis1Y && y<=skerslis1Y+skerslis1AUGST)) {
      zaude=true;
      return;
    }

    display.fillRect(skerslis1X,skerslis1Y,skerslis1GAR,skerslis1AUGST,WHITE);      // zīmējam šķērsli
    if (kaste5) display.drawRect(5,28,5,5,WHITE); //centrs +2 un +2
    if (kaste6) display.drawRect(55,5,5,5,WHITE);
    if (kaste7) display.drawRect(99,20,5,5,WHITE);

    if (x>=0 && x+8<=14 && y>=23 && y+8<=39) {
      kaste5=false;
    }
    if (x>=50 && x+8<=64 && y>=0 && y+8<=14) {
      kaste6=false;
    }
    if (x>=94 && x+8<=108 && y>=15 && y+8<=29) {  //   x -5 un +9,   y -5 un +9
      kaste7=false;
    }

    // ja visas kastes savāktas, zīmējam durvis un ir iespēja tikt uz nākamo istabu
    if (!kaste5 && !kaste6 && !kaste7) {
      pass=true;
      display.drawLine(90,3,90,-2,WHITE);
      display.drawLine(105,3,105,-2,WHITE);
    }
    if (pass && x>=90 && x+8<=105 && y==-7) istaba++; // būs nākamā istaba

    zvaigznes();
    virziens(xPieaug, xSamazinas, yPieaug, ySamazinas,x,y,xj,yj);
    display.display();
    display.clearDisplay();
  }
  if (istaba==2) zaude=true;
  else zaude=false;

}

void istaba3(int &xj,int &yj,int &x,int &y,int &istaba, bool &xPieaug, bool &xSamazinas, bool &yPieaug, bool &ySamazinas, bool &pass, bool &kaste8, bool &kaste9, bool &kaste10, bool &zaude){
  int i=10;
  int skerslis1X, skerslis1Y=12, skerslis1GAR=20, skerslis1AUGST=10;
  bool right=true;
  pass=false;
  kaste8=true;
  kaste9=true;
  kaste10=true;
 //------------------------ sākuma koordinātas
  //istaba=3;
  //y=28;
  //y=41;
  //------------------------
  
  if (zaude) return;
  y=32;

  while (x>=-7 && x<=128 && y>=-7 && y<=32 && istaba==3){

    if ((x+8>=skerslis1X && x<=skerslis1X+skerslis1GAR) && (y+8>=skerslis1Y && y<=skerslis1Y+skerslis1AUGST)) {
      zaude=true;
      return;
    }

    skerslis1X=i/2;

    display.fillRect(skerslis1X,skerslis1Y,skerslis1GAR,skerslis1AUGST,WHITE);      //šķērslis
    if (kaste8) display.drawRect(15,15,5,5,WHITE); //centrs +2 un +2
    if (kaste9) display.drawRect(70,15,5,5,WHITE);
    if (kaste10) display.drawRect(110,15,5,5,WHITE);

    if (i==200) right=false;
    if (i==20) right=true;
    if (right) i++;
    else i--;

    if (x>=10 && x+8<=24 && y>=10 && y+8<=24) {
      kaste8=false;
    }
    if (x>=65 && x+8<=79 && y>=10 && y+8<=24) {
      kaste9=false;
    }
    if (x>=105 && x+8<=119 && y>=10 && y+8<=24) {  //   x -5 un +9,   y -5 un +9
      kaste10=false;
    }

    if (!kaste8 && !kaste9 && !kaste10) {
      pass=true;
      display.drawLine(10,3,10,-2,WHITE);
      display.drawLine(25,3,25,-2,WHITE);

    }
    if (pass && x>=10 && x+8<=25 && y==-7) istaba++;

    zvaigznes();
    virziens(xPieaug, xSamazinas, yPieaug, ySamazinas,x,y,xj,yj);
    display.display();
    display.clearDisplay();
  }
  if (istaba==3) zaude=true;
  else zaude=false;
}

void istaba4 (int &xj,int &yj,int &x,int &y,int &istaba, bool &xPieaug, bool &xSamazinas, bool &yPieaug, bool &ySamazinas, bool &pass, bool &kaste11, bool &kaste12, bool &kaste13, bool &kaste14, bool &kaste15, bool &kaste16, bool &zaude){
  
  if (zaude) return;

  int i=8; // koeficients priekš dinamiskā šķēršļa bīdīšanās ātruma
  bool right=true; // sākotnējais dinamiskā šķēršļa bīdīšanās virziens
  int skerslis1X=0, skerslis1Y=i, skerslis1GAR=52, skerslis1AUGST=2;
  int skerslis2X=78, skerslis2Y=i, skerslis2GAR=52, skerslis2AUGST=2;

  pass=false;
  kaste11=true;
  kaste12=true;
  kaste13=true;
  kaste14=true;
  kaste15=true;
  kaste16=true;

  //------------------------
  //istaba=4;
  //y=28;
  y=32;
  //------------------------

  while (x>=-7 && x<=128 && y>=-7 && y<=32 && istaba==4){

    if ((x+8>=skerslis1X && x<=skerslis1X+skerslis1GAR) && (y+8>=skerslis1Y && y<=skerslis1Y+skerslis1AUGST)) {
      zaude=true;
      return;
    }
    if ((x+8>=skerslis2X && x<=skerslis2X+skerslis2GAR) && (y+8>=skerslis2Y && y<=skerslis2Y+skerslis2AUGST)) {
      zaude=true;
      return;
    }

    // dinamisks šķērslis, bīdās no labās uz kreiso un pēc tam atpakaļ, un tā visu laiku
    skerslis1Y=i/8; // nosaka bīdīšanās ātrumu
    skerslis2Y=i/8; // bīdīšanās ātrums
    if (i==256) right=false; // lai bīdītos uz vienu pusi
    if (i==8) right=true; // lai bīdītos uz otru pusi
    if (right) i++;
    else i--;

    display.fillRect(skerslis1X,skerslis1Y,skerslis1GAR,skerslis1AUGST,WHITE);      // šķērslis
    display.fillRect(skerslis2X,skerslis2Y,skerslis2GAR,skerslis2AUGST,WHITE);
    if (kaste11) display.drawRect(5,5,5,5,WHITE); //centrs +2 un +2
    if (kaste12) display.drawRect(110,5,5,5,WHITE);
    if (kaste13) display.drawRect(40,14,5,5,WHITE);
    if (kaste14) display.drawRect(80,14,5,5,WHITE);
    if (kaste15) display.drawRect(5,25,5,5,WHITE);
    if (kaste16) display.drawRect(110,25,5,5,WHITE);

    if (x>=0 && x+8<=14 && y>=0 && y+8<=14) {
      kaste11=false;
    }
    if (x>=105 && x+8<=119 && y>=0 && y+8<=14) {
      kaste12=false;
    }
    if (x>=35 && x+8<=49 && y>=10 && y+8<=23) {  //   x -5 un +9,   y -5 un +9
      kaste13=false;
    }
    if (x>=75 && x+8<=89 && y>=10 && y+8<=23) {
      kaste14=false;
    }
    if (x>=0 && x+8<=14 && y>=20 && y+8<=34) {
      kaste15=false;
    }
    if (x>=105 && x+8<=119 && y>=20 && y+8<=44) {  //   x -5 un +9,   y -5 un +9
      kaste16=false;
    }

    if (!kaste11 && !kaste12 && !kaste13 && !kaste14 && !kaste15 && !kaste16) {
      pass=true;
      display.drawLine(57,3,57,-2,WHITE);
      display.drawLine(72,3,72,-2,WHITE);

    }
    if (pass && x>=57 && x+8<=72 && y==-7) istaba++;

    zvaigznes();
    virziens(xPieaug, xSamazinas, yPieaug, ySamazinas,x,y,xj,yj);
    display.display();
    display.clearDisplay();
  }
  if (istaba==4) zaude=true;
  else zaude=false;
}

void istaba5 (int &xj,int &yj,int &x,int &y,int &istaba, bool &xPieaug, bool &xSamazinas, bool &yPieaug, bool &ySamazinas, bool &pass, bool &kaste17, bool &kaste18, bool &kaste19, bool &kaste20, bool &zaude){
  
  if (zaude) return;

  int i=0;
  bool right=true;
  // šajā istabā istaba no kreisās puses konstanti pildās ar šķērsli jeb saspiezas bez iespējām izmukt, un pēdējā brīdī labajā pusē parādās durvis
  int skerslis1X=-17, skerslis1Y=0, skerslis1GAR=i, skerslis1AUGST=32;

  pass=false;
  kaste17=true;
  kaste18=true;
  kaste19=true;
  kaste20=true;
  x=60;
  y=32;

  //------------------------
  /*istaba=5;
  xPieaug=false;
  ySamazinas=true;*/
  //------------------------

  while (x>=-7 && x<=128 && y>=-7 && y<=32 && istaba==5){

    if ((x+8>=skerslis1X && x<=skerslis1X+skerslis1GAR) && (y+8>=skerslis1Y && y<=skerslis1Y+skerslis1AUGST)) {
      zaude=true;
      return;
    }

    skerslis1GAR=i/4; // saspiešanās ātrums istabai
    if (right) i++; // lai būtu dinamiska saspiešanās

    display.fillRect(skerslis1X,skerslis1Y,skerslis1GAR,skerslis1AUGST,WHITE);      //šķērslis

    if (kaste17) display.drawRect(15,5,5,5,WHITE); //centrs +2 un +2
    if (kaste18) display.drawRect(35,12,5,5,WHITE);
    if (kaste19) display.drawRect(20,27,5,5,WHITE);
    if (kaste20) display.drawRect(50,19,5,5,WHITE);

    if (x>=10 && x+8<=24 && y>=0 && y+8<=14) {
      kaste17=false;
    }
    if (x>=30 && x+8<=44 && y>=7 && y+8<=21) {
      kaste18=false;
    }
    if (x>=15 && x+8<=29 && y>=22 && y+8<=36) {  //   x -5 un +9,   y -5 un +9
      kaste19=false;
    }
    if (x>=45 && x+8<=59 && y>=14 && y+8<=28) {
      kaste20=false;
    }

    if (!kaste17 && !kaste18 && !kaste19 && !kaste20 && i>=470) {
      pass=true;
      display.drawLine(122,0,129,5,WHITE);
      display.drawLine(122,32,129,28,WHITE);

    }
    if (pass && y>=6 && y+8<=27 && x==128) istaba++;

    zvaigznes();
    virziens(xPieaug, xSamazinas, yPieaug, ySamazinas,x,y,xj,yj);
    display.display();
    display.clearDisplay();
  }
  if (istaba==5) zaude=true;
  else zaude=false;
}

void istaba6 (int &xj,int &yj,int &x,int &y,int &istaba, bool &xPieaug, bool &xSamazinas, bool &yPieaug, bool &ySamazinas, bool &pass, bool &zaude){
  
  if (zaude) return;

  int skerslis1X=0, skerslis1Y=0, skerslis1GAR=35, skerslis1AUGST=20;
  int skerslis2X=55, skerslis2Y=18, skerslis2GAR=78, skerslis2AUGST=20;
  int skerslis3X=0, skerslis3Y=0, skerslis3GAR=128, skerslis3AUGST=1;
  int skerslis4X=0, skerslis4Y=31, skerslis4GAR=128, skerslis4AUGST=1;

  pass=true;


  //------------------------
  //istaba=6;
  x=-7;
  y=22;
  //------------------------

  while (x>=-7 && x<=128 && y>=-7 && y<=32 && istaba==6){

    if ((x+8>=skerslis1X && x<=skerslis1X+skerslis1GAR) && (y+8>=skerslis1Y && y<=skerslis1Y+skerslis1AUGST)) {
      zaude=true;
      return;
    }
    if ((x+8>=skerslis2X && x<=skerslis2X+skerslis2GAR) && (y+8>=skerslis2Y && y<=skerslis2Y+skerslis2AUGST)) {
      zaude=true;
      return;
    }
    if ((x+8>=skerslis3X && x<=skerslis3X+skerslis3GAR) && (y+8>=skerslis3Y && y<=skerslis3Y+skerslis3AUGST)) {
      zaude=true;
      return;
    }
    if ((x+8>=skerslis4X && x<=skerslis4X+skerslis4GAR) && (y+8>=skerslis4Y && y<=skerslis4Y+skerslis4AUGST)) {
      zaude=true;
      return;
    }


    display.fillRect(skerslis1X,skerslis1Y,skerslis1GAR,skerslis1AUGST,WHITE);      //šķērslis
    display.fillRect(skerslis2X,skerslis2Y,skerslis2GAR,skerslis2AUGST,WHITE);
    display.fillRect(skerslis3X,skerslis3Y,skerslis3GAR,skerslis3AUGST,WHITE);
    display.fillRect(skerslis4X,skerslis4Y,skerslis4GAR,skerslis4AUGST,WHITE);

    if (pass && y>=6 && y+8<=27 && x==128) istaba++;
 
    // šajā līmenī nav paredzētas zvaigznes, tas ir domāts kā tunelis
    //zvaigznes();
    virziens(xPieaug, xSamazinas, yPieaug, ySamazinas,x,y,xj,yj);
    display.display();
    display.clearDisplay();
  }
  if (istaba==6) zaude=true;
  else zaude=false;
}

void istaba7 (int &xj,int &yj,int &x,int &y,int &istaba, bool &xPieaug, bool &xSamazinas, bool &yPieaug, bool &ySamazinas, bool &pass, bool &zaude){
  
  if (zaude) return;

  int i=64;
  int j=31;
  int k=128;
  int skerslis1X=0, skerslis1Y=0, skerslis1GAR=128, skerslis1AUGST=i;
  int skerslis2X=0, skerslis2Y=j, skerslis2GAR=128, skerslis2AUGST=32;
  int skerslis3X=0, skerslis3Y=0, skerslis3GAR=i, skerslis3AUGST=32;
  int skerslis4X=k, skerslis4Y=0, skerslis4GAR=128, skerslis4AUGST=32;
  bool zimet=false;


  pass=true;


  //------------------------
  //istaba=7;
  x=-7;
  y=12;
  //------------------------

  while (x>=-7 && x<=128 && y>=-7 && y<=32 && istaba==7){

    if (x>=2) zimet=true;

    if (zimet){

      if ((x+8>=skerslis1X && x<=skerslis1X+skerslis1GAR) && (y+8>=skerslis1Y && y<=skerslis1Y+skerslis1AUGST)) {
        //zaude=true;
        return;
      }
      if ((x+8>=skerslis2X && x<=skerslis2X+skerslis2GAR) && (y+8>=skerslis2Y && y<=skerslis2Y+skerslis2AUGST)) {
       // zaude=true;
        return;
      }
      if ((x+8>=skerslis3X && x<=skerslis3X+skerslis3GAR) && (y+8>=skerslis3Y && y<=skerslis3Y+skerslis3AUGST)) {
        //zaude=true;
        return;
      }
      if ((x+8>=skerslis4X && x<=skerslis4X+skerslis4GAR) && (y+8>=skerslis4Y && y<=skerslis4Y+skerslis4AUGST)) {
        //zaude=true;
        return;
      }
    }

    skerslis1AUGST=i/64;
    skerslis2Y=j;
    skerslis3GAR=(i-64)/8;
    skerslis4X=k;

    i++;
    if (i%64==0)j--;
    if (i%8==0)k--;
  
    // istaba saspiezas no visām pusēm
    if (zimet){
    display.fillRect(skerslis1X,skerslis1Y,skerslis1GAR,skerslis1AUGST,WHITE);
    display.fillRect(skerslis2X,skerslis2Y,skerslis2GAR,skerslis2AUGST,WHITE);
    display.fillRect(skerslis3X,skerslis3Y,skerslis3GAR,skerslis3AUGST,WHITE); 
    display.fillRect(skerslis4X,skerslis4Y,skerslis4GAR,skerslis4AUGST,WHITE);
    }

    if (pass && y>=6 && y+8<=27 && x==128) istaba++; // izdzīvo šo istabu, paliekot gandrīz centrā, tiec uz nākamo istabu

    //zvaigznes(); // te nav paredzētas zvaigznes
    virziens(xPieaug, xSamazinas, yPieaug, ySamazinas,x,y,xj,yj);
    display.display();
    display.clearDisplay();
  }
  if (istaba==5) zaude=true;
  else zaude=false;
}

// uzvaras istaba. šeit sākumā ir tukšs, balts ekrāns, kurā redzamas tikai zvaigznes, un pēc tam ekrāns paliek melns, un secīgi, ar nelielu laika nobīdi pēc katra burta, parādās burti, kas veido uzrakstu "VICTORY" pa visu ekrānu.
void istaba8(bool &zaude){
  if (zaude) return;
  int i, d=1;
  int j=1;
  int jam=20;
  display.setTextSize(2);
  for (i=0; i<=50; i++){
    display.invertDisplay(true); // ekrāns paliek balts
    display.display();
    delay(d);
    display.clearDisplay();
  }

  // balts ekrāns ar zvaigznēm 
  for (i=0; i<=100; i++){
    zvaigznes();
    display.display();
    delay(d);
    display.clearDisplay();
  }

  // ekrāns paliek melns ar zvaigznēm
  display.invertDisplay(false); // ekrāns paliek melns
  for (i=0; i<=30; i++){
    zvaigznes();
    display.display();
    delay(d);
    display.clearDisplay();
  }

  // sākam zīmēt VICTORY uzrakstu. šo varēja uztaisīt par vienu metodi, kuru izsauc ciklā ar laika nobīdi un parametrā padod burtus un to koordinātas, lai tīrāks kods. 
  i=0;
  while (i<=d){
  zvaigznes();
  display.setCursor(0, 10);
  display.setTextColor(WHITE);
  display.setCursor(15,10);
  display.print("V");
  display.display();
  delay(d);
  display.clearDisplay();
  i++;
  }
  i=0;
  while (i<=d){
  zvaigznes();
  display.setCursor(15,10);
  display.print("V");
  display.setCursor(30,10);
  display.print("I");
  display.display();
  delay(d);
  display.clearDisplay();
  i++;
  }
  i=0;
  while (i<=d){
  zvaigznes();
  display.setCursor(15,10);
  display.print("V");
  display.setCursor(30,10);
  display.print("I");
  display.setCursor(45,10);
  display.print("C");
  display.display();
  delay(d);
  display.clearDisplay();
  i++;
  }
  i=0;
  while (i<=d){
  zvaigznes();
  display.setCursor(20,15);
  display.setCursor(15,10);
  display.print("V");
  display.setCursor(30,10);
  display.print("I");
  display.setCursor(45,10);
  display.print("C");
  display.setCursor(60,10);
  display.print("T");
  display.display();
  delay(d);
  display.clearDisplay();
  i++;
  }
  i=0;
  while (i<=d){
  zvaigznes();
  display.setCursor(15,10);
  display.print("V");
  display.setCursor(30,10);
  display.print("I");
  display.setCursor(45,10);
  display.print("C");
  display.setCursor(60,10);
  display.print("T");
  display.setCursor(75,10);
  display.print("O");
  display.display();
  delay(d);
  display.clearDisplay();
  i++;
  }
  i=0;
  while (i<=d){
  zvaigznes();
  display.setCursor(15,10);
  display.print("V");
  display.setCursor(30,10);
  display.print("I");
  display.setCursor(45,10);
  display.print("C");
  display.setCursor(60,10);
  display.print("T");
  display.setCursor(75,10);
  display.print("O");
  display.setCursor(90,10);
  display.print("R");
  display.display();
  delay(d);
  display.clearDisplay();
  i++;
  }
  i=0;
  while (i<=100){
  zvaigznes();
  display.setCursor(15,10);
  display.print("V");
  display.setCursor(30,10);
  display.print("I");
  display.setCursor(45,10);
  display.print("C");
  display.setCursor(60,10);
  display.print("T");
  display.setCursor(75,10);
  display.print("O");
  display.setCursor(90,10);
  display.print("R");
  display.setCursor(105,10);
  display.print("Y");
  display.display();
  delay(d);
  display.clearDisplay();
  i++;
  }
  display.setTextSize(1);
  display.clearDisplay();
  //delay(1000);
}

// zvaigznu zīmēšanas metode. tiek vienlaicīgi uzzīmēti 3 punkti pilnīgi nejaušā vietā uz ekrāna. šī metode tiek izsaukta katrā spēles ekrāna iterācijā, radot vizuālu iespaidu, ka zvaigznes mirguļo un spīguļo.
void zvaigznes(){
    display.drawPixel(random(0,128), random(0,32), WHITE); 
    display.drawPixel(random(0,128), random(0,32), WHITE);
    display.drawPixel(random(0,128), random(0,32), WHITE);
}

// metode, kas atbild par varoņa pārvietošanos pa ekrānu. šī metode varoni nezīmē, bet tikai nosaka tā pozīciju un staigāšanas animāciju.
void virziens(bool &xPieaug, bool &xSamazinas, bool &yPieaug, bool &ySamazinas, int &x, int &y, int &xj, int &yj){

    /*
    te būs vairākas variācijas, piem., kas notiek, kad varonis iet uz augšu un tiek nospiesta poga = varonim tad ir jāmaina virziens uz kreiso pusi.
    */
    if (xPieaug==true && digitalRead(poga)==HIGH) {
      ySamazinas=true; // virziens turpināsies pretēji plkst. rādītāja virzienam
      xPieaug=false;
      xSamazinas=false;
      yPieaug=false;
      while (digitalRead(poga)==HIGH){
        delay(10); // lai nospiešana netiktu uzreiz reģistrēta atkārtoti - lai tiktu reģistrēts tikai viens tāds pogas klikšķis
      }
    }
    if (xSamazinas==true && digitalRead(poga)==HIGH) {
      yPieaug=true;
      xSamazinas=false;
      ySamazinas=false;
      xPieaug=false;
      while (digitalRead(poga)==HIGH){
        delay(10);
      }
    }
    if (yPieaug==true && digitalRead(poga)==HIGH) {
      xPieaug=true;
      yPieaug=false;
      ySamazinas=false;
      xSamazinas=false;
      while (digitalRead(poga)==HIGH){
        delay(10);
      }
    }
    if (ySamazinas==true && digitalRead(poga)==HIGH) {
      xSamazinas=true;
      ySamazinas=false;
      xPieaug=false;
      yPieaug=false;
      while (digitalRead(poga)==HIGH){
        delay(10);
      }
    }

      // animāciju zīmēšana
      // doma tāda, ka ar if nosakām virzienu, un tad ar ļoti īsu periodu pārslēdzamies starp abām pašā faila augšā iekodētajām bitmap bildēm, veidojot staigāšanas animāciju

      if (xPieaug){
      x++;
      if (x%4==0) xj++;
      if (xj%2==0) display.drawBitmap(x,y, right1, 8,8, WHITE);
      else display.drawBitmap(x,y, right2, 8,8, WHITE);
    }
    if (yPieaug){
      y++;
      if (y%4==0) yj++;
      if (yj%2==0) display.drawBitmap(x,y, down1, 8,8, WHITE);
      else display.drawBitmap(x,y, down2, 8,8, WHITE);
    }
    if (xSamazinas){
      x--;
      if (x%4==0) xj--;
      if (xj%2==0) display.drawBitmap(x,y, left1, 8,8, WHITE);
      else display.drawBitmap(x,y, left2, 8,8, WHITE);
    }
    if (ySamazinas){
      y--;
      if (y%4==0) yj--;
      if (yj%2==0) display.drawBitmap(x,y, up1, 8,8, WHITE);
      else display.drawBitmap(x,y, up2, 8,8, WHITE);
    }
}

// galvenā izvēlne
void menu(){
  int i=1, j=65;
  bool box=true;

  // kamēr nav nekādas lietotāja ievades, kamēr poga NAV nospiesta, zīmējam galvenās izvēlnes ekrānu
  while (digitalRead(poga)==LOW && i>0){
    zvaigznes(); // zīmējam zvaigznes
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.setTextSize(2);

    // zīmējam mazu kastīti kā norādi lietotājam, kas būs jādara spēlē.
    if (box) display.drawRect(100,5,5,5,WHITE);
    if (j+8>=100) box=false; // ja varonis ir uzgājis uz kastītes, tā galvenajā izvēlnē ir savākta un vairs netiek zīmēta

    // zīmējam durvis
    display.drawLine(122,1,128,1, WHITE);
    display.drawLine(122,14,128,14, WHITE);

    // spēles nosaukums
    display.print("MOGUS");
    if (i%32==0) j++; // lai varonis galvenajā ekrānā pats no sevis ļoti, ļoti lēni virzītos uz durvīm pa labi
    if (j>=129) return; // ja varonis tādā veidā iziet no ekrāna, spēle sākas automātiski
    display.drawBitmap(j, 4, right1, 8,8, WHITE);

    // maza, apaļa poga uz ekrāna, kas simbolizē lietotājam, ka jāspiez poga, lai sāktu spēli. ifs nepieciešams, lai poga ik pa laikam varētu pulsēt, norādot, ka tā ir jāspiez
    if (i%32==0) display.drawCircle(60,22,5,WHITE); 
    else display.drawCircle(60,22,6,WHITE);

    // zīmējam press to start tekstu
    display.setCursor(19,19);
    display.setTextSize(1);
    display.print("press");
    display.setCursor(72,19);
    display.print("to start");
    display.display();
    display.setTextSize(1);
    display.clearDisplay();
    delay(10);
    i++; // iterācijas, kas vajadzīgas animācijām un kustībām galvenajā izvēlnē
  }

  // ja tiek nospiesta poga, sāksies spēle, bet vispirms notiek animācija, kur varonis iet uz durvīm
  if (digitalRead(poga)==HIGH){ 
    while (digitalRead(poga)==HIGH){
      display.invertDisplay(true); //nospiezot pogu, ekrāns paliek balts uz vienu frame
    }
    display.invertDisplay(false); // ekrāns paliek atkal melns
    while (j<=129){
      zvaigznes();
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.setTextSize(2);

      // kastītes zīmēšana un ar if palīdzību arī savākšana galvenajā izvēlnē pēc pogas nospiešanas
      if (box) display.drawRect(100,5,5,5,WHITE);
      if (j+8>=103) box=false;

      display.drawLine(122,1,128,1, WHITE);
      display.drawLine(122,14,128,14, WHITE);
      display.print("MOGUS");
      j++;
      display.drawBitmap(j, 4, right1, 8,8, WHITE); // varonis iet uz durvīm
      display.display();
      display.clearDisplay();
      delay(5);
      i++;
    }

    // neliela pauze, līdz sākas spēle - tukšs ekrāns ar zvaigznēm
    int k=0;
    while (k<=15){
      zvaigznes();
      display.display();
      delay(10);
      k++;
      display.clearDisplay();
    }
    return; // būs pāreja uz spēli, pirmo istabu
  }
}

// zaudēšanas animācijas metode
void zaudeFN(){

  // te ir iešūta varoņa rotācija, katrs mazais koda bloks parāda varoni, pagrieztu par 90 grādiem
  #define right1r_width  8
  #define right1r_height 8
  static unsigned char right1r [] = {
  0x3c,0x5e,0xa1,0xa1,0xbe,0x42,0x5a,0x66};

  #define right2r_width  8
  #define right2r_height 8
  static unsigned char right2r [] = {
  0x1c,0xe2,0x9d,0x53,0x53,0x93,0xf2,0x0c};
  
  #define right3r_width  8
  #define right3r_height 8
  static unsigned char right3r [] = {
  0x66,0x5a,0x42,0x7d,0x85,0x85,0x7a,0x3c};

  #define right4r_width  8
  #define right4r_height 8
  static unsigned char right4r [] = {
  0x30,0x4f,0xc9,0xca,0xca,0xb9,0x47,0x38};

    display.setTextSize(1);
    int i;
    int j=1;
    int jam=20;

    // sākumā ir aizture - tukšs ekrāns ar zvaigznēm, lai izskatās kā atklāts kosmoss
    for (i=0; i<=10; i++){
      zvaigznes();
      display.display();
      delay(5);
      display.clearDisplay();
    }
    // tad sākas animācija, ka varonis tiek izmests kosmosā (ar rotācijas animāciju
    for (i=-8; i<=135; i++){ //kur i ir x koordināta uz ekrāna
      if (i%9==0) j++; // lai rotācija notiek reizi 9 pikseļos pa x asi
      if (i%8==0) jam--;
      if (j==5) j=1;
      // zemāk ir rotācijas funkcionalitāte. ja koordināta ir
      switch (j) {
        case 1: {
          display.drawBitmap(i,jam, right1r, 8,8, WHITE);
          break;
        }
        case 2: {
          display.drawBitmap(i,jam, right4r, 8,8, WHITE);
          break;
        }
        case 3: {
          display.drawBitmap(i,jam, right3r, 8,8, WHITE);
          break;
        }
        case 4: {
          display.drawBitmap(i,jam, right2r, 8,8, WHITE);
          break;
        }
      }

      // kad varonis ir palidojis gandrīz pāri ekrānam, parādās paziņojums par zaudēšanu
      if (i>95) {
          display.setCursor(20, 10);
          display.setTextColor(WHITE);
          display.print("impostors won");
      }

      // zīmējam zvaigznes aiz varoņa
      zvaigznes();
      display.display();
      delay(5);
      display.clearDisplay();

    }

    // tukšs ekrāns ar zvaigznēm un uzrakstu
    for (i=0; i<=30; i++){
      zvaigznes();
      display.setCursor(20, 10);
      display.setTextColor(WHITE);
      display.print("impostors won");
      display.display();
      delay(5);
      display.clearDisplay();
    }

    // tukšs ekrāns ar zvaigznēm
    for (i=0; i<=15; i++){
      zvaigznes();
      display.display();
      delay(5);
      display.clearDisplay();
    }
}

  /*       NEIZMANTOTI RESURSI
  
  display.drawBitmap(0, 0, right, 8,8, WHITE);
  display.drawBitmap(10, 0, left, 8,8, WHITE);
  display.drawBitmap(20, 0, up, 8,8, WHITE);
  display.drawBitmap(30, 0, down, 8,8, WHITE);
  
  */


/*      static left
#define leftr1_width 8
#define leftr1_height 8

static unsigned char leftr1 [] =
{
 0x3c,0x7a,0x85,0x85,0x7d,0x42,0x5a,0x66
};
------------------------------------


      static right
#define right1r_width  8
#define right1r_height 8
static unsigned char right1r [] = {
 0x3c,0x5e,0xa1,0xa1,0xbe,0x42,0x5a,0x66
};

#define right2r_width  8
#define right2r_height 8
static unsigned char right2r [] = {
 0x1c,0xe2,0x9d,0x53,0x53,0x93,0xf2,0x0c};
 
#define right3r_width  8
#define right3r_height 8
static unsigned char right3r [] = {
 0x66,0x5a,0x42,0x7d,0x85,0x85,0x7a,0x3c};

#define right4r_width  8
#define right4r_height 8
static unsigned char right4r [] = {
 0x30,0x4f,0xc9,0xca,0xca,0xb9,0x47,0x38};
*/