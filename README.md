# 💾 text-encryption-system
C program implementing a two-phase text encoding and decoding system using character shifting. Designed for educational purposes with modular functions and file operations.

## 🛠️ How the program works
This program encodes a text message in two stages using a custom character-shifting method based on a predefined alphabet.

### First stage:
Each character in the message is replaced by another character found by subtracting a fixed positive integer key (N) from its position in the alphabet. This uniform arithmetic operation shifts all characters backward cyclically within the alphabet.

### Second stage:
After the first substitution, characters at positions that are multiples of 2 (including position zero) undergo the same backward shift of N positions again, applying a second substitution.

### Output:
The final encoded message is saved into a text file along with the numeric key N, which is required for decoding.