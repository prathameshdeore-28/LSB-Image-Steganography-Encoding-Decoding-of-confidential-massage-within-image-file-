# 🔒 LSB Image Steganography

A command-line based **LSB (Least Significant Bit) Image Steganography** application developed in **C** that securely hides secret text files inside **24-bit BMP images** without causing any visible changes to the image.

The project demonstrates low-level file handling, bit manipulation, and binary data processing in C.

---

## 📌 Features

- Encode any text file into a 24-bit BMP image
- Decode the hidden message from the stego image
- Uses **Least Significant Bit (LSB)** technique
- Supports **Magic String** verification before decoding
- Validates image capacity before encoding
- Automatically creates output files if not specified
- Command-line interface
- Comprehensive error handling and user prompts

---

## 🛠 Technologies Used

- C Programming
- Linux
- GCC Compiler
- File Handling
- Bit Manipulation
- Command Line Interface (CLI)

---

## 📂 Project Structure

```
.
├── main.c
├── encode.c
├── decode.c
├── encodeDecode.c
├── common.h
├── encode.h
├── decode.h
├── types.h
├── beautiful.bmp
├── secret.txt
└── Makefile
```

---

## ⚙️ Working Principle

### Encoding

1. Read the source BMP image.
2. Validate image format and capacity.
3. Copy the BMP header (54 bytes).
4. Encode:
   - Magic String
   - Secret file extension
   - Secret file size
   - Secret file data
5. Copy remaining image data.
6. Generate the stego image.

---

### Decoding

1. Open the stego BMP image.
2. Skip BMP header.
3. Extract and verify the Magic String.
4. Decode:
   - Secret file extension
   - Secret file size
   - Secret message
5. Write the extracted data into an output file.

---

## 💻 Usage

### Build

```bash
gcc *.c -o stego
```

---

### Encode

```bash
./stego -e beautiful.bmp secret.txt
```

or specify output image

```bash
./stego -e beautiful.bmp secret.txt stego.bmp
```

---

### Decode

```bash
./stego -d stego.bmp
```

or specify output file

```bash
./stego -d stego.bmp output.txt
```

---

## 🔍 Validation Performed

- Validates command-line arguments
- Checks BMP file format
- Verifies secret file extension
- Confirms image capacity
- Magic String verification
- Output filename validation
- File open/read/write error handling

---

## 📖 LSB Steganography

Least Significant Bit (LSB) Steganography hides information by replacing the least significant bit of each image byte with bits from the secret message.

Since only the least significant bit changes, the visual appearance of the image remains almost identical to the original.

---

## 🚀 Learning Outcomes

- Binary File Processing
- Bit Manipulation Techniques
- BMP Image Format
- Command-Line Argument Parsing
- Memory Management
- Modular Programming
- Error Handling
- Linux File Operations

---

## 📷 Sample Workflow

```
Secret.txt
      │
      ▼
+----------------+
| beautiful.bmp  |
+----------------+
        │
        ▼
   LSB Encoding
        │
        ▼
+----------------+
|   stego.bmp    |
+----------------+
        │
        ▼
   LSB Decoding
        │
        ▼
Recovered Secret.txt
```

---

## 📈 Future Improvements

- Support PNG images
- Password-protected encryption
- AES encrypted secret files
- Support for hiding PDFs, images, and other file types
- GUI application using Qt

---

## 👨‍💻 Author

**Prathamesh Deore**

Embedded Firmware Developer

- C Programming
- Embedded C
- Linux System Programming
- Embedded Systems
- Git & GitHub

---

⭐ If you found this project interesting, consider giving it a star!
