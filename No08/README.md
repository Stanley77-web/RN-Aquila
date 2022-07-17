# Kalkulator Low Level

## Daftar Isi
  - [Daftar Isi](#daftar-isi)
  - [Deskripsi](#deskripsi)
  - [Requirement Program](#requirement-program)
  - [Setup](#setup)
<br>

## Deskripsi
Program kalkulator yang hanya menggunakan operasi bitwise dan control flow label dan goto.
<br>

## Requirement Program
- [Windows OS](https://en.wikipedia.org/wiki/Microsoft_Windows) 
<br>

## Setup
- Compile <br>
    Pertama-pertama program harus dicompile terlebih dahulu dengan memasukan command seperti dibawah ini ke dalam terminal 
    
    ```
    g++ calc.cpp -o calc
    ```

- Run <br>
Setelah program berhasil dicompile untuk menjalankan cukup memasukkan command seperti dibawah ini ke dalam terminal
    ```
    ./calc
    ``` 
Untuk contoh format penulisan file inputan yang valid adalah seperti dibawah ini
    ```
      4 + 5 * 9 - 8
    ```
Dengan
    - Penjumlahan (+)
    - Pengurangan (-)
    - Perkalian (*)
    - Pembagian (/)
    - Perpangkatan (^)