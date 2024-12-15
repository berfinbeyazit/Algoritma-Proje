#include <stdio.h>

typedef struct  //personelin yapısının belirlenmesi her personel için sicili,adı,soyadı ve satış miktarı tutulacak
{
    int sicil;
    char ad[50];
    char soyad[50];
    int satis;
} Personel;

int main(void)
{
    int personelSayisi = 0;
    int maxPersonel = 50;
    int maxSatis = 0;
    Personel personel[maxPersonel]; //personel bilgilerini tutacağımız dizinin oluşturulması


    FILE* yillikp = fopen("yillik.dat", "r"); //yillik.dat dosyamızı okuma modunda aç
    if (yillikp == NULL)
    {
        printf("Dosya Bulunamadi\n"); //dosyanın bulunamaması durumunda yazılacak hata mesajımız
        return 0;
    }
    else
    {
        while (fscanf(yillikp, "%d %s %s %d", &personel[personelSayisi].sicil, &personel[personelSayisi].ad,
                      &personel[personelSayisi].soyad,
                      &personel[personelSayisi].satis) == 4) //yillik.dat icerisindeki verilerimizin okunma işlemi
        {
            if (personel[personelSayisi].satis > maxSatis) // en yüksek satısı bulma işlemi
            {
                maxSatis = personel[personelSayisi].satis;
            }
            personelSayisi++;
        }
        fclose(yillikp); //dosyayı kapat
    }

    FILE* satisp = fopen("satislar.dat", "w"); // satislar.dat dosyamızı yazma modunda aç
    if (satisp == NULL)
    {
        printf("Hata Olustu Program Kapatiliyor\n"); //dosya olusturulamadığı durumda yazılacak hata mesajı
        return 1;
    }
    else
    {
        for (int i = 0; i < personelSayisi; i++)
        {
            int ihtiyac = maxSatis - personel[i].satis;
            //en fazla satıs yapan personele ulaşmak için gerekli satis miktarının bulunması
            fprintf(satisp, "%d %s %s %d\n", personel[i].sicil, personel[i].ad, personel[i].soyad, ihtiyac);
            //sicil,ad,soyad ve en yüksek satış yapan personele ulaşılması için gerekli olan ihtiyacın satislar.dat dosyasına yazdırılma işlemi
        }
        fclose(satisp); //dosyanın kapatılması
        printf("satislar.dat Dosyasina Yazdirilma Isi Basariyla Tamamlandi\n");
        return 0;
    }
}
