


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct book {
    int book_ID;
    char book_title[50];
    char book_author[50];
    bool book_status;

};

struct member {
    char member_ID[12];
    char member_name[50];
    char member_phone[11];
};

struct borrow {
    int book_ID;
    char member_ID[12];
    char borrow_date[11];
    char return_date[11];

};

struct book *books;
struct member *members;
struct borrow *borrows;

int count_book=0;
int count_member=0;
int count_borrows=0;

void add_book();
void delete_book();
void search_book();
void list_book();

void add_member();
void search_member();
void list_member();

void borrow_book();
void return_book();
void list_borrows();

void list_Nonborrowed();
void list_borrowed();




int main(){

    books = malloc(100 * sizeof(struct book));  // Kitaplar icin dinamik bellek 
    members = malloc(100 * sizeof(struct member));  // Uyeler icin dinamik bellek 
    borrows = malloc(100 * sizeof(struct borrow));  // Odunc islemleri icin dinamik bellek 

    int choice=0;

    while(choice !=5){
    
    printf ("\t--Kutuphane Yonetim Sistemi--\n");
    printf("1. Kitap Yonetimi\n");
    printf("2. Uye Yönetimi\n");
    printf("3. Odunc Islemleri\n");
    printf("4. Raporlama\n");
    printf("5. Cikis\n");

    printf ("Lutfen yapmak istediginiz secimi girin: ");
    scanf_s("%d", &choice);

    if (choice==5){
        printf ("Cikis yapildi.\n");
        break;

    }
    
    switch(choice){ //ana menünün isleyisi için switch-case kullanilir
        case 1: {
            int choice_book;
            printf ("\t--Kitap Yönetimi--\n");
            printf ("1.Kitap Ekleme.\n");
            printf ("2.Kitap Silme.\n");
            printf ("3.Kitap Bulma.\n");
            printf ("4.Kitap Listele.\n");

            printf ("Lutfen Seciminizi Giriniz: \n");
            scanf_s ("%d", &choice_book);

            switch (choice_book){
                case 1:
                add_book();
                break;

                case 2:
                delete_book();
                break;

                case 3:
                search_book();
                break;

                case 4:
                list_book();
                break;

                default: 
                printf ("Gecersiz secim.\n");

            }
        break; 
        }

        case 2: {
            int choice_member;
            printf ("\t--Uye Yonetimi--\n");
            printf ("1.Uye Ekleme.\n");
            printf ("2.Uye Bulma.\n");
            printf ("3.Uyeleri Listele.\n");

            printf ("Lutfen Seciminizi Giriniz: \n");
            scanf_s ("%d", &choice_member);

            switch (choice_member){
                case 1:
                add_member();
                break;

                case 2:
                search_member();
                break;

                case 3:
                list_member();
                break;

                default:
                printf ("Gecersiz islem");
            
            }
        break;
        }

        case 3:{
        int choice_borrow;
            printf ("\t--Odunc Islemleri--\n");
            printf ("1.Kitap odunc alma.\n");
            printf ("2.Kitap iadesi alma.\n");
            printf ("3.Odunc listesi görüntüleme.\n");

            printf ("Lütfen Seciminizi Giriniz: \n");
            scanf_s ("%d", &choice_borrow);

            switch (choice_borrow){
                case 1:
                borrow_book();
                break;

                case 2:
                return_book();
                break;

                case 3:
                list_borrows();
                break;

                default:
                printf ("gecersiz işlem\n");
            
            }
        break;
        }

        case 4:{
        int choice_report;
            printf ("\t--Raporlama--\n");
            printf ("1.Mevcut Kitaplari Listeleme.\n");
            printf ("2.Odunc Alinan Kitaplari Listeleme\n");

            printf ("Lutfen Seciminizi Giriniz: \n");
            scanf_s ("%d", &choice_report);

            switch (choice_report){
                case 1:
                list_Nonborrowed();
                break;

                case 2:
                list_borrowed();
                break;

                default:
                printf ("Gecersiz islem");

            }
        break;
        }

        case 5:
        printf ("Cikis yapiliyor.");
        free(books);
        free(members); 
        free(borrows); //dinamik bellekler manuel olarak serbest bırakilir
        return 0;

        default:
        printf ("Gecersiz islem");
            


        }

    }
    free(books);
    free(members);
    free(borrows); //dinamik bellekler manuel olarak serbest bırakilir

    return 0;
}


