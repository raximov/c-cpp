# Linux Administration Report

---

## Part 1. Installation of the OS

- Ubuntu 20.04 Server LTS versiyasini tekshirish (`cat /etc/issue`):

![useradd command](images/Screenshot_from_2026-03-05_09-43-29.png)


---

## Part 2. Creating a user

- Yangi foydalanuvchi yaratish buyrug'i (`sudo useradd -G adm newuser`):

![/etc/passwd output](images/Screenshot_from_2026-03-05_09-45-44.png)


- `cat /etc/passwd` chiqishi (yangi user ko'rinmoqda):

![set hostname](images/Screenshot_from_2026-03-05_09-47-00.png)


---

## Part 3. Setting up the OS network

- Mashinaga `user-1` nomi berildi (`hostnamectl set-hostname user-1`):

![ip a output](images/Screenshot_from_2026-03-05_10-04-06.png)


- Timezone o'rnatildi (`timedatectl set-timezone Asia/Tashkent`):

![external IP](images/Screenshot_from_2026-03-05_10-05-31.png)


- Network interfacelar ro'yxati (`ip a`):


> **lo interface haqida:** `lo` (loopback) — virtual network interface bo'lib, kompyuterning o'ziga o'zi murojaat qilishi uchun ishlatiladi (IP: 127.0.0.1). Tashqi tarmoqqa chiqmaydi.

- DHCP dan IP olish (`sudo dhclient -v`):

![netplan config](images/Screenshot_from_2026-03-05_10-07-03.png)


> **DHCP:** Dynamic Host Configuration Protocol — tarmoqdagi qurilmalarga avtomatik ravishda IP manzil, gateway, DNS kabi sozlamalarni beruvchi protokol.

- Tashqi IP manzil (`curl ifconfig.me`):

![netplan apply](images/Screenshot_from_2026-03-05_10-07-50.png)

- Default gateway (`ip r`):

![ip route](images/Screenshot_from_2026-03-05_10-06-17.png)

![ip a after reboot](images/Screenshot_from_2026-03-05_10-08-22.png)

- Statik IP sozlash — netplan config (`/etc/netplan/00-installer-config.yaml`):

![no updates available](images/Screenshot_from_2026-03-05_10-25-44.png)

- `sudo netplan apply` bajarildi:


- Qayta yuklashdan keyin statik sozlamalar tekshirildi (`ip a`):


- `ip r` — gateway tekshirildi:


- `ping 1.1.1.1` — 0% packet loss:
- `ping ya.ru` — 0% packet loss:

![sudo hostname change](images/Screenshot_from_2026-03-05_10-28-45.png)




---

## Part 4. OS Update

- Tizim paketlari yangilandi (`sudo apt update && sudo apt upgrade -y`):


- Qayta yangilash — yangi paketlar yo'qligi tasdiqlandi:

![new hostname](images/Screenshot_from_2026-03-05_10-34-22.png)


---

## Part 5. Using the sudo command

- Yangi userga sudo huquqi berildi va hostname o'zgartirildi:


> **sudo ning maqsadi:** `sudo` (superuser do) — oddiy foydalanuvchiga root huquqlari bilan buyruq bajarish imkonini beradi. Xavfsizlikni ta'minlaydi — faqat kerakli paytda yuqori huquqlar olinadi va barcha sudo amallar `/var/log/auth.log` da qayd qilinadi.


- O'zgartirilgan hostname ko'rsatildi:

![timedatectl output](images/Screenshot_from_2026-03-05_10-36-54.png)


---

## Part 6. Installing and configuring the time service

- NTP o'rnatildi va vaqt sinxronizatsiyasi tekshirildi (`timedatectl`):


- `timedatectl show` — `NTPSynchronized=yes` ko'rinmoqda:

![timedatectl show](images/Screenshot_from_2026-03-05_10-38-33.png)

![vim with nickname](images/Screenshot_from_2026-03-05_10-39-09.png)

![vim edited](images/Screenshot_from_2026-03-05_10-47-16.png)

---

## Part 7. Installing and using text editors

### VIM

- `test_vim.txt` fayli yaratildi, nickname yozildi:


> Saqlash va chiqish: `Esc` → `:wq`

- Matn "21 School 21" bilan almashtirildi (tahrirlash rejimi):


> Saqlamasdan chiqish: `Esc` → `:q!`

- VIM da qidirish (`/nickname`):

![vim search](images/Screenshot_from_2026-03-05_11-02-33.png)

- VIM da almashtirish (`:%s/eski/yangi/g`):

![vim replace](images/Screenshot_from_2026-03-05_11-03-58.png)
![nano search](images/Screenshot_from_2026-03-05_11-08-14.png)
![nano edited](images/Screenshot_from_2026-03-05_11-06-39.png)
![nano with nickname](images/Screenshot_from_2026-03-05_11-05-16.png)

---

### NANO

- `test_nano.txt` fayli yaratildi, nickname yozildi:


> Saqlash va chiqish: `Ctrl+O` → `Enter` → `Ctrl+X`

- Matn "21 School 21" bilan almashtirildi:


> Saqlamasdan chiqish: `Ctrl+X` → `N`

- NANO da qidirish (`Ctrl+W`):


- NANO da almashtirish (`Ctrl+\`):

![nano replace](images/Screenshot_from_2026-03-05_11-10-25.png)

![joe with nickname](images/Screenshot_from_2026-03-05_11-11-12.png)

![joe edited](images/Screenshot_from_2026-03-05_11-12-01.png)

![joe search](images/Screenshot_from_2026-03-05_11-13-51.png)

![joe replace](images/Screenshot_from_2026-03-05_11-14-18.png)

---

### JOE

- `test_joe.txt` fayli yaratildi, nickname yozildi:


> Saqlash va chiqish: `Ctrl+K` → `X`

- Matn "21 School 21" bilan almashtirildi:

![sshd install + enable](images/Screenshot_from_2026-03-05_11-17-15.png)

> Saqlamasdan chiqish: `Ctrl+C` → `y`
![sshd_config port 2022](images/Screenshot_from_2026-03-05_11-17-49.png)

- JOE da qidirish (`Ctrl+K` → `F`):

![ps sshd](images/Screenshot_from_2026-03-05_11-18-19.png)

- JOE da almashtirish (`Ctrl+K` → `H`):

![netstat -tan](images/Screenshot_from_2026-03-05_11-19-29.png)

---

## Part 8. Installing and basic setup of the SSHD service

- SSHd o'rnatildi va avtomatik ishga tushirish yoqildi:


- `/etc/ssh/sshd_config` faylida port 2022 ga o'zgartirildi:
![top output](images/Screenshot_from_2026-03-05_11-22-29.png)


- SSHd jarayoni `ps -aux | grep sshd` bilan ko'rsatildi:

![htop sorted by PID](images/Screenshot_from_2026-03-05_11-23-38.png)


> **ps -aux kalitlari:** `-a` — barcha userlar jarayonlari; `-u` — foydalanuvchi/CPU/memory; `-x` — terminal bog'liq bo'lmagan jarayonlar

- `netstat -tan` chiqishi — `tcp 0 0.0.0.0:2022 0.0.0.0:* LISTEN`:

![htop sorted by CPU%](images/Screenshot_from_2026-03-05_11-26-00.png)


> **netstat -tan kalitlari:** `-t` TCP ulanishlar; `-a` barcha holatlar; `-n` IP raqam formatida
>


> **0.0.0.0 ma'nosi:** Barcha mavjud network interfacelarga bog'lanish — har qanday IP dan 2022 portga ulanish qabul qilinadi


---

## Part 9. Installing and using the top, htop utilities

- `top` buyrug'i chiqishi:


> - **Uptime:** `up X:XX` (birinchi qator)
> - **Avtorizatsiya qilingan userlar:** `X users`
> - **O'rtacha yuklanish:** `load average: X.XX, X.XX, X.XX`
> - **Jarayonlar soni:** `Tasks: XX total`
> - **CPU yuklanishi:** `%Cpu(s): X.X us`
> - **Xotira yuklanishi:** `MiB Mem: XXXX used`

- `htop` — PID bo'yicha saralash:


- `htop` — PERCENT_CPU bo'yicha saralash:


- `htop` — PERCENT_MEM bo'yicha saralash:

![htop sorted by MEM%](images/Screenshot_from_2026-03-05_11-32-48.png)

- `htop` — TIME bo'yicha saralash:

![htop sorted by TIME](images/Screenshot_from_2026-03-05_11-33-57.png)

- `htop` — sshd jarayoni filtrlandi (`F4: sshd`):

![htop filtered sshd](images/Screenshot_from_2026-03-05_11-34-57.png)

- `htop` — syslog jarayoni qidirildi (`F3: syslog`):

![htop search syslog](images/Screenshot_from_2026-03-05_11-36-13.png)

- `htop` — hostname, clock, uptime qo'shildi (`F2 → Meters`):

![htop with hostname clock uptime](images/Screenshot_from_2026-03-05_11-36-35.png)

---

## Part 10. Using the fdisk utility

- `sudo fdisk -l` chiqishi:

![fdisk -l output](images/Screenshot_from_2026-03-05_11-37-10.png)

> - **Disk nomi:** `/dev/sda`
> - **Sig'imi:** `XX GiB`
> - **Sektorlar soni:** `XXXXXXX sectors`
> - **Swap hajmi:** `XXX MB` (`Linux swap` bo'limi)

---
![df -Th output](images/Screenshot_from_2026-03-05_11-45-15.png)
![df output](images/Screenshot_from_2026-03-05_11-38-13.png)


## Part 11. Using the df utility

- `df` buyrug'i chiqishi (root `/` uchun):


> - **Bo'lim hajmi (1K-blocks):** XXXXXXX
> - **Ishlatilgan (Used):** XXXXXXX
> - **Bo'sh (Available):** XXXXXXX
> - **Foiz (Use%):** XX%
> - **O'lchov birligi:** 1K blok (kilobyte)

- `df -Th` chiqishi (root `/` uchun):

![du /home bytes](images/Screenshot_from_2026-03-05_11-45-57.png)

> - **Fayl tizimi turi (Type):** ext4
> - **Bo'lim hajmi (Size):** XX G
> - **Ishlatilgan (Used):** XX G
> - **Bo'sh (Avail):** XX G
> - **Foiz (Use%):** XX%

---

## Part 12. Using the du utility

- `/home` hajmi baytlarda (`du -sb /home`):


- `/var` va `/var/log` hajmi (`du -sh`):

![du /var /var/log](images/Screenshot_from_2026-03-05_11-47-38.png)

- `/var/log` ichidagi har bir element (`sudo du -sh /var/log/*`):

![du /var/log/*](images/Screenshot_from_2026-03-05_11-47-51.png)

---

## Part 13. Installing and using the ncdu utility

- `/home` papkasi ncdu bilan ko'rsatildi:

![ncdu /home](images/Screenshot_from_2026-03-05_11-48-52.png)

- `/var` papkasi ncdu bilan ko'rsatildi:

![ncdu /var](images/Screenshot_from_2026-03-05_11-49-16.png)

- `/var/log` papkasi ncdu bilan ko'rsatildi:

![ncdu /var/log](images/Screenshot_from_2026-03-05_11-49-33.png)

---

## Part 14. Working with system logs

- `/var/log/dmesg` ko'rish:

![/var/log/dmesg](images/Screenshot_from_2026-03-05_11-50-47.png)

- `/var/log/syslog` ko'rish:

![/var/log/syslog](images/Screenshot_from_2026-03-05_11-51-06.png)

- `/var/log/auth.log` ko'rish:

![/var/log/auth.log](images/Screenshot_from_2026-03-05_11-51-19.png)

> **Oxirgi muvaffaqiyatli login:**
> - **Vaqt:** `Mar 5 XX:XX:XX`
> - **Foydalanuvchi:** `username`
> - **Usul:** `password` / `publickey`

- SSHd qayta ishga tushirildi (`sudo systemctl restart ssh`) va log tekshirildi:

![sshd restart log](images/Screenshot_from_2026-03-05_11-53-49.png)

---

## Part 15. Using the CRON job scheduler

- CRON task o'rnatildi — har 2 daqiqada `uptime` bajariladi (`*/2 * * * * uptime`):

![crontab -e](images/Screenshot_from_2026-03-05_11-54-43.png)

- Joriy CRON tasklar ro'yxati (`crontab -l`):

![crontab -r empty](images/Screenshot_from_2026-03-05_12-06-32.png)

- Tizim loglarida CRON ijrolari (kamida 2 ta) — `grep "CRON" /var/log/syslog`:

![grep CRON syslog](images/Screenshot_from_2026-03-05_11-57-04.png)

- `grep 'uptime'` — uptime bajarilganligi tasdiqlandi:

![grep uptime](images/grep_'uptime'.png)

- Barcha CRON tasklar o'chirildi (`crontab -r`) — bo'sh ro'yxat:

![crontab -l](images/crontab.png)
