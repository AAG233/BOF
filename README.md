## 📊 Laboratorios basado en el libro: El arte de la explotación de vulnerabilidades en sistemas modernos

<img width="1536" height="1024" alt="Designer0" src="https://github.com/user-attachments/assets/a24edfdd-8c60-4fa4-b595-f2247df44282" />

## 🛒 Adquiere el libro

Puedes conseguir tu copia en las siguientes modalidades:

### 📖 Libro Físico  
[![Amazon](https://img.shields.io/badge/Amazon-Compra%20el%20libro%20físico-orange?logo=amazon&logoColor=white)](https://www.amazon.com/dp/6072988741)  
Copia impresa disponible en Amazon.

### 💻 Libro Digital (PDF)  
[![Hotmart](https://img.shields.io/badge/Hotmart-Compra%20el%20libro%20digital-blue?logo=hotmart&logoColor=white)](https://hotmart.com/es/marketplace/productos/el-arte-de-la-explotacion-de-vulnerabilidades-en-sistemas-modernos/K105948688E)  
Adquiere la versión digital al instante en Hotmart.


###

> **Libro técnico especializado** que analiza la explotación de vulnerabilidades en sistemas Linux y Windows bajo arquitecturas x86 y x64.  
> Expone principios de memoria, ingeniería inversa y depuración para comprender el comportamiento de software vulnerable.  
> Examina mecanismos modernos de protección y su interacción con técnicas de análisis y evaluación de seguridad.  
> Concluye resaltando el carácter formativo, analítico y ético del estudio profesional de la ciberseguridad.

---

## 📚 Descripción

Este repositorio contiene los **laboratorios prácticos** que acompañan al libro: El arte de la explotación de vulnerabilidades en sistemas modernos.  
A través de ejercicios guiados, el estudiante aprenderá a:

- Identificar y explotar vulnerabilidades de **desbordamiento de búfer** (stack-based).
- Construir **ROP chains** (Return Oriented Programming) en arquitecturas x86 y x64.
- Generar y depurar **shellcode** para Linux y Windows.
- Entender el impacto de mecanismos de protección como **ASLR**, **DEP** y **Stack Canaries**.
- Aplicar técnicas de **ingeniería inversa** y depuración con `gdb`, `objdump`, `windbg` y `VirtualProtect`.

---

## 📂 Estructura del Repositorio

| Carpeta | Descripción |
|------------------|-------------|
| `BOF_x32` | Prácticas relacionadas a la explotación de vulnerabilidades el Linux x86|
| `BOF_x64` | Prácticas relacionadas a la explotación de vulnerabilidades el Linux x64 |
| `BOF_x32_Windows` | Prácticas relacionadas a la explotación de vulnerabilidades el Windows x86 |
| `BOF_x64_Windows` | Prácticas relacionadas a la explotación de vulnerabilidades el Windows x64 |


---

## 🖥️ Descarga de máquinas virtuales

Las siguientes máquinas virtuales están configuradas con los entornos necesarios para seguir los laboratorios del libro.

| Archivo | Sistema operativo |
|---------|-------------------|
| `Debian 12.5 x86 - BOF - ExploitLab.ova` | Debian 12.5 (32 bits) |
| `Debian 12.6 x86_64 - BOF - ExploitLab.ova` | Debian 12.6 (64 bits) |

**Credenciales de acceso** (para ambas máquinas):

- Usuario `debian` → contraseña: `BOFdebian!1987`
- Usuario `root` → contraseña: `BOFroot!1987`

> Las imágenes están disponibles en el siguiente enlace de Google Drive:  
> [https://drive.google.com/drive/folders/14tSJVQOLlDGACR72DRYjndpEYgH2AoRI?usp=sharing](https://drive.google.com/drive/folders/14tSJVQOLlDGACR72DRYjndpEYgH2AoRI?usp=sharing)

---

## 🛠️ Herramientas adicionales | Windows
- MinGW Version 9.1.0
- [MinGW Version 16.1.0] (https://winlibs.com/)
- x64dbg

Liga de descarga completa: https://drive.google.com/drive/folders/1qeGbGQkcnxoEYwSBEKCDMCQb5gpM093c?usp=sharing

