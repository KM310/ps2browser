# PS2 Webbrowser
<p align="center">
    <img src="Logo.png" width="200" height="200" style="image-rendering: pixelated;">
</p>


A simple web browser for **MIPS / Linux / PlayStation 2**, running directly on real PS2 hardware using the **PS2 Linux Kit**.

Currently supported:
- ✅ HTML 1.0 (basic tags)
- ✅ Simple JavaScript
- ✅ HTTP 1.0 (GET)
- ✅ MIPS‑optimized assembly routines (memcpy, strlen)
- ✅ Terminal text renderer
- ✅ JavaScript interpreter

Planned features:
- 🔒 HTTPS (optional, later)
- 📄 HTML 2.0
- 🎨 Framebuffer graphics renderer

---

## 🚀 Opening a Website

The browser expects **host** and **path** as separate arguments:

```sh
./ps2browser example.com /
Examples:

./ps2browser example.com /index.html
./ps2browser 192.168.0.10 /tictactoe.html
./ps2browser myserver.local /page.html
Important:  
Do not enter full URLs like http://example.com — the browser only accepts the hostname.

📁 Opening Local HTML Files
If you start the browser without arguments:

./ps2browser
it automatically loads:

test_pages/index.html
✅ Opening TicTacToe locally
Place your file inside test_pages/

Rename it:

mv test_pages/tictactoe.html test_pages/index.html
Start the browser:

./ps2browser
🛠️ Building on PS2 Linux
Navigate to your project folder:

cd /your/path/to/ps2browser
Then compile:

make
This creates the executable:

ps2browser
🌐 Network Setup (if needed)
If PS2 Linux has no network connection yet:

ifconfig eth0 up
dhclient eth0
or configure a static IP.

👤 Info
Version: 1.0

Code: C + MIPS Assembly + JavaScript + HTML + Cpp 

Author: K_M

Debugging: Copilot

Have fun experimenting on real PS2 hardware!
