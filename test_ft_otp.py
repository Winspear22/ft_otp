#!/usr/bin/env python3
"""
Test script pour ft_otp
Lance ce script depuis le repertoire de ton projet, apres avoir compile.
Usage: python3 test_ft_otp.py
"""

import subprocess
import os
import time
import hmac
import hashlib
import struct
import sys

HEX_KEY = "3132333435363738393031323334353637383930313233343536373839303132333435363738393031323334353637383930"
KEY_FILE = "key.hex"
KEY_FILE_ENCRYPTED = "ft_otp.key"
EXECUTABLE = "./ft_otp"

# Couleurs
GREEN = "\033[92m"
RED = "\033[91m"
YELLOW = "\033[93m"
CYAN = "\033[96m"
RESET = "\033[0m"

passed = 0
failed = 0
total = 0


def run_cmd(cmd):
    """Execute une commande et retourne (returncode, stdout, stderr)"""
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    return (result.returncode, result.stdout.strip(), result.stderr.strip())


def test(name):
    """Decorateur pour compter les tests"""
    global total
    total += 1
    print(f"\n{CYAN}[TEST {total}] {name}{RESET}")


def ok(msg):
    global passed
    passed += 1
    print(f"  {GREEN}PASS{RESET} - {msg}")


def fail(msg):
    global failed
    failed += 1
    print(f"  {RED}FAIL{RESET} - {msg}")


