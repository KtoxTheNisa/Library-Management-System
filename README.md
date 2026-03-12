# Library-Management-System - C Tabanlı Kütüphane Yönetim Sistemi

Bu proje, bir kütüphanenin temel operasyonel ihtiyaçlarını karşılamak amacıyla C dilinde geliştirilmiş bir yönetim sistemidir. Birinci sınıfın ilk döneminde, C dilinin temel kavramlarını ve dosya sistemlerini öğrenmek amacıyla geliştirilmiştir.

## 🚀 Özellikler
- **Kitap Yönetimi:** Kitap ekleme, silme, ID ile arama ve tüm kitapları listeleme.
- **Üye Yönetimi:** 11 haneli TC kimlik kontrolü ile üye kaydı ve takibi.
- **Ödünç İşlemleri:** Kitapların ödünç verilmesi, iade alınması ve durumlarının (Mevcut/Ödünçte) otomatik güncellenmesi.
- **Raporlama:** Mevcut ve ödünçteki kitapların ayrı ayrı listelenmesi.
- **Veri Kalıcılığı:** Tüm veriler `txt` dosyalarında saklanır, uygulama kapansa bile veriler korunur.

## 🛠 Teknik Detaylar
- **Dinamik Bellek Yönetimi:** `malloc` ve `free` kullanılarak veriler için çalışma anında bellek tahsisi yapılmıştır.
- **Dosya İşlemleri:** `fopen`, `fprintf`, `fscanf` ve geçici dosya (`temp file`) mantığı ile veri güncelleme işlemleri yönetilmiştir.
- **Veri Yapıları:** `struct` yapısı kullanılarak kitap, üye ve ödünç alma süreçleri modellenmiştir.
- **Hata Yönetimi:** TC Kimlik numarası ve Tarih (YYYY-MM-DD) formatları için temel doğrulama mekanizmaları içerir.

## 💻 Kurulum
1. C derleyicisine (GCC vb.) sahip olduğunuzdan emin olun.
2. Kodları indirin ve derleyin:
   ```bash
   gcc main.c -o kutuphane_sistemi