void replace_characters(char *str, char replace, char replacement) { //kitap ismi, uye ismi ve yazar ismi alırken sorun ortaya cikabilir
    for (int i = 0; str[i] != '\0'; i++) {                          //  bu sebepten oturu iki isimli string degiskenlerini saklamak ve geri kolaylıkla yazdırabilmek için 
        if (str[i] == replace) {                                    //space ile _ karakteri degisimi icin ekstradan bir fonksiyon ekleriz
            str[i] = replacement;
        }
    }
}

void add_book(){
    FILE *file = fopen("books.txt", "a");
    if (file == NULL) {
        printf("Kitap dosyasi acilamadi.\n");
        return;
    }

    struct book new_book;
    printf ("Lutfen kitap ID giriniz: \n");  //scanf zaten char boyutu kadar algılayacagı için her halukarda fgets kullanmayiz
    scanf ("%d", &new_book.book_ID);

    printf ("Lutfen kitap basligini giriniz: ");
    getchar();
    fgets (new_book.book_title, sizeof(new_book.book_title), stdin);
    
    

    printf ("Lutfen kitap yazarini giriniz: ");
    fgets (new_book.book_author, sizeof(new_book.book_author), stdin);


    new_book.book_status= 1;     //ekledigimiz kitabın stastusunu manuel olarak ayarlariz

    books[count_book] =new_book;  
    count_book++; //daha sonraki list vb gibi fonksiyonlarda kullamak icin de kitap sayısı icin bi degisken kullaniriz

    replace_characters(new_book.book_title, ' ', '_');
    replace_characters(new_book.book_author, ' ', '_');
    fprintf(file, "%d\n%s%s\n%d\n", new_book.book_ID, new_book.book_title, new_book.book_author, new_book.book_status); //dosyaya yazdirir
    fclose(file);

    printf("Kitap basariyla eklendi.\n");
}




void delete_book(){
    
    int book_ID;
    printf("Silmek istediginiz kitabin ID'sini girin: ");
    scanf("%d", &book_ID);

    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Kitap dosyasi acilamadi.\n");
        return;
    }

    FILE *temp_file = fopen("temp_books.txt", "w"); //olasi yanlis yazilma durumunu onlemek için gecici bir dosya olustururuz
    if (temp_file == NULL) {
        printf("Gecici dosya acilamadi.\n");
        fclose(file);
        return;
    }

    int found = 0;
    struct book current_book;

    while (fscanf(file, "%d\n%s\n%s\n%d\n", 
                  &current_book.book_ID, 
                  current_book.book_title, 
                  current_book.book_author, 
                  &current_book.book_status) != EOF) {
        if (current_book.book_ID == book_ID) {
            found = 1; // Silinecek kitap bulur ve eger found =1 ise diger if blogunu calıstirir 
        } else {
            // Kitap bilgilerini gecici dosyaya yazdirir
            fprintf(temp_file, "%d\n%s\n%s\n%d\n", 
                    current_book.book_ID, 
                    current_book.book_title, 
                    current_book.book_author, 
                    current_book.book_status);
        }
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
        // Eski dosyayı siler ve gecici dosyayi yeniden adlandir yani eski her kitap silindiginde dosyayi siler, kaydettiklerini tempe aktarır ve temp dosyasinin ismini degistirir
        if (remove("books.txt") == 0 && rename("temp_books.txt", "books.txt") == 0) { 
            printf("Kitap basariyla silindi.\n");
        } else {
            printf("Dosya islemlerinde hata oluştu.\n");
        }
    } else {
        // Silme islemi basarısız olursa da temp dosyasını siler
        remove("temp_books.txt");
        printf("Silmek istediginiz kitap bulunamadi.\n");
    }
}

    

void search_book(){
    int book_ID;
    int found=0;

    printf("Aramak istediginiz kitabin ID'sini giriniz: ");
    scanf_s("%d", &book_ID);

    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Kitap dosyasi acilamadi.\n");
        return;
    }
    int count=0;

    while (fscanf(file, "%d\n%s\n%s\n%d\n", &books[count].book_ID, books[count].book_title, books[count].book_author, &books[count].book_status)!=EOF) {
        replace_characters(books[count].book_title, '_', ' ');
        replace_characters(books[count].book_author, '_', ' ');

        if (books[count].book_ID == book_ID) {

            printf("Kitap bulundu:\n");
            printf("ID: %d\nBaslik: %s\nYazar: %s\n", books[count].book_ID, books[count].book_title, books[count].book_author);

            if (books[count].book_status == true) { //statusu belirlemek için bir if kullaniriz
                printf("Durum: Mevcut\n");
            } else if (books[count].book_status == false) {
                printf("Durum: Oduncte\n");
 
            }
            found=1;
        
        }
        count++; //dongu icin gereklidir
    }

    fclose(file);
    if (!found) {
        printf("Kitap bulunamadi.\n");
    
    
    }
}

