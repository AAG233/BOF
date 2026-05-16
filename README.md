# Laboratorios basado en el libro: El arte de la explotación de vulnerabilidades en sistemas modernos

[![Licencia](https://img.shields.io/badge/Licencia-Academic%20Free-blue)](LICENSE)
[![Plataformas](https://img.shields.io/badge/Plataformas-Linux%20%7C%20Windows-lightgrey)]()
[![Arquitecturas](https://img.shields.io/badge/Arquitecturas-x86%20%7C%20x64-red)]()

> **Obra técnica especializada** que analiza la explotación de vulnerabilidades en sistemas Linux y Windows bajo arquitecturas x86 y x64.  
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
- Desarrollar un enfoque **ético y profesional** en seguridad ofensiva.

---

## 📂 Estructura del Repositorio

| Archivo / Carpeta | Descripción |
|------------------|-------------|
| `p5.c`, `p6.c`, `p7.c` | Programas vulnerables en Linux (x86/x64) para explotación local/remota. |
| `s1.c` | Servidor TCP vulnerable en Linux x64 (palíndromo con buffer overflow). |
| `exploit.py`, `exploit2.py`, `exploit2_dinamico.py` | Scripts de explotación (ROP + shellcode) para los binarios vulnerables. |
| `P1_64bits.cpp` | Servidor Windows x64 con vulnerabilidad y llamada a `VirtualProtect`. |
| `AnalisisVirtualProtect.cpp` | Demostración de cambio de permisos en memoria (Windows). |
| `Get_Env.c` | Utilidad para obtener direcciones de variables de entorno (útil para explotación). |
| `entrada.txt` (generado) | Archivo de entrada con payload para explotación local. |

> **Nota:** Los nombres de los archivos (`p5.c`, `p6.c`, etc.) corresponden a ejercicios progresivos en el libro.

---

## 🛠️ Herramientas adicionales | Windows
- MinGW Version 9.1.0
- MinGW Version 16.1.0
- x64dbg

Liga de descarga: https://drive.google.com/drive/folders/1qeGbGQkcnxoEYwSBEKCDMCQb5gpM093c?usp=sharing

