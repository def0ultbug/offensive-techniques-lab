# Offensive Techniques Lab 🔬

A collection of low-level C scripts documenting my hands-on learning of 
offensive security techniques, Windows internals, and malware development concepts.

> ⚠️ **Disclaimer:** This repository is strictly for educational and research 
> purposes only. Do not use any of these techniques on systems you do not own 
> or have explicit written permission to test. The author is not responsible 
> for any misuse of this code.

## 📚 What's Inside

- **Payload Encryption** - Techniques to obfuscate shellcode from static analysis
- **Process Injection** - Methods to execute code inside other processes
- **Thread Manipulation** - Hijacking and queuing execution via threads
- **Anti-Debugging** - Detecting analysis environments via Windows internals

## 🗂️ Repository Structure
```
offensive-techniques-lab/
├── encryption/
│   ├── XOR_Encryption.c
│   └── AES_Encryption.c
├── injection/
│   ├── shellcode_injection.c
│   ├── apc_injection.c
│   └── thread_hijacking.c
├── anti-analysis/
│   └── Anti-Debugging.c
├── payloads/
│   └── payload_placement_data.c
└── README.md
```

## 📖 Scripts

### Encryption
| Script | Concept | Status |
|---|---|---|
| `XOR_Encryption.c` | XOR payload encryption (single key, index-based, input key) | ✅ Completed |
| `AES_Encryption.c` | AES-CBC payload decryption using Tiny-AES | ✅ Completed |

### Injection
| Script | Concept | Status |
|---|---|---|
| `shellcode_injection.c` | Remote process shellcode injection | ✅ Completed |
| `apc_injection.c` | Shellcode execution via APC injection | ✅ Completed |
| `thread_hijacking.c` | Thread hijacking via context manipulation | ✅ Completed |

### Anti-Analysis
| Script | Concept | Status |
|---|---|---|
| `Anti-Debugging.c` | Anti-debugging via PEB BeingDebugged flag | ✅ Completed |

### Payloads
| Script | Concept | Status |
|---|---|---|
| `payload_placement_data.c` | PoC calc.exe shellcode for lab testing | ✅ Completed |

## 🛠️ Tech Stack

- **Language:** C
- **Platform:** Windows x64
- **Libraries:** Windows API (WinAPI), Tiny-AES
- **Tools:** MSVC / MinGW, x64dbg, Visual Studio

## 🎯 Learning Goals

- [ ] Understand common shellcode encryption and obfuscation techniques
- [ ] Learn process injection methods and how defenders detect them
- [ ] Explore Windows thread internals and execution flow manipulation
- [ ] Study anti-analysis techniques used in real-world malware

## 🔐 Ethical Usage

This repository is intended for:
- Preparing for certifications like **eJPT**, **CRTP**, **OSCP**
- Learning how malware works to better **defend** against it
- Understanding attacker techniques from a **red team / blue team** perspective

**Always test in an isolated lab environment.**

## 📄 License

MIT License - feel free to use these examples for your own learning.

---

⭐ **Note:** This is a living repository that grows as I learn.
```
