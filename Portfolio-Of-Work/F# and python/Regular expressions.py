# Homework 7
import re
# REGULAR EXPRESSIONS

# Write patterns for regular expressions a-d here.
# You must use a single regular expression for each item.
# For part d, also include a substitution string.

a = re.compile(r"^([0-46-9]*)5([0-46-9]*)5[0-46-9]*$")

b = re.compile(r"^(([0]?[1-9])|([1][012])):(([0-5][0-9])) (AM|PM)$")

c = re.compile(r"^([a-zA-Z_][a-zA-Z0-9_]*((, )|()))*$")

d = re.compile(r"([a-zA-Z0-9_]+)\s+(<(=)?)\s+([a-zA-Z0-9_]+)")
subStr = r"\4 >\3 \1"   # Place what you want to substitute (used in sub)

# TESTS

# Write additional tests for each item.
# Include both matching and non-matching tests.
# A portion of your grade will be based on the thoroughness of your tests.

print("----Part a tests that match:")
print(a.search("55"))
print(a.search("12345678901234567890"))
print(a.search("15253"))
print(a.search("515777"))
print(a.search("1234567895"))


print("----Part a tests that do not match:")
print(a.search("5"))
print(a.search("Hello Dr. Larson"))
print(a.search("555"))
print(a.search("00500500500"))
print(a.search("500500500"))
print(a.search("005005005"))
print(a.search("1234678905123467890"))
print(a.search("5005005"))


print("----Part b tests that match:")
print(b.search("1:45 PM"))
print(b.search("12:00 PM"))
print(b.search("1:45 AM"))
print(b.search("09:45 AM"))


print("----Part b tests that do not match:")
print(b.search("21:45 PM"))
print(b.search("00:45 PM"))
print(b.search("00:99 PM"))
print(b.search("99:99 FM"))
print(b.search("Hello Dr. Larson"))
print(b.search("00:4 PM"))

print("----Part c tests that match:")
print(c.search("foo, bar1, x, file_status"))
print(c.search("Feline, dog, __12345"))
print(c.search("first, second, third, "))
print(c.search("Hello, Dr_Larson, I_Did_My_Homework"))
print(c.search("_1, _2, _3, _4, _5, _6, _7, _8, _9"))
print(c.search("________, _______, ______"))

print("----Part c tests that do not match:")
print(c.search("hello,"))
print(c.search("1, 2, 3, 4, 5, "))
print(c.search("hello Dr. Larson"))
print(c.search("(), !, @#$, "))

print("----Part d tests:")
print(d.sub(subStr, "a < b and c <= d"))
print(d.sub(subStr, "ardvark < bat and crocodile <= donkey"))
print(d.sub(subStr, "1 < 2 and 3 <= 4"))
print(d.sub(subStr, "3 < b and 1 <= d"))
print(d.sub(subStr, "____ < f and _______ <= d"))
print(d.sub(subStr, "Jason < wes and  Jason <= Wes"))
