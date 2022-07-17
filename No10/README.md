# Parallel String Finder

## Daftar Isi
* [Deskripsi](#deskripsi)
* [Requirement Program](#requirement-program)
* [Setup & Instalasi](#setup)
<br>

## Deskripsi
Program sederhana untuk melakukan pencarian string _pattern_ secara paralel
<br>
<br>
## Requirement Program
- [Linux OS](https://id.wikipedia.org/wiki/Kernel_Linux) 
<br>

## Setup
Setup ini hanya bisa dijalankan di sistem operasi linux karena ada beberapa library yang hanya disediakan di sistem operasi linux
- Compile <br>
    Pertama-pertama program harus dicompile terlebih dahulu dengan memasukan command seperti dibawah ini ke dalam terminal 
    
```
make install
```

- Run <br>
Setelah program berhasil dibuild untuk menjalankan cukup memasukkan command seperti dibawah ini ke dalam terminal
```
./paringder <jumlah proses> <jumlah thread> <pattern string>
```  
