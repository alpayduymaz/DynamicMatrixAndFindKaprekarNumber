#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//prototip fonksiyonlar
void MatrisBoyutlari();
void DinamikMatrisOlusturma(int Satir,int Sutun);
void MatrisiRastgeleDoldurma(int *MatrisinAdresiniTutucu, int SatirinUzunlugu);
void BubbleSort(int *MatrisSatiri, int SatirBoyutu);
void Takas(int *Ptr1, int *Ptr2);
void DosyayaYazma(int **DinamikMatris, int Satir, int Sutun);
void TranspozeMatrisiOlusturma(int **DinamikMatris,int Satir, int Sutun);
int KaprekarAramasi(int **TranspozeMatris, int Satir, int Sutun);
int KaprekarMi(int sayi);
void KaprekariDosyayaYazma(int *DosyayaYazilacakKprkrSayilar, int boyut);

int main()
{
    MatrisBoyutlari();
    return 0; //program bitiyor
}
void MatrisBoyutlari()  //Matrisin satir ve sutunlari belirleniyor
{
    int Satir,Sutun;
    printf("Satir:");
    scanf("%d",&Satir);
    printf("\n");
    printf("Sutun:");
    scanf("%d",&Sutun);
    printf("\n");
    DinamikMatrisOlusturma(Satir,Sutun); //Satir ve Sutun bilgileri dinamikmatrisolusturmaya gönderiliyor
}
void DinamikMatrisOlusturma(int Satir,int Sutun)
{
    int i;
    int **DinamikMatris;

    DinamikMatris = (int*)malloc(Satir*sizeof(int));  //Ramdan satir boyutunda yer ayriliyor.
    for(i=0;i<Satir;i++)
        DinamikMatris[i] = (int*)malloc(Sutun*sizeof(int)); //Ramdan her bir satir icin sutun boyutunda yer ayriliyor.

    srand(time(NULL));   // Her seferinde farkli sayilar alabilmesi için srand(time(NULL)) dahil ediliyor.
    for(i=0;i<Satir;i++)
    MatrisiRastgeleDoldurma(&DinamikMatris[i][0],Sutun);   //Matrisin her bir satirindaki elemanlara rastgele degerler atanmasi icin MatrisiRastgeleDoldurma(&DinamikMatris[i][0],Sutun) fonksiyonu parametreleri ile cagiriliyor.

    for(i=0;i<Satir;i++)
    BubbleSort(&DinamikMatris[i][0],Sutun); //Matrisin her bir satirindaki elemanlarin kucukten buyuge siralanmasi icin BubbleSort(&DinamikMatris[i][0],Sutun) fonksiyonu parametreleri ile cagiriliyor.

    DosyayaYazma(DinamikMatris,Satir,Sutun); //DinamikMatris,Satir,Sutun parametreleri ile hem matrisi hemde transpozunu dosyaya yazma fonksiyonu cagiriliyor.

    TranspozeMatrisiOlusturma(DinamikMatris,Sutun,Satir); //Matrisin transpozesi aliniyor!!! Buradaki önemli nokta TranspozeMatrisiOlusturma fonksiyonunun parametresindeki satira sutun, sutuna ise satir ataniyor cunku DüzMatrisin satir boyutu Transpozunun sutun boyutu olacaktir, DüzMatrisin sutun boyutuda Transpozunun satir boyutu olacaktir.

    for(i=0;i<Satir;i++)  //Ramdan ayrilan her bir satirin sutun uzunlugundaki bellek geri birakiliyor.
        free(DinamikMatris[i]);
    free(DinamikMatris); //Ramdan her bir satir icin ayrilan bellek geri birakiliyor.
}

void MatrisiRastgeleDoldurma(int *MatrisinAdresiniTutucu, int SatirinUzunlugu)
{
    int i,j;
    int RastgeleDeger1,RastgeleDeger2;
    for(i=0;i<SatirinUzunlugu;i++)
        {
            RastgeleDeger1 = 3+rand()%19998;  //[3 - 20000] araliginda rastgele sayi üretilip RastgeleDeger1 degiskenine atiliyor
            RastgeleDeger2 = 2+rand()%19999;  //[2 ile 20000] araliginda rastgele sayi üretilip RastgeleDeger2 degiskenine atiliyor
            MatrisinAdresiniTutucu[i] = RastgeleDeger1 + RastgeleDeger2; //[5 - 40000] araligindaki toplam degeri gelen Matris satirinin i. deðerine ataniyor
        }
}

