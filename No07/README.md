# Titc Tac Toe

## Daftar Isi
* [Deskripsi](#deskripsi)
* [Requirement Program](#requirement-program)
* [Setup & Instalasi](#setup)
<br>

## Deskripsi
Program permainan tic tac toe sederhana. Kedua pemain bermain di program yang berbeda dan kedua program tersebut akan saling berkomunikasi melalui socket udp protokol tcp
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
Setelah program berhasil dicompile, <br>
    - Untuk Bermain di sisi Server dapat memasukkan command
        ```
        ./server
        ```  
    - Untuk Bermain di sisi Client dapat memasukkan command
        ```
        ./client
        ``` 