void list_book(){
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Kitap dosyasi acilamadi.\n"); //ayni mantikla calisir, tek fark arama yerine cikti olarak kitaplari yine bir döngü ile listeler
        return;
    }

    int count = 0;
    printf("Tüm Kitaplar:\n");
    printf("-----------------------------------------\n");

    while (fscanf(file, "%d\n%s\n%s\n%d\n", &books[count].book_ID, books[count].book_title, books[count].book_author, &books[count].book_status) != EOF) {
        replace_characters(books[count].book_title, '_', ' ');
        replace_characters(books[count].book_author, '_', ' ');

        printf("ID: %d\nBaslik: %s\nYazar: %s\n", books[count].book_ID, books[count].book_title, books[count].book_author);

        if (books[count].book_status == 1) {
            printf("Durum: Mevcut\n");
        } else if (books[count].book_status == 0) {
            printf("Durum: Oduncte\n");
        }

        printf("-----------------------------------------\n");
        count++;
    }

    fclose(file);
}

void add_member(){
    
    FILE *file = fopen("members.txt", "a");
    if (file == NULL) {
        printf("Uye dosyasi acilamadi.\n");
        return;
    }
    
    struct member new_member;

    printf("Lutfen uye ID'sini girin: ");
    scanf("%s", new_member.member_ID);
    if (strlen(new_member.member_ID) != 11) {
        printf("Gecersiz uye ID'si! Lutfen 11 haneli bir TC kimlik numarasi girin.\n");
        return; // Hatali ID girildiginde islemi sonlandirir
    }
    for (int i = 0; i < 11; i++) {
        if (new_member.member_ID[i] < '0' || new_member.member_ID[i] > '9') {
            printf("Gecersiz uye ID'si! TC kimlik numarasi sadece rakamlardan olusmalidir.\n");
            return; // Hatali karakter girildiginde islemi sonlandirir
        }
    }

    printf("Lutfen uye adini girin: ");
    getchar();  // Olası hata durumunu onlemek icin kullanilir
    fgets(new_member.member_name, sizeof(new_member.member_name), stdin);

    printf("Lutfen uye telefon numarasini girin: ");
    scanf("%s", new_member.member_phone);


    replace_characters(new_member.member_name, ' ', '_');

    fprintf(file, "%s\n%s\n%s\n", new_member.member_ID, new_member.member_name, new_member.member_phone);
    count_member++; //add book fonksiyonunda oldugu gibi daha sonra kullanılacak olan list members icin vs kullanilir bu yüzden zaten global olarak tanımladik bu degiskeni
    fclose(file);

    printf ("Uye basariyla sisteme eklendi.\n");
}

void search_member(){ // search book ile aynı isleve sahip 
    char member_ID[12];

    printf("Aramak istediginiz uyenin ID'sini giriniz: ");
    scanf("%s", member_ID, sizeof(member_ID));
    if (strlen(member_ID) != 11) {
        printf("Gecersiz uye ID'si! Lütfen 11 haneli bir TC kimlik numarasi girin.\n");
        return; // Hatali ID girildiginde islemi sonlandirir
    }
    for (int i = 0; i < 11; i++) {
        if (member_ID[i] < '0' || member_ID[i] > '9') {
            printf("Geçersiz uye ID'si! TC kimlik numarasi sadece rakamlardan oluşmalidir.\n");
            return; // Hatali karakter girildiginde islemi sonlandirir
        }
    }


    FILE *file = fopen("members.txt", "r");
    if (file == NULL) {
        printf("Uye dosyasi acilamadi.\n");
        return;
    }

    struct member temp_member;
    while (fscanf(file, "%s\n%s\n%s\n", temp_member.member_ID, temp_member.member_name, temp_member.member_phone) != EOF) {
        if (strcmp(temp_member.member_ID, member_ID) == 0) {
            printf("Uye bulundu:\n");
            printf("ID: %s\nAd: %s\nTelefon: %s\n", temp_member.member_ID, temp_member.member_name, temp_member.member_phone);
            fclose(file);
            return; // Uye bulundu, fonksiyondan cıkarır
        }
    }

    fclose(file);

    printf("Uye bulunamadi.\n");
}


