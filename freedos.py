"""
MIT License

Copyright (c) 2025 PSD Authors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
"""

import os
import platform
import subprocess

# ---------------- Kernel Checks ---------------- #

def get_installed_kernels_linux():
    kernels = []
    boot_dir = "/boot"
    if os.path.exists(boot_dir):
        try:
            for f in os.listdir(boot_dir):
                if f.startswith("vmlinuz-"):
                    kernels.append(f.replace("vmlinuz-", ""))
        except Exception as e:
            kernels.append(f"Error reading /boot: {e}")
    return kernels

def get_running_kernel():
    return os.uname().release

# ---------------- OEM Checks ---------------- #

def check_windows_oem_key():
    if platform.system() == "Windows":
        try:
            cmd = [
                "powershell",
                "-Command",
                "(Get-CimInstance -ClassName SoftwareLicensingService).OA3xOriginalProductKey"
            ]
            result = subprocess.check_output(cmd, universal_newlines=True).strip()
            if result:
                return f"Windows OEM key found: {result}"
            else:
                return "No Windows OEM key found."
        except Exception as e:
            return f"Error checking Windows OEM key: {e}"
    return "Not Windows."

def check_linux_oem():
    if platform.system() == "Linux":
        try:
            vendor = subprocess.check_output(
                ['cat', '/sys/class/dmi/id/sys_vendor'],
                universal_newlines=True
            ).strip()
            return f"Linux system vendor: {vendor}"
        except Exception as e:
            return f"Error checking Linux OEM: {e}"
    return "Not Linux."

def check_macos():
    if platform.system() == "Darwin":
        return "MacOS detected (Apple OEM)."
    return "Not MacOS."

def check_freedos():
    """
    FreeDOS OEM detection:
    Scan DMI identifiers and disk partitions for possible FreeDOS traces.
    """
    if platform.system() == "Linux":
        dmi_paths = [
            "/sys/class/dmi/id/bios_vendor",
            "/sys/class/dmi/id/bios_version",
            "/sys/class/dmi/id/product_name",
            "/sys/class/dmi/id/board_vendor"
        ]
        try:
            # Scan DMI identifiers
            for path in dmi_paths:
                if os.path.exists(path):
                    with open(path) as f:
                        content = f.read().strip()
                        if "FreeDOS" in content:
                            return f"FreeDOS OEM detected via {os.path.basename(path)}."

            # Extra: check for DOS-style partitions
            try:
                output = subprocess.check_output(
                    ["lsblk", "-o", "NAME,FSTYPE"], universal_newlines=True
                )
                if any("vfat" in line.lower() or "fat" in line.lower() for line in output.splitlines()):
                    return "Possible DOS/FreeDOS partition detected."
            except Exception:
                pass

            return "No explicit FreeDOS signature found. OEM vendor may have shipped FreeDOS originally."
        except Exception as e:
            return f"Unable to check FreeDOS: {e}"
    return "Not FreeDOS."

# ---------------- Main ---------------- #

def main():
    print("=== Kernel Scan ===")
    if platform.system() == "Linux":
        installed = get_installed_kernels_linux()
        print("Installed kernels in /boot:")
        for k in installed:
            print(f" - {k}")
        current = get_running_kernel()
        print(f"\nCurrently running kernel: {current}")
        if current in installed:
            print(f"✅ Running kernel {current} is installed and active.")
        else:
            print(f"⚠️ Running kernel {current} not found in /boot.")
    else:
        print("Kernel scan only applies to Linux systems.")

    print("\n=== OEM Check ===")
    print(check_windows_oem_key())
    print(check_linux_oem())
    print(check_macos())
    print(check_freedos())

if __name__ == "__main__":
    main()
