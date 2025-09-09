import re

MAX_ID_LEN = 32
MAX_STR_LEN = 32

KEYWORDS = {'array', 'of'}
TYPES = {'integer', 'real', 'byte', 'word', 'char'}

def roman_to_int(s: str) -> int:
    values = {'I': 1, 'V': 5, 'X': 10, 'L': 50,
              'C': 100, 'D': 500, 'M': 1000}
    total = 0
    prev = 0
    for ch in s:
        val = values.get(ch)
        if val is None:
            return -1
        if val > prev:
            total += val - 2 * prev
        else:
            total += val
        prev = val
    return total


def int_to_roman(num: int) -> str:
    vals = [
        (1000, "M"), (900, "CM"), (500, "D"), (400, "CD"),
        (100, "C"), (90, "XC"), (50, "L"), (40, "XL"),
        (10, "X"), (9, "IX"), (5, "V"), (4, "IV"),
        (1, "I")
    ]
    result = ""
    for v, sym in vals:
        while num >= v:
            result += sym
            num -= v
    return result


def valid_roman(s: str) -> bool:
    s = s.upper()
    num = roman_to_int(s)
    if num <= 0:
        return False
    return int_to_roman(num) == s


class Lexer:
    def __init__(self, text):
        self.text = text
        self.tokens = []
        self.errors = []

        token_spec = [
            ("COMMENT",   r"//[^\n]*"),
            ("STRING",    r"'[^']*'?"),
            ("IDENT",     r"[A-Za-z_][A-Za-z0-9_]*"),
            ("LBRACK",    r"\["),
            ("RBRACK",    r"\]"),
            ("COLON",     r":"),
            ("SEMICOLON", r";"),
            ("SKIP",      r"[ \t\r\n]+"),
            ("MISMATCH",  r"."),
        ]

        tok_regex = "|".join(f"(?P<{name}>{pattern})" for name, pattern in token_spec)
        self.master_pat = re.compile(tok_regex, re.IGNORECASE)

    def run(self):
        for m in self.master_pat.finditer(self.text):
            typ = m.lastgroup
            lexeme = m.group()

            if typ == "COMMENT" or typ == "SKIP":
                continue

            elif typ == "IDENT":
                low = lexeme.lower()
                if low in KEYWORDS:
                    self.tokens.append({"type": "KEYWORD", "lexeme": lexeme})
                elif low in TYPES:
                    self.tokens.append({"type": "TYPE", "lexeme": lexeme})
                elif valid_roman(lexeme):
                    self.tokens.append({"type": "ROMAN", "lexeme": lexeme})
                else:
                    if len(lexeme) > MAX_ID_LEN:
                        self.errors.append(f"Слишком длинный идентификатор: {lexeme}")
                    self.tokens.append({"type": "IDENT", "lexeme": lexeme})

            elif typ == "STRING":
                if not lexeme.endswith("'"):
                    self.errors.append("Незакрытая строка")
                content = lexeme.strip("'")
                if len(content) > MAX_STR_LEN:
                    self.errors.append(f"Слишком длинная строка: {content}")
                self.tokens.append({"type": "STRING", "lexeme": lexeme})

            elif typ == "MISMATCH":
                self.errors.append(f"Недопустимый символ: {lexeme}")

            else:
                self.tokens.append({"type": typ, "lexeme": lexeme})

        if self.tokens and self.tokens[-1]["type"] != "SEMICOLON":
            self.errors.append("Описание массива должно заканчиваться ';'")

        return self.tokens, self.errors


def print_table(tokens, errors):
    print("\nЛексемы:")
    print("{:>3} {:<15} {:<10}".format("#", "LEXEME", "TYPE"))
    print("-"*30)
    for i, t in enumerate(tokens, 1):
        print("{:>3} {:<15} {:<10}".format(i, t['lexeme'], t['type']))
    if errors:
        print("\nОшибки:")
        for e in errors:
            print(" -", e)
    else:
        print("\nОшибок не обнаружено.")


def main():
    try:
        with open("input.txt", encoding="utf-8") as f:
            text = f.read()
    except FileNotFoundError:
        print("Файл input.txt не найден! Создайте его рядом со скриптом.")
        return

    lexer = Lexer(text)
    tokens, errors = lexer.run()
    print_table(tokens, errors)


if __name__ == "__main__":
    main()
