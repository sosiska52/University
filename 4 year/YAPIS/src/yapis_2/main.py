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
        self.pos = 0
        self.length = len(text)
        self.tokens = []
        self.errors = []

    def peek(self, n=0):
        i = self.pos + n
        return self.text[i] if i < self.length else ''

    def advance(self, n=1):
        self.pos += n

    def add_token(self, typ, lexeme):
        self.tokens.append({'type': typ, 'lexeme': lexeme})

    def add_error(self, msg):
        self.errors.append(msg)

    def skip_whitespace(self):
        moved = False
        while self.peek() in ' \t\r\n':
            self.advance()
            moved = True
        return moved

    def skip_comment(self):
        if self.peek() == '/' and self.peek(1) == '/':
            while self.peek() not in ('', '\n', ''):
                self.advance()
            if self.peek() == '\n':
                self.advance()
            return True
        return False

    def lex_identifier_or_keyword(self):
        if not self.peek().isalpha():
            return False
        lex = ''
        while self.peek().isalnum() or self.peek() == '_':
            lex += self.peek()
            self.advance()
        low = lex.lower()
        if low in KEYWORDS:
            self.add_token('KEYWORD', lex)
        elif low in TYPES:
            self.add_token('TYPE', lex)
        else:
            if len(lex) > MAX_ID_LEN:
                self.add_error(f"Слишком длинный идентификатор: {lex}")
            self.add_token('IDENT', lex)
        return True

    def lex_roman(self):
        if self.peek().isalpha():
            lex = ''
            while self.peek().isalpha():
                lex += self.peek()
                self.advance()
            if valid_roman(lex):
                self.add_token('ROMAN', lex)
            else:
                self.add_error(f"Некорректное римское число: {lex}")
                self.add_token('ROMAN', lex)
            return True
        return False

    def lex_string(self):
        if self.peek() != "'":
            return False
        self.advance()
        content = ''
        while True:
            ch = self.peek()
            if ch == '':
                self.add_error("Незакрытая строка")
                return True
            if ch == "'":
                self.advance()
                break
            content += ch
            self.advance()
        if len(content) > MAX_STR_LEN:
            self.add_error(f"Слишком длинная строка: {content}")
        self.add_token('STRING', "'" + content + "'")
        return True

    def next_token(self):
        while self.pos < self.length:
            if self.skip_comment():
                continue
            if self.skip_whitespace():
                continue
            if self.lex_string():
                continue
            if self.lex_identifier_or_keyword():
                continue
            if self.lex_roman():
                continue

            ch = self.peek()
            if ch in '[]:;':
                mapping = {'[': 'LBRACK', ']': 'RBRACK', ':': 'COLON', ';': 'SEMICOLON'}
                self.add_token(mapping[ch], ch)
                self.advance()
                continue

            self.add_error(f"Недопустимый символ: {ch}")
            self.advance()

    def run(self):
        self.next_token()
        if self.tokens and self.tokens[-1]['type'] != 'SEMICOLON':
            self.add_error("Описание массива должно заканчиваться ';'")
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
        with open("input.txt", encoding='utf-8') as f:
            text = f.read()
    except FileNotFoundError:
        print("Файл input.txt не найден! Создайте его рядом со скриптом.")
        return
    lexer = Lexer(text)
    tokens, errors = lexer.run()
    print_table(tokens, errors)


if __name__ == '__main__':
    main()
