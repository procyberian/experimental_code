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

# Path to the boot directory
boot_dir = "/boot"

# Collect all kernel images installed (files starting with 'vmlinuz-')
installed_kernels = [
    f.replace("vmlinuz-", "")
    for f in os.listdir(boot_dir)
    if f.startswith("vmlinuz-")
]

# Get the currently running kernel
current_kernel = os.uname().release

print("Installed kernels in /boot:")
for k in installed_kernels:
    print(f" - {k}")

print("\nCurrently running kernel:")
print(f" - {current_kernel}")

# Check if the running kernel is among the installed ones
if current_kernel in installed_kernels:
    print(f"\n✅ The running kernel {current_kernel} is installed and active.")
else:
    print(f"\n⚠️ The running kernel {current_kernel} is NOT found in /boot.")