void list_member(){

    FILE *file = fopen("members.txt", "r");
    if (file == NULL) {
        printf("Uye dosyasi acilamadi.\n");
        return;
    }
    int count=0;
    printf("Tum uyeler:\n");
    printf("-----------------------------------------\n");


    while (fscanf(file, "%s\n%s\n%s\n", &members[count].member_ID, members[count].member_name, &members[count].member_phone)!=EOF) {
        replace_characters(members[count].member_name, '_', ' ');
	    printf("Uye ID: %s\nUye Isim: %s\nUye telefon numarasi: %s\n", members[count].member_ID, members[count].member_name, members[count].member_phone);

        printf("-----------------------------------------\n");

        count++;
    }

    fclose(file);
    
    
}

void borrow_book(){

    if (count_book == 0) { // Kitaplar henüz yuklenmemisse bunu kontrol eder ve yukler
        FILE *file = fopen("books.txt", "r");
        if (file != NULL) {
            while (fscanf(file, "%d\n%s\n%s\n%d\n",
                          &books[count_book].book_ID,
                          books[count_book].book_title,
                          books[count_book].book_author,
                          &books[count_book].book_status) != EOF) {
                replace_characters(books[count_book].book_title, '_', ' ');
                replace_characters(books[count_book].book_author, '_', ' ');
                count_book++;
            }
            fclose(file);
        }
    }

    struct borrow new_borrow;

    printf("Kitap odunc vermek icin kitap ID'sini girin: ");
    scanf("%d", &new_borrow.book_ID);

    printf("Uye ID'sini girin: (11 haneli tc kimlik no)");
    scanf("%s", new_borrow.member_ID);
    if (strlen(new_borrow.member_ID) != 11) {
        printf("Gecersiz uye ID'si! Lutfen 11 haneli bir TC kimlik numarasi girin.\n");
        return; // Hatali ID girildiginde islemi sonlandirir
    }
    for (int i = 0; i < 11; i++) {
        if (new_borrow.member_ID[i] < '0' || new_borrow.member_ID[i] > '9') {
            printf("Gecersiz uye ID'si! TC kimlik numarasi sadece rakamlardan oluşmalidir.\n");
            return; // Hatali karakter girildiginde islemi sonlandirir
        }
    }

    printf("Ödünç alinma tarihi (YYYY-MM-DD): ");
    scanf("%s", new_borrow.borrow_date);
    
    if (strlen(new_borrow.borrow_date) != 10 || new_borrow.borrow_date[4] != '-' || new_borrow.borrow_date[7] != '-') {
        printf("Geçersiz tarih formatı! Lütfen tarihi YYYY-MM-DD formatında girin.\n");
        return; // Gecersiz formatta tarih girildiginde islemi sonlandirir
    }
    
    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7) { // Tire karakterleri haric olması icin gerekli
            if (new_borrow.borrow_date[i] < '0' || new_borrow.borrow_date[i] > '9') {
                printf("Gecersiz tarih formati! Tarih sadece rakamlardan ve '-' isaretlerinden olusmalidir.\n");
                return; // Gecersiz karakter girildiginde islemi sonlandirir
            }
        }
    }

    printf("Kitap iade tarihi (YYYY-MM-DD): ");
    scanf("%s", new_borrow.return_date);
    
    if (strlen(new_borrow.return_date) != 10 || new_borrow.return_date[4] != '-' || new_borrow.return_date[7] != '-') {
        printf("Gecersiz tarih formati! Lutfen tarihi YYYY-MM-DD formatinda girin.\n");
        return; // Gecersiz formatta tarih girildiginde islemi sonlandirir
    }

    // Iade tarihindeki rakamları kontrol eder
    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7) { // Tire karakterleri haric olması icin gerekli
            if (new_borrow.return_date[i] < '0' || new_borrow.return_date[i] > '9') {
                printf("Gecersiz tarih formati! Tarih sadece rakamlardan ve '-' isaretlerinden olusmalidir.\n");
                return; // Gecersiz karakter girildiginde islemi sonlandirir
            }
        }
    }

    // Kitabı dizide bulur ve statusu gunceller
    int found = 0;
    for (int i = 0; i < count_book; i++) {
        if (books[i].book_ID == new_borrow.book_ID) {
            printf("Kitap bulundu!\n");
            // Kitap bulundu icin sırada kitabı Odunc verme var, bu yüzden status degistirilir
            if (books[i].book_status == 1) { // Eger kitap mevcutsa Odunc verir ve statusü 0a cevirir
                books[i].book_status = 0; // Kitap Odunc verilmis duruma getirilir
                found = 1;
                break;
            } else {
                printf("Kitap zaten Odunc verilmis.\n"); //eger kitap zaten Odunc verildiyse de statusu değismez
                return;
            }
        }
    }

    if (!found) {
        printf("Kitap bulunamadi.\n");
        return;
    }

    // Odunc islemini struct sayesinde borrows.txt ye kaydediyoruz 
    FILE *file = fopen("borrows.txt", "a");
    if (file == NULL) {
        printf("Odunc dosyasi acilamadi.\n");
        return;
    }

    // Odunc bilgilerini dosyaya yazmasini saglar
    fprintf(file, "%d\n%s\n%s\n%s\n",
            new_borrow.book_ID, new_borrow.member_ID, new_borrow.borrow_date, new_borrow.return_date);

    fclose(file);

    // Güncellenmis kitap durumunu dosyaya kaydetmek icin books dosyasini açar
    FILE *book_file = fopen("books.txt", "w");
    if (book_file == NULL) {
        printf("Kitap dosyasi acilamadi.\n");
        return;
    }

    // Kitapları dosyaya yazdirir ki böylelikle status de books.txt ye kaydedilir cünkü kitaplari listelerken vs stastusu de yazdiriyoruz
    for (int i = 0; i < count_book; i++) {
        replace_characters(books[i].book_title, ' ', '_');
        replace_characters(books[i].book_author, ' ', '_');
        fprintf(book_file, "%d\n%s\n%s\n%d\n",
                books[i].book_ID,
                books[i].book_title,
                books[i].book_author,
                books[i].book_status);
    }

    fclose(book_file);

    printf("Kitap basariyla odunc verildi.\n");
}