void BubbleSort(int *MatrisSatiri, int SatirBoyutu)  //Kabarcik siralamasi yapiliyor
{
    int i,j;
    for(i=0;i<SatirBoyutu-1;i++)
        for(j=0;j<SatirBoyutu-1;j++)
            if(MatrisSatiri[j]>MatrisSatiri[j+1])  //Matris satirinin j. degeri j+1. degerinden buyukse
                Takas(&MatrisSatiri[j],&MatrisSatiri[j+1]); // Matris Satirinin j. degeri ile j+1. degeri adreslenerek takas icin takas fonksiyonuna gönderiliyor.
}
void Takas(int *Ptr1, int *Ptr2)
{
    int gecici=*Ptr1; //Buyuk sayi bir degiskene ataniyor
    *Ptr1=*Ptr2;  //Kucuk sayi buyuk sayiyi tutan degiskene ataniyor ve artik bu degisken kucuk sayiyi tutuyor
    *Ptr2=gecici; //Buyuk sayida daha önce kucuk sayiyi tutan degiskene ataniyor boylece pointer vasitasiyla matris elemanlarinin yerleri degisiyor
}

void DosyayaYazma(int **DinamikMatris, int Satir, int Sutun)
{
    int i,j;
    FILE *MatrisDosyasiPtr;
    if( (MatrisDosyasiPtr = fopen("Transpoze.txt","w")) == NULL ) //Dosyanin acilip acilmama kontrolü yapiliyor.
    {
        printf("Dosya Acilamadi");
        exit(1);
    }
    for(i=0;i<Satir;i++) //Düz Matris Transpoze.txt ye yazdiriliyor
    {
        for(j=0;j<Sutun;j++)
            fprintf(MatrisDosyasiPtr,"%d ",DinamikMatris[i][j]);
        fputc('\n',MatrisDosyasiPtr);
    }
    fputc('\n',MatrisDosyasiPtr);
    for(i=0;i<Sutun;i++) //Matrisin Transpozesi Transpoze.txt ye yazdiriliyor
    {
        for(j=0;j<Satir;j++)
            fprintf(MatrisDosyasiPtr,"%d ",DinamikMatris[j][i]);
        fputc('\n',MatrisDosyasiPtr);
    }
    printf("Yazdirma islemi tamamlandi\n");
    fclose(MatrisDosyasiPtr); //Matris dosyasi kapatiliyor
}

void TranspozeMatrisiOlusturma(int **DinamikMatris,int Satir, int Sutun)
{
    int i,j;
    int **TranspozeMatris;
    TranspozeMatris = (int*)malloc(Satir*sizeof(int)); //TranspozeMatrise ramden satir boyutunda alan ayriliyor
    for(i=0;i<Satir;i++)
        TranspozeMatris[i] = (int*)malloc(Sutun*sizeof(int)); //TranspozeMatrisin her i. satiri icin ramdan sutun boyutunda alan ayriliyor

    for(i=0;i<Satir;i++)  //Düz Matrisin Sutun sayisi, TranspozeMatrisin Satir sayisi kadar dönecek ki zaten bunlar birbirine eşittir
        for(j=0;j<Sutun;j++)  //Düz Matrisin Satir sayisi, TranspozeMatrisin Sutun sayisi kadar dönecek ki zaten bunlar birbirine eşittir
            TranspozeMatris[i][j] = DinamikMatris[j][i];  //Düz Matrisin Sutuna Satirinci degeri TranspozeMatrisin Satıra Sutununcu degerine ataniyor.

    KaprekarAramasi(TranspozeMatris,Satir,Sutun);  //TranspozeMatris üzerinde kaprekar araması yapilmasi icin TranspozeMatris KaprekarAramasi fonksiyonuna boyutlariyla parametre olarak geciriliyor


    for(i=0;i<Satir;i++)
        free(TranspozeMatris[i]);  //Ramden ayrılan her satir icin sutun kadar alan geriye birakiliyor.
    free(TranspozeMatris);  //Ramden ayrılan satir kadar alan geriye birakiliyor.
}

