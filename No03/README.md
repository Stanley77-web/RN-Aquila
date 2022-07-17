# Memory Editor

## Daftar Isi
  - [Daftar Isi](#daftar-isi)
  - [Deskripsi](#deskripsi)
  - [Requirement Program](#requirement-program)
  - [Setup](#setup)
<br>

## Deskripsi
Program memory editor sederhana yang dapat digunakan untuk membaca atau mengubah isi dari memory pada target program pada address tertentu.
<br>

## Requirement Program
- [Windows OS](https://en.wikipedia.org/wiki/Microsoft_Windows) 
- [Lib Win32 Api](https://docs.microsoft.com/en-us/windows/win32/learnwin32/learn-to-program-for-windows) 
<br>

## Setup
Setup ini bisa digunakan untuk menjalankan program dengan catatan sudah mendownload [Lib Win32 Api](https://sourceforge.net/projects/win32-framework/) yang diperlukan
- Compile <br>
    Pertama-pertama program harus dicompile terlebih dahulu dengan memasukan command seperti dibawah ini ke dalam terminal 
    
    ```
    make install
    ```

- Run <br>
Setelah program berhasil dicompile, <br>
    1. Jalankan program target dengan cara memasukan command
        ```
        ./target-program
        ```  
    2. Jalankan program memory editor dengan cara memasukan command
        ```
        ./memory-editor
        ``` 
    3. Program memory editor akan memintakan masukan berupa address memory yang akan diubah 
        <br> Contoh : 0x400000 <br>
    4. Address memory ini dapat dari program target yang dijalankan, yaitu seperti pada gambar dibawah ini

    ![image](https://media.discordapp.net/attachments/973185624070848542/998255296889766028/unknown.png)

    5. Selamat menikmati menu editor yang sudah disediakan