void return_book(){
    struct borrow borrowd;
    struct book book;
    int found = 0;
    
    printf("Kitabi iade etmek icin kitap ID'sini girin: ");
    scanf("%d", &borrowd.book_ID);

    printf("Uye ID'sini girin: (11 haneli tc kimlik no)");
    scanf("%s", borrowd.member_ID);
    if (strlen(borrowd.member_ID) != 11) {
        printf("Gecersiz uye ID'si! Lutfen 11 haneli bir TC kimlik numarasi girin.\n");
        return; // Hatali ID girildiginde islemi sonlandirir
    }
    for (int i = 0; i < 11; i++) {
        if (borrowd.member_ID[i] < '0' || borrowd.member_ID[i] > '9') {
            printf("Gecersiz uye ID'si! TC kimlik numarasi sadece rakamlardan olusmalidir.\n");
            return; // Hatali karakter girildiginde islemi sonlandirir
        }
    }

    printf("Kitap iade tarihi (YYYY-MM-DD): ");
    scanf("%s", borrowd.return_date);
    if (strlen(borrowd.return_date) != 10 || borrowd.return_date[4] != '-' || borrowd.return_date[7] != '-') {
        printf("Gecersiz tarih formati! Lutfen tarihi YYYY-MM-DD formatinda girin.\n");
        return; // Gecersiz formatta tarih girildiginde islemi sonlandirir
    }

    // Tarih kismindaki rakamlari kontrol eder
    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7) { // Tire karakterleri haric olmasi icin gerekli
            if (borrowd.return_date[i] < '0' || borrowd.return_date[i] > '9') {
                printf("Gecersiz tarih formati! Tarih sadece rakamlardan ve '-' isaretlerinden olusmalidir.\n");
                return; // Gecersiz karakter girildiginde islemi sonlandirir
            }
        }
    }

    FILE *borrows_file = fopen("borrows.txt", "r"); //Odunc dosyası acılır 
    if (borrows_file == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    
    FILE *books_file = fopen("books.txt", "r"); //kitap dosyasını acar böylelikle status degistirilsin
    if (books_file == NULL) {
        printf("Dosya acilamadi!\n");
        fclose(borrows_file);
        return;
    }

    
    while (fscanf(books_file, "%d\n%s\n%s\n%d\n", //kitabi bulmaya yarar
           &book.book_ID, 
           book.book_title, 
           book.book_author, 
           &book.book_status) != EOF) {
        
        if (book.book_ID == borrowd.book_ID) {
            found = 1;
            book.book_status = 1;  //status degistirilir 
            break;
        }
    }

    if (!found) {
        printf("Kitap bulunamadi!\n");
        fclose(borrows_file);
        fclose(books_file);
        return;
    }


    rewind(books_file);
    FILE *temp_file = fopen("temp.txt", "w"); //bir fonksiyonda birden fazla dosya kullanildigi icin file olarak degil de books_file ve temp_file olarak yazdim
    
    struct book temp_book;
    while (fscanf(books_file, "%d\n%s\n%s\n%d\n", 
           &temp_book.book_ID, 
           temp_book.book_title, 
           temp_book.book_author, 
           &temp_book.book_status) != EOF) {
        
        if (temp_book.book_ID == borrowd.book_ID) { //eger kitap, iade edilen kitap ise kitabi tekrardan mevcut hale getiriyoruz
            fprintf(temp_file, "%d\n%s\n%s\n1\n", 
                    temp_book.book_ID,
                    temp_book.book_title,
                    temp_book.book_author);
        } else {
            fprintf(temp_file, "%d\n%s\n%s\n%d\n",  //Diger kitaplari oldugu gibi gecici dosyaya yaziyoruz
                    temp_book.book_ID,
                    temp_book.book_title,
                    temp_book.book_author,
                    temp_book.book_status);
        }
    }

    fclose(borrows_file);
    fclose(books_file);
    fclose(temp_file);


    remove("books.txt"); //dosya kaldirilir cünkü ici bos ve icindekiler artık temp dosyasinda
    rename("temp.txt", "books.txt"); //yine aynı sekilde temp dosyasi yeniden isimlendirilir

    printf("Kitap iade edildi!\n");
}
    

