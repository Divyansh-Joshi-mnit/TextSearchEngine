```markdown
# 🧠 TextSearchEngine

A cross-platform, high-performance command-line search engine written in modern **C++**. Designed for blazing-fast text file searches with clean logging, ANSI-styled output, interactive mode, and command-based UX.

Perfect for developers, students, or nerds who hate slow `Ctrl+F`.

---

## 🚀 Features

- ✅ Single-word & multi-word search
- ✅ Interactive CLI with `/` commands
- ✅ ANSI-colored output for better UX
- ✅ Logs all searches to `output/output.txt`
- ✅ Search history viewer
- ✅ Timestamps for every search
- ✅ Reset, clear, and version commands
- ✅ Cross-platform build via **CMake**

---

## 📂 Folder Structure

```

TextSearchEngine/
├── include/             # Header files
│   └── SearchCore.h
├── src/                 # Source files
│   ├── main.cpp
│   └── SearchCore.cpp
├── data/                # Your .txt files to be indexed
│   ├── fileList.txt     # List of files to index (relative paths)
│   └── sample1.txt
├── output/              # Search logs stored here
│   └── output.txt
├── CMakeLists.txt       # Cross-platform build script
├── .gitignore
└── README.md

````

---

## 🛠️ Build Instructions

### 🖥️ Prerequisites:
- CMake >= 3.10
- C++17 compatible compiler
  - GCC >= 9, Clang >= 7, MSVC >= 2017

### 🧪 Build (All Platforms)
```bash
mkdir build
cd build
cmake ..
cmake --build .
````

### ▶️ Run

```bash
# Run 
./build/TextSearchEngine
```

---

## ⚙️ Usage Modes

### A. CLI Argument Search (no prompt)

```bash
./build/TextSearchEngine neural networks
```

### B. Interactive Mode

```bash
./build/TextSearchEngine
```

Then type:

```
> hello world
> /history
> /clear
> /reset
> /quit
```

---

## 🧩 Supported CLI Commands

| Command    | Description                        |
| ---------- | ---------------------------------- |
| `/help`    | Show help message                  |
| `/history` | Show past searches with timestamps |
| `/clear`   | Clear the search log file          |
| `/reset`   | Rebuild index and clear logs       |
| `/version` | Show version info                  |
| `/quit`    | Exit the interactive mode          |

You can still search for the word `history` — just don’t prefix it with `/` 

---

## 💡 Customization

* Add your `.txt` files inside `data/`
* Update `data/fileList.txt` with relative paths to those files

```txt
sample1.txt
folder/notes.txt
```

* Then run `/reset` inside the CLI or rebuild

---

## 💬 Output Example

```bash
[->] Searching for: hello world
[✔] Found in:
  ↪ data/sample1.txt (4 total occurrences)
```

### Logged in `output/output.txt`:

```
[2025-06-25 23:07:03] [Search] hello world
  ↪ data/sample1.txt (4 total occurrences)
```

---

## 🌍 Cross-Platform Notes


If `g++` is old, you may need to upgrade or use a modern MinGW-w64 on Windows

---

## 📦 Want to Package as Executable?

Zip these:

```
TextSearchEngine.exe
/data/
/output/
```

And ship it to friends or demo it — no build required.

---

## 📜 License

MIT — Use it, break it, improve it.

---

## 👨‍💻 Built by Divyansh Joshi

Student | C++ Enthusiast |

```
```