def compute_totp_reference(hex_key):
    """Calcule le TOTP avec Python (reference RFC 6238/4226)"""
    key = bytes.fromhex(hex_key)
    t = struct.pack('>Q', int(time.time()) // 30)
    h = hmac.new(key, t, hashlib.sha1).digest()
    o = h[-1] & 0xf
    code = ((h[o] & 0x7f) << 24 |
            (h[o+1] & 0xff) << 16 |
            (h[o+2] & 0xff) << 8 |
            (h[o+3] & 0xff)) % 1000000
    return f"{code:06d}"


def compute_totp_at(hex_key, timestamp):
    """Calcule le TOTP pour un timestamp precis"""
    key = bytes.fromhex(hex_key)
    t = struct.pack('>Q', timestamp // 30)
    h = hmac.new(key, t, hashlib.sha1).digest()
    o = h[-1] & 0xf
    code = ((h[o] & 0x7f) << 24 |
            (h[o+1] & 0xff) << 16 |
            (h[o+2] & 0xff) << 8 |
            (h[o+3] & 0xff)) % 1000000
    return f"{code:06d}"


# =====================================================================
#  PHASE 1 : Compilation
# =====================================================================
print(f"\n{'='*60}")
print(f"{YELLOW}PHASE 1 : Compilation{RESET}")
print(f"{'='*60}")

test("Compilation avec make")
ret, out, err = run_cmd("make re")
if ret == 0 and os.path.exists(EXECUTABLE):
    ok("Compilation reussie")
else:
    fail(f"Compilation echouee. stderr: {err}")
    sys.exit(1)

test("L'executable ft_otp existe")
if os.path.exists(EXECUTABLE) and os.access(EXECUTABLE, os.X_OK):
    ok("Executable present")
else:
    fail("Executable introuvable ou non executable")
    sys.exit(1)

# =====================================================================
#  PHASE 2 : Tests d'erreurs (args invalides)
# =====================================================================
print(f"\n{'='*60}")
print(f"{YELLOW}PHASE 2 : Gestion des erreurs{RESET}")
print(f"{'='*60}")

test("Pas d'arguments")
ret, out, err = run_cmd("./ft_otp")
if ret != 0:
    ok("Le programme retourne une erreur sans arguments")
else:
    fail("Le programme devrait echouer sans arguments")

test("Clé non hexadécimale")
with open("bad.hex", "w") as f:
    f.write("CECINESTPASDELHEXACECINESTPASDELHEXACECINESTPASDE")
ret, out, err = run_cmd("./ft_otp -g bad.hex")
if ret != 0:
    ok("Rejette une clé non hexa")
else:
    fail("Devrait rejeter les caractères non hexa")

test("Clé trop courte (< 64 chars)")
with open("short.hex", "w") as f:
    f.write("aabbccdd")
ret, out, err = run_cmd("./ft_otp -g short.hex")
if ret != 0:
    ok("Rejette une clé trop courte")
else:
    fail("Devrait rejeter les clés de moins de 64 caractères")

test("Fichier inexistant")
ret, out, err = run_cmd("./ft_otp -g fichier_qui_existe_pas.hex")
if ret != 0:
    ok("Rejette un fichier inexistant")
else:
    fail("Devrait echouer si le fichier n'existe pas")

test("Fichier invalide avec -k")
with open("fake.key", "w") as f:
    f.write("ceci n'est pas un vrai fichier de clé")
ret, out, err = run_cmd("./ft_otp -k fake.key")
if ret != 0:
    ok("Rejette un fichier clé invalide")
else:
    fail("Devrait echouer avec un fichier non-FTOTP")

test("Flag invalide")
with open(KEY_FILE, "w") as f:
    f.write(HEX_KEY)
ret, out, err = run_cmd("./ft_otp -x key.hex")
if ret != 0:
    ok("Rejette un flag invalide")
else:
    fail("Devrait echouer avec un flag inconnu")

# =====================================================================
#  PHASE 3 : Génération (-g)
# =====================================================================
print(f"\n{'='*60}")
print(f"{YELLOW}PHASE 3 : Génération de la clé (-g){RESET}")
print(f"{'='*60}")

# Nettoyer l'ancien fichier
if os.path.exists(KEY_FILE_ENCRYPTED):
    os.remove(KEY_FILE_ENCRYPTED)

test("Génération avec clé valide de 64 hex chars")
with open(KEY_FILE, "w") as f:
    f.write(HEX_KEY)
ret, out, err = run_cmd("./ft_otp -g key.hex")
if ret == 0:
    ok(f"-g a réussi. Output: {out}")
else:
    fail(f"-g a échoué. stderr: {err}")

test("Le fichier ft_otp.key a été créé")
if os.path.exists(KEY_FILE_ENCRYPTED):
    size = os.path.getsize(KEY_FILE_ENCRYPTED)
    # 5 (magic) + 16 (IV) + N (ciphertext)
    # 64 hex chars = 32 bytes plaintext + padding PKCS7 → 48 bytes ciphertext
    expected_min = 5 + 16 + 32  # minimum: magic + IV + plaintext
    if size >= expected_min:
        ok(f"ft_otp.key créé ({size} bytes, minimum attendu: {expected_min})")
    else:
        fail(f"ft_otp.key trop petit: {size} bytes (minimum: {expected_min})")
else:
    fail("ft_otp.key n'a pas été créé")

test("Le fichier commence par le magic number 'FTOTP'")
if os.path.exists(KEY_FILE_ENCRYPTED):
    with open(KEY_FILE_ENCRYPTED, "rb") as f:
        magic = f.read(5)
    if magic == b"FTOTP":
        ok("Magic number FTOTP présent")
    else:
        fail(f"Magic number incorrect: {magic}")
else:
    fail("Pas de fichier à vérifier")

# =====================================================================
#  PHASE 4 : TOTP (-k) — le test le plus important
# =====================================================================
print(f"\n{'='*60}")
print(f"{YELLOW}PHASE 4 : Génération TOTP (-k){RESET}")
print(f"{'='*60}")

test("Le TOTP généré correspond à la référence Python")

if not os.path.exists(KEY_FILE_ENCRYPTED):
    fail("Pas de ft_otp.key, on ne peut pas tester -k")
else:
    # On calcule la référence AVANT de lancer le programme
    reference = compute_totp_reference(HEX_KEY)
    ret, out, err = run_cmd("./ft_otp -k ft_otp.key")

    if ret == 0 and out:
        print(f"  Python référence : {reference}")
        print(f"  ft_otp           : {out}")
        if out == reference:
            ok("LES DEUX CODES SONT IDENTIQUES ! Le programme est correct.")
        else:
            fail(f"Les codes diffèrent. Python={reference} ft_otp={out}")
    else:
        fail(f"-k a échoué. stderr: {err}")

# =====================================================================
#  PHASE 5 : Cohérence temporelle
# =====================================================================
print(f"\n{'='*60}")
print(f"{YELLOW}PHASE 5 : Le TOTP change toutes les 30 secondes{RESET}")
print(f"{'='*60}")

test("Deux appels dans la même fenêtre de 30s donnent le même code")
if os.path.exists(KEY_FILE_ENCRYPTED):
    ret1, out1, err1 = run_cmd("./ft_otp -k ft_otp.key")
    ret2, out2, err2 = run_cmd("./ft_otp -k ft_otp.key")
    if ret1 == 0 and ret2 == 0 and out1 == out2:
        ok(f"Même code dans la même fenêtre: {out1}")
    else:
        fail(f"Codes differents dans la meme fenetre: {out1} vs {out2}")
else:
    fail("Pas de ft_otp.key")

test("Le code fait exactement 6 chiffres")
if os.path.exists(KEY_FILE_ENCRYPTED):
    ret, out, err = run_cmd("./ft_otp -k ft_otp.key")
    if ret == 0 and len(out) == 6 and out.isdigit():
        ok(f"Code valide: {out} (6 chiffres)")
    else:
        fail(f"Code invalide: '{out}' (longueur: {len(out) if out else 0})")
else:
    fail("Pas de ft_otp.key")

# =====================================================================
#  PHASE 6 : Vérification avec des timestamps connus (RFC 6238 vectors)
# =====================================================================
print(f"\n{'='*60}")
print(f"{YELLOW}PHASE 6 : Vérification algorithme (RFC vectors){RESET}")
print(f"{'='*60}")

# Ces tests vérifient l'algo TOTP indépendamment du chiffrement
# On utilise Python comme référence pour vérifier que l'algo est correct
test("Vérification de l'algorithme TOTP avec des timestamps connus")

# Pour SHA-1 avec la clé "12345678901234567890" (20 bytes)
# Référence: RFC 6238 Appendix B, Table 1
# La clé doublée (64 hex chars) = "12345678901234567890" x2
# On ne peut pas tester exactement les vectors RFC car la clé est doublée
# mais on vérifie que l'algo Python est cohérent
rfc_key_40 = "3132333435363738393031323334353637383930"  # 40 hex = 20 bytes = "12345678901234567890"
rfc_vectors = [
    (59, 94287082),
    (1111111109, 07081804),
    (1111111111, 14050471),
    (1234567890, 89005924),
    (2000000000, 69279037),
]

all_rfc_ok = True
for ts, expected in rfc_vectors:
    result = compute_totp_at(rfc_key_40, ts)
    if int(result) == expected:
        pass  # ok implicitement
    else:
        all_rfc_ok = False
        print(f"  T={ts//30:>12d} | attendu: {expected:08d} | obtenu: {result} | FAIL")

if all_rfc_ok:
    ok("Tous les vectors RFC 6238 (SHA-1) sont corrects")
else:
    fail("Certains vectors RFC sont incorrects (mais ça peut être juste le Python ref)")

# =====================================================================
#  RÉSUMÉ
# =====================================================================
print(f"\n{'='*60}")
print(f"{YELLOW}RÉSUMÉ{RESET}")
print(f"{'='*60}")
print(f"  Tests passés : {GREEN}{passed}{RESET} / {total}")
if failed > 0:
    print(f"  Tests échoués : {RED}{failed}{RESET} / {total}")
else:
    print(f"  Tests échoués : 0 / {total}")

# Nettoyage
for f in ["bad.hex", "short.hex", "fake.key"]:
    if os.path.exists(f):
        os.remove(f)

if failed == 0:
    print(f"\n  {GREEN}TOUT EST OK ! Ton programme est fonctionnel.{RESET}")
    sys.exit(0)
else:
    print(f"\n  {RED}Il y a des erreurs à corriger.{RESET}")
    sys.exit(1)