void list_borrows(){

    struct borrow borrowd_book;
    FILE *file = fopen("borrows.txt", "r");
    if (file == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    printf("\nOdunc listesi:\n");
    printf("----------------------------------------\n");
    printf("Kitap ID\t\tUye ID\tOdunç tarihi\tIade tarihi\n");
    printf("----------------------------------------\n");

    
    while (fscanf(file, "%d\n%s\n%s\n%s\n",  //dosyadan Odunc bilgilerini okur
           &borrowd_book.book_ID, 
           borrowd_book.member_ID, 
           borrowd_book.borrow_date, 
           borrowd_book.return_date) != EOF) {
        
        
        printf("%d\t\t%s\t\t%s\t%s\n",  //sonra da cikti olarak verir
               borrowd_book.book_ID, 
               borrowd_book.member_ID, 
               borrowd_book.borrow_date, 
               borrowd_book.return_date);
    }

    fclose(file);
    printf("\nOdunc listesi başariyla listelendi!\n");
}

void list_Nonborrowed(){
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Kitap dosyasi acilamadi.\n");
        return;
    }

    printf("\nMevcut Kitaplar:\n");
    printf("-----------------------------------------\n");

    struct book temp_book;
    while (fscanf(file, "%d\n%s\n%s\n%d\n",
                 &temp_book.book_ID,
                 temp_book.book_title,
                 temp_book.book_author,
                 &temp_book.book_status) != EOF) {
        if (temp_book.book_status == 1) { // Mevcut kitapları yazdirmak icin status bilgisinden yararlaniriz
            replace_characters(temp_book.book_title, '_', ' ');
            replace_characters(temp_book.book_author, '_', ' ');
            printf("ID: %d\n", temp_book.book_ID);
            printf("Başlik: %s\n", temp_book.book_title);
            printf("Yazar: %s\n", temp_book.book_author);
            printf("-----------------------------------------\n");
        }
    }

    fclose(file);
}

void list_borrowed(){
   FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Kitap dosyasi acilamadi.\n");
        return;
    }

    printf("\nOdunc Alinan Kitaplar:\n");
    printf("-----------------------------------------\n");

    struct book temp_book;
    while (fscanf(file, "%d\n%s\n%s\n%d\n",
                 &temp_book.book_ID,
                 temp_book.book_title,
                 temp_book.book_author,
                 &temp_book.book_status) != EOF) {
        if (temp_book.book_status == 0) { //yine aynı sekilde statusun 1 ya da 0 olmasına bakilir ve buna göre kitaplar yazdırilir
            replace_characters(temp_book.book_title, '_', ' ');
            replace_characters(temp_book.book_author, '_', ' ');
            printf("ID: %d\n", temp_book.book_ID);
            printf("Başlik: %s\n", temp_book.book_title);
            printf("Yazar: %s\n", temp_book.book_author);
            printf("-----------------------------------------\n");
        }
    }

    fclose(file);
}