int KaprekarAramasi(int **TranspozeMatris, int Satir, int Sutun)
{

    int i,j,k=0;
    int *KaprekarSayilar;
    for(i=0;i<Satir;i++)
        for(j=0;j<Sutun;j++)
            if(KaprekarMi(TranspozeMatris[i][j])) //KaprekarMi fonksiyonuna gonderilen sayi kaprekar ise yani KaprekarMi fonksiyonu 1 donerse
                {
                    KaprekarSayilar[k] = TranspozeMatris[i][j]; //KaprekarSayilar dizisinin k. elemanina o sayi ataniyor
                    k++; //k bir arttiriliyor
                }
    if(k==0) //Eger k hic artmadi ise yani KaprekarMi fonksiyonu hic 1 return etmediyse
        printf("Kaprekar sayisi yok\n"); //Kaprekar sayisi yok diye ekrana belirtiliyor
    else KaprekariDosyayaYazma(&KaprekarSayilar[0],k); //Kaprekar sayilari tutan dizi KaprekariDosyayaYazma parametresine adresleniyor, boyutuda k oldugu icin boyut olarak k gönderiliyor
}

int KaprekarMi(int sayi)
{
    int ModundanKalan,karesi,carpan=1;

    while(carpan < sayi)
        carpan *= 10;   //Matristen gelen sayi 10un bir kuvveti degilse sayinin basamak sayisi kadar 10un kuvveti alinip carpan degiskenine ataniyor

    if(sayi == carpan) //Matristen gelen sayi 10un bir kuvveti ise bu if calisiyor ve fonksiyon 0 dönüp sonlaniyor
        return 0;

    karesi = sayi*sayi;  //Matristen gelen sayinin karesi karesi degiskenine ataniyor

    while( (ModundanKalan = karesi % carpan) < sayi ) //Karesinin carpana göre modu sayidan kücük oldugu sürece
        {
            if(karesi / carpan + ModundanKalan == sayi) //Karesinin carpana bolumu ile karesinin carpana göre modu(yani modundan kalan degeri)'nin toplami sayiya esit ise
            return 1; //Fonksiyon 1 return ediyor yani sayi kaprekar!!!
            carpan *= 10; //Karesinin carpana bolumu ile karesinin carpana göre modunun toplami sayiya esit degilse carpan degeri 10 katina cikiyor ve döngü devam ediyor cunku karesinin solundaki basamaklardaki ilk deger 0 olabilir ör:4879^2=23804641 => 238+4641=4879 yani karesinin carpana bolumunden gelen degerin ilk basamagi 0 olabilir bunu denetlemek icin carpanı dongude her seferinde 10 katina cikariyoruz bu durum zaten az onceki ornekteki gibi bir sayiysa sayinin carpana gore modunu desigtirmez
        }
    return 0;  //Eger Sayinin karesinin carpana göre modu zaten sayidan büyükse dongu sonlaniyor, cunku bu modundan kalan degeriyle sayinin carpana bolumunun toplamı sayiya esit olmasi imkansizdir boylece fonksiyon 0 donuyor ve cagirildigi yerde if blogu calismiyor
}

void KaprekariDosyayaYazma(int *DosyayaYazilacakKprkrSayilar, int boyut)
{
    int i;
    FILE *KaprekarDosya;
    if( (KaprekarDosya = fopen("Kaprekar.txt","w")) == NULL )  //Kaprekar.txt dosyasinin acilip acilmama kontrolü yapiliyor
    {
        printf("Dosya Acilamadi");
        exit(1);
    }
    for(i=0;i<boyut;i++)       //Bu döngü ilede kaprekar sayilar dosyaya yazdiriliyor
    fprintf(KaprekarDosya,"%d ",DosyayaYazilacakKprkrSayilar[i]);
    fclose(KaprekarDosya); //Kaprekar.txt dosyasi kapatiliyor
}

